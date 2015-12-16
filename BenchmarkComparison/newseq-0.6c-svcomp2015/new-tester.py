#!/usr/bin/env python
"""

	CSeq-Tester:  C Sequentialiser benchmark tester.
	
				  This small script runs  cseq-feeder.py  on all the files at the given path.
				 (please try  ./cseq-tester.py  for a complete list of options).


"""
import utils
import os, sys, getopt, subprocess, shlex
from time import gmtime, strftime


def usage(cmd):
	print "CSeq-tester:   verification front-end for multi-thread C code based on CSeq\n"
	print "Usage:"
	print "   -h, --help	             display this help screen\n"
	print "   -p<path>, --path=path      read test cases from the given path"
	print "   -T<X>, --timelimit<X>      timeout to kill the backend (in seconds, default: no limit)\n"
	print "   -M<X>, --memorylimit<X>    timeout to kill the backend (in MBytes, default: no limit)\n"
	print "   -b<fmt>, --backend=<fmt>   backend tool to use (std, esbmc, cbmc or llbmc)"
	print "   -t<X>, --threads<X>        set maxthread for the sequentialisation (default: no bound)"
	print "   -r<X>, --rounds<X>         set maxround for the sequentialisation (default: 1)"
	print "   -u<X>, --unwind<X>         set max loop unwind (default: 1, overrides all other unwind setting)"
	print "   -f<X>, --for-unwind<X>     set max for loop unwind when no max can be calculated (default: 1)"
	print "   -F<X>, --for-unwind-max<X> set max for loop unwind when max can be calculated (needs -s, default: not used)"
	print "   -s, --softunwindbound      soft unwind bound for option (enables extra -F loop bound, default: disabled)"
	print "   -w<X>, --while-unwind<X>   set max while loop unwind (default: 1)"
	print "   -d<X>, --depth<X>          set depth parameter for the backend (not used for the translation, default: no bound)"
	print "   -S, --skip                 test on original file (do not sequentialize)"
	print "   example:  %s -p benchmarks_set1 -t3 -r6 -u25 -b esbmc\n" % cmd


def getbackendtime(searchstring, filename):
	if not os.path.isfile(filename): return '-1';

	for line in open(filename):
		if searchstring in line:
		   return line[:line.rfind(searchstring)].replace(' ', '')

	return '-1'
	

def getbackendspace(filename):
	if not os.path.isfile(filename): return '-1';

	for line in open(filename):
		if 'peak' in line:
		   return line[:line.rfind('peak')].replace(' ', '')

	return '-1'


''' Check whether the given string appears as a substring in at least one line of the given file.
'''
def check(filename, string):
	if not os.path.isfile(filename): return False

	for line in open(filename):
		if string in line:
			print '  ' + line,
			return True

	return False


def main(args):
	''' 1. Check command-line options
	'''
	"""
	if (len(args) != 2):
		print "\nThis script is to generate C sequentialisations for all C files in the given directory\n"
		print "and then verify them using ESBMC.\n" 
		print "The input file  'filename.c'  will generate  'out_filename.c'."
		print "Only the '.c' files from the given directory will be considered.\n"
		print "Usage: %s <path-to-c-files>\n\n" % cmd
		return
	"""

	cmd = args[0]

	try:
		opts, args = getopt.getopt(sys.argv[1:], "hp:b:u:f:w:t:r:T:M:d:SsF:", ["help", "path=", "backend=", "unwind=", "for-unwind=", "while-unwind=", "threads=", "rounds=", "timelimit=", "memorylimit=", "depth=", "skip", "softunwindbound", "for-max-unwind="])
	except getopt.GetoptError, err:
		# print help information and exit:
		usage(cmd)
		print "error: " +str(err) # will print something like "option -a not recognized"
		sys.exit(2)

	dontsequentialise = softforunwind = False
	inputpath = ''	
	seconds = memorylimit = threads = 0
	rounds = 1
	depth = 0
	unwind = forunwind = forunwindmax = whileunwind = -1
	format = 'cbmc'

	for o, a in opts:
		if o == "-v": verbose = True
		elif o in ("-h", "--help"): usage(cmd); sys.exit()
		elif o in ("-S", "--skip"): dontsequentialise = True
		elif o in ("-p", "--path"): inputpath = a
		elif o in ("-b", "--backend"): format = a
		elif o in ("-f", "--for-unwind"): forunwind = a
		elif o in ("-w", "--while.unwind"): whileunwind = a
		elif o in ("-u", "--unwind"): unwind = a
		elif o in ("-t", "--threads"): threads = int(a)
		elif o in ("-r", "--rounds"): rounds = int(a)
		elif o in ("-T", "--timelimit"): seconds = int(a)
		elif o in ("-M", "--memorylimit"): memorylimit = int(a)
		elif o in ("-d", "--depth"): depth = int(a)
		elif o in ("-s", "--softunwindbound"): softforunwind = True
		elif o in ("-F", "--for-max-unwind"): forunwindmax = a
		else: assert False, "unhandled option"

	# Validation of command-line parameters
	if inputpath == '':
		usage(cmd)
		print "error: path for input test cases not specified\n"
		sys.exit(2)

	if not os.path.isdir(inputpath):
		usage(cmd)
		print "error: the given path (%s) for input test cases does not exist\n" % inputpath
		sys.exit(2)

	if format not in ('std', 'esbmc', 'cbmc', 'llbmc', 'cpachecker', 'smack'):
		usage(cmd)
		print "error: output format (%s) not supported\n" % format
		sys.exit(2)

	# Set default values if needed
	if forunwindmax != -1 and not softforunwind:
		usage(cmd)
		print "error:  --for-max-unwind  parameter only works with  --softunwindbound\n"
		sys.exit(2)

	if seconds == 0: seconds = 3600

	if unwind == -1 and (forunwind == -1 or whileunwind == -1):
		usage(cmd)
		print "error: either  --unwind  or both  --for-unwind  and  --while-unwind  parameters must be provided\n"
		sys.exit(2)

	if inputpath.endswith('/'): directory = inputpath[:-1]
	else: directory = inputpath

	# print "path: " + "./"+directory.rsplit('/', 1)[0]

	# if directory not in os.listdir("./"+directory.rsplit('/', 1)[0]):
	#	print "The path  '%s'  cannot be reached from the current path.\n" % directory
	#	return

	# delete the old files from the previous sequentialisation
	logfilename = directory + '.' + format + ".csv"

	os.system('rm ' + directory + '/_cs_* 2> /dev/null')
	os.system('rm ' + inputpath + '/*strip* 2> /dev/null')

	os.system('mv ' + logfilename +' '+ logfilename+'.old 2> /dev/null')
	fd = os.open( logfilename, os.O_RDWR|os.O_CREAT )


	''' 2. Verifying files...
	'''
	current = howmany = correcttrue = correctfalse = missedbugs = falsepositives = unknowns = timeouts = 0
	overalltime = 0

	for file in sorted(os.listdir(inputpath)):
		if file.endswith('.i'): howmany = howmany +1

	print '\nverifying  %s  files in  %s/*.i \n' % (howmany, directory)

	parameters = " -t%s -r%s -b%s -d%s -M%s -T%s" % (threads, rounds, format, depth, memorylimit, seconds)

	if unwind != -1: parameters += ' -u'+str(unwind)
	if forunwind != -1: parameters += ' -f'+str(forunwind)
	if forunwindmax != -1: parameters += ' -F'+str(forunwindmax)
	if whileunwind != -1: parameters += ' -w'+str(whileunwind)
	if dontsequentialise == True: parameters += " -S"
	if softforunwind: parameters += ' -s'
	
	os.write(fd, "parameters: %s\n\n" % parameters);

	for file in sorted(os.listdir(inputpath)):
		if file.endswith('.i'):
			print "%s%s/%s, " %(' '*(len(str(howmany-1)) - len(str(current))), current, howmany-1),
			current = current +1
			filename = directory+'/'+file
			logfilename = filename+'.log'

			cmdline = "./new-feeder.py -i %s %s > %s" % (filename, parameters, logfilename)

			print file,

			p = subprocess.Popen(shlex.split(cmdline), stdout=subprocess.PIPE)
			out, err = p.communicate()
			out = out.replace(utils.colors.BLINK, '')
			out = out.replace(utils.colors.GREEN, '')
			out = out.replace(utils.colors.DARKRED, '')
			out = out.replace(utils.colors.RED, '')
			out = out.replace(utils.colors.BLACK, '')
			out = out.replace(utils.colors.NO, '')

			if (('_safe' in file or '_true' in file or '-true' in file) and 'TRUE' in out):
				checkTrueFalse = utils.colors.GREEN + 'PASS' + utils.colors.NO
				correcttrue = correcttrue +1
			elif ('_unsafe' in file or '_false' in file and 'FALSE' in out):
				checkTrueFalse = utils.colors.GREEN + 'PASS' + utils.colors.NO
				correctfalse = correctfalse +1
			elif (('_safe' in file or '_true' in file) and 'FALSE' in out):
				checkTrueFalse = utils.colors.RED + utils.colors.BLINK + 'FALSE POSITIVE' + utils.colors.NO
				falsepositives = falsepositives +1
			elif (('_unsafe' in file or '_false' in file) and 'TRUE' in out):
				checkTrueFalse = utils.colors.DARKRED + 'MISSED' + utils.colors.NO
				missedbugs = missedbugs +1
			elif ('TIMEOUT' in out):
				checkTrueFalse = utils.colors.YELLOW + 'TIMEOUT' + utils.colors.NO
				timeouts = timeouts +1
			else:
				checkTrueFalse = utils.colors.YELLOW + 'UNKNOWN' + utils.colors.NO
				unknowns = unknowns +1

			print ',' +out[out.find(', ')+1:][:-1] + ', ' + checkTrueFalse,

			###new_csv_entry = file +', '+ memory +', '+ tottime +', '+ backendtime +', '+ preprocesstime +', '+ finished +', '+ success +', '+ checkTrueFalse + '\n'
			###os.write(csv_fd, new_csv_entry)

			lasttime = out[out.rfind(', ')+2:][:-1]
			overalltime += float(lasttime)
			print ''

	print ''
	print "total test cases ... %s (from %s)" % (howmany, directory)
	print "correct analysis ... %s (%s true + %s false)" % ((howmany - (falsepositives+missedbugs+unknowns)), correcttrue, correctfalse)
	print "false positives .... %s" % falsepositives
	print "missed bugs ........ %s" % missedbugs
	print "timeouts ........... %s" % timeouts
	print "unknowns ........... %s" % unknowns
	print ''
	print 'elapsed time ....... %ss' % overalltime
	print ''


if __name__ == '__main__':
	import sys
	main(sys.argv[0:])
