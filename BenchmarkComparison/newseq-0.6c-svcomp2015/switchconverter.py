VERSION = 'switchconverter-0.0-2014.10.26'
#VERSION = 'switchconverter-0.0-2014.10.15'
##VERSION = 'switchconverter-0.0-2014.06.03' (CSeq-Lazy-0.4)
###VERSION = 'switchconverter-0.0-2014.03.14'
####VERSION = 'switchconverter-0.0-2014.02.25' (CSeq-lazy-0.2)

"""

Transforms all  switch..case..default  statements into  if + goto  statements and an extra label,
for example:

	switch(x) {
		case A: blkA; break;
		case B: blkB; break; blkB2;
		case C: blkC;
		case D: blkD;
		default: blkDef;
	}

into:

	if (x==A) { blkA; }
	if (x==A || x==B) { blkB; goto __cs_switch_exit; blkB2; }
	if (x==C) { blkC; }
	if (x==C || x==D) { blkD; }
	if ( (x!=A && x!=B && x!=C && x!=D) || (x==C || x==D) ) { blkDef; }
	__cs_switch_exit:;

Each set of statements between two consecutive  case  statements
is converted into a guarded block as shown above.
To model fall-through the previous guards are propagated when needed
(see  case D  above).

This also applies to the  default  case, where in addition the guard
includes the logical conjunction for all inverted previous condition.

Break statements are converted into jumps to an exit label
that is appended at the end of the translation,
unless they are not immediately before a  case  statement,
in which case they are simply removed (see case A)

Break statements from within loops are not affected.

Changelog:
	2014.10.26  changed  __stack  to  stack  (to inherit stack handling from module.py)
	2014.10.26  removed dead/commented-out/obsolete code
	2014.10.15  removed visit() and moved visit call-stack handling to module class (module.py)
	2014.06.03  mostly re-implemented from scratch
	2014.03.14  further code refactory to match  module.Module  class interface
	2014.02.25  switched to  module.Module  base class for modules

"""

import pycparser.c_parser, pycparser.c_ast, pycparser.c_generator
import utils, common, module, parser
import re


class Switchconverter(module.Module):
	__currentSwitchCount = 0

	__currentSwitchVar = []      # an extra variable introduced for each switch,
	                             # indexed by __currentSwitchCount
	                             # and handled in a stack fashion as switches may be nested

	__currentSwitchExpr = []     # all the case conditions since the last break

	__currentSwitchExprALL = []  # all the case conditions since the beginning of the switch statement


	def visit_Switch(self, n):
		cond = self.visit(n.cond)

		self.__currentSwitchCount += 1
		switchCondVar = '__cs_switch_cond_%s' % self.__currentSwitchCount
		switchEndLabel = '__cs_switch_exit_%s' % self.__currentSwitchCount
		self.__currentSwitchVar.append(switchCondVar)

		s = ''
		s += self._make_indent()+ 'static int %s; %s = %s;\n' % (switchCondVar, switchCondVar, cond)
		#s += self._make_indent()+ 'do '

		self.__currentSwitchExpr.append([])
		self.__currentSwitchExprALL.append([])
		s += self._generate_stmt(n.stmt, add_indent=True)
		self.__currentSwitchExpr.pop()
		self.__currentSwitchExprALL.pop()

		s+= self._make_indent() + switchEndLabel + ':;'
		#s += self._make_indent()+ ' while(0);'

		self.__currentSwitchVar.pop()
		return s.replace('<case-break-was-here>', 'goto %s;' % switchEndLabel)


	def visit_Case(self, n):
		expr = self.visit(n.expr)

		self.__currentSwitchExpr[-1].append(expr)
		self.__currentSwitchExprALL[-1].append(expr)

		ifcondition = '0'
		for e in self.__currentSwitchExpr[-1]:
			ifcondition += ' || %s == %s' % (self.__currentSwitchVar[-1], e)
		
		s = 'if (%s)\n' % ifcondition

		s += self._make_indent() + '{\n'

		self.indent_level += 1

		for i in range(0,len(n.stmts)):
			if i==len(n.stmts)-1  and  type(n.stmts[i]) == pycparser.c_ast.Break:
				# optimisation: remove all  break  statements,
				# when they are the last statement before the next  case  statement
				# (this avoids an unnecessary jump)
				#
				self.__currentSwitchExpr[-1] = []
				continue
			else:
				s += self._generate_stmt(n.stmts[i], add_indent=False)

		self.indent_level -= 1
		s += self._make_indent() + '}'

		return s


	def visit_Default(self, n):
		''' When the control-flow gets to the default statement is because:

			1. none of the case statements was entered (see case1 below)

			                 OR 

			2. some of the case statements was entered,
			   and from that statement to the default case 
			   no  break  statements are met (case 2 below)
		'''

		# all conditions
		case1 = '1'
		for e in self.__currentSwitchExprALL[-1]:
			case1 += ' && !(' + self.__currentSwitchVar[-1] + ' == ' + e + ')'

		# all conditions since the last break
		case2 = '0'
		for e in self.__currentSwitchExpr[-1]:
			case2 += ' || ' + self.__currentSwitchVar[-1] + ' == ' + e 


		ifcondition = '1'

		s = 'if ( (%s) || (%s) )\n' % (case1, case2)

		s += self._make_indent() + '{\n'
		self.indent_level += 1

		for stmt in n.stmts:
			s += self._generate_stmt(stmt, add_indent=False)

		self.indent_level -= 1
		s += self._make_indent() + '}'

		return s


	def visit_Break(self, n):
		''' Handling of break statements is done
			by looking at the innermost statement block enclosing it:

		    case 1: if the break statement is in a loop (i.e. for, while, do..while)
		            it is left unchanged

		    case 2: if the break statement is anywhere in a case statement,
		            it is changed into a placeholder <case-break-was-here>;
		            at the end of the whole visit of the  switch  block,
		            all such placeholders are changed into a jump
		            to the end of the block itself.
		''' 
		#print "break found: " + str(self.stack) + '   prev:' + str(self.stack[len(self.stack)-2])

		# the stack is inspected backwards
		# to check whether the innermost block containing this break statement
		# is a switch or a loop
		#
		innermostSwitch = -1

		for i in reversed(range(0,len(self.stack))):
			#print "    elem: %s  %s" % (i, self.stack[i])
			if self.stack[i] == 'Case': innermostSwitch = 1; break;   
			if self.stack[i] == 'For': innermostSwitch = 0; break;    
			if self.stack[i] == 'While': innermostSwitch = 0; break;  
			if self.stack[i] == 'DoWhile': innermostSwitch = 0; break;

		# this should never happen as a break statement is allowed only in the above cases
		if innermostSwitch == -1:
			raise module.ModuleError("break statement outside switch, for, while or do..while blocks.")

		# only break  stmts inside  switch..case..default  blocks are removed,
		# break  stmts inside  for, while  blocks are not.
		#
		if innermostSwitch == 1:
			self.__currentSwitchExpr[-1] = []
			return '<case-break-was-here>'  # case 2
		else:
			return 'break;'                 # case 1











