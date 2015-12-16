"""

Changelog:
	2014.10.09  linemarkerinfo method
	2014.10.07  improved timeout management (Class Command: ctrl-C now kills the backend)

"""

import getopt, sys, os.path, os

class colors:
	BLINK = '\033[5m'
	BLACK = '\033[90m'
	DARKRED = '\033[31m'
	RED = '\033[91m'
	GREEN = '\033[92m'
	YELLOW = '\033[93m'
	BLUE = '\033[94m'
	NO = '\033[0m'


''' Reverse replace
'''
def rreplace(s, old, new, occurrence):
	li = s.rsplit(old, occurrence)
	return new.join(li)


''' Loads in a string the content of a file, then returns it. 
'''
def printFile(filename):
	if not os.path.isfile(filename):
		print "ERROR: printfile(%s): file does not exist.\n" % filename
		return

	in_file = open(filename,"r")
	text = in_file.read()
	in_file.close()

	return text


''' Write to a file the contents of a string. 
'''
def saveFile(filename, string):
	outfile = open(filename,"w")
	outfile = open(filename,"w")
	outfile.write(string)
	outfile.close()



'''
'''
def linesContain(string_lines, string):
	for line in string_lines:
		if string in line: return True

	return False


''' Return the number of lines (or of '\n's +1) in the given file.
'''
def fileLength(filename):
	with open(filename) as f:
		for i, l in enumerate(f): pass

	return i + 1


''' 
	strip()  -  Strips every line in the given string
				from the line with '_____STARTSTRIPPINGFROMHERE_____' as substring
				to the one with '_____STOPSTRIPPINGFROMHERE_____' as substring.

				Lines are identified by '\n'
'''
def strip(s):
	s2 = ''
	status = 0

	for line in s.split('\n'):
		if '_____STARTSTRIPPINGFROMHERE_____' in line:
			status = 1
			continue;


		if '_____STOPSTRIPPINGFROMHERE_____' in line:
			status = 2
			continue;

		if status == 0 or status == 2: s2 += line + '\n'

	return s2


''' 
	strip()  -  Strips every line in the given string
				from the line with 'startmarker' as substring
				to the one with 'endmarker' as substring.

				Lines are identified by '\n'
'''
def strip2(s, startmarker='_____STARTSTRIPPINGFROMHERE_____', endmarker='_____STOPSTRIPPINGFROMHERE_____' ):
	s2 = ''
	status = 0

	for line in s:
		if line.startswith(startmarker) and status == 0:
			print "start marker found\n"
			status = 1
			continue;

		if line.endswith(endmarker) and line.startswith(startmarker) and status == 1:
			print "end marker found\n"
			status = 2
			continue;

		if status == 0 or status == 2: s2 += line + '\n'

	return s2





''' Check whether a file starts with 'string'
'''
def fileStartsWith(filename, string):
	if os.path.isfile(filename):
		myfile = open(filename)
		lines = list(myfile)

		if lines[0].startswith(string): return True
		else: return False

	else: return False

	return False


''' Check whether a file contains at least one occurrence of 'string' in any of its lines
'''
def fileContains(filename, string):
	if os.path.isfile(filename):
		myfile = open(filename)
		lines = list(myfile)

		for line in lines:
			if string in line: return True
	else: return False

	return False


''' For now, we assume that if the input file contains "__attribute__ ((",
	it is in (.i) preprocessed format rather than in plain (.c) format.
'''
def isPreprocessed(filename):
	return fileContains(filename, "__attribute__ ((")


def stripIfNeeded(filename):
	stripped = False
	outputfilecontents = ''

	if isPreprocessed(filename):
		myfile = open(filename)
		allLines = list(myfile)

		if fileStartsWith(filename, '# '):
			# delete every line from the top of the file to 
			# the very last line starting with '# '

			for i in range(len(allLines)):
				stillLinesWithDash = False

				# are there any more lines from the i-th on which start with '# '?
				for j in range(i, len(allLines)):
					if allLines[j].startswith('# '):
						stillLinesWithDash = True
						break

				if stillLinesWithDash == False:
					# copy all the remaining lines in a file
					outputfilecontents = '#include <stdio.h>\n' # force fake_include inclusion

					for j in range(i, len(allLines)):
						outputfilecontents += allLines[j]

					stripped = True
					break
		else:
			# delete every line from the top of the file to 
			# the very last line starting with 'extern ',
			# then keep deleting until the fist line ending with ';' is reached 

			lastSemiColonSeen = None

			for i in range(len(allLines)):
				# are there any more lines from the i-th on which start with 'extern '?
				stillLinesWithExtern = False

				for j in range(i, len(allLines)):
					if allLines[j].startswith('extern '):
						stillLinesWithExtern = True
						lastSemiColonSeen = allLines[j].endswith(';\n')
						##print "LAST LINE: %s" % allLines[j]
						break

				# once there are no more 'extern ' lines,
				# copy all the remaining lines in a file
				##print "WAS LAST LINE TERMINATING?? %s" % lastSemiColonSeen
				##print "\n\n"

				if stillLinesWithExtern == False:
					outputfilecontents = '#include <stdio.h>\n'

					lastStatementStripped = False # the last statement to strip can have multiple lines

					for j in range(i, len(allLines)):
						##print "CHECKING LINE %s '%s'" % (j, allLines[j])

						if not lastStatementStripped:   # skip until the first ';'
							if not lastSemiColonSeen and not allLines[j].endswith(';\n'):
								lastStatementStripped = True
								continue

						if ')) __attribute__ ((' not in allLines[j]:
							outputfilecontents += allLines[j]

					stripped = True
					break

	return (stripped, outputfilecontents)


''' Extract a snippet of code from  string,
    lines from  linenumber-width  to  linenumber+width (when possible).

    Lines are trimmed down to the terminal column size
    when  trim  is set.

    Note: following compiler and editor conventions,
          line numbers start from 1, not zero!
'''
def snippet(string, linenumber, colnumber, width, trim=False):
	#return ### the 'while not finished' loop below may not terminate

	columnwidth = getTerminalSize()[1]
	splitinput = string.splitlines()

	#####print "input:\n%s\n" % len(splitinput)

	snippet = ''
	#return ''

	shiftedcolumns = 0

	#####print "linenumber=%s  colnumber=%s  width=%s  trim=%s" % (linenumber, colnumber, width, trim)

	# first and last line numbers of the snippet
	a = max(0, linenumber-width-1)     
	b = min(len(splitinput), linenumber+width)

	#snippet += "see lines %s-%s below:\n" % (linenumber-width,linenumber+width)
	#snippet += ">  "+"-"*10 + '\n'

	# Convert tab to spaces
	for i in range(a,b):
		splitinput[i] = splitinput[i].replace('\t', ' ')  # each tab counts as a column in the parser

	# Get rid of all the empty spaces in common at the beginning to each line,
	# so to shift all the printed code to the left.. 
	finished = False

	while not finished:
		count = 0
		#####print "count: %s   -   finished: %s,   %s %s   shifted:%s" % (count, finished, a, b, shiftedcolumns)

		for i in range(a,b):
			if splitinput[i].startswith(' ') or splitinput[i] == '': count = count+1
			else: finished = True

		#print "count %s    -    len %s " % (count, len(range(a,b)))

		if count == len(range(a,b)):
			if count == 0: finished = True
			else: 
				for i in range(a,b):
					splitinput[i] = splitinput[i][1:]

				shiftedcolumns+=1

	# Concatenate the actual (possibly shortened) lines from parameter  string,
	# to make the snippet
	extraline = ''

	#for i in range(a,b):
	for i in range(a,linenumber):
		shiftedcolumns2 = 0

		if i+1 == linenumber:
			# shorten internally the line when it does not fit the terminal
			if colnumber-shiftedcolumns > int(columnwidth*0.9):
				splitinput[i] = splitinput[i][:int(columnwidth*0.1)] + ' ... ' + splitinput[i][colnumber-shiftedcolumns-int(columnwidth*0.6):]
				shiftedcolumns2 = colnumber - int(columnwidth*0.1) - int(columnwidth*0.6) - 5

			nextline = " >  %s" % (splitinput[i])
			pointer = '~~~^' if (colnumber-shiftedcolumns-shiftedcolumns2) > 4 else '^~~~'
			extraline = "   " + ' '*(colnumber-shiftedcolumns-shiftedcolumns2) + pointer
		else:
			nextline = "    %s" % (splitinput[i])

		if trim and len(nextline) > columnwidth:
			nextline = nextline[:int(columnwidth*0.9)] + '...'

		snippet += nextline + '\n'

		if extraline != '':
			snippet += extraline + '\n'
			extraline = ''

	return snippet


''' Find the index of the  n-th  occurrence of  key  in  string
   (starting from the 0-th), or  -1  if it cannot be found.
'''
def findNth(string, key, n):
	parts = string.split(key, n+1)

	if len(parts) <= n+1:
		return -1

	return len(string)-len(parts[-1])-len(key)


def getTerminalSize():	
	rows, columns = os.popen('stty size', 'r').read().split()
	return (int(rows), int(columns))


''' Timeout management

 See:
   http://stackoverflow.com/questions/1191374/subprocess-with-timeout
   http://stackoverflow.com/questions/4789837/how-to-terminate-a-python-subprocess-launched-with-shell-true

'''
import shlex, signal, subprocess, threading

class Command(object):
 	status = None
	output = stderr = ''

	def __init__(self, cmdline):
		self.cmd = cmdline
		self.process = None


	def run(self, timeout):
		def target():
			# Thread started
			self.process = subprocess.Popen(self.cmd, shell=True, preexec_fn=os.setsid, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
			self.output, self.stderr = self.process.communicate()
			# Thread finished

		thread = threading.Thread(target=target)

		try:
			thread.start()
			thread.join(timeout)

			if thread.is_alive():
				# Terminating process
				###self.process.terminate()
				##os.killpg(self.process.pid, signal.SIGTERM)
				os.killpg(self.process.pid, signal.SIGKILL)
				thread.join()
		except KeyboardInterrupt:
			self.process.kill()

		return self.output, self.stderr, self.process.returncode


''' Extract linemarker information.

	Examples:
		linemarkerinfo('# 1 "<built-in>" 1')         -->  (1, '<built-in>', 1)
		linemarkerinfo('# 1 "<stdin>"')              -->  (1, '<stdin>', -1)
		linemarkerinfo('# 1 "include/pthread.h" 2')  -->  (1, 'include/pthread.h', 2)

   (for a description of linemarkers see:
   	https://gcc.gnu.org/onlinedocs/gcc-4.3.6/cpp/Preprocessor-Output.html)

'''
def linemarkerinfo(marker):
	# linemarker format:  # LINENO FILE FLAG
	# (note  FLAG  is not mandatory)
	#
	#print "MARKER: '%s'" % marker

	line = marker

	# 1st field: line number
	line = line[2:]
	marker_lineno = line[:line.find('"')-1]
	if marker_lineno.isdigit(): marker_lineno = int(marker_lineno)
	else: return (-1, -1, -1)

	# 2nd field: source file
	line = line[line.find('"')+1:]	
	marker_filename = line[:line.find('"')]

	# 3rd field: flag (optional)
	line = line[line.rfind(' ')+1:]
	if line.isdigit() and int(line) <=4 and int(line) >= 1:	marker_flag = int(line)
	else: marker_flag = -1

	#print " LINENO: '%s'" % marker_lineno
	#print " FILE: '%s'" % marker_filename
	#print " FLAG: '%s'" % marker_flag
	#print "\n\n"

	return (marker_lineno, marker_filename, marker_flag)







