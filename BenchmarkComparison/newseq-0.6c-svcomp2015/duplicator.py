VERSION = 'duplicator-0.0-2014.10.26'
#VERSION = 'duplicator-0.0-2014.10.15'
##VERSION = 'duplicator-0.0-2014.03.14' (CSeq-Lazy-0.4)
###VERSION = 'duplicator-0.0-2014.02.25' (CSeq-Lazy-0.2)

"""

This module:
	- clones the threads functions so that all threads have different names
	 (including the case when multiple create()s using the same function as argument are done)
	 
	- update pthread_create() calls to call such functions


Prerequisites:
	- input for this module is the output from unroller.py


Changelog:
	2014.10.26  removed dead/commented-out/obsolete code
	2014.10.15  removed visit() and moved visit call-stack handling to module class (module.py)
	2014.03.14  further code refactory to match  module.Module  class interface
	2014.02.25  switched to  module.Module  base class for modules

"""

import pycparser.c_parser, pycparser.c_ast, pycparser.c_generator
import utils, common, module, parser
import re


class Duplicator(module.Module):
	__actualthreads = 0     # the extra thread is for main() is not counted at this stage
	__threadCallCnt = {}    # number of pthread_create()s on the same function generated so far 


	def loadfromstring(self, string, env):
		super(Duplicator, self).loadfromstring(string, env)
		'''
		self.Parser = parser.Parser()		
		self.Parser.loadfromstring(string)
		self.ast = self.Parser.ast
		self.output = self.visit(self.ast)
		'''
		self.postprocess()
		env.threads = self.getactualthreads() if env.threads == 0 else env.threads
		#print "OMAR: THREADNUMBER = %s" %  env.threads


	def postprocess(self):
		#for t in self.Parser.threadName:
		#	print "thread %s times %s" % (t, self.Parser.threadCallCnt[t])

		# The thread functions prototypes of duplicated threads
		# need to be duplicated too.
		#
		for f in self.Parser.threadName:
			if f in self.Parser.funcDecl:
				oldPrototype = self.Parser.funcDecl[f] + ';'
				newPrototype = ''

				for i in range(0, self.Parser.threadCallCnt[f]):
					newPrototype += oldPrototype.replace(f+'(', f+'_'+str(i)+'(', 1)

				#print "replacing '%s' with '%s'\n\n\n\n" %( oldPrototype, newPrototype)
				self.output = self.output.replace(oldPrototype, newPrototype)


	def getactualthreads(self):
		return self.__actualthreads


	def visit_FuncCall(self, n):
		fref = self._parenthesize_unless_simple(n.name)
		args = self.visit(n.args)

		if fref == common.changeID['pthread_create']:
			self.__actualthreads += 1
			fName = args[:args.rfind(',')]
			fName = fName[fName.rfind(',')+2:]
			fName = fName.replace('&', '')

			##print "OMAR found thread creation  %s(%s)  \n\n\n" % (fref, fName)

			if fName not in self.__threadCallCnt:			
			#####if fName in self.Parser.threadName:
				##print "OMAR ---- thread %s\n" % fName
				self.__threadCallCnt[fName] = 0;
			else:
				self.__threadCallCnt[fName] += 1;

			args = args.replace(fName, fName+'_'+str(self.__threadCallCnt[fName]))   # TODO: this needs proper implementation
			##print "OMAR: oldargs: %s, args: %s\n\n" % (fName, fName+'_'+str(self.__threadCallCnt[fName]))

			####self.__threadCallCnt[fName] += 1
			#print "name: %s    value= %s +1\n\n" % (fName, self.__threadCallCnt[fName])

		return fref + '(' + args + ')'


	''' Each thread function is duplicated exactly the number of times
	    that function is used to create a thread (as an argument to  pthread_call() )
	'''
	def visit_FuncDef(self, n):
		block = ''

		if n.decl.name == 'main':
			decl = self.visit(n.decl)
			body = self.visit(n.body)
			block = decl + '\n' + body + '\n'
		elif n.decl.name not in self.Parser.threadName:
			block = self.Parser.funcBlock[n.decl.name]
			#decl = self.visit(n.decl)
			#body = self.visit(n.body)
			#block = decl + '\n' + body + '\n'
		else:
			#print "thread %s, %s times\n" % (n.decl.name, self.Parser.threadCallCnt[n.decl.name])

			for i in range(0, self.Parser.threadCallCnt[n.decl.name]):
				##print "OMAR: Duplicating: %s" % n.decl.name
				#block += self.Parser.funcBlock[n.decl.name].replace(n.decl.name, n.decl.name+'_'+str(i), 1)
				tmp = self.Parser.funcBlock[n.decl.name].replace(n.decl.name, n.decl.name+'_'+str(i), 1)
				tmp = self.visit(n.decl) + '\n' + self.visit(n.body) + '\n'
				tmp = tmp.replace(n.decl.name, n.decl.name+'_'+str(i), 1)   # TODO this needs proper implementation

				##print "OMAR: new name: %s" % tmp

				block += tmp

		return block


















