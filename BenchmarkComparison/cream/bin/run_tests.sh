#!/bin/bash
# requires cream cfrontend.asm.exe gcc
cream="cream"
output_log="output.log"
error_log="error.log"

# counters
exp_successful=0
exp_failed=0
unexp_successful=0
unexp_failed=0
block="block"


run_test() {
    echo "Running $@ ..."
    if $@ >> $output_log 2>> $error_log
    then exp_successful=$[ $exp_successful+1 ]
    else unexp_failed=$[ $unexp_failed+1 ]
    fi
}

fail_test() {
    echo "Running $@ ..."
    if $@ >> $output_log 2>> $error_log
    then unexp_successful=$[ $unexp_successful+1 ]
    else exp_failed=$[ $exp_failed+1 ]
    fi
}

print_summary() {
    echo ""
    echo "Expected successful tests:     $exp_successful"
    echo "Expected failed tests:         $exp_failed"
    echo "Unexpected successful tests:   $unexp_successful"
    echo "Unexpected failed tests:       $unexp_failed"
}

# rely-guarantee examples
block-rely-guarantee() {
    fail_test $cream --threads thr1:thr2 c_tests/lu-fig2.c
    run_test $cream --threads thr1:thr2 c_tests/lu-fig2.fixed.c
    fail_test $cream --threads readWriteProc:asyncIOCompletion c_tests/lu-fig4-complete.c
    run_test $cream --threads readWriteProc:asyncIOCompletion c_tests/lu-fig4-complete.fixed.c
    #run_test $cream --threads adder:stopper c_tests/bluetooth.cav09.c
    #fail_test $cream --threads adder:stopper:stopper c_tests/bluetooth.cav09.c
    #run_test $cream --threads loader:thread1:thread2 c_tests/scull.c
    run_test $cream --threads thr1:thr2 c_tests/dekker.c
    run_test $cream --threads thr1:thr2 c_tests/peterson.c
    run_test $cream --threads thr1:thr2 c_tests/read_write_lock.c
    run_test $cream --threads thr1:thr2 c_tests/time_var_mutex.c
    run_test $cream --threads thr1:thr2 c_tests/szymanski.c
    run_test $cream --threads thr1:thr2 c_tests/bakery.simple.c
    #run_test $cream --threads thr1:thr2 c_tests/bakery.c
    #run_test $cream --threads thr1:thr2 c_tests/lamport.c
    #run_test $cream --threads qrcu_reader1:qrcu_updater c_tests/qrcu.c
}

# monotlithic examples
block-monolithic() {
    run_test $cream --threads thr:thr --algorithm:monolithic c_tests/spin2003.c
    fail_test $cream --threads thr:thr:thr --algorithm:monolithic c_tests/spin2003-cex.c
    fail_test $cream --threads thr1:thr2 --algorithm:monolithic c_tests/lu-fig2.c
    fail_test $cream --threads readWriteProc:asyncIOCompletion --algorithm:monolithic c_tests/lu-fig4-complete.c
}

# owicki-gries examples
block-owicki-gries() {
    fail_test $cream --threads thr1:thr2 --algorithm:owicki-gries c_tests/lu-fig2.c
    run_test $cream --threads thr1:thr2 --algorithm:owicki-gries c_tests/lu-fig2.fixed.c
    fail_test $cream --threads readWriteProc:asyncIOCompletion --algorithm:owicki-gries c_tests/lu-fig4-complete.c
    run_test $cream --threads readWriteProc:asyncIOCompletion --algorithm:owicki-gries c_tests/lu-fig4-complete.fixed.c
    run_test $cream --threads adder:stopper --algorithm:owicki-gries c_tests/bluetooth.cav09.c
    fail_test $cream --threads adder:stopper:stopper --algorithm:owicki-gries c_tests/bluetooth.cav09.c
    #run_test $cream --threads loader:thread1:thread2 --algorithm:owicki-gries c_tests/scull.c
    run_test $cream --threads thr1:thr2 --algorithm:owicki-gries c_tests/dekker.c
    run_test $cream --threads thr1:thr2 --algorithm:owicki-gries c_tests/peterson.c
    run_test $cream --threads thr1:thr2 --algorithm:owicki-gries c_tests/read_write_lock.c
    run_test $cream --threads thr1:thr2 --algorithm:owicki-gries c_tests/time_var_mutex.c
    run_test $cream --threads thr1:thr2 --algorithm:owicki-gries c_tests/szymanski.c
    run_test $cream --threads thr1:thr2 --algorithm:owicki-gries c_tests/bakery.simple.c
    run_test $cream --threads thr1:thr2 --algorithm:owicki-gries c_tests/bakery.c
    run_test $cream --threads thr1:thr2 --algorithm:owicki-gries c_tests/lamport.c
    run_test $cream --threads qrcu_reader1:qrcu_updater --algorithm:owicki-gries c_tests/qrcu.c
}

# termination examples
block-termination() {
    fail_test $cream --threads thr1:thr2 --algorithm:termination --pc-abstraction-for-environment:off c_tests/cook.fig2.pldi07.extended.c
    run_test $cream --threads thr1:thr2 --algorithm:termination --pc-abstraction-for-environment:off c_tests/podelski.fig2.lics04.c
    fail_test $cream --threads thr1:thr2 --algorithm:termination --pc-abstraction-for-environment:off c_tests/podelski.fig3.lics04.c
}

# main
rm -rf $output_log $error_log
case "$1" in
    -block)
	shift
	block="$block-$1"
	$block
	;;
    *)
	block-rely-guarantee
	;;
esac
print_summary

