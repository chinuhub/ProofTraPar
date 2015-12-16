/*  Generated 0.0.0.0.0.0 (-t4 -r2 -u1 -bcbmc) 2015-12-15 06:59:41  */
#include <stdio.h>
#include <stdlib.h>

#define THREADS 4
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
unsigned __CPROVER_bitvector[4] pc[THREADS+1];                                          //unsigned char active_thread[THREADS+1]={1};
unsigned __CPROVER_bitvector[5] pc_cs[THREADS+1];                                    //unsigned int pc[THREADS+1];
unsigned int thread_index;                                 //unsigned int thread_index;
unsigned __CPROVER_bitvector[4] thread_lines[] = {8, 3, 7, 3, 7}; //unsigned __CPROVER_bitvector[4] thread_lines[] = {3, 8, 8};

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



                                                       int w = 0;
                                                       int r = 0;
                                                       int x;
                                                       int y;
                                                       void __CS_atomic_take_write_lock()
                                                       {
                                                          __VERIFIER_assume((w == 0) && (r == 0));
                                                          w = 1;
                                                       }
                                                       
                                                       void __CS_atomic_take_read_lock()
                                                       {
                                                          __VERIFIER_assume(w == 0);
                                                          r = r + 1;
                                                       }
                                                       
                                                       void *writer_0(void *__csLOCALPARAM_writer_arg)
                                                       {
IF(1,0,twriter_0_1)                                    	__CS_atomic_take_write_lock();
twriter_0_1: IF(1,1,twriter_0_2)                       	x = 3;
twriter_0_2: IF(1,2,twriter_0_3)                       	w = 0;
                                                       	__exit_writer: GUARD(1,3)
                                                       	;
twriter_0_3:                                           	STOP_NONVOID(3);
                                                       }
                                                       
                                                       
                                                       
                                                       void *writer_1(void *__csLOCALPARAM_writer_arg)
                                                       {
IF(3,0,twriter_1_1)                                    	__CS_atomic_take_write_lock();
twriter_1_1: IF(3,1,twriter_1_2)                       	x = 3;
twriter_1_2: IF(3,2,twriter_1_3)                       	w = 0;
                                                       	__exit_writer: GUARD(3,3)
                                                       	;
twriter_1_3:                                           	STOP_NONVOID(3);
                                                       }
                                                       
                                                       
                                                       
                                                       void *reader_0(void *__csLOCALPARAM_reader_arg)
                                                       {
                                                       	static int __csLOCAL_reader_l;
IF(2,0,treader_0_1)                                    	__cs_init_scalar(&__csLOCAL_reader_l, sizeof(int));
treader_0_1: IF(2,1,treader_0_2)                       	__CS_atomic_take_read_lock();
treader_0_2: IF(2,2,treader_0_3)                       	__csLOCAL_reader_l = x;
treader_0_3: IF(2,3,treader_0_4)                       	y = __csLOCAL_reader_l;
treader_0_4: IF(2,4,treader_0_5)                       	if (!(y == x))
                                                       	{
                                                       		assert(0);
                                                       	}
                                                       	
                                                       	;
treader_0_5: IF(2,5,treader_0_6)                       	__csLOCAL_reader_l = r - 1;
treader_0_6: IF(2,6,treader_0_7)                       	r = __csLOCAL_reader_l;
                                                       	__exit_reader: GUARD(2,7)
                                                       	;
treader_0_7:                                           	STOP_NONVOID(7);
                                                       }
                                                       
                                                       
                                                       
                                                       void *reader_1(void *__csLOCALPARAM_reader_arg)
                                                       {
                                                       	static int __csLOCAL_reader_l;
IF(4,0,treader_1_1)                                    	__cs_init_scalar(&__csLOCAL_reader_l, sizeof(int));
treader_1_1: IF(4,1,treader_1_2)                       	__CS_atomic_take_read_lock();
treader_1_2: IF(4,2,treader_1_3)                       	__csLOCAL_reader_l = x;
treader_1_3: IF(4,3,treader_1_4)                       	y = __csLOCAL_reader_l;
treader_1_4: IF(4,4,treader_1_5)                       	if (!(y == x))
                                                       	{
                                                       		assert(0);
                                                       	}
                                                       	
                                                       	;
treader_1_5: IF(4,5,treader_1_6)                       	__csLOCAL_reader_l = r - 1;
treader_1_6: IF(4,6,treader_1_7)                       	r = __csLOCAL_reader_l;
                                                       	__exit_reader: GUARD(4,7)
                                                       	;
treader_1_7:                                           	STOP_NONVOID(7);
                                                       }
                                                       
                                                       
                                                       
                                                       int main_thread(void)
                                                       {;
IF(0,0,tmain_1)                                        	static __cs_t __csLOCAL_main_t1;
                                                       	__cs_init_scalar(&__csLOCAL_main_t1, sizeof(__cs_t));
                                                       	static __cs_t __csLOCAL_main_t2;
                                                       	__cs_init_scalar(&__csLOCAL_main_t2, sizeof(__cs_t));
                                                       	static __cs_t __csLOCAL_main_t3;
                                                       	__cs_init_scalar(&__csLOCAL_main_t3, sizeof(__cs_t));
                                                       	static __cs_t __csLOCAL_main_t4;
                                                       	__cs_init_scalar(&__csLOCAL_main_t4, sizeof(__cs_t));
                                                       	__cs_create(&__csLOCAL_main_t1, 0, writer_0, 0, 1);
tmain_1: IF(0,1,tmain_2)                               	__cs_create(&__csLOCAL_main_t2, 0, reader_0, 0, 2);
tmain_2: IF(0,2,tmain_3)                               	__cs_create(&__csLOCAL_main_t3, 0, writer_1, 0, 3);
tmain_3: IF(0,3,tmain_4)                               	__cs_create(&__csLOCAL_main_t4, 0, reader_1, 0, 4);
tmain_4: IF(0,4,tmain_5)                               	__cs_join(__csLOCAL_main_t1, 0);
tmain_5: IF(0,5,tmain_6)                               	__cs_join(__csLOCAL_main_t2, 0);
tmain_6: IF(0,6,tmain_7)                               	__cs_join(__csLOCAL_main_t3, 0);
tmain_7: IF(0,7,tmain_8)                               	__cs_join(__csLOCAL_main_t4, 0);
                                                       	goto __exit_main;
                                                       	__exit_main: GUARD(0,8)
                                                       	;
tmain_8:                                               	STOP_NONVOID(8);
                                                       }
                                                       
                                                       
                                                       
                                                       int main(void) {
                                                                 unsigned __CPROVER_bitvector[4] tmp_t0_r0;
                                                                 unsigned __CPROVER_bitvector[2] tmp_t1_r0;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r0;
                                                                 unsigned __CPROVER_bitvector[2] tmp_t3_r0;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t4_r0;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t0_r1;
                                                                 unsigned __CPROVER_bitvector[2] tmp_t1_r1;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t2_r1;
                                                                 unsigned __CPROVER_bitvector[2] tmp_t3_r1;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t4_r1;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t0_r2;
                                                       
                                                                 unsigned __CPROVER_bitvector[6] top0 = 8;
                                                                 unsigned __CPROVER_bitvector[6] sum0 = tmp_t0_r0 + tmp_t0_r1 + tmp_t0_r2;
                                                                 assume(sum0 <= top0);
                                                                 // round 0
                                                                 thread_index = 0;
                                                                 pc_cs[0] = pc[0] + tmp_t0_r0;
                                                                 main_thread();
                                                                 pc[0] = pc_cs[0];
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // writer_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r0;
                                                                    assume(pc_cs[1] <= 3);
                                                                    writer_0(threadargs[1]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // reader_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r0;
                                                                    assume(pc_cs[2] <= 7);
                                                                    reader_0(threadargs[2]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // writer_1
                                                                    pc_cs[3] = pc[3] + tmp_t3_r0;
                                                                    assume(pc_cs[3] <= 3);
                                                                    writer_1(threadargs[3]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 thread_index = 4;
                                                                 if (active_thread[thread_index] == 1) { // reader_1
                                                                    pc_cs[4] = pc[4] + tmp_t4_r0;
                                                                    assume(pc_cs[4] <= 7);
                                                                    reader_1(threadargs[4]);
                                                                    pc[4] = pc_cs[4];
                                                                 }
                                                       
                                                                 // round 1
                                                                 thread_index = 0;
                                                                 if (active_thread[thread_index] == 1) { // main
                                                                     pc_cs[0] = pc[0] + tmp_t0_r1;
                                                                     main_thread();
                                                                     pc[0] = pc_cs[0];
                                                                 }
                                                       
                                                                 thread_index = 1;
                                                                 if (active_thread[thread_index] == 1) { // writer_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r1;
                                                                    assume(pc_cs[1] <= 3);
                                                                    writer_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // reader_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r1;
                                                                    assume(pc_cs[2] <= 7);
                                                                    reader_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // writer_1
                                                                    pc_cs[3] = pc[3] + tmp_t3_r1;
                                                                    assume(pc_cs[3] <= 3);
                                                                    writer_1(threadargs[thread_index]);
                                                                    pc[3] = pc_cs[3];
                                                                 }
                                                       
                                                                 thread_index = 4;
                                                                 if (active_thread[thread_index] == 1) { // reader_1
                                                                    pc_cs[4] = pc[4] + tmp_t4_r1;
                                                                    assume(pc_cs[4] <= 7);
                                                                    reader_1(threadargs[thread_index]);
                                                                    pc[4] = pc_cs[4];
                                                                 }
                                                       
                                                                 thread_index = 0;
                                                                 if (active_thread[0] == 1) {
                                                                    pc_cs[0] = pc[0] + tmp_t0_r2;
                                                                    assume(pc_cs[0] <= 8);
                                                                    main_thread();
                                                                 }
                                                       
                                                          return 0;
                                                       }
                                                       


