#!/usr/bin/env python
VERSION = 'threadlocal-0.0-2014.03.14'
#VERSION = 'threadlocal-0.0-2014.02.25' (Cseq-Lazy-0.2)

"""

Changelog:
	2014.03.14  further code refactory to match  module.Module  class interface
	2014.02.25  switched to  module.Module  base class for modules

"""

import pycparser.c_parser, pycparser.c_ast, pycparser.c_generator
import utils, module, parser
import inspect, os, sys, getopt, time


class Threadlocal(module.Module):
	#__output = ''
	__parsingFunction = False
	__threadLocals = []


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

		if (n.name is not None) and (n.name.startswith('__cs_thread_local_')):
			varname = n.name
			#varname = varname.replace('__cs_thread_local_', '')
			self.__threadLocals.append(varname.replace('__cs_thread_local_', ''))
			#print "FOUND %s --> %s\n" % (n.name, varname)

		return s


	def visit_ID(self, n):
		if n.name in self.__threadLocals:
			return '__cs_thread_local_'+n.name+'[thread_index]'
		else:
			return n.name





