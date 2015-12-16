#!/usr/bin/env python
FRAMEWORK_VERSION = 'CSeq-2014.09.27'
#FRAMEWORK_VERSION = 'CSeq-2014.06.02'
##FRAMEWORK_VERSION = 'CSeq-2014.02.28'

"""

Changelog:
	2014.09.27  moved all code-sanitising to merger stage (merger.py).
	2014.09.22  use strings rather than temporary files before merging (faster)
	2014.09.22  moved thread_local workaround to merging stage (merger.py)
	2014.06.02  introduced specific  module.ModuleError  exception for detailed error handling
	2014.02.28  major code refactory
	            error details from module->module transforms incl. source snippet
	            uniform module importing and handling through one main for loop

"""

import getopt, importlib, os.path, re, sys, time, traceback
from pycparser.plyparser import ParseError
import merger, module, parser, utils


''' Modules that will be executed,
    in this particular order.
'''
moduleNames = [ 'threadlocal', 'workarounds' , 'constants', 'switchconverter',
                'spinlook' , 'remover', 'errorlabel', 'extractor',
                'varnames', 'inliner', 'unroller', 'duplicator', 'labeler' ]

class cseqenvironment:
	threads = rounds = forunwind = whileunwind = 0
	errorlabel = format = ''


def usage(cmd, errormsg):
	print "Lazy-CSeq - C Sequentialiser (Oct. 2014)"
	print ""
	print "Usage: "
	print ""
	#print "   %s [-h] [--help]" % cmd
	print "   %s -i [input.c] [options]" % cmd
	print ""
	print " options: "
	print "   -h, --help                 display this help screen"
	print "   -v  --version              show version number"
	##print "   -l  --listmodules          show available modules, module-chains and version numbers for each of them"
	###print "   -D, --debug                debug mode"
	###print "   -S  --symbols              perform full merging, then print symbol table and then quit"
	###print "   -M  --modules              only list the modules then quit"
	###print "   -E  --exit <module>        show the output from module and quit"
	print ""
	print " instrumentation and other options:"
	print "   -i<file>, --input=<file>   input filename"
	#print "   -o<filename>, --output=<filename>  output filename"
	print "   -b<fmt>, --backend=<fmt>   backend (cbmc, esbmc, llbmc, klee, smack)"
	print "   -m, --mallocscanfail       malloc()s can return NULL (default: no)"
	print "   -e<X>, --error-label<X>    error label to check for reachability (default: ERROR)"
	print "   -s, --softunwindbound      full unroll definitely bounded loops (default: no)"
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

	if errormsg: print errormsg + '\n'
	sys.exit(1)


def main(args):
	cmd = args[0]

	try:
		shortargs = "hdi:o:b:t:u:f:F:w:r:e:DSME:vms"
		longargs = [ "help", "detail", "input=", "output=", "backend=", "threads=",
		             "unwind=", "for-unwind=", "for-max-unwind", "while-unwind=", "rounds=", "error-label=", 
		             "debug", "symbols", "modules", "exit=", "version", "mallocscanfail", "softunwindbound" ]
		opts, args = getopt.getopt(sys.argv[1:], shortargs, longargs)
	except getopt.GetoptError, err:
		usage(cmd, 'error: ' +str(err))

	inputfile = outputfile = ''

	# Set default conversion parameters
	format = 'cbmc'
	label = 'ERROR'
	threads = realthreads = 0  # this will grow, based on how many thread creations are found after inlining & unrolling
	forunwind = whileunwind = formaxunwind = None
	rounds = unwind = 1
	debug = detail = symbols = False
	mallocscanfail = False
	softforunwind = False
	exit = ''

	# Set conversion parameters & options from command-line
	for o, a in opts:
		if o in ("-v", "--version"): print FRAMEWORK_VERSION; return
		elif o in ("-h", "--help"): usage(cmd,'')
		elif o in ("-D", "--debug"): debug = True
		elif o in ("-M", "--modules"): print moduleNames; return
		elif o in ("-E", "--exit"): exit = a
		elif o in ("-S", "--symbols"): symbols = True
		elif o in ("-d", "--detail"): detail = True
		elif o in ("-i", "--input"): inputfile = a
		elif o in ("-o", "--output"): outputfile = a
		elif o in ("-b", "--backend"): format = a
		elif o in ("-t", "--threads"): threads = int(a)
		elif o in ("-f", "--for-unwind"): forunwind = int(a)
		elif o in ("-F", "--for-max-unwind"): formaxunwind = int(a)
		elif o in ("-w", "--while-unwind"): whileunwind = int(a)
		elif o in ("-u", "--unwind"): unwind = forunwind = whileunwind = int(a)
		elif o in ("-r", "--rounds"): rounds = int(a)
		elif o in ("-e", "--error-label"): label = a
		elif o in ("-m","--mallocscanfail"): mallocscanfail = True  # TODO
		elif o in ("-s", "--softunwindbound"): softforunwind = True
		else: assert False, "unhandled option"

	# Check parameters
	if inputfile == '': usage(cmd, 'error: input file name not specified')
	if not os.path.isfile(inputfile): usage(cmd, 'error: unable to open input file (%s)' % inputfile)
	if format not in ('esbmc', 'cbmc', 'llbmc', 'smack', 'satabs', 'blitz', 'klee'): usage(cmd, 'error: output format (%s) not supported' % format)
	if format == 'blitz': format = 'cbmc' # Blitz and CBMC need the same instrumentation
	if formaxunwind and not softforunwind: usage(cmd, "error: --for-max-unwind requires --softunwindbound")
	# TODO: if --unwind is given, there should be no --for-unwind nor --while-unwind

	cseqenvironment.threads = threads
	cseqenvironment.rounds = rounds
	cseqenvironment.forunwind = forunwind
	cseqenvironment.formaxunwind = formaxunwind
	cseqenvironment.softforunwind = softforunwind
	cseqenvironment.whileunwind = whileunwind
	cseqenvironment.unwind = unwind
	cseqenvironment.errorlabel = label
	cseqenvironment.format = format
	cseqenvironment.mallocscanfail = mallocscanfail

	transforms = 0  # no. of transformations (i.e. modules the original file has gone through) so far

	# Load the input file
	sourcecode = ''

	myfile = open(inputfile)
	lines = list(myfile)

	for line in lines:
		sourcecode += line

	# Merge all the source files into one string.
	#
	try:
		timeBefore = time.time()
		if debug: print "/* merger",
		Merger = merger.Merger()
		Merger.loadfromstring(sourcecode, cseqenvironment)
		sourcecode = Merger.string()
		transforms += 1
		if debug: utils.saveFile('___%s_%s.c' % (0,"merger"), sourcecode)
		if debug: print "ok %0.2fs */" % (int(time.time()) - int(timeBefore))
		if debug:
			if os.path.isfile("___0_merger.linemap"): os.remove("___0_merger.linemap")
			fd = os.open("___0_merger.linemap", os.O_RDWR|os.O_CREAT)

			for i in range(1, Merger.lastoutputlineno+1):
				if Merger.outputtoinput.has_key(i):
					os.write(fd, "%d %d\n" % (i, Merger.outputtoinput[i]))

	#exceptions.SystemExit TODO
	except ParseError as e:
		if debug: print "ERROR: %s */\n" % sys.exc_info()[0]
		print "Parse error (%s):\n" % str(e) 
		print "%s%s%s" % (utils.colors.YELLOW, utils.snippet(sourcecode, Merger.getLineNumber(e), Merger.getColumnNumber(e), 5, True), utils.colors.NO)
		sys.exit(1)
	except:
		print "ERROR: %s */\n" % sys.exc_info()[0]
		traceback.print_exc(file=sys.stdout)
		sys.exit(1)


	# Invoke the modules to perform one transformation at once.
	#
	for index, moduleName in enumerate(moduleNames):
		try:
			mod = importlib.import_module(moduleName)

			timeBefore = time.time()
			if debug: print "/* " + moduleName,
			func = getattr(mod, moduleName[0].upper()+moduleName[1:])
			m = func()

			# module-specific handling of the input
			m.loadfromstring(sourcecode, cseqenvironment)

			# right after workarounds the  Parser  can provide its full functionality
			if symbols and moduleName == 'constants': m.Parser.ast.show(); m.Parser.printsymbols(); return

			sourcecode = m.string()

			if debug: utils.saveFile('___%s_%s.marked.c' % (transforms,moduleName), sourcecode)

			m.generatelinenumbers()
			sourcecode = m.string()

			if debug: utils.saveFile('___%s_%s.c' % (transforms,moduleName), sourcecode)
			if debug: print "[%s] ok %0.2fs */" % (transforms, int(time.time()) - int(timeBefore))
			if debug: 
				if os.path.isfile("___%s_%s.linemap" % (transforms,moduleName)): 
					os.remove("___%s_%s.linemap" % (transforms,moduleName)) 

				fd = os.open("___%s_%s.linemap" % (transforms,moduleName), os.O_RDWR|os.O_CREAT)

				print "lines: %s" % m.lastoutputlineno

				for i in range(1,m.lastoutputlineno+1):
					if m.outputtoinput.has_key(i):
						os.write(fd, "%d %d\n" % (i, m.outputtoinput[i]))

			transforms += 1
		except ParseError as e:
			print "\nParse error (%s) while performing %s->%s:\n" % (str(e), moduleNames[index-1] if index>0 else '', moduleName)
			print "%s%s%s" % (utils.colors.YELLOW, utils.snippet(sourcecode, Merger.getLineNumber(e), Merger.getColumnNumber(e), 5, True), utils.colors.NO)
			sys.exit(1)
		except module.ModuleError as e:
			print "Module error (%s) while performing %s->%s.\n" % (str(e), moduleNames[index-1] if index>0 else '', moduleName)
			sys.exit(1)
		except KeyboardInterrupt as e:
			#print "\nInterrupted by user.\n" 
			sys.exit(1)
		except ImportError as e:
			print "Import error (%s),\nplease re-install the tool.\n" % str(e) 
			sys.exit(1)
		except:
			print "\nError while performing %s->%s:\n" % (moduleNames[index-1] if index>0 else '', moduleName)
			#print "ERROR: %s */\n" % sys.exc_info()[0]
			traceback.print_exc(file=sys.stdout)
			print "\n\n parsing coords: <%s>" % (m.Parser.currentInputCoord)
			sys.exit(1)

	print utils.strip(sourcecode)


if __name__ == "__main__":
	main(sys.argv[0:])
