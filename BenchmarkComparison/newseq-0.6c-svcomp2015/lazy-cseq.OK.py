#!/usr/bin/env python
'''
	Lazy-CSeq
	SV-COMP 2014 wrapper script

	October 2014  SV-COMP 2015 VERSION
	November 2013  original version

'''


import sys, getopt, os.path, shlex, subprocess, time
import utils


svcompparams = []
svcompparams = []
svcompparams.append('-M10000 -T200 -f1 -s -F50 -w1 -r2 -d800 -bcbmc ')  
svcompparams.append('-M10000 -T600 -f2 -w2 -r2 -d200 -bcbmc')  # -130>140 pthread-ext/buggy-simple.c;  140>160 pthread-ext/25_stack_false_longer.c
svcompparams.append('-M10000 -T250 -f4 -w4 -r1 -d145 -bcbmc')
svcompparams.append('-M10000 -T100 -f16 -w1 -r1 -d350 -bcbmc')
svcompparams.append('-M10000 -T600 -f11 -w1 -r11 -d300 -bcbmc') 
#svcompparams.append('-t0 -f2 -w2 -r2 -bcbmc')
#svcompparams.append('-t0 -f4 -w4 -r1 -bcbmc')
#svcompparams.append('-t0 -f16 -w1 -r1 -bcbmc')
#svcompparams.append('-t0 -f11 -w1 -r11 -bcbmc')

def usage(cmd, errormsg):
	print "Lazy-Cseq SV-COMP wrapper script,  October 2014\n"

	print " Usage:"
	print "   -h, --help                            display this help screen"
	print ""
	print "   -i<filename>, --input=<filename>      read input from the filename"
	print "   -s<specfile>, --spec=<specfile>       SV-COMP 2014 specfile (default:ALL.spc)"
	print "   -w<logfile>, --witness=<logfile>      SV-COMP 2014 counterexample output file (default:a.log)"

	print '\n' + errormsg + '\n'
	sys.exit(1)


def main(args):
	realstarttime = time.time()    # save wall time

	cmd = args[0]

	#
	try:
		opts, args = getopt.getopt(sys.argv[1:], "hi:s:w:", ["help", "input=", "spec=", "witness="])
	except getopt.GetoptError, err:
		print "error"
		usage(cmd, 'error: ' +str(err))

	inputfile = spec = witness = ''

	#
	for o, a in opts:
		if o == "-v": verbose = True
		
		elif o in ("-h", "--help"): usage(cmd)
		elif o in ("-w", "--witness"): witness = a
		elif o in ("-s", "--spec"): spec = a
		elif o in ("-i", "--input"): inputfile = a

		else: assert False, "unhandled option"

	# Check parameters
	if inputfile == '':
		#usage(cmd, 'error: input file name not specified')
		print 'error: input file name not specified'
		exit(1)

	if not os.path.isfile(inputfile):
		#usage(cmd, 'error: unable to open input file (%s)' % inputfile)
		print 'error: unable to open input file (%s)' % inputfile
		exit(1)

	if spec == '': spec = 'ALL.spc'

	if not os.path.isfile(spec):
		#usage(cmd, 'error: unable to open spec file (%s)' % spec)
		print 'error: unable to open spec file (%s)' % spec
		exit(1)

	if witness == '':
		#usage(cmd, 'error: witness file not specified')
		witness = 'a.log'

	print inputfile+', ',

	#
	last = '' 

	for params in svcompparams:
		cmdline = './new-feeder.py  %s  --input %s  --spec %s  --witness %s ' % (params, inputfile, spec, witness)
		#print "%s\n" %cmdline
		if last == 'FALSE':
			print "0.00, O,  ",
			continue

		try: 
			p = subprocess.Popen(shlex.split(cmdline), stdout=subprocess.PIPE)
			out, err = p.communicate()
			out = out.replace(utils.colors.BLINK, '')
			out = out.replace(utils.colors.GREEN, '')
			out = out.replace(utils.colors.DARKRED, '')
			out = out.replace(utils.colors.RED, '')
			out = out.replace(utils.colors.BLACK, '')
			out = out.replace(utils.colors.NO, '')

			lasttime = float(out[out.rfind(', ')+2:][:-1])

			str = '%2.2f,' % float(lasttime)
			print str,

			if 'FALSE' in out:
				last = 'FALSE'
				print 'F,  ',
				#break
				continue
			elif 'TRUE' in out: last = 'TRUE'; print 'T,  ',
			elif 'TIMEOUT' in out: last = 'TRUE'; print 'X,  ',
			else: last = 'UNKNOWN'; print 'U, ',

		except subprocess.CalledProcessError, err:
			last = 'UNKNOWN'; print 'U,  ',
			continue


	# Check that the filename matches verification outcome.
	verdict = utils.colors.YELLOW +'--'+ utils.colors.NO

	if last != 'UNKNOWN':
		if ('_false' in inputfile or '_unsafe' in inputfile) and last == 'TRUE':
			verdict = utils.colors.RED +'ko'+ utils.colors.NO
		elif ('_true' in inputfile or '_safe' in inputfile) and last == 'FALSE':
			verdict = utils.colors.RED +'ko'+ utils.colors.NO
		else:
			verdict = utils.colors.GREEN +'ok'+ utils.colors.NO

 	print '[%s], %s, %0.2f' % (verdict, last, (time.time() - realstarttime))


if __name__ == "__main__":
	main(sys.argv[0:])

