#!/usr/bin/env python

import sys, shlex, subprocess
from multiprocessing import Process
import signal, os, threading

p1 = None
p2 = None

''' Executes command  cmdline   in a separate process,
	and waits to its completion. 
'''
def launcher1(cmdline):
	global p1, p2

	p = subprocess.Popen(shlex.split(cmdline))
	p.wait()

	if p2 is not None:
		print "ABC process 1 finished, other is %s" % p2.pid
		p2.terminate()
	else:
		print "ABC process 1 finished, other is None"


def launcher2(cmdline):
	global p1, p2

	p = subprocess.Popen(shlex.split(cmdline))
	p.wait()

	if p1 is not None:
		print "ABC process 2 finished, other is %s" % p1.pid
		p1.terminate()
	else:
		print "ABC process 2 finished, other is None"


def main(args):
	global p1, p2

	cmdline1 = 'cbmc fib_longer_unsafe.c --error-label ERROR'
	cmdline2 = 'esbmc fib_longer_unsafe.c --error-label ERROR --unwind 7'

	p1 = Process(target=launcher1, args=(cmdline1, ))
	p2 = Process(target=launcher2, args=(cmdline2, ))

	p1.start()
	p2.start()

	p1.join()
	p2.join()

	print "main end!\n"


if __name__ == "__main__":
	main(sys.argv[0:])


