VERSION = 'constants-0.0-2014.10.26'
#VERSION = 'constants-0.0-2014.10.15'
##VERSION = 'constants-0.0-2014.03.14' (CSeq-Lazy-0.4)
###VERSION = 'constants-0.0-2014.02.25' (Cseq-Lazy-0.2)

"""

	Constant expression semplifications: change  20 + 3  --->  23

Changelog:
	2014.10.26  removed dead/commented-out/obsolete code
	2014.10.15  removed visit() and moved visit call-stack handling to module class (module.py)
	2014.03.14  further code refactory to match  module.Module  class interface
	2014.02.25  switched to  module.Module  base class for modules

"""

import pycparser.c_parser, pycparser.c_ast, pycparser.c_generator
import utils, common, module, parser
import inspect, os, sys, getopt, time


class Constants(module.Module):
	def visit_BinaryOp(self, n):
		lval_str = self._parenthesize_if(n.left, lambda d: not self._is_simple_node(d))
		rval_str = self._parenthesize_if(n.right, lambda d: not self._is_simple_node(d))

		#if n.op == '-' and type(n.left) == pycparser.c_ast.Constant and  and type(n.right) == pycparser.c_ast.Constant:
		if n.op == '-' and self._isInteger(lval_str) and self._isInteger(rval_str):
			return str(int(lval_str) - int(rval_str))
		if n.op == '+' and self._isInteger(lval_str) and self._isInteger(rval_str):
			return str(int(lval_str) + int(rval_str))

		return '%s %s %s' % (lval_str, n.op, rval_str)


	def _isInteger(self, s):
		if s[0] in ('-', '+'): return s[1:].isdigit()
		else: return s.isdigit()













