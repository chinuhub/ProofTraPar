/*  Generated 0.0.0.0.0.0 (-t3 -r11 -u1 -bcbmc) 2015-12-15 06:55:50  */
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
unsigned __CPROVER_bitvector[5] thread_lines[] = {7, 9, 18, 17}; //unsigned __CPROVER_bitvector[4] thread_lines[] = {3, 8, 8};

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



                                                       int i;
                                                       __cs_mutex_t lock;
                                                       int __cs_function_down_interruptible_inlined = 1;
                                                       int __cs_function_up_inlined = 1;
                                                       int __cs_function_copy_to_user_inlined = 1;
                                                       int __cs_function_copy_from_user_inlined = 1;
                                                       int __cs_function___get_user_inlined = 1;
                                                       int __cs_function___put_user_inlined = 1;
                                                       int scull_quantum = 4000;
                                                       int scull_qset = 1000;
                                                       int dev_data;
                                                       int dev_quantum;
                                                       int dev_qset;
                                                       int dev_size;
                                                       int __X__;
                                                       int __cs_function_scull_trim_inlined = 1;
                                                       int __cs_function_scull_open_inlined = 1;
                                                       int __cs_function_scull_follow_inlined = 1;
                                                       int __cs_function_scull_read_inlined = 1;
                                                       int __cs_function_scull_write_inlined = 1;
                                                       int __cs_function_scull_ioctl_inlined = 1;
                                                       int __cs_function_scull_llseek_inlined = 1;
                                                       int __cs_function_scull_cleanup_module_inlined = 1;
                                                       int __cs_function_scull_init_module_inlined = 1;
                                                       void *loader_0(void *__csLOCALPARAM_loader_arg)
                                                       {
                                                       	static int __retval__scull_init_module_1;
                                                       	{
                                                       		static int __csLOCAL_scull_init_module_result = 0;
IF(1,0,tloader_0_1)                                    		__retval__scull_init_module_1 = 0;
                                                       		goto __exit__scull_init_module_1;
                                                       		{
                                                       			static int __csLOCAL_scull_cleanup_module_dev = __VERIFIER_nondet_int();
                                                       			static int __retval__scull_trim_1;
                                                       			{
                                                       				static int __csLOCALPARAM_scull_trim_dev;
                                                       				__csLOCALPARAM_scull_trim_dev = __csLOCAL_scull_cleanup_module_dev;
                                                       				static int __csLOCAL_scull_trim_qset = dev_qset;
tloader_0_1: IF(1,1,tloader_0_2)                       				dev_size = 0;
tloader_0_2: IF(1,2,tloader_0_3)                       				dev_quantum = scull_quantum;
tloader_0_3: IF(1,3,tloader_0_4)                       				dev_qset = scull_qset;
tloader_0_4: IF(1,4,tloader_0_5)                       				dev_data = 0;
                                                       				__retval__scull_trim_1 = 0;
                                                       				goto __exit__scull_trim_1;
                                                       				__exit__scull_trim_1: GUARD(1,5)
                                                       				;
                                                       			}
                                                       			__retval__scull_trim_1;
                                                       			__exit__scull_cleanup_module_1: GUARD(1,5)
                                                       			;
                                                       		}
                                                       		fail: GUARD(1,5)
                                                       		__retval__scull_init_module_1 = __csLOCAL_scull_init_module_result;
                                                       		goto __exit__scull_init_module_1;
                                                       		__exit__scull_init_module_1: GUARD(1,5)
                                                       		;
                                                       	}
                                                       	__retval__scull_init_module_1;
                                                       	{
                                                       		static int __csLOCAL_scull_cleanup_module_dev = __VERIFIER_nondet_int();
                                                       		static int __retval__scull_trim_2;
                                                       		{
                                                       			static int __csLOCALPARAM_scull_trim_dev;
                                                       			__csLOCALPARAM_scull_trim_dev = __csLOCAL_scull_cleanup_module_dev;
                                                       			static int __csLOCAL_scull_trim_qset = dev_qset;
tloader_0_5: IF(1,5,tloader_0_6)                       			dev_size = 0;
tloader_0_6: IF(1,6,tloader_0_7)                       			dev_quantum = scull_quantum;
tloader_0_7: IF(1,7,tloader_0_8)                       			dev_qset = scull_qset;
tloader_0_8: IF(1,8,tloader_0_9)                       			dev_data = 0;
                                                       			__retval__scull_trim_2 = 0;
                                                       			goto __exit__scull_trim_2;
                                                       			__exit__scull_trim_2: GUARD(1,9)
                                                       			;
                                                       		}
                                                       		__retval__scull_trim_2;
                                                       		__exit__scull_cleanup_module_2: GUARD(1,9)
                                                       		;
                                                       	}
                                                       	__exit_loader: GUARD(1,9)
                                                       	;
tloader_0_9:                                           	STOP_NONVOID(9);
                                                       }
                                                       
                                                       
                                                       
                                                       void *thread1_0(void *__csLOCALPARAM_thread1_arg)
                                                       {
                                                       	static int __csLOCAL_thread1_filp = __VERIFIER_nondet_int();
                                                       	static int __csLOCAL_thread1_buf = __VERIFIER_nondet_int();
                                                       	static int __csLOCAL_thread1_count = 10;
                                                       	static int __csLOCAL_thread1_off = 0;
                                                       	static int __retval__scull_open_1;
                                                       	{
                                                       		static int __csLOCALPARAM_scull_open_tid;
IF(2,0,tthread1_0_1)                                   		__csLOCALPARAM_scull_open_tid = 1;
                                                       		static int __csLOCALPARAM_scull_open_i;
tthread1_0_1: IF(2,1,tthread1_0_2)                     		__csLOCALPARAM_scull_open_i = i;
                                                       		static int __csLOCALPARAM_scull_open_filp;
                                                       		__csLOCALPARAM_scull_open_filp = __csLOCAL_thread1_filp;
                                                       		static int __csLOCAL_scull_open_dev;
                                                       		__cs_init_scalar(&__csLOCAL_scull_open_dev, sizeof(int));
                                                       		__csLOCAL_scull_open_dev = __csLOCALPARAM_scull_open_i;
                                                       		__csLOCALPARAM_scull_open_filp = __csLOCAL_scull_open_dev;
                                                       		static _Bool __csLOCAL_scull_open___if_cond_0;
                                                       		__cs_init_scalar(&__csLOCAL_scull_open___if_cond_0, sizeof(_Bool));
                                                       		static int __retval__down_interruptible_1;
                                                       		{
tthread1_0_2: IF(2,2,tthread1_0_3)                     			__cs_mutex_lock(&lock);
                                                       			__retval__down_interruptible_1 = 0;
                                                       			goto __exit__down_interruptible_1;
                                                       			__exit__down_interruptible_1: GUARD(2,3)
                                                       			;
                                                       		}
                                                       		__csLOCAL_scull_open___if_cond_0 = __retval__down_interruptible_1;
                                                       		if (__csLOCAL_scull_open___if_cond_0)
                                                       		{
                                                       			__retval__scull_open_1 = -512;
                                                       			goto __exit__scull_open_1;
                                                       		}
                                                       		
tthread1_0_3: IF(2,3,tthread1_0_4)                     		__X__ = 2;
                                                       		static int __retval__scull_trim_3;
                                                       		{
                                                       			static int __csLOCALPARAM_scull_trim_dev;
                                                       			__csLOCALPARAM_scull_trim_dev = __csLOCAL_scull_open_dev;
                                                       			static int __csLOCAL_scull_trim_qset = dev_qset;
tthread1_0_4: IF(2,4,tthread1_0_5)                     			dev_size = 0;
tthread1_0_5: IF(2,5,tthread1_0_6)                     			dev_quantum = scull_quantum;
tthread1_0_6: IF(2,6,tthread1_0_7)                     			dev_qset = scull_qset;
tthread1_0_7: IF(2,7,tthread1_0_8)                     			dev_data = 0;
                                                       			__retval__scull_trim_3 = 0;
                                                       			goto __exit__scull_trim_3;
                                                       			__exit__scull_trim_3: GUARD(2,8)
                                                       			;
                                                       		}
                                                       		__retval__scull_trim_3;
tthread1_0_8: IF(2,8,tthread1_0_9)                     		if (!(__X__ >= 2))
                                                       		{
                                                       			assert(0);
                                                       		}
                                                       		
                                                       		;
                                                       		{
tthread1_0_9: IF(2,9,tthread1_0_10)                    			__cs_mutex_unlock(&lock);
                                                       			goto __exit__up_1;
                                                       			__exit__up_1: GUARD(2,10)
                                                       			;
                                                       		}
                                                       		__retval__scull_open_1 = 0;
                                                       		goto __exit__scull_open_1;
                                                       		__exit__scull_open_1: GUARD(2,10)
                                                       		;
                                                       	}
                                                       	__retval__scull_open_1;
                                                       	static int __retval__scull_read_1;
                                                       	{
                                                       		static int __csLOCALPARAM_scull_read_tid;
                                                       		__csLOCALPARAM_scull_read_tid = 1;
                                                       		static int __csLOCALPARAM_scull_read_filp;
                                                       		__csLOCALPARAM_scull_read_filp = __csLOCAL_thread1_filp;
                                                       		static int __csLOCALPARAM_scull_read_buf;
                                                       		__csLOCALPARAM_scull_read_buf = __csLOCAL_thread1_buf;
                                                       		static int __csLOCALPARAM_scull_read_count;
                                                       		__csLOCALPARAM_scull_read_count = __csLOCAL_thread1_count;
                                                       		static int __csLOCALPARAM_scull_read_f_pos;
                                                       		__csLOCALPARAM_scull_read_f_pos = __csLOCAL_thread1_off;
                                                       		static int __csLOCAL_scull_read_dev = __csLOCALPARAM_scull_read_filp;
                                                       		static int __csLOCAL_scull_read_dptr;
                                                       		__cs_init_scalar(&__csLOCAL_scull_read_dptr, sizeof(int));
                                                       		static int __csLOCAL_scull_read_quantum = dev_quantum;
                                                       		static int __csLOCAL_scull_read_qset = dev_qset;
                                                       		static int __csLOCAL_scull_read_itemsize = __csLOCAL_scull_read_quantum * __csLOCAL_scull_read_qset;
                                                       		static int __csLOCAL_scull_read_item;
                                                       		__cs_init_scalar(&__csLOCAL_scull_read_item, sizeof(int));
                                                       		static int __csLOCAL_scull_read_s_pos;
                                                       		__cs_init_scalar(&__csLOCAL_scull_read_s_pos, sizeof(int));
                                                       		static int __csLOCAL_scull_read_q_pos;
                                                       		__cs_init_scalar(&__csLOCAL_scull_read_q_pos, sizeof(int));
                                                       		static int __csLOCAL_scull_read_rest;
                                                       		__cs_init_scalar(&__csLOCAL_scull_read_rest, sizeof(int));
                                                       		static int __csLOCAL_scull_read_retval = 0;
                                                       		static _Bool __csLOCAL_scull_read___if_cond_1;
                                                       		__cs_init_scalar(&__csLOCAL_scull_read___if_cond_1, sizeof(_Bool));
                                                       		static int __retval__down_interruptible_2;
                                                       		{
tthread1_0_10: IF(2,10,tthread1_0_11)                  			__cs_mutex_lock(&lock);
                                                       			__retval__down_interruptible_2 = 0;
                                                       			goto __exit__down_interruptible_2;
                                                       			__exit__down_interruptible_2: GUARD(2,11)
                                                       			;
                                                       		}
                                                       		__csLOCAL_scull_read___if_cond_1 = __retval__down_interruptible_2;
                                                       		if (__csLOCAL_scull_read___if_cond_1)
                                                       		{
                                                       			__retval__scull_read_1 = -512;
                                                       			goto __exit__scull_read_1;
                                                       		}
                                                       		
tthread1_0_11: IF(2,11,tthread1_0_12)                  		__X__ = 0;
tthread1_0_12: IF(2,12,tthread1_0_13)                  		if (__csLOCALPARAM_scull_read_f_pos >= dev_size)
                                                       		{
                                                       			goto out;
                                                       		}
                                                       		
tthread1_0_13: IF(2,13,tthread1_0_14)                  		if ((__csLOCALPARAM_scull_read_f_pos + __csLOCALPARAM_scull_read_count) >= dev_size)
                                                       		{
tthread1_0_14: IF(2,14,tthread1_0_15)                  			__csLOCALPARAM_scull_read_count = dev_size - __csLOCALPARAM_scull_read_f_pos;
                                                       		}
                                                       		GUARD(2,15)
                                                       		__csLOCAL_scull_read_item = __csLOCALPARAM_scull_read_f_pos / __csLOCAL_scull_read_itemsize;
                                                       		__csLOCAL_scull_read_rest = __csLOCALPARAM_scull_read_f_pos;
                                                       		__csLOCAL_scull_read_s_pos = __csLOCAL_scull_read_rest / __csLOCAL_scull_read_quantum;
                                                       		__csLOCAL_scull_read_q_pos = __csLOCAL_scull_read_rest;
                                                       		static int __retval__scull_follow_1;
                                                       		{
                                                       			static int __csLOCALPARAM_scull_follow_dev;
                                                       			__csLOCALPARAM_scull_follow_dev = __csLOCAL_scull_read_dev;
                                                       			static int __csLOCALPARAM_scull_follow_n;
                                                       			__csLOCALPARAM_scull_follow_n = __csLOCAL_scull_read_item;
                                                       			__retval__scull_follow_1 = __VERIFIER_nondet_int();
                                                       			goto __exit__scull_follow_1;
                                                       			__exit__scull_follow_1: GUARD(2,15)
                                                       			;
                                                       		}
                                                       		__csLOCAL_scull_read_dptr = __retval__scull_follow_1;
                                                       		if (__csLOCALPARAM_scull_read_count > (__csLOCAL_scull_read_quantum - __csLOCAL_scull_read_q_pos))
                                                       		{
                                                       			__csLOCALPARAM_scull_read_count = __csLOCAL_scull_read_quantum - __csLOCAL_scull_read_q_pos;
                                                       		}
                                                       		
                                                       		static _Bool __csLOCAL_scull_read___if_cond_2;
                                                       		__cs_init_scalar(&__csLOCAL_scull_read___if_cond_2, sizeof(_Bool));
                                                       		static int __retval__copy_to_user_1;
                                                       		{
                                                       			static int __csLOCALPARAM_copy_to_user_to;
                                                       			__csLOCALPARAM_copy_to_user_to = __csLOCALPARAM_scull_read_buf;
                                                       			static int __csLOCALPARAM_copy_to_user_from;
tthread1_0_15: IF(2,15,tthread1_0_16)                  			__csLOCALPARAM_copy_to_user_from = (dev_data + __csLOCAL_scull_read_s_pos) + __csLOCAL_scull_read_q_pos;
                                                       			static int __csLOCALPARAM_copy_to_user_n;
                                                       			__csLOCALPARAM_copy_to_user_n = __csLOCALPARAM_scull_read_count;
                                                       			__csLOCALPARAM_copy_to_user_to = __csLOCALPARAM_copy_to_user_from;
                                                       			__retval__copy_to_user_1 = __VERIFIER_nondet_int();
                                                       			goto __exit__copy_to_user_1;
                                                       			__exit__copy_to_user_1: GUARD(2,16)
                                                       			;
                                                       		}
                                                       		__csLOCAL_scull_read___if_cond_2 = __retval__copy_to_user_1;
                                                       		if (__csLOCAL_scull_read___if_cond_2)
                                                       		{
                                                       			__csLOCAL_scull_read_retval = -2;
                                                       			goto out;
                                                       		}
                                                       		
                                                       		__csLOCALPARAM_scull_read_f_pos += __csLOCALPARAM_scull_read_count;
                                                       		__csLOCAL_scull_read_retval = __csLOCALPARAM_scull_read_count;
tthread1_0_16: IF(2,16,tthread1_0_17)                  		if (!(__X__ <= 0))
                                                       		{
                                                       			assert(0);
                                                       		}
                                                       		
                                                       		;
                                                       		{
tthread1_0_17: IF(2,17,tthread1_0_18)                  			__cs_mutex_unlock(&lock);
                                                       			goto __exit__up_2;
                                                       			__exit__up_2: GUARD(2,18)
                                                       			;
                                                       		}
                                                       		out: GUARD(2,18)
                                                       		__retval__scull_read_1 = __csLOCAL_scull_read_retval;
                                                       		goto __exit__scull_read_1;
                                                       		__exit__scull_read_1: GUARD(2,18)
                                                       		;
                                                       	}
                                                       	__retval__scull_read_1;
                                                       	0;
                                                       	__exit_thread1: GUARD(2,18)
                                                       	;
tthread1_0_18:                                         	STOP_NONVOID(18);
                                                       }
                                                       
                                                       
                                                       
                                                       void *thread2_0(void *__csLOCALPARAM_thread2_arg)
                                                       {
                                                       	static int __csLOCAL_thread2_filp = __VERIFIER_nondet_int();
                                                       	static int __csLOCAL_thread2_buf = __VERIFIER_nondet_int();
                                                       	static int __csLOCAL_thread2_count = 10;
                                                       	static int __csLOCAL_thread2_off = 0;
                                                       	static int __retval__scull_open_2;
                                                       	{
                                                       		static int __csLOCALPARAM_scull_open_tid;
IF(3,0,tthread2_0_1)                                   		__csLOCALPARAM_scull_open_tid = 2;
                                                       		static int __csLOCALPARAM_scull_open_i;
tthread2_0_1: IF(3,1,tthread2_0_2)                     		__csLOCALPARAM_scull_open_i = i;
                                                       		static int __csLOCALPARAM_scull_open_filp;
                                                       		__csLOCALPARAM_scull_open_filp = __csLOCAL_thread2_filp;
                                                       		static int __csLOCAL_scull_open_dev;
                                                       		__cs_init_scalar(&__csLOCAL_scull_open_dev, sizeof(int));
                                                       		__csLOCAL_scull_open_dev = __csLOCALPARAM_scull_open_i;
                                                       		__csLOCALPARAM_scull_open_filp = __csLOCAL_scull_open_dev;
                                                       		static _Bool __csLOCAL_scull_open___if_cond_0;
                                                       		__cs_init_scalar(&__csLOCAL_scull_open___if_cond_0, sizeof(_Bool));
                                                       		static int __retval__down_interruptible_3;
                                                       		{
tthread2_0_2: IF(3,2,tthread2_0_3)                     			__cs_mutex_lock(&lock);
                                                       			__retval__down_interruptible_3 = 0;
                                                       			goto __exit__down_interruptible_3;
                                                       			__exit__down_interruptible_3: GUARD(3,3)
                                                       			;
                                                       		}
                                                       		__csLOCAL_scull_open___if_cond_0 = __retval__down_interruptible_3;
                                                       		if (__csLOCAL_scull_open___if_cond_0)
                                                       		{
                                                       			__retval__scull_open_2 = -512;
                                                       			goto __exit__scull_open_2;
                                                       		}
                                                       		
tthread2_0_3: IF(3,3,tthread2_0_4)                     		__X__ = 2;
                                                       		static int __retval__scull_trim_4;
                                                       		{
                                                       			static int __csLOCALPARAM_scull_trim_dev;
                                                       			__csLOCALPARAM_scull_trim_dev = __csLOCAL_scull_open_dev;
                                                       			static int __csLOCAL_scull_trim_qset = dev_qset;
tthread2_0_4: IF(3,4,tthread2_0_5)                     			dev_size = 0;
tthread2_0_5: IF(3,5,tthread2_0_6)                     			dev_quantum = scull_quantum;
tthread2_0_6: IF(3,6,tthread2_0_7)                     			dev_qset = scull_qset;
tthread2_0_7: IF(3,7,tthread2_0_8)                     			dev_data = 0;
                                                       			__retval__scull_trim_4 = 0;
                                                       			goto __exit__scull_trim_4;
                                                       			__exit__scull_trim_4: GUARD(3,8)
                                                       			;
                                                       		}
                                                       		__retval__scull_trim_4;
tthread2_0_8: IF(3,8,tthread2_0_9)                     		if (!(__X__ >= 2))
                                                       		{
                                                       			assert(0);
                                                       		}
                                                       		
                                                       		;
                                                       		{
tthread2_0_9: IF(3,9,tthread2_0_10)                    			__cs_mutex_unlock(&lock);
                                                       			goto __exit__up_3;
                                                       			__exit__up_3: GUARD(3,10)
                                                       			;
                                                       		}
                                                       		__retval__scull_open_2 = 0;
                                                       		goto __exit__scull_open_2;
                                                       		__exit__scull_open_2: GUARD(3,10)
                                                       		;
                                                       	}
                                                       	__retval__scull_open_2;
                                                       	static int __retval__scull_write_1;
                                                       	{
                                                       		static int __csLOCALPARAM_scull_write_tid;
                                                       		__csLOCALPARAM_scull_write_tid = 2;
                                                       		static int __csLOCALPARAM_scull_write_filp;
                                                       		__csLOCALPARAM_scull_write_filp = __csLOCAL_thread2_filp;
                                                       		static int __csLOCALPARAM_scull_write_buf;
                                                       		__csLOCALPARAM_scull_write_buf = __csLOCAL_thread2_buf;
                                                       		static int __csLOCALPARAM_scull_write_count;
                                                       		__csLOCALPARAM_scull_write_count = __csLOCAL_thread2_count;
                                                       		static int __csLOCALPARAM_scull_write_f_pos;
                                                       		__csLOCALPARAM_scull_write_f_pos = __csLOCAL_thread2_off;
                                                       		static int __csLOCAL_scull_write_dev = __csLOCALPARAM_scull_write_filp;
                                                       		static int __csLOCAL_scull_write_dptr;
                                                       		__cs_init_scalar(&__csLOCAL_scull_write_dptr, sizeof(int));
                                                       		static int __csLOCAL_scull_write_quantum = dev_quantum;
                                                       		static int __csLOCAL_scull_write_qset = dev_qset;
                                                       		static int __csLOCAL_scull_write_itemsize = __csLOCAL_scull_write_quantum * __csLOCAL_scull_write_qset;
                                                       		static int __csLOCAL_scull_write_item;
                                                       		__cs_init_scalar(&__csLOCAL_scull_write_item, sizeof(int));
                                                       		static int __csLOCAL_scull_write_s_pos;
                                                       		__cs_init_scalar(&__csLOCAL_scull_write_s_pos, sizeof(int));
                                                       		static int __csLOCAL_scull_write_q_pos;
                                                       		__cs_init_scalar(&__csLOCAL_scull_write_q_pos, sizeof(int));
                                                       		static int __csLOCAL_scull_write_rest;
                                                       		__cs_init_scalar(&__csLOCAL_scull_write_rest, sizeof(int));
                                                       		static int __csLOCAL_scull_write_retval = -4;
                                                       		static _Bool __csLOCAL_scull_write___if_cond_3;
                                                       		__cs_init_scalar(&__csLOCAL_scull_write___if_cond_3, sizeof(_Bool));
                                                       		static int __retval__down_interruptible_4;
                                                       		{
tthread2_0_10: IF(3,10,tthread2_0_11)                  			__cs_mutex_lock(&lock);
                                                       			__retval__down_interruptible_4 = 0;
                                                       			goto __exit__down_interruptible_4;
                                                       			__exit__down_interruptible_4: GUARD(3,11)
                                                       			;
                                                       		}
                                                       		__csLOCAL_scull_write___if_cond_3 = __retval__down_interruptible_4;
                                                       		if (__csLOCAL_scull_write___if_cond_3)
                                                       		{
                                                       			__retval__scull_write_1 = -512;
                                                       			goto __exit__scull_write_1;
                                                       		}
                                                       		
                                                       		__csLOCAL_scull_write_item = __csLOCALPARAM_scull_write_f_pos / __csLOCAL_scull_write_itemsize;
                                                       		__csLOCAL_scull_write_rest = __csLOCALPARAM_scull_write_f_pos;
                                                       		__csLOCAL_scull_write_s_pos = __csLOCAL_scull_write_rest / __csLOCAL_scull_write_quantum;
                                                       		__csLOCAL_scull_write_q_pos = __csLOCAL_scull_write_rest;
                                                       		static int __retval__scull_follow_2;
                                                       		{
                                                       			static int __csLOCALPARAM_scull_follow_dev;
                                                       			__csLOCALPARAM_scull_follow_dev = __csLOCAL_scull_write_dev;
                                                       			static int __csLOCALPARAM_scull_follow_n;
                                                       			__csLOCALPARAM_scull_follow_n = __csLOCAL_scull_write_item;
                                                       			__retval__scull_follow_2 = __VERIFIER_nondet_int();
                                                       			goto __exit__scull_follow_2;
                                                       			__exit__scull_follow_2: GUARD(3,11)
                                                       			;
                                                       		}
                                                       		__csLOCAL_scull_write_dptr = __retval__scull_follow_2;
                                                       		if (__csLOCAL_scull_write_dptr == 0)
                                                       		{
                                                       			goto out;
                                                       		}
                                                       		
                                                       		if (__csLOCALPARAM_scull_write_count > (__csLOCAL_scull_write_quantum - __csLOCAL_scull_write_q_pos))
                                                       		{
                                                       			__csLOCALPARAM_scull_write_count = __csLOCAL_scull_write_quantum - __csLOCAL_scull_write_q_pos;
                                                       		}
                                                       		
tthread2_0_11: IF(3,11,tthread2_0_12)                  		__X__ = 1;
                                                       		static _Bool __csLOCAL_scull_write___if_cond_4;
                                                       		__cs_init_scalar(&__csLOCAL_scull_write___if_cond_4, sizeof(_Bool));
                                                       		static int __retval__copy_from_user_1;
                                                       		{
                                                       			static int __csLOCALPARAM_copy_from_user_to;
tthread2_0_12: IF(3,12,tthread2_0_13)                  			__csLOCALPARAM_copy_from_user_to = (dev_data + __csLOCAL_scull_write_s_pos) + __csLOCAL_scull_write_q_pos;
                                                       			static int __csLOCALPARAM_copy_from_user_from;
                                                       			__csLOCALPARAM_copy_from_user_from = __csLOCALPARAM_scull_write_buf;
                                                       			static int __csLOCALPARAM_copy_from_user_n;
                                                       			__csLOCALPARAM_copy_from_user_n = __csLOCALPARAM_scull_write_count;
                                                       			__csLOCALPARAM_copy_from_user_to = __csLOCALPARAM_copy_from_user_from;
                                                       			__retval__copy_from_user_1 = __VERIFIER_nondet_int();
                                                       			goto __exit__copy_from_user_1;
                                                       			__exit__copy_from_user_1: GUARD(3,13)
                                                       			;
                                                       		}
                                                       		__csLOCAL_scull_write___if_cond_4 = __retval__copy_from_user_1;
                                                       		if (__csLOCAL_scull_write___if_cond_4)
                                                       		{
                                                       			__csLOCAL_scull_write_retval = -2;
                                                       			goto out;
                                                       		}
                                                       		
                                                       		__csLOCALPARAM_scull_write_f_pos += __csLOCALPARAM_scull_write_count;
                                                       		__csLOCAL_scull_write_retval = __csLOCALPARAM_scull_write_count;
tthread2_0_13: IF(3,13,tthread2_0_14)                  		if (dev_size < __csLOCALPARAM_scull_write_f_pos)
                                                       		{
tthread2_0_14: IF(3,14,tthread2_0_15)                  			dev_size = __csLOCALPARAM_scull_write_f_pos;
                                                       		}
                                                       		GUARD(3,15)
tthread2_0_15: IF(3,15,tthread2_0_16)                  		if (!(__X__ == 1))
                                                       		{
                                                       			assert(0);
                                                       		}
                                                       		
                                                       		;
                                                       		{
tthread2_0_16: IF(3,16,tthread2_0_17)                  			__cs_mutex_unlock(&lock);
                                                       			goto __exit__up_4;
                                                       			__exit__up_4: GUARD(3,17)
                                                       			;
                                                       		}
                                                       		out: GUARD(3,17)
                                                       		__retval__scull_write_1 = __csLOCAL_scull_write_retval;
                                                       		goto __exit__scull_write_1;
                                                       		__exit__scull_write_1: GUARD(3,17)
                                                       		;
                                                       	}
                                                       	__retval__scull_write_1;
                                                       	0;
                                                       	__exit_thread2: GUARD(3,17)
                                                       	;
tthread2_0_17:                                         	STOP_NONVOID(17);
                                                       }
                                                       
                                                       
                                                       
                                                       int main_thread(void)
                                                       {;
IF(0,0,tmain_1)                                        	static __cs_t __csLOCAL_main_t1;
                                                       	__cs_init_scalar(&__csLOCAL_main_t1, sizeof(__cs_t));
                                                       	static __cs_t __csLOCAL_main_t2;
                                                       	__cs_init_scalar(&__csLOCAL_main_t2, sizeof(__cs_t));
                                                       	static __cs_t __csLOCAL_main_t3;
                                                       	__cs_init_scalar(&__csLOCAL_main_t3, sizeof(__cs_t));
                                                       	__cs_mutex_init(&lock, 0);
                                                       	__cs_create(&__csLOCAL_main_t1, 0, loader_0, 0, 1);
tmain_1: IF(0,1,tmain_2)                               	__cs_create(&__csLOCAL_main_t2, 0, thread1_0, 0, 2);
tmain_2: IF(0,2,tmain_3)                               	__cs_create(&__csLOCAL_main_t3, 0, thread2_0, 0, 3);
tmain_3: IF(0,3,tmain_4)                               	__cs_join(__csLOCAL_main_t1, 0);
tmain_4: IF(0,4,tmain_5)                               	__cs_join(__csLOCAL_main_t2, 0);
tmain_5: IF(0,5,tmain_6)                               	__cs_join(__csLOCAL_main_t3, 0);
tmain_6: IF(0,6,tmain_7)                               	__cs_mutex_destroy(&lock);
                                                       	goto __exit_main;
                                                       	__exit_main: GUARD(0,7)
                                                       	;
tmain_7:                                               	STOP_NONVOID(7);
                                                       }
                                                       
                                                       
                                                       
                                                       int main(void) {
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r0;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r0;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t2_r0;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r0;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r1;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r1;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t2_r1;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r1;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r2;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r2;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t2_r2;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r2;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r3;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r3;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t2_r3;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r3;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r4;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r4;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t2_r4;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r4;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r5;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r5;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t2_r5;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r5;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r6;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r6;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t2_r6;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r6;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r7;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r7;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t2_r7;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r7;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r8;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r8;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t2_r8;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r8;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r9;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r9;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t2_r9;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r9;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r10;
                                                                 unsigned __CPROVER_bitvector[4] tmp_t1_r10;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t2_r10;
                                                                 unsigned __CPROVER_bitvector[5] tmp_t3_r10;
                                                                 unsigned __CPROVER_bitvector[3] tmp_t0_r11;
                                                       
                                                                 unsigned __CPROVER_bitvector[8] top1 = 9;
                                                                 unsigned __CPROVER_bitvector[8] sum1 = tmp_t1_r0 + tmp_t1_r1 + tmp_t1_r2 + tmp_t1_r3 + tmp_t1_r4 + tmp_t1_r5 + tmp_t1_r6 + tmp_t1_r7 + tmp_t1_r8 + tmp_t1_r9 + tmp_t1_r10;
                                                                 assume(sum1 <= top1);
                                                                 unsigned __CPROVER_bitvector[9] top2 = 18;
                                                                 unsigned __CPROVER_bitvector[9] sum2 = tmp_t2_r0 + tmp_t2_r1 + tmp_t2_r2 + tmp_t2_r3 + tmp_t2_r4 + tmp_t2_r5 + tmp_t2_r6 + tmp_t2_r7 + tmp_t2_r8 + tmp_t2_r9 + tmp_t2_r10;
                                                                 assume(sum2 <= top2);
                                                                 unsigned __CPROVER_bitvector[9] top3 = 17;
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
                                                                 if (active_thread[thread_index] == 1) { // loader_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r0;
                                                                    loader_0(threadargs[1]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r0;
                                                                    thread1_0(threadargs[2]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r0;
                                                                    thread2_0(threadargs[3]);
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
                                                                 if (active_thread[thread_index] == 1) { // loader_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r1;
                                                                    loader_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r1;
                                                                    thread1_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r1;
                                                                    thread2_0(threadargs[thread_index]);
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
                                                                 if (active_thread[thread_index] == 1) { // loader_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r2;
                                                                    loader_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r2;
                                                                    thread1_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r2;
                                                                    thread2_0(threadargs[thread_index]);
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
                                                                 if (active_thread[thread_index] == 1) { // loader_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r3;
                                                                    loader_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r3;
                                                                    thread1_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r3;
                                                                    thread2_0(threadargs[thread_index]);
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
                                                                 if (active_thread[thread_index] == 1) { // loader_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r4;
                                                                    loader_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r4;
                                                                    thread1_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r4;
                                                                    thread2_0(threadargs[thread_index]);
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
                                                                 if (active_thread[thread_index] == 1) { // loader_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r5;
                                                                    loader_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r5;
                                                                    thread1_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r5;
                                                                    thread2_0(threadargs[thread_index]);
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
                                                                 if (active_thread[thread_index] == 1) { // loader_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r6;
                                                                    loader_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r6;
                                                                    thread1_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r6;
                                                                    thread2_0(threadargs[thread_index]);
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
                                                                 if (active_thread[thread_index] == 1) { // loader_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r7;
                                                                    loader_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r7;
                                                                    thread1_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r7;
                                                                    thread2_0(threadargs[thread_index]);
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
                                                                 if (active_thread[thread_index] == 1) { // loader_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r8;
                                                                    loader_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r8;
                                                                    thread1_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r8;
                                                                    thread2_0(threadargs[thread_index]);
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
                                                                 if (active_thread[thread_index] == 1) { // loader_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r9;
                                                                    loader_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r9;
                                                                    thread1_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r9;
                                                                    thread2_0(threadargs[thread_index]);
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
                                                                 if (active_thread[thread_index] == 1) { // loader_0
                                                                    pc_cs[1] = pc[1] + tmp_t1_r10;
                                                                    loader_0(threadargs[thread_index]);
                                                                    pc[1] = pc_cs[1];
                                                                 }
                                                       
                                                                 thread_index = 2;
                                                                 if (active_thread[thread_index] == 1) { // thread1_0
                                                                    pc_cs[2] = pc[2] + tmp_t2_r10;
                                                                    thread1_0(threadargs[thread_index]);
                                                                    pc[2] = pc_cs[2];
                                                                 }
                                                       
                                                                 thread_index = 3;
                                                                 if (active_thread[thread_index] == 1) { // thread2_0
                                                                    pc_cs[3] = pc[3] + tmp_t3_r10;
                                                                    thread2_0(threadargs[thread_index]);
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
                                                       


