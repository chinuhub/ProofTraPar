"""

CSeq module template class

Note:
	to enable linemapping (still experimental) uncomment instructions in _getCurrentCoords()

Changelog:
	2014.10.22  implemented linemapping (now disabled to improve performance and stability - it needs proper testing before releasing)
	2014.10.15  implemented  self.stack  to examine the stack of calls to visit() (modules may use this)
	2014.06.02  introduced specific  module.ModuleError  exception for detailed error handling

"""

import os, re
import pycparser.c_parser, pycparser.c_ast, pycparser.c_generator
import parser, utils


class ModuleError(Exception):
	def __init__(self, value): self.value = value
	def __str__(self): return repr(self.value)


class Module(pycparser.c_generator.CGenerator):
	stack = []            # keep track of the structure of what's been parsed so far

	cseqenvironment = None  # translation settings (e.g. unwind bound, ... see new.py)

	# Statements start with indentation of self.indent_level spaces, using
	# the _make_indent method
	#
	indent_level = 0		# to keep track of the depth of the block {}
	INDENT_SPACING = '\t'	# ....

	#
	lastCoords = ''         # coords of the last fragment of code parsed (used also to produce parsing error messages etc.)
	lines = []

	#
	input = ''   # the original input of the module, unchanged
	output = ''  # the final output of the module

	#
	inputtooutput = {}
	outputtoinput = {}

	# coords given by the last linemarker
	lastsinputfile = ''    # input file in the last linemarker
	lastinputlineno = 0    # line number since last linemarker
	lastoutputlineno = 0   # line number in output


	Parser = parser.Parser()


	def __init__(self):
		#pass
		self.stack = []

		self.lastCoords = ''
		self.lines = []

		self.inputtooutput = {}
		self.outputtoinput = {}

		self.lastsinputfile = ''    # input file in the last linemarker
		self.lastinputlineno = 0    # line number since last linemarker
		self.lastoutputlineno = 0   # line number in output


	def getversion(self):
		return self.MODULE_VERSION


	def _make_indent(self, delta=0):
		return (self.indent_level+delta) * self.INDENT_SPACING


	def _getCurrentCoords(self, item):
		return ''
		''' NOTE: uncomment instructions below to enable linemapping '''
		lineno = str(item.coord)[1:] if str(item.coord)[0] == ':' else -1
		return '# %s "<previous_module>"\n' % (lineno)


	def loadfromstring(self, string, env):
		self.cseqenvironment = env

		self.input = string
		self.Parser.reset()  # resets all the parser datastructs
		self.Parser.loadfromstring(string)
		self.ast = self.Parser.ast
		self.output = self.visit(self.ast)

		# remove indentation (if any) before linemarkers
		newoutput = ''

		for line in self.output.splitlines():
			newoutput += re.sub(r'(%s)*#'%self.INDENT_SPACING, r'#', line) + '\n'

		self.output = newoutput


	def generatelinenumbers(self):		
		# Generate the map of line numbers.
		#
		# Every time a linemarker in the output is found...
		#
		# This way we can extract from the line annotation the input line number to which
		# the output line refers to, and associate it correctly.
		# 
		# In the module's output, 
		# linemarkers will indicate precisely where the lines come from,
		# but this information needs to be removed from the input block, or
		# pycparser won't handle it.
		#
		inputline = 0      # actual input line number in the input (i.e. lines[]), including line with markers
		inputmarkers = 0   # count the linemarkers in the input (we know each linemarker takes one entire line)

		cleanoutput = '' # clean output (without linemarkers)

		for line in self.output.splitlines():
			inputline +=1 
			##print "LINE LINE LINE %s" % inputline

			if line.startswith('# '): 
				inputmarkers += 1
				markerinfo = utils.linemarkerinfo(line)
				self.lastinputlineno = markerinfo[0]
				self.lastinputfile = markerinfo[1]

				##print "MARKER: '%s'" % line
				##print "   " + str(utils.linemarkerinfo(line))
				##print "   last '%s'" % (utils.linemarkerinfo(line)[1])
				##print "\n\n"
			else:
				#print "input:%s  ->  output:%s" % (lastlineno, inputline-inputmarkers)
				#print "output:%s  ->  input:%s" % (inputline-inputmarkers, lastlineno)

				#  > > >   Our line map   < < <
				self.inputtooutput[self.lastinputlineno] = inputline-inputmarkers
				self.outputtoinput[inputline-inputmarkers] = self.lastinputlineno

				self.lastoutputlineno += 1
				cleanoutput += line + '\n'

		self.output = cleanoutput


	def string(self):
		return self.output


	def save(self, filename):
		outfile = open(filename,"w")
		###outfile.write('/* module:<%s> */\n\n' % inspect.getmodulename(inspect.stack()[1][1]))
		outfile.write(self.output)
		outfile.close()


	def show(self):
		print(self.output)


	# Extract the coords from an error condition
	#
	def parseErrorCoords(self, error):
		errorstring = str(error)
		k = utils.findNth(errorstring,':',2)

		if k != -1: errorcoords = errorstring[:utils.findNth(errorstring,':',2)]
		else: errorcoords = ':-1:-1'

		return errorcoords


	def getLineNumber(self, error):
		return int(self.parseErrorCoords(error).split(':')[1])


	def getColumnNumber(self, error):
		return int(self.parseErrorCoords(error).split(':')[2])


	''' TODO integrate stack management
	def visit(self, node):
		method = 'visit_' + node.__class__.__name__
		
		##print "       VISITING %s\n\n" % (str(node))

		self.__stack.append(node.__class__.__name__)
		retval = getattr(self, method, self.generic_visit)(node) 
		##print str(self.__stack) + '   prev:' + str(self.__stack[len(self.__stack)-2])
		self.__stack.pop()

		return retval
	'''


	def visit(self, node):
		method = 'visit_' + node.__class__.__name__
		self.stack.append(node.__class__.__name__)
		lineCoords = ''

		# Extracts node coords where possible.
		#
		# This is to update the current coord (= filename+line number) of the input file being parsed,
		# considering that:
		#
		# - on the same line of input, there may be more AST nodes (shouldn't enter duplicates)
		# - compound statement and empty statements have line number 0 (shouldn't update the current line)
		# - the same line of input may correspond to many lines of output
		#
		if hasattr(node, 'coord'):
			if node.coord:
				self.lastCoords = str(node.coord)
				##print "visiting coords: %s" % (self.lastCoords)

				# line number handling borrowed from CSeq-0.5
				linenumber = str(node.coord)
				linenumber = linenumber[linenumber.rfind(':')+1:]
				self.currentInputLineNumber = int(linenumber)

				##print "> > >    current Line No. %s\n" % (self.currentInputLineNumber)

				# Each line of the output is annotated when 
				# either it is coming from a new input line number
				# or the input line has generated many output lines, 
				# in which case the annotation needs to be repeated at each line..
				#
				if linenumber != '0' and linenumber not in self.lines:
					##print "      adding line number %s <-> %s\n\n\n" % (linenumber, self.output)
					self.lines.append(linenumber)
					lineCoords = self._getCurrentCoords(node)

		##tmp = ''
		retval = lineCoords + super(Module, self).visit(node)
		self.stack.pop()

		return retval







