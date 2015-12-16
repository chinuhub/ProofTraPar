#!/usr/bin/env python
VERSION = 'feeder-2014.09.25'   # removed the 3rd party timeout tool (due to portability issues, especially not working well on OSX despite the latest fixes available around)
                                # new timeout mechanism embedded in CSeq implemented from scratch using python multithread+subprocess management
#VERSION = 'feeder-2014.09.21'   # minor front-end adjustments
#VERSION = 'feeder-2014.06.03'   # front-end adjustments: default output is now more compact, for old-style output use -v 
#VERSION = 'feeder-2014.03.10'

"""

	CSeq-feeder:  C Sequentialiser front-end for the ESBMC/CBMC/LLBMC/.. verifiers.
                 
                 (Jun 2014: removed command-line redirection - switched from  os.system  to  subprocess.open)
                 (Jun 2014: moved common ancilliary functions to utils.py)
                 (Mar 2014: time and memory limits)
                 (May 2013: detecting insufficient maxthread parameter, CBMC-only)
				 (Jan 2013: fine-tuning of back-end options, --skip option)
				 (Dec 2012: last version to handle multiple back-end rather than ESBMC only)
			  	 (Nov 2012: extended version to handle .i preprocessed files in addition to .c files)

				  This small script runs  CSeq  on the given input file,
				  saves its sequentialised version and then 
				  feeds it to the specified tool to perform verification.
				 (please try  ./cseq-feeder.py  for a complete list of options).

TODO:
	- when memory/time limits are hit, the feeder must report UNKNOWN
	- fix memory peak calculation
	- fix LLBMC support
	- handle exception CalledProcessError 

"""

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

                  Options & parameters below. 

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
# Name of the executable file to run, by backend.
backendFilename = {}
backendFilename['esbmc'] = 'esbmc'
backendFilename['cbmc'] = './cbmc'
backendFilename['blitz'] = 'blitz'
backendFilename['llbmc'] = 'llbmc'
backendFilename['smack'] = 'smack-verify.py'
backendFilename['satabs'] = 'satabs'
backendFilename['klee'] = 'klee'

# Command-line parameters, by backend.
cmdLineOptions = {};
cmdLineOptions['esbmc'] = ' --no-slice --no-bounds-check --no-div-by-zero-check --no-pointer-check --unwind 1 --no-unwinding-assertions ' # cmdLineOptions['esbmc'] = ' --no-slice --no-bounds-check --no-div-by-zero-check --no-pointer-check --unwind 1 --no-unwinding-assertions --z3-ir '
cmdLineOptions['cbmc'] = '  --unwind 1 --no-unwinding-assertions '
cmdLineOptions['blitz'] = '  --terminate-on-firstbug '
cmdLineOptions['llbmc'] = ' -no-max-function-call-depth-checks -no-memory-free-checks -no-shift-checks -no-memcpy-disjoint-checks -no-memory-access-checks -no-memory-allocation-checks --max-loop-iterations=1 --no-max-loop-iterations-checks --ignore-missing-function-bodies -no-overflow-checks -no-div-by-zero-checks'
cmdLineOptions['smack'] = ' --unroll 1 '
cmdLineOptions['satabs'] = ' '
cmdLineOptions['klee'] = ' '

# Command-line parameters, by backend - when no sequentialisation is performed.
cmdLineOptionsNOSEQ = {};
cmdLineOptionsNOSEQ['esbmc'] = ' --no-slice --no-bounds-check --no-div-by-zero-check --no-pointer-check --z3-ir '
cmdLineOptionsNOSEQ['cbmc'] = '  '
cmdLineOptionsNOSEQ['llbmc'] = ' -no-max-function-call-depth-checks -no-memory-free-checks -no-shift-checks -no-memcpy-disjoint-checks -no-memory-access-checks -no-memory-allocation-checks --ignore-missing-function-bodies -no-overflow-checks -no-div-by-zero-checks '
cmdLineOptionsNOSEQ['smack'] = ' '
cmdLineOptionsNOSEQ['satabs'] = ' '
cmdLineOptionsNOSEQ['klee'] = ' '

# Expressions to check for from the log to see whether verification went fine.
verificationOK = {}
verificationOK['esbmc'] = 'VERIFICATION SUCCESSFUL\n'
verificationOK['cbmc'] = 'VERIFICATION SUCCESSFUL\n'
verificationOK['blitz'] = 'VERIFICATION SUCCESSFUL\n'
verificationOK['llbmc'] = 'No error detected.\n'
verificationOK['cpachecker'] = 'Verification result: SAFE. No error path found by chosen configuration.\n'
verificationOK['smack'] = 'Finished with 1 verified, 0 errors\n'
verificationOK['satabs'] = 'VERIFICATION SUCCESSFUL\n'
verificationOK['klee'] = 'DKJFHSDKJDFHSJKF\n' # no such thing for Klee?

# Expressions to check for from the log to check whether verification failed.
verificationFAIL = {}
verificationFAIL['esbmc'] = 'VERIFICATION FAILED\n'
verificationFAIL['cbmc'] = 'VERIFICATION FAILED\n'
verificationFAIL['blitz'] = 'VERIFICATION FAILED\n'
verificationFAIL['llbmc'] = 'Error detected.\n'
verificationFAIL['cpachecker'] = 'Verification result: UNSAFE. Error path found by chosen configuration.\n' #verificationFAIL['smack'] = 'Error BP5001: This assertion might not hold.\n'
verificationFAIL['smack'] = 'Finished with 0 verified,'
verificationFAIL['satabs'] = 'VERIFICATION FAILED\n'
verificationFAIL['klee'] = 'ASSERTION FAIL: '


'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

                  Nothing to set past this point.

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
import os, sys, getopt, time, signal, subprocess, shlex
from time import sleep, gmtime, strftime
from threading import Timer

import utils


def usage(cmd, errormsg=''):
	print "CSeq-Feeder - back-end wrapper for CSeq (Oct. 2014)"
	print ""
	print "Usage: "
	print ""
	#print "   %s [-h] [--help]" % cmd
	print "   %s -i [input.c] [options]" % cmd
	print ""
	print " options: "
	print "   -h, --help                 display this help screen"
	print "   -v  --version              show version number"
	print ""
	print " debug options"
	print "   -C, --cex                  output counterexample from the backend"
	print "   -S, --skip                 do not sequentialize: analyse original file"
	print "   -V, --verbose              display extra information"
	print ""


	print " instrumentation and other options:"
	print "   -i<file>, --input=<file>   input filename"
	#print "   -o<filename>, --output=<filename>  output filename"
	print "   -b<fmt>, --backend=<fmt>   backend (cbmc, esbmc, llbmc, klee, smack)" # TODO: divide by category: bounded model-checkers, abstraction-based, ...
	print "   -m, --mallocscanfail       malloc()s can return NULL (default: no)"
	print "   -e<X>, --error-label<X>    error label to check for reachability (default: ERROR)"
	print "   -s, --softunwindbound      full unroll definitely bounded loops (default: no)"
	print "   -d<X>, --depth<X>          backend depth bound (if supported, default: no bound)"
	print ""
	print " unwind bounds:"
	print "   -u<X>, --unwind<X>         all loops (default: 1)"
	print "   -w<X>, --while-unwind<X>   potentially unbounded loops (default: 1)"
	print "   -f<X>, --for-unwind<X>     potentially bounded loops (default: 1)"
	print "   -F<X>, --for-unwind-max<X> definitely bounded loops (requires -s, default: no bound)"
	print ""
	print " other bounds:"
	print "   -t<X>, --threads<X>        max number of threads (default: auto)"
	print "   -r<X>, --rounds<X>         number of round-robin schedules (default: 1)"
	print ""
	#print "   -s, --spec<specfile>       SV-COMP 2014 specfile"
	#print "   -W, --witness<logfile>     SV-COMP 2014 counterexample output file"
	#print ""
	print " back-end resource limits:"
	print "   -T, --timelimit<X>         time limit (in seconds, default: 3600)"
	print "   -M, --memorylimit<X>       memory limit (in megabytes, default: no limit)"
	print ""
	print ""

	if errormsg: print errormsg + '\n'
	sys.exit(1)


def geterrorlabel(specfile):
	error_label = 'ERROR'  # default error label

	inp = open(specfile,"r")

	for line in inp.readlines():
		i_label = line.find("label")

		if i_label>=0:
			line = line[i_label:]
			i_label = line.find("(",)
			line = line[i_label+1:]
			i_label = line.find(")",)
			error_label = line[:i_label]

	inp.close()
	return error_label


def printStats(file,result,time):
	if result == 'UNKNOWN': result = utils.colors.YELLOW + result + utils.colors.NO
	elif result == 'TRUE': result = utils.colors.GREEN + result + utils.colors.NO
	elif result == 'FALSE': result = utils.colors.RED + result + utils.colors.NO

	print "%s, %s, %0.2f" % (file, result, time)


def main(args):
	realstarttime = time.time()    # save wall time

	''' 1. Check command-line options
	'''
	cmd = args[0]

	try:
		opts, args = getopt.getopt(sys.argv[1:], "hd:Ci:b:u:f:F:w:t:r:e:W:T:M:SVs", ["help", "depth=", "cex", "input=", "backend=", "unwind=", 
			                                                                         "for-unwind=", "for-max-unwind=", "while-unwind=", "threads=", "rounds=", "spec=",
			                                                                         "witness=", "timelimit=", "memorylimit=", "skip", "verbose", "softunwindbound"])
	except getopt.GetoptError, err:
		usage(cmd, "error: " +str(err))
		sys.exit(2)

	inputfile = seconds = witness = ''
	unwind = forunwind = whileunwind = rounds = 1
	forunwindmax = -1
	threads = depth = 0
	timelimit = 3600
	memorylimit = 0
	label = 'ERROR'
	outputcounterexample = donotsequentialize = verbose = softforunwind = False
	format = 'cbmc'

	for o, a in opts:
		if o in ("-h", "--help"): usage(cmd,''); sys.exit()
		elif o in ("-V", "--verbose"): verbose = True
		elif o in ("-d", "--depth"): depth = int(a)
		elif o in ("-C", "--cex"): outputcounterexample = True
		elif o in ("-i", "--input"): inputfile = a
		elif o in ("-b", "--backend"): format = a
		elif o in ("-f", "--for-unwind"): forunwind = int(a)
		elif o in ("-F", "--for-max-unwind"): forunwindmax = int(a)
		elif o in ("-s", "--softunwindbound"): softforunwind = True
		elif o in ("-w", "--while-unwind"): whileunwind = int(a)
		elif o in ("-u", "--unwind"): unwind = forunwind = whileunwind = int(a)
		elif o in ("-t", "--threads"): threads = int(a)
		elif o in ("-r", "--rounds"): rounds = int(a)
		elif o in ("-W", "--witness"): witness = a   # SV-COMP'14
		elif o in ("-T", "--timelimit"): timelimit = int(a)
		elif o in ("-M", "--memorylimit"): memorylimit = int(a)
		elif o in ("-S", "--skip"): donotsequentialize = True
		elif o in ("-e", "--spec"):
			spec = a
			if not os.path.isfile(spec): usage(cmd, 'error: unable to open spec file (%s)' % spec)
			label = geterrorlabel(spec)
		else: assert False, "unhandled option"

	if inputfile == '':
		usage(cmd,'')
		print "error: input file name not specified\n"
		sys.exit(2)

	# set default values if needed
	if unwind == -1 and (forunwind == -1 or whileunwind == -1):
		usage(cmd, "error: either  --unwind  or both  --for-unwind  and  --while-unwind  parameters must be provided")
		sys.exit(2)

	if forunwindmax != -1 and not softforunwind:
		usage(cmd, "error: --for-max-unwind requires  --softunwindbound")
		sys.exit(2)

	# tool configuration/installation/integrity check (TODO)
	if not os.path.isfile(backendFilename[format]):
		usage(cmd, "error: unable to find the given backend (%s)" % backendFilename[format] )
		sys.exit(2)

	''' 1'. Intermediate step - if the filename ends with .i, then the file has to be stripped
								and transformed back into a .c file in order to get properly
								parsed with PYCparser 
	'''
	seqfile = utils.rreplace(inputfile, '/', '/_cs_', 1) if '/' in inputfile else '_cs_' + inputfile
	oldinputfile = inputfile

	(filestripped, contents) = utils.stripIfNeeded(inputfile)

	if filestripped:
		inputfile = inputfile[:-2] + '.strip.c'
		utils.saveFile(inputfile, contents)

	logfilename = seqfile + '.' +format +'.log' if witness == '' else witness


	''' 2. Call CSeq and save the sequentialised file as '_cs_.....'
	'''
	if donotsequentialize == False:
		if verbose: print ("\ninput:  %s") % (inputfile)

		cmdline = './new.py -i%s -t%s -r%s -b%s -e%s' % (str(inputfile), str(threads), str(rounds), format, label)

		if unwind != -1: cmdline += ' -u'+str(unwind)
		if forunwind != -1: cmdline += ' -f'+str(forunwind)
		if forunwindmax != -1: cmdline += ' -F'+str(forunwindmax) 
		if whileunwind != -1: cmdline += ' -w'+str(whileunwind)
		if softforunwind: cmdline += ' -s'

		if seqfile.endswith('.i'): seqfile = seqfile[:-2] + '.c'

		p = subprocess.Popen(shlex.split(cmdline), stdout=subprocess.PIPE)
		out, err = p.communicate()
		cseqanswer = p.returncode

		utils.saveFile(seqfile, out)

		if verbose: print "cmd:    " + cmdline

		''' now check that the sequentialisation went fine '''
		if cseqanswer != 0:
			if verbose: print "\n       (unable to sequentialise input file  -  see below for details)\n"
			if verbose: print utils.colors.BLACK + '- '*32

			with open(seqfile) as file:
				data = file.read()
				print data,

			if verbose: print utils.colors.BLACK + '- '*32 + utils.colors.NO + '\n'
			if verbose: print utils.colors.YELLOW + "        UNKNOWN\n" + utils.colors.NO
			printStats(seqfile,'REJECT',-1)
			sys.exit(-1)
	else:
		seqfile = oldinputfile

		cmdLineOptionsNOSEQ['esbmc'] += ' --unwind %s --no-unwinding-assertions --error-label ERROR  ' % unwind
		cmdLineOptionsNOSEQ['cbmc'] += ' --unwind %s --no-unwinding-assertions --error-label ERROR '  % unwind
		cmdLineOptionsNOSEQ['llbmc'] += ' --max-loop-iterations=%s --no-max-loop-iterations-checks '  % unwind
		cmdLineOptionsNOSEQ['smack'] += ' '
		cmdLineOptionsNOSEQ['satabs'] += ' '

		cmdLineOptions[format] = cmdLineOptionsNOSEQ[format]


	''' 3. Run the verification tool (from the command-line option -b) on the sequentialised file
	'''
	if verbose: print "output: %s" % (seqfile)
	
	timeBeforeCallingBackend = time.time()    # save wall time

	if format == 'esbmc':
		cmdline =  backendFilename[format] + cmdLineOptions[format] + seqfile
		if depth != 0: cmdline += ' --depth %s ' % str(depth)
	elif format == 'cbmc':
		cmdline = backendFilename[format] + cmdLineOptions[format] + seqfile
		if depth != 0: cmdline += ' --depth %s ' % str(depth)
	elif format == 'blitz':
		cmdline = backendFilename[format] + cmdLineOptions[format] + seqfile
		if depth != 0: cmdline += ' --depth %s ' % str(depth)
	elif format == 'llbmc': # TODO LLBMC support is broken
		cmdline = "clang -c -g -I. -emit-llvm %s -o %s.bc 2> %s " % (seqfile, seqfile[:-2], logfilename)
		p = subprocess.Popen(shlex.split(cmdline), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		cmdline = backendFilename[format] + ' ' + cmdLineOptions[format] + ' ' + seqfile[:-2] +'.bc'
	elif format == 'cpachecker':
		options = ' -predicateAnalysis  -spec ErrorLabel.spc '
		cmdline = 'scripts/cpa.sh ' + options + seqfile
	elif format == 'smack':
		cmdline = backendFilename[format] + cmdLineOptions[format] + seqfile
	elif format == 'satabs':
		cmdline = backendFilename[format] + cmdLineOptions[format] + seqfile
	elif format == 'klee':
		cmdline = "clang -c -g -emit-llvm %s -o %s.bc " % (seqfile, seqfile[:-2])
		#cmdline = backendFilename[format] + ' ' + cmdLineOptions[format] + ' ' + seqfile[:-2] +'.bc'
		#print "CLANG: %s" % cmdline
		p = subprocess.Popen(shlex.split(cmdline), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		out, err = p.communicate()
		utils.saveFile('clang_stdout.log', out)
		utils.saveFile('clang_stderr.log', err)
		cmdline = backendFilename[format] + ' ' + cmdLineOptions[format] + ' ' + seqfile[:-2] +'.bc'

	# handling of memory and time restrictions
	#
	# `-t T` - set up CPU+SYS time limit to T seconds
	# `-m M` - set up virtual memory limit to M kilobytes
	'''
	memorylimit = 1000*memorylimit # kBytes --> mBytes
	timespacecheck = 'timeout/timeout' 
	if timelimit > 0: timespacecheck += ' -t %s' % (timelimit)
	if memorylimit > 0: timespacecheck += ' -m %s' % (memorylimit)
	'''

	if verbose: print "log:    %s\n" % (logfilename)
	if verbose: print "cmd:    " + cmdline
	if verbose: print "start:  %s\n" % (strftime("%Y-%m-%d %H:%M:%S", gmtime()))

	command = utils.Command(cmdline)
	out, err, code = command.run(timeout=timelimit)   # store stdout, stderr, process' return value

	if format != 'klee': utils.saveFile(logfilename, out)   # klee outputs errors to stdout, all other backends to stderr
	else: utils.saveFile(logfilename, err)

	# report analysis details
	if os.path.isfile(logfilename):
		myfile = open(logfilename)
		backendAnswer = list(myfile)

		outcome = ''
		mem = maxmem = cpu = stale = variables = clauses = 0

		for line in backendAnswer:
			''' old wrapper for  timeout/timeout  tool
			if ('MEM CPU ' in line or 'HANGUP CPU ' in line or 'TIMEOUT CPU ' in line or 'SIGNAL CPU ' in line or 'FINISHED CPU ' in line):
				# example output from timeout tool:
				# SIGNAL CPU 4.90 MEM 84596 MAXMEM 84596 STALE 0
				line = line[line.find('CPU '):]
				splitline = line.split()
				cpu = splitline[1]
				mem = splitline[3]
				maxmem = splitline[5]
				stale = splitline[7]
			'''
			if ' variables, ' in line:
				splitline = line.split()
				variables = splitline[0]
				clauses = splitline[2]

		# this works only with CBMC and ESBMC,
		# example: 2174 variables, 5558 clauses
		backendtime = time.time() - timeBeforeCallingBackend
		overalltime = time.time() - realstarttime

		if verbose: 
			print "size:   %s variables" % variables
			print "        %s clauses" % clauses
			print ""
			print "space:  %s " % mem
			print "        %s peak" % maxmem
			print ""
			print "time:   %0.2fs preprocess" % (timeBeforeCallingBackend - realstarttime)
			print "        %0.2fs backend" % (backendtime)
			print "        %0.2fs overall" % (overalltime)
			print ""

			if 'warning' in err:
				print utils.colors.YELLOW + "       (warnings on stderr from the backend)" + utils.colors.NO

		# scan the backend's output to check the outcome of the verification
		for line in backendAnswer:
			if verificationFAIL[format] in line:
				if verbose: print utils.colors.RED + "        FALSE" + utils.colors.NO
				outcome = 'FALSE'
				break
			elif verificationOK[format] in line:
				if verbose: print utils.colors.GREEN + "        TRUE" + utils.colors.NO 
				outcome = 'TRUE'	
				break

		if outcome == '' and code == -9:  # backend killed due to timeout
			if verbose: print utils.colors.YELLOW + "        TIMEOUT" + utils.colors.NO
			outcome = 'TIMEOUT'

		if outcome == '':
			if verbose: print utils.colors.YELLOW + "        UNKNOWN" + utils.colors.NO
			outcome = 'UNKNOWN'

		if verbose: print ''

		if not verbose:
			printStats(inputfile,outcome,overalltime)


	if outputcounterexample:
		with open(logfilename) as file:
			data = file.read()
			print data


if __name__ == '__main__':
	import sys
	main(sys.argv[0:])





