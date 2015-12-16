VERSION = 'errorlabel-0.0-2014.03.14'
#VERSION = 'errorlabel-0.0-2014.02.25' (Cseq-Lazy-0.2)

"""

Transformation:
	- remove all ERROR labels
		- goto ERROR; ---> assert(0);
		- ERROR :;    ----> assert(0);

	- rename all pthread_ id following the table in common.py

	- rename all other function calls (e.g. malloc) following the table in common.py

Changelog:
	2014.03.14  further code refactory to match  module.Module  class interface
	2014.02.25  switched to  module.Module  base class for modules
	2013.11.01  errorlabel now passed as an argument to load()

"""

import pycparser.c_parser, pycparser.c_ast, pycparser.c_generator
import utils, common, module, parser
import re


class Errorlabel(module.Module):
	currentFunction = ''
	__errorlabel = ''


	def loadfromstring(self, string, env):
		self.__errorlabel = env.errorlabel

		super(Errorlabel, self).loadfromstring(string, env)


	def visit_Goto(self, n):
		if n.name == self.__errorlabel: 
			return 'assert(0);'
		else: return 'goto ' + n.name + ';'


	def visit_Label(self, n):
		##### print "visiting LABEL, coords = %s\n" % self.Parser.nodecoords[n]

		if n.name == self.__errorlabel:
			return 'assert(0);'
		else:
			return n.name + ':\n' + self._generate_stmt(n.stmt)


	def visit_ID(self, n):
		if n.name.startswith('pthread_') and n.name not in common.changeID and n.name not in self.Parser.funcBlock:
			print "error: id %s is not mapped.\n" % n.name
			exit(1)

		if n.name in common.changeID:
			return common.changeID[n.name]

		return n.name


	def visit_Decl(self, n, no_type=False):
		# no_type is used when a Decl is part of a DeclList, where the type is
		# explicitly only for the first delaration in a list.
		#
		s = n.name if no_type else self._generate_decl(n)
		if n.bitsize: s += ' : ' + self.visit(n.bitsize)
		if n.init:
			if isinstance(n.init, pycparser.c_ast.InitList):
				s += ' = {' + self.visit(n.init) + '}'
			elif isinstance(n.init, pycparser.c_ast.ExprList):
				s += ' = (' + self.visit(n.init) + ')'
			else:
				s += ' = ' + self.visit(n.init)

		#print "type: %s   decl: %s\n" % (n.storage, n.name)
		for expr in common.changeID:
			if s.startswith(expr+' '):
				s = s.replace(expr+' ', common.changeID[expr]+' ')

		'''
		if n.name in self.Parser.varNames[self.currentFunction] and self.Parser.varType[n.name, self.currentFunction] in common.changeID:
				s = s.replace(self.Parser.varType[n.name, self.currentFunction], common.changeID[self.Parser.varType[n.name, self.currentFunction]])
		elif n.name in self.Parser.varNames[''] and self.Parser.varType[n.name, ''] in common.changeID:
				s = s.replace(self.Parser.varType[n.name, ''], common.changeID[self.Parser.varType[n.name, '']])
		'''

		return s


	'''
	def visit_FuncDef(self, n):
		self.currentFunction = n.decl.name

		decl = self.visit(n.decl)
		self.indent_level = 0
		body = self.visit(n.body)

		# At the bottom of each thread, add a pthread_exit() statement
		# 
		returnStmt = ''


		##print "threadnames: %s" % str(self.Parser.threadName)

		if (self.currentFunction in self.Parser.threadName or self.currentFunction == 'main'):
			#print "visiting function %s and adding stuff.." % self.currentFunction
			returnStmt = self.INDENT_SPACING + '__exit_%s: ; %s(0);\n' % (self.currentFunction, common.changeID['pthread_exit'])
		#else:
			#print "visiting function %s" % self.currentFunction


		# Continue the visit.
		if n.param_decls:
			knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
			body = body[:body.rfind('}')] + self._make_indent() + returnStmt + '}'
			block = decl + '\n' + knrdecls + ';\n' + body + '\n'
		else:
			body = body[:body.rfind('}')] + self._make_indent() + returnStmt + '}'
			block = decl + '\n' + body + '\n'

		return block
	'''


	'''
	def _generate_type(self, n, modifiers=[]):
		""" Recursive generation from a type node. n is the type node.
			modifiers collects the PtrDecl, ArrayDecl and FuncDecl modifiers
			encountered on the way down to a TypeDecl, to allow proper
			generation from it.
		"""
		typ = type(n)
		#~ print(n, modifiers)

		retstr = ''

		if typ == pycparser.c_ast.TypeDecl:
			s = ''
			if n.quals: s += ' '.join(n.quals) + ' '
			s += self.visit(n.type)

			nstr = n.declname if n.declname else ''
			# Resolve modifiers.
			# Wrap in parens to distinguish pointer to array and pointer to
			# function syntax.
			#
			for i, modifier in enumerate(modifiers):
				if isinstance(modifier, pycparser.c_ast.ArrayDecl):
					if (i != 0 and isinstance(modifiers[i - 1], pycparser.c_ast.PtrDecl)):
						nstr = '(' + nstr + ')'
					nstr += '[' + self.visit(modifier.dim) + ']'
				elif isinstance(modifier, pycparser.c_ast.FuncDecl):
					if (i != 0 and isinstance(modifiers[i - 1], pycparser.c_ast.PtrDecl)):
						nstr = '(' + nstr + ')'
					nstr += '(' + self.visit(modifier.args) + ')'
				elif isinstance(modifier, pycparser.c_ast.PtrDecl):
					if modifier.quals:
						nstr = '* %s %s' % (' '.join(modifier.quals), nstr)
					else:
						nstr = '*' + nstr
			if nstr: s += ' ' + nstr
			retstr = s
		elif typ == pycparser.c_ast.Decl:
			retstr = self._generate_decl(n.type)
		elif typ == pycparser.c_ast.Typename:
			retstr = self._generate_type(n.type)
		elif typ == pycparser.c_ast.IdentifierType:
			retstr = ' '.join(n.names) + ' '
		elif typ in (pycparser.c_ast.ArrayDecl, pycparser.c_ast.PtrDecl, pycparser.c_ast.FuncDecl):
			retstr = self._generate_type(n.type, modifiers + [n])
		else:
			retstr = self.visit(n)

		if retstr not in common.changeID:
			return retstr
		else:
			return common.changeID[retstr]
	'''


	def visit_IdentifierType(self, n):
		s = ' '.join(n.names)

		if s in common.changeID:
			s = common.changeID[s]

		return s


	def visit_Typename(self, n):
		s = self._generate_type(n.type)

		if s[:s.rfind(' ')] in common.changeID:
			print "changing  %s --> %s\n" % (s[:s.rfind(' ')], common.changeID[s[:s.rfind(' ')]])
			return common.changeID[s[:s.rfind(' ')]]
		else:
			return s


	def visit_FuncCall(self, n):
		fref = self._parenthesize_unless_simple(n.name)
		args = self.visit(n.args)

		if fref in common.changeID:
			fref = common.changeID[fref]

		return fref + '(' + args + ')'













