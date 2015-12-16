VERSION = 'labeler-0.0-2014.10.29'
#VERSION = 'labeler-0.0-2014.10.26'   newseq-0.6a
##VERSION = 'labeler-0.0-2014.10.15'
###VERSION = 'labeler-0.0-2014.06.26' (CSeq-Lazy-0.4)
####VERSION = 'labeler-0.0-2014.03.14' (CSeq-Lazy-0.3)
#####VERSION = 'labeler-0.0-2014.02.25' (CSeq-Lazy-0.2)

"""

Transformation:
	- inserting labels at the beginning of each relevant line of code
	- instrumentation

Prerequisites:
	- all functions should have been inlined, except the main(), all thread functions, all __VERIFIER_atomic_ functions, and function __VERIFIER_assert
	- all loops should habe been unrolled
	- no two threads refers to the same thread function (use module duplicator.py)

TODO:
	- check the STOP() inserting mechanism
	- calculate max length of added stamps, and change label padding accordingly  

Changelog:
	2014.10.29  bitvector encoding for all control variables (pc, pc_cs, ...)
	            new main driver where guessed jump lenghts are all at the top (this allows inserting p.o.r. constraints right after them)

	2014.10.26  removed dead/commented-out/obsolete code
	2014.10.15  removed visit() and moved visit call-stack handling to module class (module.py)
	2014.06.26  improved backend-specific instrumentation
	            added new backend Klee
	2014.03.14  further code refactory to match  module.Module  class interface
	2014.02.25  switched to  module.Module  base class for modules
	2014.01.19  fixed assert()s missing their stamps at the beginning 

"""
from time import gmtime, strftime
import pycparser.c_parser, pycparser.c_ast, pycparser.c_generator
import utils, common, module, parser
import math, re

from pycparser import c_ast


class Labeler(module.Module):
	__lines = {}            # lines for each thread
	__threadName = ['main']       # name of threads, as they are found in pthread_create(s) - the threads all have different names
	__threadIndex = {}      # index of the thread = value of threadcount when the pthread_create to that thread was discovered
	__threadCount = 0       # pthread create()s found so far

	__labelLine = {}       # statement number where labels are defined [function, label]
	__gotoLine = {}        # statement number where goto to labels appear [function, label]
	__maxInCompound = 0    # max label within a compound
	__labelLength = 55     # for labels to have all the same length, adding padding when needed 
	__startChar = 't'      # special char to distinguish between labeled and non-labelled lines 

	__stmtCount = -1       # thread statement counter (to build thread labels)

	__currentThread = ''   # name of the current thread (also used to build thread labels)

	__threadbound = 0      # bound on the number of threads

	__firstThreadCreate = False   # set once the first thread creation is met
	__globalMemoryAccessed = False   # used to avoid inserting labels when global memory is not accessed

	__first = False


	def loadfromstring(self, string, env):
		threads = env.threads
		rounds = env.rounds
		unwind = env.unwind
		backend = env.format

		self.__threadbound = threads

		super(Labeler, self).loadfromstring(string, env)

		'''
		print "THREADS!\n"

		for t in self.__threadName:
			print "thread %s, index %s" %(t, self.Parser.threadIndex[t])
		'''


		# Add the new main().
		#
		self.output += self.__createMain(rounds)

		# Thread sizes (i.e. number of visible statements) comma separated.
		#
		lines = ''
 		#lines += str(self.__lines['main'])

 		i = 0
 		maxsize = 0

		for t in self.__threadName:
			if i <= self.__threadbound:
				if i>0: lines += ', ' 
				lines += str(self.__lines[t])
				maxsize = max(int(maxsize), int(self.__lines[t]))
				#print "CONFRONTO %s %s " % (int(maxsize), int(self.__lines[t]))
				#print "    max: %s " % maxsize
			i +=1

		# Generate the header.
		#
		header = utils.printFile('include/newseq-include.c')
 		header = header.replace('<insert-version-here>', '0.0.0.0.0.0')
 		header = header.replace('<insert-maxthreads-here>', str(threads)) 
 		header = header.replace('<insert-maxrounds-here>', str(rounds))
 		header = header.replace('<insert-unwind-here>', str(unwind))
 		header = header.replace('<insert-backend-here>', str(backend))
 		header = header.replace('<insert-date-here>', strftime("%Y-%m-%d %H:%M:%S", gmtime()))
 		header = header.replace('<insert-threads-params-here>', '')  # other thread parameters, they are transformed to global vars...

 		# Instrumentation.
 		#
 		if backend == 'esbmc':
 			header = header.replace('<insert-extraheaders-here>\n', '')
 			header = header.replace('<insert-assume-here>', '__ESBMC_assume')
 			header = header.replace('<insert-assert-here>', 'assert')
 			header = header.replace('<insert-nondet_int-here>', 'nondet_int')
 			header = header.replace('<insert-nondet_uint-here>', 'nondet_uint')
 			header = header.replace('<insert-nondet_int-body-here>', 'int nondet_int();')
 			header = header.replace('<insert-nondet_uint-body-here>', 'unsigned int nondet_uint();')
 		elif backend == 'cbmc':
 			header = header.replace('<insert-extraheaders-here>\n', '')
 			header = header.replace('<insert-assume-here>', '__CPROVER_assume')
 			header = header.replace('<insert-assert-here>', 'assert')
 			header = header.replace('<insert-nondet_int-here>', 'nondet_int')
 			header = header.replace('<insert-nondet_uint-here>', 'nondet_uint')
 			header = header.replace('<insert-nondet_int-body-here>', 'int nondet_int();')
 			header = header.replace('<insert-nondet_uint-body-here>', 'unsigned int nondet_uint();')
 			# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 			k = int(math.floor(math.log(maxsize,2)))+1
 			header = header.replace('<insert-active_thread-type-here>', '__CPROVER_bitvector[1]')
 			header = header.replace('<insert-pc-type-here>', '__CPROVER_bitvector[%s]' % (k))
 			header = header.replace('<insert-pc_cs-type-here>', '__CPROVER_bitvector[%s]' % (k+1))   # pc_cs stores the sum of two bitvectors of size (k+1), needs to be one bit wider
 			header = header.replace('<insert-thread_index-type-here>', 'int')
 			header = header.replace('<insert-thread_lines-type-here>', '__CPROVER_bitvector[%s]' % (k))
 		elif backend == 'smack':
 			header = header.replace('<insert-extraheaders-here>\n', '#define SMACK_H_\n#define __VERIFIER_assume __SMACK_assume\n#define __VERIFIER_assert __SMACK_assert\n#define assert __SMACK_assert\nvoid __SMACK_assert(int val);\nvoid __SMACK_assume(int val);\nint __SMACK_nondet(void);\n\n')
 			header = header.replace('<insert-assume-here>', '__SMACK_assume')
 			header = header.replace('<insert-assert-here>', 'assert')
 			header = header.replace('<insert-nondet_int-here>', '__SMACK_nondet')
 			header = header.replace('<insert-nondet_uint-here>', '__SMACK_nondet')
 			header = header.replace('<insert-nondet_int-body-here>', 'int nondet_int();')   ## TODO: see how it was done in the manual translation
 			header = header.replace('<insert-nondet_uint-body-here>', 'unsigned int nondet_uint();')
 		elif backend == 'llbmc':
 			header = header.replace('<insert-extraheaders-here>\n', '')
 			header = header.replace('<insert-assume-here>', '__llbmc_assume')
 			header = header.replace('<insert-assert-here>', 'assert')
 			header = header.replace('<insert-nondet_int-here>', 'nondet_int')
 			header = header.replace('<insert-nondet_uint-here>', 'nondet_uint')
 			header = header.replace('<insert-nondet_int-body-here>', 'int nondet_int();')
 			header = header.replace('<insert-nondet_uint-body-here>', 'unsigned int nondet_uint();')
 		elif backend == 'satabs':
 			header = header.replace('<insert-extraheaders-here>\n', '')
 			header = header.replace('<insert-assume-here>', '__CPROVER_assume')
 			header = header.replace('<insert-assert-here>', 'assert')
 			header = header.replace('<insert-nondet_int-here>', 'nondet_int')
 			header = header.replace('<insert-nondet_uint-here>', 'nondet_uint')
 			header = header.replace('<insert-nondet_int-body-here>', 'int nondet_int();')
 			header = header.replace('<insert-nondet_uint-body-here>', 'unsigned int nondet_uint();')
 		elif backend == 'klee':
 			header = header.replace('<insert-extraheaders-here>\n', '#include <klee/klee.h>\n')
 			header = header.replace('<insert-assume-here>', 'klee_assume')
 			header = header.replace('<insert-assert-here>', 'klee_assert')
 			header = header.replace('<insert-nondet_int-here>', 'nondet_int')
 			header = header.replace('<insert-nondet_uint-here>', 'nondet_uint')
 			header = header.replace('<insert-nondet_int-body-here>', 'int nondet_int() { int x; klee_make_symbolic(&x, sizeof(x), "x"); return x; }')
 			header = header.replace('<insert-nondet_uint-body-here>', 'unsigned int nondet_uint() { unsigned int x; klee_make_symbolic(&x, sizeof(x), "x"); return x; }')

 		header = header.replace('<insert-threadsizes-here>', lines);

		# Fix gotos by inserting ASS_GOTO(..) blocks before each goto,
		# excluding gotos which destination is the line below.
		#
		for (a,b) in self.__labelLine:
			if (a,b) in self.__gotoLine and (self.__labelLine[a,b] == self.__gotoLine[a,b]+1):
				self.output = self.output.replace('<%s,%s>' % (a, b), '')
			else:
				self.output = self.output.replace('<%s,%s>' % (a, b), 'ASS_GOTO(%s)' % self.__labelLine[a,b])

		# Fix indentation.
		#
		new = ''

		for line in self.output.splitlines():
			if len(line) > 0 and (line[0] == self.__startChar or line.startswith('IF(')):
			#if len(line) > 0 and re.search(r'[a-zA-Z0-9]+', line[0]): 
				new += line + '\n'
			else:
				new += self.__labelLength*' ' + line + '\n'

		'''
 		if self.Parser.funcBlockIn['main'] not in ('', 'void'):      # forward main() parameters to main_thread()
 			self.output = self.output.replace('<insert-main-params-here>', self.Parser.funcBlockIn['main'].replace(',', ';')+ ';')
 		else:
 			self.output = self.output.replace('<insert-main-params-here>', '')
 		'''

		self.output = header + '\n\n' + new


	def visit_Compound(self, n):
		s = self._make_indent() + '{\n'
		self.indent_level += 1

		# Insert the labels at the beginning of each statement,
		# with a few exclusions to reduce context-switch points...
		#
		if n.block_items:
			for stmt in n.block_items:
				# Case 1: returns
				if type(stmt) == pycparser.c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name) == common.changeID['pthread_exit']:
					extraStmt = ''
					self.__stmtCount += 1
					self.__maxInCompound = self.__stmtCount
					stamp = '%s%s_%s: ' % (self.__startChar, self.__currentThread, str(self.__stmtCount))
					padding = ' '*(self.__labelLength - len(stamp))
					newStmt = extraStmt + stamp + padding + self._generate_stmt(stmt)
					s += newStmt
				# Case 2: labels
				elif (type(stmt) in (pycparser.c_ast.Label,)):
					# --1-- Simulate a visit to the stmt block to see whether it makes any use of pointers or shared memory.
					#
					oldStmtCount = self.__stmtCount             # backup counters
					oldMaxInCompound = self.__maxInCompound
					oldGlobalMemoryAccessed = self.__globalMemoryAccessed

					globalAccess = False
					self.__globalMemoryAccessed = False

					if type(stmt) not in (pycparser.c_ast.If, ):
						tmp = self._generate_stmt(stmt)
					else:						
						tmp = self._generate_stmt(stmt.cond)

					globalAccess = self.__globalMemoryAccessed

					self.__stmtCount = oldStmtCount             # restore counters
					self.__maxInCompound = oldMaxInCompound
					self.__globalMemoryAccessed = oldGlobalMemoryAccessed


					newStmt = ''

					# --2-- Now rebuilds the stmt block again, 
					#       this time using the proper formatting
					#      (now we know if the statement is accessing global memory,
					#       so to insert the stamp at the beginning when needed)
					#
					if self.__stmtCount == -1:   # first statement for each thread
						self.__stmtCount += 1
						self.__maxInCompound = self.__stmtCount
						###stamp = 'IF(%s,%s%s_%s)' % (str(self.__stmtCount), self.__startChar, self.__currentThread, str(self.__stmtCount+1))
						threadIndex = self.Parser.threadIndex[self.__currentThread] if self.__currentThread in self.Parser.threadIndex else 0
						stamp = 'IF(%s,%s,%s%s_%s)' % (threadIndex,str(self.__stmtCount), self.__startChar, self.__currentThread, str(self.__stmtCount+1))
						padding = ' '*(self.__labelLength - len(stamp))
						newStmt = stamp + padding + self._generate_stmt(stmt.stmt)
					elif (globalAccess or
						(type(stmt) == pycparser.c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name) == common.changeID['pthread_create']) or
						(type(stmt) == pycparser.c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name) == common.changeID['pthread_join']) ):
						#(type(stmt) == pycparser.c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name) == 'assume') ):

						self.__stmtCount += 1
						self.__maxInCompound = self.__stmtCount
						###stamp = '%s%s_%s: IF(%s,%s%s_%s)' % (self.__startChar, self.__currentThread, str(self.__stmtCount), str(self.__stmtCount), self.__startChar, self.__currentThread, str(self.__stmtCount+1))
						threadIndex = self.Parser.threadIndex[self.__currentThread] if self.__currentThread in self.Parser.threadIndex else 0
						stamp = '%s%s_%s: IF(%s,%s,%s%s_%s)' % (self.__startChar, self.__currentThread, str(self.__stmtCount),threadIndex,str(self.__stmtCount), self.__startChar, self.__currentThread, str(self.__stmtCount+1))
						padding = ' '*(self.__labelLength - len(stamp))
						newStmt = stamp + padding + self._generate_stmt(stmt.stmt)
					else:
						newStmt = self._generate_stmt(stmt.stmt)

					threadIndex = self.Parser.threadIndex[self.__currentThread] if self.__currentThread in self.Parser.threadIndex else 0
					newStmt = self._make_indent()+ stmt.name + ': ' + 'GUARD(%s,%s)\n' % (threadIndex,self.__stmtCount+1) + newStmt

					s += newStmt
				# Case 3: all the rest....
				elif (type(stmt) not in (pycparser.c_ast.Compound, pycparser.c_ast.Goto, pycparser.c_ast.Decl)
					##### and not (type(stmt) == pycparser.c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name) == 'assert') Omar 19.Jan.2014 - missing context-switch points before assert()s
					#and not (type(stmt) == pycparser.c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name) == 'assume')
					and not (self.__currentThread=='main' and self.__firstThreadCreate == False) or (self.__currentThread=='main' and self.__stmtCount == -1)) :

					# --1-- Simulate a visit to the stmt block to see whether it makes any use of pointers or shared memory.
					#
					oldStmtCount = self.__stmtCount             # backup counters
					oldMaxInCompound = self.__maxInCompound
					oldGlobalMemoryAccessed = self.__globalMemoryAccessed

					globalAccess = False
					self.__globalMemoryAccessed = False

					if type(stmt) not in (pycparser.c_ast.If, ):
						tmp = self._generate_stmt(stmt)
					else:						
						tmp = self._generate_stmt(stmt.cond)

					globalAccess = self.__globalMemoryAccessed

					self.__stmtCount = oldStmtCount             # restore counters
					self.__maxInCompound = oldMaxInCompound
					self.__globalMemoryAccessed = oldGlobalMemoryAccessed

					newStmt = ''

					# --2-- Now rebuilds the stmt block again, 
					#       this time using the proper formatting
					#      (now we know if the statement is accessing global memory,
					#       so to insert the stamp at the beginning when needed)
					#
					if self.__stmtCount == -1:   # first statement for each thread
						self.__stmtCount += 1
						self.__maxInCompound = self.__stmtCount
						###stamp = 'IF(%s,%s%s_%s)' % (str(self.__stmtCount), self.__startChar, self.__currentThread, str(self.__stmtCount+1))
						threadIndex = self.Parser.threadIndex[self.__currentThread] if self.__currentThread in self.Parser.threadIndex else 0
						stamp = 'IF(%s,%s,%s%s_%s)' % (threadIndex,str(self.__stmtCount), self.__startChar, self.__currentThread, str(self.__stmtCount+1))
						padding = ' '*(self.__labelLength - len(stamp))
						newStmt = stamp + padding + self._generate_stmt(stmt)
					elif (globalAccess or
						(type(stmt) == pycparser.c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name) == common.changeID['pthread_create']) or
						(type(stmt) == pycparser.c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name) == common.changeID['pthread_join']) or
						(type(stmt) == pycparser.c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name).startswith('__VERIFIER_atomic')) or
						(type(stmt) == pycparser.c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name).startswith('__VERIFIER_assume')) or
						(type(stmt) == pycparser.c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name).startswith(  common.funcPrefixChange['__VERIFIER_atomic'])) ):
						self.__stmtCount += 1
						self.__maxInCompound = self.__stmtCount
						###stamp = '%s%s_%s: IF(%s,%s%s_%s)' % (self.__startChar, self.__currentThread, str(self.__stmtCount), str(self.__stmtCount), self.__startChar, self.__currentThread, str(self.__stmtCount+1))
						threadIndex = self.Parser.threadIndex[self.__currentThread] if self.__currentThread in self.Parser.threadIndex else 0
						stamp = '%s%s_%s: IF(%s,%s,%s%s_%s)' % (self.__startChar, self.__currentThread, str(self.__stmtCount),threadIndex,str(self.__stmtCount), self.__startChar, self.__currentThread, str(self.__stmtCount+1))
						padding = ' '*(self.__labelLength - len(stamp))
						newStmt = stamp + padding + self._generate_stmt(stmt)
					else:
						newStmt = self._generate_stmt(stmt)

					s += newStmt
				else:
					newStmt = self._generate_stmt(stmt)
					s += newStmt

		self.indent_level -= 1
		s += self._make_indent() + '}\n'

		######threadIndex = self.Parser.threadIndex[self.__currentThread] if self.__currentThread in self.Parser.threadIndex else 0
		######s = s.replace('<insert-threadindex-here>', )
		
		return s


	def visit_FuncDef(self, n):
		if (n.decl.name.startswith('__VERIFIER_atomic_') or 
			n.decl.name.startswith(common.funcPrefixChange['__VERIFIER_atomic']) or
			n.decl.name == '__VERIFIER_assert' or
			n.decl.name in self.Parser.funcReferenced ):   # <--- functions called through pointers are not inlined yet
			return self.Parser.funcBlock[n.decl.name]

		self.__first = False
		self.__currentThread = n.decl.name
		self.__firstThreadCreate = False

		decl = self.visit(n.decl)
		self.indent_level = 0
		body = self.visit(n.body)

		f = ''

		self.__lines[self.__currentThread] = self.__stmtCount

		###print "THREAD %s, LINES %s \n\n" % (self.__currentThread, self.__lines)

		# 
		if n.param_decls:
			knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
			self.__stmtCount = -1
			#body = body[:body.rfind('}')] + self._make_indent() + returnStmt + '\n}'
			f = decl + '\n' + knrdecls + ';\n' 
		else:
			self.__stmtCount = -1
			#body = body[:body.rfind('}')] + self._make_indent() + returnStmt + '\n}'
			f = decl + '\n'

		# Remove arguments (if any) for main() and transform them into local variables in main_thread.
		#
		if self.__currentThread == 'main':
			#f = f.replace(' main(', ' main_thread(')
			#f = re.sub(r' main([-a-zA-Z0-9_, *]+)', r' main_thread(void)', f)
			f = re.sub(r' main(.*)', r' main_thread(void)', f)

			body = '{' + self.Parser.funcBlockIn['main'].replace(',', ';')+';' + body[body.find('{')+1:]

			# Change *argv[] and **argv[] --> **argv
			body = re.sub(r'\*(.*)\[\]', r'** \1', body)
			body = re.sub(r'(.*)\[\]\[\]', r'** \1', body)

		f += body + '\n'

		return f + '\n\n'


	def visit_If(self, n):
		ifStart = self.__maxInCompound   # label where the if stmt begins

		s = 'if ('

		if n.cond:
			condition = self.visit(n.cond)
			s += condition

		s += ')\n'
		s += self._generate_stmt(n.iftrue, add_indent=True)

		ifEnd = self.__maxInCompound   # label for the last stmt in the if block:  if () { block; }
		nextLabelID = ifEnd+1

		if n.iffalse:
			elseBlock = self._generate_stmt(n.iffalse, add_indent=True)

			elseEnd = self.__maxInCompound   # label for the last stmt in the if_false block if () {...} else { block; }

			if ifStart < ifEnd:
				threadIndex = self.Parser.threadIndex[self.__currentThread] if self.__currentThread in self.Parser.threadIndex else 0
				elseHeader = 'GUARD(%s,%s)' % (threadIndex, str(ifEnd+1))
			else:
				elseHeader = ''

			nextLabelID = elseEnd+1
			s += self._make_indent() + 'else\n'

			elseBlock = elseBlock.replace('{', '{ '+elseHeader, 1)
			s += elseBlock

		header = ''

		if ifStart+1 < nextLabelID:
			threadIndex = self.Parser.threadIndex[self.__currentThread] if self.__currentThread in self.Parser.threadIndex else 0
			footer = 'GUARD(%s,%s)' % (threadIndex, nextLabelID)
		else:
			footer = ''

		'''
		if n.iffalse:
			header = 'ASS_ELSE(%s, %s, %s)' % (condition, ifEnd+1, elseEnd+1) + '\n' + self._make_indent()
		else:
			if ifEnd > ifStart:
				header = 'ASS_THEN(%s, %s)' % (condition, ifEnd+1) + '\n' + self._make_indent()
			else: header = ''
		'''

		return header + s + self._make_indent() + footer


	def visit_Return(self, n):
		if self.__currentThread != '__VERIFIER_assert' and self.__currentThread not in self.Parser.funcReferenced:
			print "error: labeler.py: return statement in thread '%s'.\n" % self.__currentThread
			exit(1)

		s = 'return'
		if n.expr: s += ' ' + self.visit(n.expr)
		return s + ';'


	def visit_Label(self, n):
		self.__labelLine[self.__currentThread, n.name] = self.__stmtCount
		return n.name + ':\n' + self._generate_stmt(n.stmt)


	def visit_Goto(self, n):
		self.__gotoLine[self.__currentThread, n.name] = self.__stmtCount
		extra = '<%s,%s>\n' % (self.__currentThread, n.name) + self._make_indent()
		extra = ''
		return extra + 'goto ' + n.name + ';'


	def visit_ID(self, n):
		# If this ID corresponds either to a global variable,
		# or to a pointer...
		#
		if ((self.__isGlobal(self.__currentThread, n.name) or self.__isPointer(self.__currentThread, n.name)) and not
			n.name.startswith('__cs_thread_local_')):
			#print "variable %s in %s is global\n" % (n.name, self.__currentThread)
			self.__globalMemoryAccessed = True

		# Rename the IDs of main() arguments
		#if self.__currentThread == 'main' and n.name in self.Parser.varNames['main'] and self.Parser.varKind['main',n.name] == 'p':
		#	return '__main_params_' + n.name

		return n.name


	def visit_FuncCall(self, n):
		fref = self._parenthesize_unless_simple(n.name)
		args = self.visit(n.args)

		# When a thread is created, extract its function name
		# based on the 3rd parameter in the pthread_create() call:
		#
		# pthread_create(&id, NULL, f, &arg);
		#                          ^^^
		#
		if fref == common.changeID['pthread_create']:
		#if fref == 'pthread_create' and not self.__dontAddThreadNames:
			fName = args[:args.rfind(',')]
			fName = fName[fName.rfind(',')+2:]
			fName = fName.replace('&', '')

			##print "checking fName = %s\n\n" % fName

			if fName not in self.__threadName:
				self.__threadName.append(fName)
				self.__threadCount = self.__threadCount + 1

				args = args + ', %s' % (self.__threadCount)
				self.__threadIndex[fName] = self.__threadCount
			else:
				# when visiting from the 2nd time on (if it happens),
				# reuse the old thread indexS!
				args = args + ', %s' % (self.__threadIndex[fName])

			self.__firstThreadCreate = True

		if fref == common.changeID['pthread_exit']:
			if self.Parser.funcBlockOut[self.__currentThread] != 'void':
				return 'STOP_NONVOID(%s)' % (self.__stmtCount)
			else:
				return 'STOP_VOID(%s)' % (self.__stmtCount)

		return fref + '(' + args + ')'


	def __createMain(self, ROUNDS):
		# the new main() is created according to the following sort of scheduling:
		#
		# main_thread    t1 t2    t1 t2   t1 t2    t1 t2     t1 t2    t1 t2      t1 t2    t1 t2    main_thread
		#
		round = 0

		main = ''
		main += "int main(void) {\n"

		''' Part I:
			Pre-guessed jump lenghts have a size in bits depending on the size of the thread. 
		'''
		for r in range(0, ROUNDS):
			for t in range(0,self.__threadbound+1):
				threadsize = self.__lines[self.__threadName[t]]

	 			k = int(math.floor(math.log(threadsize,2)))+1

				main += "          unsigned __CPROVER_bitvector[%s] tmp_t%s_r%s;\n" % (k, t, r)

	 	k = int(math.floor(math.log(self.__lines['main'],2)))+1
		main += "          unsigned __CPROVER_bitvector[%s] tmp_t%s_r%s;\n" % (k, 0, ROUNDS)




		''' Part II:
			Schedule pruning constraints.
		'''
		main += '\n'

		schedulesPruned = []  # remeember which rounds have been pruned 

		for t in range(0,self.__threadbound+1):
			#print "thread %s,  name %s,   maxrepr %s,  threadsize %s" % (t,self.__threadName[t],maxrepresentable, threadsize)
			threadsize = self.__lines[self.__threadName[t]]
			maxrepresentable =  2**int((math.floor(math.log(threadsize,2)))+1) - 1

			sumall = ''

			for r in range(0, ROUNDS):
				sumall += 'tmp_t%s_r%s%s' % (t,r, ' + ' if r<ROUNDS-1 else '')

			if t == 0:
				sumall += ' + tmp_t0_r%s' % (ROUNDS)

			######if (maxrepresentable > threadsize+1) and int((math.floor(math.log(threadsize,2)))+1)+1 > 4: 
			if (maxrepresentable > threadsize+1) and int((math.floor(math.log(threadsize,2)))+1)+1 > 4: 
				schedulesPruned.append(True)
				if t == 0:
					wow =   int(math.ceil(math.log((maxrepresentable*(ROUNDS+1)),2)))
				else:
					wow =   int(math.ceil(math.log((maxrepresentable*ROUNDS),2)))
				##wow =   int(math.ceil(math.log((maxrepresentable*ROUNDS),2)))

				main += "          unsigned __CPROVER_bitvector[%s] top%s = %s;\n" % (wow, t, threadsize)
				main += "          unsigned __CPROVER_bitvector[%s] sum%s = %s;\n" % (wow, t, sumall)
				main += "          assume(sum%s <= top%s);\n" % (t,t)
			else:
				schedulesPruned.append(False)


		''' Part III: 

		'''
		# 1st round (round 0)
		#
		main +="          // round %s\n" % round 
		main +="          thread_index = 0;\n"
		main +="          pc_cs[0] = pc[0] + tmp_t0_r0;\n"

		if not schedulesPruned[0]:
			main +="          assume(pc_cs[0] > 0);\n"
			main +="          assume(pc_cs[0] <= %s);\n" % (self.__lines['main'])

		main +="          main_thread();\n"
		main +="          pc[0] = pc_cs[0];\n"
		main +="\n"

		i = 1
		for t in self.__threadName:
			if t == 'main': continue
			if i <= self.__threadbound:
				main +="          thread_index = %s;\n" % i
				main +="          if (active_thread[thread_index] == 1) { // %s\n"  % (t)
				main +="             pc_cs[%s] = pc[%s] + tmp_t%s_r%s;\n" % (i, i, i, 0)

				if  not schedulesPruned[i]:
					main +="             assume(pc_cs[%s] <= %s);\n" % (i, self.__lines[t])

				main +="             %s(%s);\n" % (t, 'threadargs[%s]') % (i)
				main +="             pc[%s] = pc_cs[%s];\n" % (i,i)
				main +="          }\n\n"
				i += 1

		# remaining rounds
		#
		for round in range(1,ROUNDS):
			i=0
			#####main +="          // round %s\n" % round 

			main +="          // round %s\n" % round 
			main +="          thread_index = 0;\n"
			main +="          if (active_thread[thread_index] == 1) { // %s\n"  % ('main')
			main +="              pc_cs[%s] = pc[%s] + tmp_t%s_r%s;\n" % (i, i, i, round)

			if  not schedulesPruned[0]:
				main +="              assume(pc_cs[%s] <= %s);\n" % (i, self.__lines['main']) 

			main +="              main_thread();\n"
			main +="              pc[0] = pc_cs[0];\n"
			main +="          }\n\n"

			i = 1
			for t in self.__threadName:
				if t == 'main': continue
				if i <= self.__threadbound:
					main +="          thread_index = %s;\n" % i
					main +="          if (active_thread[thread_index] == 1) { // %s\n"  % ( t)
					main +="             pc_cs[%s] = pc[%s] + tmp_t%s_r%s;\n" % (i, i, i, round)

					if  not schedulesPruned[i]:
						main +="             assume(pc_cs[%s] <= %s);\n" % (i, self.__lines[t])

					main +="             %s(%s);\n" % (t, 'threadargs[thread_index]')
					main +="             pc[%s] = pc_cs[%s];\n" % (i,i)
					main +="          }\n\n"
					i += 1

		# Last call to main()
		#
		round = ROUNDS-1
		main +="          thread_index = 0;\n"
		main +="          if (active_thread[0] == 1) {\n"
		main +="             pc_cs[0] = pc[0] + tmp_t0_r%s;\n" % (ROUNDS)

		main +="             assume(pc_cs[0] <= %s);\n" % (self.__lines['main'])

		main +="             main_thread();\n"
		main +="          }\n\n"
		main += "   return 0;\n"

		main += "}\n\n"

		return main


	# Checks whether variable  v  from function  f  is a pointer.
	#
	def __isPointer(self, f, v):
		if v in self.Parser.varNames[f] and self.Parser.varType[f,v].endswith('*'): return True
		elif v in self.Parser.varNames[''] and self.Parser.varType['',v].endswith('*'): return True
		else: return False


	# Checks whether variable  v  from function  f  is global.
	#
	def __isGlobal(self, f, v):
		if (v in self.Parser.varNames[''] and v not in self.Parser.varNames[f]): return True
		else: return False



