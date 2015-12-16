/*  Generated 0.0.0.0.0.0 (-t3 -r2 -u1 -bcbmc) 2015-12-15 06:19:36  */
#include <stdio.h>
#include <stdlib.h>

#define THREADS 3
#define ROUNDS 2

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
unsigned __CPROVER_bitvector[3] pc[THREADS+1];                                          //unsigned char active_thread[THREADS+1]={1};
unsigned __CPROVER_bitvector[4] pc_cs[THREADS+1];                                    //unsigned int pc[THREADS+1];
unsigned int thread_index;                                 //unsigned int thread_index;
unsigned __CPROVER_bitvector[3] thread_lines[] = {6, 3, 3, 3}; //unsigned __CPROVER_bitvector[4] thread_lines[] = {3, 8, 8};

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



                                                       __cs_mutex_t mutex;
                                                       int data = 0;
                                                       void *thread1_0(void *__csLOCALPARAM_thread1_arg)
                                                       {
IF(1,0,tthread1_0_1)                                   	__cs_mutex_lock(&mutex);
tthread1_0_1: IF(1,1,tthread1_0_2)                     	data++;
tthread1_0_2: IF(1,2,tthread1_0_3)                     	__cs_mutex_unlock(&mutex);
                                                       	__exit_thread1: GUARD(1,3)
                                                       	;
tthread1_0_3:                                          	STOP_NONVOID(3);
                                                       }
                                                       
                                                       
                                                       
                                                       void *thread2_0(void *__csLOCALPARAM_thread2_arg)
                                                       {
IF(2,0,tthread2_0_1)                                   	__cs_mutex_lock(&mutex);
tthread2_0_1: IF(2,1,tthread2_0_2)                     	data += 2;
tthread2_0_2: IF(2,2,tthread2_0_3)                     	__cs_mutex_unlock(&mutex);
                                                       	__exit_thread2: GUARD(2,3)
                                                       	;
tthread2_0_3:                                          	STOP_NONVOID(3);
                                                       }
                                                       
                                                       
                                                       
                                                       void *thread3_0(void *__csLOCALPARAM_thread3_arg)
                                                       {
IF(3,0,tthread3_0_1)                                   	__cs_mutex_lock(&mutex);
tthread3_0_1: IF(3,1,tthread3_0_2)                     	if (data >= 3)
                                                       	{
                                                       		assert(0);
                                                       		;
                                                       	}
                                                       	
tthread3_0_2: IF(3,2,tthread3_0_3)                     	__cs_mutex_unlock(&mutex);
                                                       	__exit_thread3: GUARD(3,3)
                                                       	;
tthread3_0_3:                                          	STOP_NONVOID(3);
                                                       }
                                                       
                                                       
                                                       
                                                       int main_thread(void)
                                                       {;
IF(0,0,tmain_1)                                        	__cs_mutex_init(&mutex, 0);
                                                       	static __cs_t __csLOCAL_main_t1;
                                                       	__cs_init_scalar(&__csLOCAL_main_t1, sizeof(__cs_t));
                                                       	static __cs_t __csLOCAL_main_t2;
                                                       	__cs_init_scalar(&__csLOCAL_main_t2, sizeof(__cs_t));
                                                       	static __cs_t __csLOCAL_main_t3;
                                                       	__cs_init_scalar(&__csLOCAL_main_t3, sizeof(__cs_t));
                                                       	__cs_create(&__csLOCAL_main_t1, 0, thread1_0, 0, 1);
tmain_1: IF(0,1,tmain_2)                               	__cs_create(&__csLOCAL_main_t2, 0, thread2_0, 0, 2);
tmain_2: IF(0,2,tmain_3)                               	__cs_create(&__csLOCAL_main_t3, 0, thread3_0, 0, 3);
tmain_3: IF(0,3,tmain_4)                               	__cs_join(__csLOCAL_main_t1, 0);
tmain_4: IF(0,4,tmain_5)                               	__cs_join(__csLOCAL_main_t2, 0);
tmain_5: IF(0,5,tmain_6)                               	__cs_join(__csLOCAL_main_t3, 0);
                                                       	goto __exit_main;
                                                       	__exit_main: GUARD(0,6)
                                                       	;
tmain_6:                                               	STOP_NONVOID(6);
                                                       }
                                                       
                                                       
                                                       
                                                       int main(void) {
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r0;
                                                                 unsigned __CPROVER_bitvector[2] tmp_t1_r0;
                                                                 unsigned __CPROVER_bitvector[2] tmp_t2_r0;
                                                                 unsigned __CPROVER_bitvector[2] tmp_t3_r0;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r1;
                                                                 unsigned __CPROVER_bitvector[2] tmp_t1_r1;
                                                                 unsigned __CPROVER_bitvector[2] tmp_t2_r1;
                                                                 unsigned __CPROVER_bitvector[2] tmp_t3_r1;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r2;
                                                       
                                                                 // round 0
                                                                 thread_index = 0;
                                                                 pc_cs[0] = pc[0] + tmp_t0_r0;
                                                                 assume(pc_cs[0] > 0);
                                                                 assume(pc_cs[0] <= 6);
                                                                 main_thread();
                                                                 pc[0] = pc_cs[0];
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r0;
                                                                    assume(pc_cs[1] <= 3);
                                                                    thread1_0(threadargs[1]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r0;
                                                                    assume(pc_cs[2] <= 3);
                                                                    thread2_0(threadargs[2]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread3_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r0;
                                                                    assume(pc_cs[3] <= 3);
                                                                    thread3_0(threadargs[3]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 // round 1
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r1;
                                                                     assume(pc_cs[0] <= 6);
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r1;
                                                                    assume(pc_cs[1] <= 3);
                                                                    thread1_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r1;
                                                                    assume(pc_cs[2] <= 3);
                                                                    thread2_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread3_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r1;
                                                                    assume(pc_cs[3] <= 3);
                                                                    thread3_0(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 thread_index = 0;
                                                                 if (active_thread[0] == 1) {
                                                                    pc_cs[0] = pc[0] + tmp_t0_r2;
                                                                    assume(pc_cs[0] <= 6);
                                                                    main_thread();
                                                                 }
                                                       
                                                          return 0;
                                                       }
                                                       


