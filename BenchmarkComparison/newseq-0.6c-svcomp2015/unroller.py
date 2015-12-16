#!/usr/bin/env python
VERSION = 'unroller-0.0-2014.10.28'     
#VERSION = 'unroller-0.0-2014.10.26'
##VERSION = 'unroller-0.0-2014.10.07'     # this continues the old unroller, not the newest fork (slower but more robust)
###VERSION = 'unroller-0.0-2014.02.25'       !NOTE! code fork to try different unrolling (see )

"""

This module unrolls all the loops up to the given unwind bound.

In this modules, loops are handled according to the following categorisation:
	- potentially unbounded loops (i.e.  while  loops)
	- potentially bounded loops (i.e.  for  loops having an upper bound that is not computable)
	- definitely bounded loops (i.e.  for  loops having an upper bound that is exactly computable)

Prerequisites:
	- no  do-while  loops - only  for  or  while  loops
	 (use module remove.py)

	- no single statement blocks (e.g. after if or for, etc..)
	 (use module merger.py)

	- no break statements used for anything else than for loop exit (e.g. in a switch..case block)
	 (use module switchconverter.py)

Changelog:
	2014.10.28  bugfix (missing if (!cond) goto _exit_loop )
	2014.10.26  new  -F  loop unwind bounding parameter to limit unrolling of definitely bounded loops
	2014.10.26  removed dead/commented-out/obsolete code
	2014.10.07  bugfix  (see regression/loop_unroll_*.c)
	2014.02.25  switched to  module.Module  base class for modules
	2013.10.31  optimisation in this case:  for (i=constant_a; i < constant_b; i++) { block-without-access-to-i }

TODO: check for(;;)

"""

import pycparser.c_parser, pycparser.c_ast, pycparser.c_generator
import utils, module, parser
import re


class Unroller(module.Module):
	__whileunwind = 0

	__sourcecode = ''

	__labelCount = {}

	__loopCount = 0         # loops discovered so far
	__loopDepth = 0         # depth of nesting for loops
	__loopUnwindRound = 0   # current unwinding round for current loop

	__visitingGoto = False

	__lastContinueLabel = ''

	__labelsDefined = []    # labels defined in the current block being unwound
	__labelChange = {}      # label renaming in unwound loops to avoid duplicating label definitions, and keep in sync with goto stmts


	def init(self):
		pass


	''' Checks whether a loop is bound to be executed exactly a fixed number of times.
	'''
	def _loopIsBounded(self, n):
		if (# init  is an assignment statement of one variable to a constant
			type(n.init) == pycparser.c_ast.Assignment and 
			type(n.init.lvalue) == pycparser.c_ast.ID and 
			type(n.init.rvalue) == pycparser.c_ast.Constant and

			# cond  is a binary op which left and right parts are a variable and a constant, respectively 
			# TODO op must be '<'
			type(n.cond) == pycparser.c_ast.BinaryOp and
			type(n.cond.left) == pycparser.c_ast.ID and
			type(n.cond.right) == pycparser.c_ast.Constant and
			(n.cond.op) == '<' and 

			# next  is a unary op ++
			type(n.next) == pycparser.c_ast.UnaryOp and
			type(n.next.expr) == pycparser.c_ast.ID and
			(n.next.op) == 'p++' and

			# all the three blocks  init, cond, next  refer to the same variable
			self.visit(n.init.lvalue) == self.visit(n.cond.left) == self.visit(n.next.expr)
			):

			# TODO magicvariable must not be accessed in the  stmt  block
			# TODO no breaks in the  stmt  block
			magicvariable = self.visit(n.init.lvalue)

			return True
		else: 
			return False


	def _calculateLoopBasevalue(self, n):
		if self._loopIsBounded(n): return int(n.init.rvalue.value)
		else: return None


	def _calculateLoopBound(self, n):
		if self._loopIsBounded(n): return int(n.cond.right.value)
		else: return None


	def _calculateLoopIncr(self, n):
		if self._loopIsBounded(n): return 1;
		else: return None


	def visit_For(self, n):
		# A  for  statement has the following structure:
		#
		#   for (init; cond; next) { block }
		#
		init = self.visit(n.init)
		cond = self.visit(n.cond)
		if cond == '': cond = '1'

		next = self.visit(n.next)

		self.__loopDepth += 1
		self.__loopCount += 1

		currentLoopID = self.__loopCount

		#if self.cseqenvironment.softforunwind:  
		#	if (self._calculateLoopBound(n) > self.cseqenvironment.forunwind):
		#		print "softbound useful: %s \n" % self._calculateLoopBound(n)
		#		exit(1)

		#~s = '/* ---------> UNROLLING loop_%s (depth:%s)  <----------------------- */\n' % (self.__loopCount, self.__loopDepth)
		s = self._make_indent() + init + ';\n'

		bound = self.cseqenvironment.forunwind

		#
		#
		if self.cseqenvironment.softforunwind:  
			if (self._calculateLoopBound(n) > self.cseqenvironment.forunwind):
				if self.cseqenvironment.formaxunwind:
					bound = min(self._calculateLoopBound(n), self.cseqenvironment.formaxunwind)
				else:
					bound = self._calculateLoopBound(n)

		for i in range(0, bound):
			self.__loopUnwindRound = i
			
			# Loop header, repeated at each unwinding round.
			#
			if i == 0: s += self._make_indent() #~+ '/*  - - - - > loop %s, iter = 0 */\n' % currentLoopID
			else: s += self._make_indent()  #~+ '/*  - - - - > loop %s, iter = %s */\n' % (currentLoopID, i);

			# 
			#
			if self._loopIsBounded(n):
				if i == self._calculateLoopBound(n) - self._calculateLoopBasevalue(n):
					break;
			else:
				if cond != '1':
					s += self._make_indent() + 'if(!(' + cond + ')) { goto __exit_loop_%s; }\n' % currentLoopID

			# Reset the list of labels before visiting the compound block,
			# after _generate_stmt this list is used to reconstruct
			# .....
			##
			self.__labelsDefined = []

			block = self._generate_stmt(n.stmt, add_indent=True)
			block += self._make_indent() + next + ';\n'

			# Duplicate every Label defined in this loop,
			# adding to the label id the current unwind round and the loop number.
			#

			# Update the labels used in goto statements...
			# 
			for l in self.__labelCount:
				block = block.replace('goto %s;' % l, 'goto %s;'  % self.__labelChange[l])
				##print "> changing in block: \n%s from :%s to %s\n result:%s\n\n\n\n" % (block, old, new, block.replace(old, new))
				############self.__labelsDefined.remove(l)

			# Handling of break statements.
			#
			block = block.replace('<break-was-here>', 'goto __exit_loop_%s; ' % currentLoopID)

			# Handling of continue statements.
			#
			if '<continue-was-here>' in block:
				block = block.replace('<continue-was-here>', 'goto __continue_%s_loop_%s;  \n' % (i, currentLoopID))
				s += block[:block.rfind('}')] + '__continue_%s_loop_%s: ;\n' % (i, currentLoopID) + self._make_indent() + '}\n' 
			else:
				s += block

		'''
		if self._loopIsBounded(n) and self.__forunwind :
			s += self._make_indent() + 'assume(!(%s)); __exit_loop_%s: ;\n' % (cond, currentLoopID)	  # case 1: print only the exit label for breaks
		elif self._loopIsBounded(n) and self.__
			s += self._make_indent() + 'assume(!(%s)); __exit_loop_%s: ;\n' % (cond, currentLoopID)   # case 2
		else:
			s += self._make_indent() + 'assume(!(%s)); __exit_loop_%s: ;\n' % (cond, currentLoopID)   # case 3
		'''
		s += self._make_indent() + 'assume(!(%s)); __exit_loop_%s: ;\n' % (cond, currentLoopID)   # case 3
		#~s += self._make_indent() + '/* --------->       END loop_%s (depth:%s)  <----------------------- */\n' % (currentLoopID, self.__loopDepth)

		self.__loopDepth -= 1

		return s


	def visit_DoWhile(self, n):
		print "error: extractor.py: do..while loop in input code.\n"
		exit(1)


	def visit_While(self, n):
		# A  while  statement has the following structure:
		#
		#   while (cond) { block }
		#
		cond = self.visit(n.cond)

		self.__loopDepth += 1
		self.__loopCount += 1

		currentLoopID = self.__loopCount


		s = '' #~'/* ---------> UNROLLING loop_%s (depth:%s)  <----------------------- */\n' % (self.__loopCount, self.__loopDepth)

		for i in range(0, self.cseqenvironment.whileunwind):
			self.__loopUnwindRound = i
			
			# Loop header, repeated at each unwinding round.
			#
			if i == 0: s += self._make_indent() #~+ '/*  - - - - > loop %s, iter = 0 */\n' % currentLoopID
			else: s += self._make_indent()  #~+ '/*  - - - - > loop %s, iter = %s */\n' % (currentLoopID, i);

			if cond != '1':
				s += self._make_indent() + 'if(!(' + cond + ')) { goto __exit_loop_%s; }\n' % currentLoopID

			# Reset the list of labels before visiting the compound block,
			# after _generate_stmt this list is used to reconstruct
			# .....
			##
			self.__labelsDefined = []

			block = self._generate_stmt(n.stmt, add_indent=True)

			# Duplicate every Label defined in this loop,
			# adding to the label id the current unwind round and the loop number.
			#

			# Update the labels used in goto statements...
			# 
			for l in self.__labelCount:
				block = block.replace('goto %s;' % l, 'goto %s;'  % self.__labelChange[l])
				##print "> changing in block: \n%s from :%s to %s\n result:%s\n\n\n\n" % (block, old, new, block.replace(old, new))
				############self.__labelsDefined.remove(l)

			# Handling of break statements.
			#
			block = block.replace('<break-was-here>', 'goto __exit_loop_%s; ' % currentLoopID)

			# Handling of continue statements.
			#
			if '<continue-was-here>' in block:
				block = block.replace('<continue-was-here>', 'goto __continue_%s_loop_%s;  \n' % (i, currentLoopID))
				s += block[:block.rfind('}')] + '__continue_%s_loop_%s: ;\n' % (i, currentLoopID) + self._make_indent() + '}\n' 
			else:
				s += block

		s += self._make_indent() + 'assume(!(%s)); __exit_loop_%s: ;\n' % (cond, currentLoopID)
		#~s += self._make_indent() + '/* --------->       END loop_%s (depth:%s)  <----------------------- */\n' % (currentLoopID, self.__loopDepth)

		self.__loopDepth -= 1

		return s
		

	def visit_FuncDef(self, n):
		# At each function,
		# reset the label occurrence counters.
		#
		self.__labelCount = {}

		decl = self.visit(n.decl)
		self.indent_level = 0
		body = self.visit(n.body)

		if n.param_decls:
			knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
			return decl + '\n' + knrdecls + ';\n' + body + '\n'
		else:
			return decl + '\n' + body + '\n'


	def visit_Label(self, n):
		# Labels defined inside loops need to be renamed to avoid multiple definition of the same label,
		# they are renamed using ........ 
		#
		#####print "label %s found, depth %s\n" % (n.name, self.__loopDepth)
		if self.__loopDepth > 0  and  not self.__visitingGoto:
			### print "found label %s\n" % n.name

			if n.name not in self.__labelCount:
				self.__labelCount[n.name] = 0
			else:
				self.__labelCount[n.name] = self.__labelCount[n.name]+1

			oldLabel = n.name
			newLabel = n.name + '_%s' % self.__labelCount[n.name]

			self.__labelChange[oldLabel] = newLabel

			return newLabel + ':\n' + self._generate_stmt(n.stmt)
		else:
			return n.name +':\n' + self._generate_stmt(n.stmt)


	def visit_Goto(self, n):
		self.__visitingGoto = True

		'''
		if self.__loopDepth > 0:
			if n.name not in self.__labelCount:
				s = 'goto %s_%s;' % (n.name, 0)
			else:
				s = 'goto %s_%s;' % (n.name, self.__labelCount[n.name]+1)
		else:
			s = 'goto %s;' % n.name
		'''

		'''
		if self.__loopDepth > 0:
			if n.name not in self.__labelCount  and  n.name not in self.__labelsDefined:
				s = 'goto %s;' % n.name
			elif n.name not in self.__labelCount:
				s = 'goto %s_%s;' % (n.name, 0)
			else:
				s = 'goto %s_%s;' % (n.name, self.__labelCount[n.name]+1)
		else:
			s = 'goto %s;' % n.name
		'''

		s = 'goto %s;' % n.name

		self.__visitingGoto = False
		return s


	def visit_Continue(self, n):
		return '<continue-was-here>'


	def visit_Break(self, n):
		return '<break-was-here>'












