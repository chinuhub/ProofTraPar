/*  Generated 0.0.0.0.0.0 (-t3 -r11 -u1 -bcbmc) 2015-12-15 06:58:52  */
#include <stdio.h>
#include <stdlib.h>

#define THREADS 3
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
unsigned __CPROVER_bitvector[5] pc[THREADS+1];                                          //unsigned char active_thread[THREADS+1]={1};
unsigned __CPROVER_bitvector[6] pc_cs[THREADS+1];                                    //unsigned int pc[THREADS+1];
unsigned int thread_index;                                 //unsigned int thread_index;
unsigned __CPROVER_bitvector[5] thread_lines[] = {7, 7, 7, 24}; //unsigned __CPROVER_bitvector[4] thread_lines[] = {3, 8, 8};

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



                                                       int idx = 0;
                                                       int ctr1 = 1;
                                                       int ctr2 = 0;
                                                       int readerprogress1 = 0;
                                                       int readerprogress2 = 0;
                                                       __cs_mutex_t mutex;
                                                       void __CS_atomic_use1(int __csLOCALPARAM___CS_atomic_use1_myidx)
                                                       {
                                                          __VERIFIER_assume((__csLOCALPARAM___CS_atomic_use1_myidx <= 0) && (ctr1 > 0));
                                                          ctr1++;
                                                       }
                                                       
                                                       void __CS_atomic_use2(int __csLOCALPARAM___CS_atomic_use2_myidx)
                                                       {
                                                          __VERIFIER_assume((__csLOCALPARAM___CS_atomic_use2_myidx >= 1) && (ctr2 > 0));
                                                          ctr2++;
                                                       }
                                                       
                                                       void __CS_atomic_use_done(int __csLOCALPARAM___CS_atomic_use_done_myidx)
                                                       {
                                                          if (__csLOCALPARAM___CS_atomic_use_done_myidx <= 0)
                                                          {
                                                             ctr1--;
                                                          }
                                                          else
                                                          {
                                                             ctr2--;
                                                          }
                                                       
                                                       }
                                                       
                                                       void __CS_atomic_take_snapshot(int *__csLOCALPARAM___CS_atomic_take_snapshot_readerstart1, int *__csLOCALPARAM___CS_atomic_take_snapshot_readerstart2)
                                                       {
                                                          *__csLOCALPARAM___CS_atomic_take_snapshot_readerstart1 = readerprogress1;
                                                          *__csLOCALPARAM___CS_atomic_take_snapshot_readerstart2 = readerprogress2;
                                                       }
                                                       
                                                       void __CS_atomic_check_progress1(int __csLOCALPARAM___CS_atomic_check_progress1_readerstart1)
                                                       {
                                                          if (__VERIFIER_nondet_int())
                                                          {
                                                             __VERIFIER_assume((__csLOCALPARAM___CS_atomic_check_progress1_readerstart1 == 1) && (readerprogress1 == 1));
                                                             if (!0)
                                                             {
                                                                assert(0);
                                                             }
                                                       
                                                             ;
                                                          }
                                                       
                                                          return;
                                                       }
                                                       
                                                       void __CS_atomic_check_progress2(int __csLOCALPARAM___CS_atomic_check_progress2_readerstart2)
                                                       {
                                                          if (__VERIFIER_nondet_int())
                                                          {
                                                             __VERIFIER_assume((__csLOCALPARAM___CS_atomic_check_progress2_readerstart2 == 1) && (readerprogress2 == 1));
                                                             if (!0)
                                                             {
                                                                assert(0);
                                                             }
                                                       
                                                             ;
                                                          }
                                                       
                                                          return;
                                                       }
                                                       
                                                       void *qrcu_reader1_0(void *__csLOCALPARAM_qrcu_reader1_arg)
                                                       {
                                                       	static int __csLOCAL_qrcu_reader1_myidx;
IF(1,0,tqrcu_reader1_0_1)                              	__cs_init_scalar(&__csLOCAL_qrcu_reader1_myidx, sizeof(int));
                                                       	{
tqrcu_reader1_0_1: IF(1,1,tqrcu_reader1_0_2)           		__csLOCAL_qrcu_reader1_myidx = idx;
                                                       		if (__VERIFIER_nondet_int())
                                                       		{
tqrcu_reader1_0_2: IF(1,2,tqrcu_reader1_0_3)           			__CS_atomic_use1(__csLOCAL_qrcu_reader1_myidx);
                                                       			goto __exit_loop_1;
                                                       		}
                                                       		else
                                                       		{ GUARD(1,3)
                                                       			if (__VERIFIER_nondet_int())
                                                       			{
tqrcu_reader1_0_3: IF(1,3,tqrcu_reader1_0_4)           				__CS_atomic_use2(__csLOCAL_qrcu_reader1_myidx);
                                                       				goto __exit_loop_1;
                                                       			}
                                                       			else
                                                       			{ GUARD(1,4)
                                                       			}
                                                       			GUARD(1,4)
                                                       		}
                                                       		GUARD(1,4)
                                                       	}
                                                       	assume(!1);
                                                       	__exit_loop_1: GUARD(1,4)
                                                       	;
tqrcu_reader1_0_4: IF(1,4,tqrcu_reader1_0_5)           	readerprogress1 = 1;
tqrcu_reader1_0_5: IF(1,5,tqrcu_reader1_0_6)           	readerprogress1 = 2;
tqrcu_reader1_0_6: IF(1,6,tqrcu_reader1_0_7)           	__CS_atomic_use_done(__csLOCAL_qrcu_reader1_myidx);
                                                       	goto __exit_qrcu_reader1;
                                                       	__exit_qrcu_reader1: GUARD(1,7)
                                                       	;
tqrcu_reader1_0_7:                                     	STOP_NONVOID(7);
                                                       }
                                                       
                                                       
                                                       
                                                       void *qrcu_reader2_0(void *__csLOCALPARAM_qrcu_reader2_arg)
                                                       {
                                                       	static int __csLOCAL_qrcu_reader2_myidx;
IF(2,0,tqrcu_reader2_0_1)                              	__cs_init_scalar(&__csLOCAL_qrcu_reader2_myidx, sizeof(int));
                                                       	{
tqrcu_reader2_0_1: IF(2,1,tqrcu_reader2_0_2)           		__csLOCAL_qrcu_reader2_myidx = idx;
                                                       		if (__VERIFIER_nondet_int())
                                                       		{
tqrcu_reader2_0_2: IF(2,2,tqrcu_reader2_0_3)           			__CS_atomic_use1(__csLOCAL_qrcu_reader2_myidx);
                                                       			goto __exit_loop_2;
                                                       		}
                                                       		else
                                                       		{ GUARD(2,3)
                                                       			if (__VERIFIER_nondet_int())
                                                       			{
tqrcu_reader2_0_3: IF(2,3,tqrcu_reader2_0_4)           				__CS_atomic_use2(__csLOCAL_qrcu_reader2_myidx);
                                                       				goto __exit_loop_2;
                                                       			}
                                                       			else
                                                       			{ GUARD(2,4)
                                                       			}
                                                       			GUARD(2,4)
                                                       		}
                                                       		GUARD(2,4)
                                                       	}
                                                       	assume(!1);
                                                       	__exit_loop_2: GUARD(2,4)
                                                       	;
tqrcu_reader2_0_4: IF(2,4,tqrcu_reader2_0_5)           	readerprogress2 = 1;
tqrcu_reader2_0_5: IF(2,5,tqrcu_reader2_0_6)           	readerprogress2 = 2;
tqrcu_reader2_0_6: IF(2,6,tqrcu_reader2_0_7)           	__CS_atomic_use_done(__csLOCAL_qrcu_reader2_myidx);
                                                       	goto __exit_qrcu_reader2;
                                                       	__exit_qrcu_reader2: GUARD(2,7)
                                                       	;
tqrcu_reader2_0_7:                                     	STOP_NONVOID(7);
                                                       }
                                                       
                                                       
                                                       
                                                       void *qrcu_updater_0(void *__csLOCALPARAM_qrcu_updater_arg)
                                                       {
                                                       	static int __csLOCAL_qrcu_updater_i;
IF(3,0,tqrcu_updater_0_1)                              	__cs_init_scalar(&__csLOCAL_qrcu_updater_i, sizeof(int));
                                                       	static int __csLOCAL_qrcu_updater_readerstart1;
                                                       	__cs_init_scalar(&__csLOCAL_qrcu_updater_readerstart1, sizeof(int));
                                                       	static int __csLOCAL_qrcu_updater_readerstart2;
                                                       	__cs_init_scalar(&__csLOCAL_qrcu_updater_readerstart2, sizeof(int));
                                                       	static int __csLOCAL_qrcu_updater_sum;
                                                       	__cs_init_scalar(&__csLOCAL_qrcu_updater_sum, sizeof(int));
tqrcu_updater_0_1: IF(3,1,tqrcu_updater_0_2)           	__CS_atomic_take_snapshot(&__csLOCAL_qrcu_updater_readerstart1, &__csLOCAL_qrcu_updater_readerstart2);
                                                       	if (__VERIFIER_nondet_int())
                                                       	{
tqrcu_updater_0_2: IF(3,2,tqrcu_updater_0_3)           		__csLOCAL_qrcu_updater_sum = ctr1;
tqrcu_updater_0_3: IF(3,3,tqrcu_updater_0_4)           		__csLOCAL_qrcu_updater_sum = __csLOCAL_qrcu_updater_sum + ctr2;
                                                       	}
                                                       	else
                                                       	{ GUARD(3,4)
tqrcu_updater_0_4: IF(3,4,tqrcu_updater_0_5)           		__csLOCAL_qrcu_updater_sum = ctr2;
tqrcu_updater_0_5: IF(3,5,tqrcu_updater_0_6)           		__csLOCAL_qrcu_updater_sum = __csLOCAL_qrcu_updater_sum + ctr1;
                                                       	}
                                                       	GUARD(3,6)
                                                       	;
                                                       	if (__csLOCAL_qrcu_updater_sum <= 1)
                                                       	{
                                                       		if (__VERIFIER_nondet_int())
                                                       		{
tqrcu_updater_0_6: IF(3,6,tqrcu_updater_0_7)           			__csLOCAL_qrcu_updater_sum = ctr1;
tqrcu_updater_0_7: IF(3,7,tqrcu_updater_0_8)           			__csLOCAL_qrcu_updater_sum = __csLOCAL_qrcu_updater_sum + ctr2;
                                                       		}
                                                       		else
                                                       		{ GUARD(3,8)
tqrcu_updater_0_8: IF(3,8,tqrcu_updater_0_9)           			__csLOCAL_qrcu_updater_sum = ctr2;
tqrcu_updater_0_9: IF(3,9,tqrcu_updater_0_10)          			__csLOCAL_qrcu_updater_sum = __csLOCAL_qrcu_updater_sum + ctr1;
                                                       		}
                                                       		GUARD(3,10)
                                                       		;
                                                       	}
                                                       	else
                                                       	{ GUARD(3,10)
                                                       	}
                                                       	GUARD(3,10)
                                                       	if (__csLOCAL_qrcu_updater_sum > 1)
                                                       	{
tqrcu_updater_0_10: IF(3,10,tqrcu_updater_0_11)        		__cs_mutex_lock(&mutex);
tqrcu_updater_0_11: IF(3,11,tqrcu_updater_0_12)        		if (idx <= 0)
                                                       		{
tqrcu_updater_0_12: IF(3,12,tqrcu_updater_0_13)        			ctr2++;
tqrcu_updater_0_13: IF(3,13,tqrcu_updater_0_14)        			idx = 1;
tqrcu_updater_0_14: IF(3,14,tqrcu_updater_0_15)        			ctr1--;
                                                       		}
                                                       		else
                                                       		{ GUARD(3,15)
tqrcu_updater_0_15: IF(3,15,tqrcu_updater_0_16)        			ctr1++;
tqrcu_updater_0_16: IF(3,16,tqrcu_updater_0_17)        			idx = 0;
tqrcu_updater_0_17: IF(3,17,tqrcu_updater_0_18)        			ctr2--;
                                                       		}
                                                       		GUARD(3,18)
tqrcu_updater_0_18: IF(3,18,tqrcu_updater_0_19)        		if (idx <= 0)
                                                       		{
tqrcu_updater_0_19: IF(3,19,tqrcu_updater_0_20)        			assume(!(ctr1 > 0));
                                                       		}
                                                       		else
                                                       		{ GUARD(3,20)
tqrcu_updater_0_20: IF(3,20,tqrcu_updater_0_21)        			assume(!(ctr2 > 0));
                                                       		}
                                                       		GUARD(3,21)
tqrcu_updater_0_21: IF(3,21,tqrcu_updater_0_22)        		__cs_mutex_unlock(&mutex);
                                                       	}
                                                       	else
                                                       	{ GUARD(3,22)
                                                       	}
                                                       	GUARD(3,22)
tqrcu_updater_0_22: IF(3,22,tqrcu_updater_0_23)        	__CS_atomic_check_progress1(__csLOCAL_qrcu_updater_readerstart1);
tqrcu_updater_0_23: IF(3,23,tqrcu_updater_0_24)        	__CS_atomic_check_progress2(__csLOCAL_qrcu_updater_readerstart2);
                                                       	goto __exit_qrcu_updater;
                                                       	__exit_qrcu_updater: GUARD(3,24)
                                                       	;
tqrcu_updater_0_24:                                    	STOP_NONVOID(24);
                                                       }
                                                       
                                                       
                                                       
                                                       int main_thread(void)
                                                       {;
IF(0,0,tmain_1)                                        	static __cs_t __csLOCAL_main_t1;
                                                       	__cs_init_scalar(&__csLOCAL_main_t1, sizeof(__cs_t));
                                                       	static __cs_t __csLOCAL_main_t2;
                                                       	__cs_init_scalar(&__csLOCAL_main_t2, sizeof(__cs_t));
                                                       	static __cs_t __csLOCAL_main_t3;
                                                       	__cs_init_scalar(&__csLOCAL_main_t3, sizeof(__cs_t));
                                                       	__cs_mutex_init(&mutex, 0);
                                                       	__cs_create(&__csLOCAL_main_t1, 0, qrcu_reader1_0, 0, 1);
tmain_1: IF(0,1,tmain_2)                               	__cs_create(&__csLOCAL_main_t2, 0, qrcu_reader2_0, 0, 2);
tmain_2: IF(0,2,tmain_3)                               	__cs_create(&__csLOCAL_main_t3, 0, qrcu_updater_0, 0, 3);
tmain_3: IF(0,3,tmain_4)                               	__cs_join(__csLOCAL_main_t1, 0);
tmain_4: IF(0,4,tmain_5)                               	__cs_join(__csLOCAL_main_t2, 0);
tmain_5: IF(0,5,tmain_6)                               	__cs_join(__csLOCAL_main_t3, 0);
tmain_6: IF(0,6,tmain_7)                               	__cs_mutex_destroy(&mutex);
                                                       	goto __exit_main;
                                                       	__exit_main: GUARD(0,7)
                                                       	;
tmain_7:                                               	STOP_NONVOID(7);
                                                       }
                                                       
                                                       
                                                       
                                                       int main(void) {
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r0;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t1_r0;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r0;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r0;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r1;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t1_r1;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r1;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r1;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r2;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t1_r2;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r2;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r2;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r3;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t1_r3;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r3;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r3;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r4;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t1_r4;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r4;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r4;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r5;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t1_r5;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r5;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r5;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r6;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t1_r6;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r6;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r6;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r7;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t1_r7;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r7;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r7;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r8;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t1_r8;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r8;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r8;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r9;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t1_r9;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r9;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r9;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r10;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t1_r10;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r10;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r10;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r11;
                                                       
                                                                 unsigned __CPROVER_bitvector[9] top3 = 24;
                                                                 unsigned __CPROVER_bitvector[9] sum3 = tmp_t3_r0 + tmp_t3_r1 + tmp_t3_r2 + tmp_t3_r3 + tmp_t3_r4 + tmp_t3_r5 + tmp_t3_r6 + tmp_t3_r7 + tmp_t3_r8 + tmp_t3_r9 + tmp_t3_r10;
                                                                 assume(sum3 <= top3);
                                                                 // round 0
                                                                 thread_index = 0;
                                                                 pc_cs[0] = pc[0] + tmp_t0_r0;
                                                                 assume(pc_cs[0] > 0);
                                                                 assume(pc_cs[0] <= 7);
                                                                 main_thread();
                                                                 pc[0] = pc_cs[0];
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r0;
                                                                    assume(pc_cs[1] <= 7);
                                                                    qrcu_reader1_0(threadargs[1]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r0;
                                                                    assume(pc_cs[2] <= 7);
                                                                    qrcu_reader2_0(threadargs[2]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_updater_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r0;
                                                                    qrcu_updater_0(threadargs[3]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 // round 1
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r1;
                                                                     assume(pc_cs[0] <= 7);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r1;
                                                                    assume(pc_cs[1] <= 7);
                                                                    qrcu_reader1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r1;
                                                                    assume(pc_cs[2] <= 7);
                                                                    qrcu_reader2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_updater_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r1;
                                                                    qrcu_updater_0(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 // round 2
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r2;
                                                                     assume(pc_cs[0] <= 7);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r2;
                                                                    assume(pc_cs[1] <= 7);
                                                                    qrcu_reader1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r2;
                                                                    assume(pc_cs[2] <= 7);
                                                                    qrcu_reader2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_updater_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r2;
                                                                    qrcu_updater_0(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 // round 3
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r3;
                                                                     assume(pc_cs[0] <= 7);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r3;
                                                                    assume(pc_cs[1] <= 7);
                                                                    qrcu_reader1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r3;
                                                                    assume(pc_cs[2] <= 7);
                                                                    qrcu_reader2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_updater_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r3;
                                                                    qrcu_updater_0(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 // round 4
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r4;
                                                                     assume(pc_cs[0] <= 7);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r4;
                                                                    assume(pc_cs[1] <= 7);
                                                                    qrcu_reader1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r4;
                                                                    assume(pc_cs[2] <= 7);
                                                                    qrcu_reader2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_updater_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r4;
                                                                    qrcu_updater_0(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 // round 5
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r5;
                                                                     assume(pc_cs[0] <= 7);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r5;
                                                                    assume(pc_cs[1] <= 7);
                                                                    qrcu_reader1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r5;
                                                                    assume(pc_cs[2] <= 7);
                                                                    qrcu_reader2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_updater_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r5;
                                                                    qrcu_updater_0(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 // round 6
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r6;
                                                                     assume(pc_cs[0] <= 7);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r6;
                                                                    assume(pc_cs[1] <= 7);
                                                                    qrcu_reader1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r6;
                                                                    assume(pc_cs[2] <= 7);
                                                                    qrcu_reader2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_updater_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r6;
                                                                    qrcu_updater_0(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 // round 7
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r7;
                                                                     assume(pc_cs[0] <= 7);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r7;
                                                                    assume(pc_cs[1] <= 7);
                                                                    qrcu_reader1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r7;
                                                                    assume(pc_cs[2] <= 7);
                                                                    qrcu_reader2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_updater_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r7;
                                                                    qrcu_updater_0(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 // round 8
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r8;
                                                                     assume(pc_cs[0] <= 7);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r8;
                                                                    assume(pc_cs[1] <= 7);
                                                                    qrcu_reader1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r8;
                                                                    assume(pc_cs[2] <= 7);
                                                                    qrcu_reader2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_updater_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r8;
                                                                    qrcu_updater_0(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 // round 9
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r9;
                                                                     assume(pc_cs[0] <= 7);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r9;
                                                                    assume(pc_cs[1] <= 7);
                                                                    qrcu_reader1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r9;
                                                                    assume(pc_cs[2] <= 7);
                                                                    qrcu_reader2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_updater_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r9;
                                                                    qrcu_updater_0(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 // round 10
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r10;
                                                                     assume(pc_cs[0] <= 7);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r10;
                                                                    assume(pc_cs[1] <= 7);
                                                                    qrcu_reader1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_reader2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r10;
                                                                    assume(pc_cs[2] <= 7);
                                                                    qrcu_reader2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // qrcu_updater_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r10;
                                                                    qrcu_updater_0(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 thread_index = 0;
                                                                 if (active_thread[0] == 1) {
                                                                    pc_cs[0] = pc[0] + tmp_t0_r11;
                                                                    assume(pc_cs[0] <= 7);
                                                                    main_thread();
                                                                 }
                                                       
                                                          return 0;
                                                       }
                                                       


