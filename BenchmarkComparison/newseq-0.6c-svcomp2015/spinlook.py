VERSION = 'spinlook-0.0-2014.10.02'
#VERSION = 'spinlook-0.0-2014.03.14'
##VERSION = 'spinlook-0.0-2014.02.25'

"""

	Transformation:
		remove spin-looks:

     		case 1:    while (cond) {}     --->     assume(!cond);
     		case 2:    while (cond) {;}    --->     assume(!cond);

     	which is safe to do only when  cond   has no side-effects.

Changelog:
	2014.10.02  added case 2
	2014.03.14  further code refactory to match  module.Module  class interface
	2014.02.25  switched to  module.Module  base class for modules

"""

import pycparser.c_parser, pycparser.c_ast, pycparser.c_generator
import utils, module, parser
import os, sys, getopt, time


class Spinlook(module.Module):
	__currentLoop = 0
	parsingSideEffect = False   # set when parsing a statement with side effects (i.e., function call, assignment, unary op)


	def visit_FuncCall(self, n):
		self.parsingSideEffect = True

		fref = self._parenthesize_unless_simple(n.name)
		return fref + '(' + self.visit(n.args) + ')'


	def visit_While(self, n):
		#
		# How do we check for side effects?
		#
		# Before visiting a while condition block ( while(....) ),
		# flag self.parsingSideEffect is reset.
		#
		# If after the visit the flag is set, then the condition block
		# contains at least one assignment statement, a unary op or a function call.
		#
		# If after visiting the condition block it is still not set,
		# it means that no assignment stmts, unary ops or function call are present.
		# The flag is in fact set by visit_... methods for each of these ast nodes.
		#
		self.parsingSideEffect = False

		s = 'while ('
		if n.cond: s += self.visit(n.cond)
		#if self.parsingSideEffect: s += ' SIDE EFFECT HERE '
		#else: s+= ' NO SE HERE '
		s += ')\n'

		t = self._generate_stmt(n.stmt, add_indent=True)

		if not t.startswith(self._make_indent()+ ('{\n')):      # add brakets for single non parenthesised statements after if
			t = self._make_indent() + '{\n' + t + self._make_indent() + '}\n'

		# When the while condition has no side effects,
		# and the while block is either the empty statement (;) or the empty block ({}),
		# the following transformation is done:
		#
		#     while (cond) {}     --->     assume(!cond);
		#     while (cond) {;}    --->     assume(!cond);
		#
		'''
		if not self.parsingSideEffect and (type(n.stmt) == pycparser.c_ast.EmptyStatement or not n.stmt.block_items):
		##if not self.parsingSideEffect and (n.stmt == ';' or not n.stmt.block_items):
			s = s.replace('while (', 'assume(!(', 1)
			s = s[:len(s)-2] + '));\n'
			t = ''
		'''
		if not self.parsingSideEffect:
			if (not n.stmt.block_items) or (
				n.stmt.block_items and len(n.stmt.block_items) == 1 and type(n.stmt.block_items[0]) == pycparser.c_ast.EmptyStatement):  # (case 1) or (case 2)
				s = s.replace('while (', 'assume(!(', 1)
				s = s[:len(s)-2] + '));\n'
				t = ''

		s += t
		return s


	def visit_UnaryOp(self, n):
		self.parsingSideEffect = True

		operand = self._parenthesize_unless_simple(n.expr)
		if n.op == 'p++':
			return '%s++' % operand
		elif n.op == 'p--':
			return '%s--' % operand
		elif n.op == 'sizeof':
			# Always parenthesize the argument of sizeof since it can be
			# a name.
			return 'sizeof(%s)' % self.visit(n.expr)
		else:
			return '%s%s' % (n.op, operand)


	def visit_Assignment(self, n):
		self.parsingSideEffect = True

		rval_str = self._parenthesize_if(
			n.rvalue,
			lambda n: isinstance(n, pycparser.c_ast.Assignment))

		return '%s %s %s' % (self.visit(n.lvalue), n.op, rval_str)








