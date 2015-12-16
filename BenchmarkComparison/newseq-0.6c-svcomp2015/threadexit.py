THREADEXIT_VERSION = 'threadexit-0.0-2014.02.25'

"""

formations:
	- thread transformation:
		- thread_exit: return;  or  thread_exit: return 0;  is added at the bottom (depending on how the thread function is declared)

Changelog:
	2014.02.25  switched to  module.Module  base class for modules

"""

import pycparser.c_parser, pycparser.c_ast, pycparser.c_generator
import utils, common, module, parser
import re
from pycparser import c_ast


class Threadexit(module.Module):
	__outputcode = ''

	currentFunction = ''


	def init(self):
		pass


	def load(self, filename):
		self.Parser = parser.Parser()
		self.Parser.load(filename)

		self.__inputfilename = filename
		###self.ast = pycparser.parse_file(filename, use_cpp=False)
		self.ast = pycparser.parse_file(self.__inputfilename, use_cpp=True, cpp_args=r'-Iinclude -E -C ')
		self.__outputcode = self.visit(self.ast)


	def save(self, filename):
		outfile = open(filename,"w")
		outfile.write(self.__outputcode)
		outfile.close()


	def show(self):
		print self.__outputcode


	def visit_FuncDef(self, n):
		self.currentFunction = n.decl.name

		decl = self.visit(n.decl)
		self.indent_level = 0
		body = self.visit(n.body)

		# At the bottom of each thread, add a pthread_exit() statement
		# 
		returnStmt = ''

		if (self.currentFunction in self.Parser.threadName or self.currentFunction == 'main'):
			returnStmt = self.INDENT_SPACING + '__exit_%s: ; %s(0);\n' % (self.currentFunction, common.changeID['pthread_exit'])

		# Continue the visit.
		if n.param_decls:
			knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
			body = body[:body.rfind('}')] + self._make_indent() + returnStmt + '}'
			block = decl + '\n' + knrdecls + ';\n' + body + '\n'
		else:
			body = body[:body.rfind('}')] + self._make_indent() + returnStmt + '}'
			block = decl + '\n' + body + '\n'

		return block



