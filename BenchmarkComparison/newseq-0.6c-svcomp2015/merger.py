VERSION = 'merger-0.0-2014.10.09'
#VERSION = 'merger-0.0-2014.09.27'
##VERSION = 'merger-0.0-2014.09.22'
###VERSION = 'merger-0.0-2014.02.25'

"""

Purpose of this module:

	- input sanitising (e.g. __thread_local workaround, removing non-standard C extensions, ...)
	- merge all the input files into one 

	Note: in this module, linemapping overrides the generic mechanism provided by class Module.

Prerequisites:
	gcc/cpp preprocessor prerequisites

Changelog:
	2014.10.09  moved all parser-based code transformations from this module to  workarounds.py
	2014.10.09  modifying sanitise() to avoid using the preprocessor at that stage (easier line mapping)
	2014.09.27  new method sanitise() now includes all code-satinising, including thread_local workaround 
	2014.09.22  moved thread local workaround from  new.py  to this module
	2014.09.22  load() / loadfromstring() now use gcc rather than cpp to preprocess,
	            needed to avoid problems with OSX (where cpp does not remove C++-style comments, causing parsing errors)
	2014.02.25  switched to  module.Module  base class for modules

"""

import pycparser.c_ast, pycparser.c_generator, pycparser.c_parser
import module, utils
import getopt, inspect, os, re, sys, subprocess, shlex, time


class Merger(module.Module):
	__parsingFunction = False
	currentAnonStructsCount = 0   # counts the number of anonymous structures (used to assign consecutive names)

	inputtooutput = {}
	outputtoinput = {}

	def __init__(self):
		pass


	''' Performs a series of simple transformations to make sure that PYCparser will handle the input.
	'''
	def _sanitise(self, input):
		# Transformation 1:
		#    _thread_local workaround, step I
		#    (step II is performed later by the corresponding  threadlocal.py  module)
		#
		text = ''

		for line in input.splitlines():
			line = re.sub(r'__thread _Bool (.*) = 0', r'_Bool __cs_thread_local_\1[THREADS] ', line)
			line = re.sub(r'_Thread_local _Bool (.*) = 0', r'_Bool __cs_thread_local_\1[THREADS] ', line)

			text += line+'\n'

		# Transformation 2:
		#    get rid of non-standard GNU C extensions by inserting preprocessor directives
		#    that will cause such extensions to be preprocessed out
		#
		# NOTE! preprocessing them out will shift down  'miniheaderlength'  lines the original input file,
		#       even after preprocessing there'll be empty lines in place of the #define lines,
		#       so we rather use regular expression for our prototype.
		#
		'''
		miniheader = '#define __extension__(x)\n#define __attribute__(x)\n'
		miniheaderlines = miniheader.count('\n')
		text = miniheader + text
		'''
		lines = text.splitlines()
		text = ''

		for line in lines:
			line = re.sub(r'__extension__ \((.*)\)', r'', line)
			line = re.sub(r'__attribute__ \((.*)\)', r'', line)

			line = re.sub(r'__extension__\((.*)\)', r'', line)
			line = re.sub(r'__attribute__\((.*)\)', r'', line)

			text += line+'\n'

		'''
		# Transformation 3:
		#    TODO (try this out on files reorder_5_... and scull_... maybe?)
		#    TODO use regular expressions rather than rough replacings
	 	###text = text.replace('__const ', 'const ')
		###text = text.replace('__extension__', '')
		'''

		return text


	def loadfromstring(self, string, env):
		self.input = string

		string = self._sanitise(string)

		'''
		parser = pycparser.c_parser.CParser()   # avoid using CSeq's enhanced parser as it is more complex - all other modules should use that.

		self.ast = parser.parse(out)
		self.output = self.visit(self.ast)
		'''
		# Run the preprocessor with linemarker generation.
		#
		# the linemarker has the following format
		# (see https://gcc.gnu.org/onlinedocs/gcc-4.3.6/cpp/Preprocessor-Output.html):
		#
		#   # LINE_NO FILENAME FLAG
		#
		# examples:
		#  # 1 "<stdin>"
		#  # 1 "include/pthread.h" 2
		#
		#
		# Workaround: cpp does not strip C++-style comments ('//') from the input code,
		# need to use gcc preprocessor
		#
		###cmdline = 'cpp -Iinclude -E -C ' + filename + ' > ' + filename + '.1' + '.c'
		##cmdline = 'gcc -Iinclude -P -E - '  # hyphen at the end forces input from stdin
		#
		cmdline = 'gcc -Iinclude -E - '  # hyphen at the end forces input from stdin
		p = subprocess.Popen(shlex.split(cmdline), stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE)
		string = p.communicate(input=string)[0]


		# After preprocessing, line markers will indicate precisely where the lines come from,
		# but this information needs to be removed from the input block, or
		# pycparser won't handle it.
		#
		lines = string.splitlines()

		inputline = 0      # actual input line number in the input (i.e. lines[]), including linemarkers count
		inputmarkers = 0   # count the linemarkers in the input (we know each linemarker takes one entire line)

		# coords given by the last linemarker
		lastinputfile = '' # input file in the last linemarker
		self.lastlineno = 0     # line number since last linemarker

		boh = '' # clean input (without linemarkers)

		for line in lines:
			inputline +=1 

			if line.startswith('# '): 
				inputmarkers += 1
				markerinfo = utils.linemarkerinfo(line)
				self.lastlineno = markerinfo[0]
				lastinputfile = markerinfo[1]

				#print "MARKER: '%s'" % line
				#print "   " + str(utils.linemarkerinfo(line))
				#print "   last '%s'" % (utils.linemarkerinfo(line)[1])
				#print "\n\n"
			else:
				#print "line %s in the input is actually coming from %s, line %s" % (inputline, lastinputfile, lastlineno)
				#print "line %s in the input (not counting '# lines') is actually coming from %s, line %s" % (inputline-inputmarkers, lastinputfile, lastlineno)
				#print "input:%s  ->  output:%s" % (lastlineno, inputline-inputmarkers)
				#print "output:%s  ->  input:%s" % (inputline-inputmarkers, lastlineno)

				#  > > >   Our line map   < < <
				self.inputtooutput[self.lastlineno] = inputline-inputmarkers
				self.outputtoinput[inputline-inputmarkers] = self.lastlineno

				#print line
				#print " -"*20
				#print "\n"
				self.lastlineno += 1
				boh += line + '\n'

		string = boh

		#super(Merger, self).loadfromstring(string, env)
		self.output = boh

		###print "LAST TOKEN: " + parser.clex.last_token
		###print "LINE No.: " + str(parser.clex.lexer.lineno)
		###print "TOKENS: " + str(parser.clex.tokens)
		###exit(1)


	def save(self, filename):
		outfile = open(filename,"w")
		outfile.write(self.output)
		outfile.close()


	def show(self):
		print(self.output)


	def string(self):
		return self.output






