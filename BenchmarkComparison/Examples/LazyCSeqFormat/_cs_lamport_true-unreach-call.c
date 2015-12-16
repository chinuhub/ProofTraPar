/*  Generated 0.0.0.0.0.0 (-t2 -r11 -u1 -bcbmc) 2015-12-15 06:54:48  */
#include <stdio.h>
#include <stdlib.h>

#define THREADS 2
#define ROUNDS 11

#define STOP_VOID(A) return;
#define STOP_NONVOID(A) return 0;

#define IF(T,A,B)  if (pc[T] > A || (A >= pc_cs[T])) goto B;
#define GUARD(T,B)  assume( pc_cs[T] >= B );

#ifndef NULL
#define NULL 0
#endif

#define assume(x) __CPROVER_assume(x)
#define __VERIFIER_assume(x) __CPROVER_assume(x)

#define assert(x) assert(x)
#define __VERIFIER_assert(x) assert(x)

#define __VERIFIER_nondet_int() nondet_int()
int nondet_int();

#define __VERIFIER_nondet_uint() nondet_uint()
unsigned int nondet_uint();
unsigned int nondet_uint();

unsigned __CPROVER_bitvector[1] active_thread[THREADS+1]={1};                //unsigned char active_thread[THREADS+1]={1};
unsigned __CPROVER_bitvector[4] pc[THREADS+1];                                          //unsigned char active_thread[THREADS+1]={1};
unsigned __CPROVER_bitvector[5] pc_cs[THREADS+1];                                    //unsigned int pc[THREADS+1];
unsigned int thread_index;                                 //unsigned int thread_index;
unsigned __CPROVER_bitvector[4] thread_lines[] = {4, 15, 15}; //unsigned __CPROVER_bitvector[4] thread_lines[] = {3, 8, 8};

void * __cs_safe_malloc(size_t size) { void * ptr = malloc(size); assume(ptr); return ptr; }
void * __cs_unsafe_malloc(size_t size) { if(nondet_int()) return 0; return malloc(size); }
//#define __cs_unsafe_malloc malloc

void __cs_init_scalar(void *var, size_t size) {
	if (size == sizeof(int))
		*(int *)var = nondet_int();
	else {
		char * ptr = (char *)var;
		size_t j;

		//for (j=0; j<size; j++)
		//	ptr[j] = __cs_nondet_char();
	}
}

/* pthread API */
typedef int __cs_mutex_t;
typedef int __cs_cond_t;
typedef int __cs_t;

int __cs_mutex_init (__cs_mutex_t *m, int val) { *m = -1; return 0; }
int __cs_mutex_destroy(__cs_mutex_t *m) { return 0; }
int __cs_mutex_lock(__cs_mutex_t *m) { assume(*m == -1); *m = thread_index; return 0; } 
int __cs_mutex_unlock(__cs_mutex_t *m) { assert(*m == thread_index); *m = -1; return 0; }

void *threadargs[THREADS+1];

int __cs_create(__cs_t *id, void *attr, void *(*t)(void*), void *arg, int threadID) { if (threadID > THREADS) return 0;  *id = threadID; active_thread[threadID] = 1; threadargs[threadID] = arg; return 0; }
int __cs_join(__cs_t id, void **value_ptr) { assume(pc[id] == thread_lines[id]); return 0; }
int __cs_exit(void *value_ptr) { return 0; }   // only for parsing

int __cs_cond_wait(__cs_cond_t *cond, __cs_mutex_t *mutex) { __cs_mutex_unlock(mutex); assume(*cond != -1); __cs_mutex_lock(mutex); return 0; }
int __cs_cond_signal(__cs_cond_t *cond) { *cond = 1; return 0; }
int __cs_cond_init(__cs_cond_t *cond, void *attr) { *cond = -1; return 0; }



/* here */



                                                       int x;
                                                       int y;
                                                       int b1;
                                                       int b2;
                                                       int X;
                                                       void *thr1_0(void *__csLOCALPARAM_thr1___cs_unused)
                                                       {
                                                       	{
IF(1,0,tthr1_0_1)                                      		b1 = 1;
tthr1_0_1: IF(1,1,tthr1_0_2)                           		x = 1;
tthr1_0_2: IF(1,2,tthr1_0_3)                           		if (y != 0)
                                                       		{
tthr1_0_3: IF(1,3,tthr1_0_4)                           			b1 = 0;
tthr1_0_4: IF(1,4,tthr1_0_5)                           			assume(!(y != 0));
                                                       			;
                                                       			goto __continue_0_loop_1;
                                                       		}
                                                       		GUARD(1,5)
tthr1_0_5: IF(1,5,tthr1_0_6)                           		y = 1;
tthr1_0_6: IF(1,6,tthr1_0_7)                           		if (x != 1)
                                                       		{
tthr1_0_7: IF(1,7,tthr1_0_8)                           			b1 = 0;
tthr1_0_8: IF(1,8,tthr1_0_9)                           			assume(!(b2 >= 1));
                                                       			;
tthr1_0_9: IF(1,9,tthr1_0_10)                          			if (y != 1)
                                                       			{
tthr1_0_10: IF(1,10,tthr1_0_11)                        				assume(!(y != 0));
                                                       				;
                                                       				goto __continue_0_loop_1;
                                                       			}
                                                       			GUARD(1,11)
                                                       		}
                                                       		GUARD(1,11)
                                                       		goto __exit_loop_1;
                                                       		__continue_0_loop_1: GUARD(1,11)
                                                       		;
                                                       	}
                                                       	assume(!1);
                                                       	__exit_loop_1: GUARD(1,11)
                                                       	;
tthr1_0_11: IF(1,11,tthr1_0_12)                        	X = 0;
tthr1_0_12: IF(1,12,tthr1_0_13)                        	if (!(X <= 0))
                                                       	{
                                                       		assert(0);
                                                       	}
                                                       	
                                                       	;
tthr1_0_13: IF(1,13,tthr1_0_14)                        	y = 0;
tthr1_0_14: IF(1,14,tthr1_0_15)                        	b1 = 0;
                                                       	__exit_thr1: GUARD(1,15)
                                                       	;
tthr1_0_15:                                            	STOP_NONVOID(15);
                                                       }
                                                       
                                                       
                                                       
                                                       void *thr2_0(void *__csLOCALPARAM_thr2___cs_unused)
                                                       {
                                                       	{
IF(2,0,tthr2_0_1)                                      		b2 = 1;
tthr2_0_1: IF(2,1,tthr2_0_2)                           		x = 2;
tthr2_0_2: IF(2,2,tthr2_0_3)                           		if (y != 0)
                                                       		{
tthr2_0_3: IF(2,3,tthr2_0_4)                           			b2 = 0;
tthr2_0_4: IF(2,4,tthr2_0_5)                           			assume(!(y != 0));
                                                       			;
                                                       			goto __continue_0_loop_2;
                                                       		}
                                                       		GUARD(2,5)
tthr2_0_5: IF(2,5,tthr2_0_6)                           		y = 2;
tthr2_0_6: IF(2,6,tthr2_0_7)                           		if (x != 2)
                                                       		{
tthr2_0_7: IF(2,7,tthr2_0_8)                           			b2 = 0;
tthr2_0_8: IF(2,8,tthr2_0_9)                           			assume(!(b1 >= 1));
                                                       			;
tthr2_0_9: IF(2,9,tthr2_0_10)                          			if (y != 2)
                                                       			{
tthr2_0_10: IF(2,10,tthr2_0_11)                        				assume(!(y != 0));
                                                       				;
                                                       				goto __continue_0_loop_2;
                                                       			}
                                                       			GUARD(2,11)
                                                       		}
                                                       		GUARD(2,11)
                                                       		goto __exit_loop_2;
                                                       		__continue_0_loop_2: GUARD(2,11)
                                                       		;
                                                       	}
                                                       	assume(!1);
                                                       	__exit_loop_2: GUARD(2,11)
                                                       	;
tthr2_0_11: IF(2,11,tthr2_0_12)                        	X = 1;
tthr2_0_12: IF(2,12,tthr2_0_13)                        	if (!(X >= 1))
                                                       	{
                                                       		assert(0);
                                                       	}
                                                       	
                                                       	;
tthr2_0_13: IF(2,13,tthr2_0_14)                        	y = 0;
tthr2_0_14: IF(2,14,tthr2_0_15)                        	b2 = 0;
                                                       	__exit_thr2: GUARD(2,15)
                                                       	;
tthr2_0_15:                                            	STOP_NONVOID(15);
                                                       }
                                                       
                                                       
                                                       
                                                       int main_thread(void)
                                                       {;
IF(0,0,tmain_1)                                        	static __cs_t __csLOCAL_main_t1;
                                                       	__cs_init_scalar(&__csLOCAL_main_t1, sizeof(__cs_t));
                                                       	static __cs_t __csLOCAL_main_t2;
                                                       	__cs_init_scalar(&__csLOCAL_main_t2, sizeof(__cs_t));
                                                       	__cs_create(&__csLOCAL_main_t1, 0, thr1_0, 0, 1);
tmain_1: IF(0,1,tmain_2)                               	__cs_create(&__csLOCAL_main_t2, 0, thr2_0, 0, 2);
tmain_2: IF(0,2,tmain_3)                               	__cs_join(__csLOCAL_main_t1, 0);
tmain_3: IF(0,3,tmain_4)                               	__cs_join(__csLOCAL_main_t2, 0);
                                                       	goto __exit_main;
                                                       	__exit_main: GUARD(0,4)
                                                       	;
tmain_4:                                               	STOP_NONVOID(4);
                                                       }
                                                       
                                                       
                                                       
                                                       int main(void) {
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r0;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r0;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t2_r0;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r1;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r1;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t2_r1;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r2;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r2;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t2_r2;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r3;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r3;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t2_r3;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r4;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r4;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t2_r4;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r5;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r5;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t2_r5;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r6;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r6;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t2_r6;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r7;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r7;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t2_r7;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r8;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r8;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t2_r8;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r9;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r9;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t2_r9;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r10;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r10;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t2_r10;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r11;
                                                       
                                                                 // round 0
                                                                 thread_index = 0;
                                                                 pc_cs[0] = pc[0] + tmp_t0_r0;
                                                                 assume(pc_cs[0] > 0);
                                                                 assume(pc_cs[0] <= 4);
                                                                 main_thread();
                                                                 pc[0] = pc_cs[0];
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thr1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r0;
                                                                    assume(pc_cs[1] <= 15);
                                                                    thr1_0(threadargs[1]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thr2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r0;
                                                                    assume(pc_cs[2] <= 15);
                                                                    thr2_0(threadargs[2]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 // round 1
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r1;
                                                                     assume(pc_cs[0] <= 4);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thr1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r1;
                                                                    assume(pc_cs[1] <= 15);
                                                                    thr1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thr2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r1;
                                                                    assume(pc_cs[2] <= 15);
                                                                    thr2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 // round 2
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r2;
                                                                     assume(pc_cs[0] <= 4);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thr1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r2;
                                                                    assume(pc_cs[1] <= 15);
                                                                    thr1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thr2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r2;
                                                                    assume(pc_cs[2] <= 15);
                                                                    thr2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 // round 3
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r3;
                                                                     assume(pc_cs[0] <= 4);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thr1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r3;
                                                                    assume(pc_cs[1] <= 15);
                                                                    thr1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thr2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r3;
                                                                    assume(pc_cs[2] <= 15);
                                                                    thr2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 // round 4
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r4;
                                                                     assume(pc_cs[0] <= 4);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thr1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r4;
                                                                    assume(pc_cs[1] <= 15);
                                                                    thr1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thr2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r4;
                                                                    assume(pc_cs[2] <= 15);
                                                                    thr2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 // round 5
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r5;
                                                                     assume(pc_cs[0] <= 4);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thr1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r5;
                                                                    assume(pc_cs[1] <= 15);
                                                                    thr1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thr2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r5;
                                                                    assume(pc_cs[2] <= 15);
                                                                    thr2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 // round 6
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r6;
                                                                     assume(pc_cs[0] <= 4);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thr1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r6;
                                                                    assume(pc_cs[1] <= 15);
                                                                    thr1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thr2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r6;
                                                                    assume(pc_cs[2] <= 15);
                                                                    thr2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 // round 7
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r7;
                                                                     assume(pc_cs[0] <= 4);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thr1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r7;
                                                                    assume(pc_cs[1] <= 15);
                                                                    thr1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thr2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r7;
                                                                    assume(pc_cs[2] <= 15);
                                                                    thr2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 // round 8
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r8;
                                                                     assume(pc_cs[0] <= 4);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thr1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r8;
                                                                    assume(pc_cs[1] <= 15);
                                                                    thr1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thr2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r8;
                                                                    assume(pc_cs[2] <= 15);
                                                                    thr2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 // round 9
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r9;
                                                                     assume(pc_cs[0] <= 4);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thr1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r9;
                                                                    assume(pc_cs[1] <= 15);
                                                                    thr1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thr2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r9;
                                                                    assume(pc_cs[2] <= 15);
                                                                    thr2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 // round 10
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r10;
                                                                     assume(pc_cs[0] <= 4);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thr1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r10;
                                                                    assume(pc_cs[1] <= 15);
                                                                    thr1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thr2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r10;
                                                                    assume(pc_cs[2] <= 15);
                                                                    thr2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 0;
                                                                 if (active_thread[0] == 1) {
                                                                    pc_cs[0] = pc[0] + tmp_t0_r11;
                                                                    assume(pc_cs[0] <= 4);
                                                                    main_thread();
                                                                 }
                                                       
                                                          return 0;
                                                       }
                                                       


