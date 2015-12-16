int lock=0;
int x;

#define acquire_thread_id(tid, l) \
  { __blockattribute__((atomic)) \
    assume(l==0); \
    l = tid; \
  } \

void thr1() {
  acquire_thread_id(1, lock); // lock=0 /\ lock'=1 
  while (x>0) {
    x = x-1;
  }
  release(lock);
}

void thr2() {
  int NONDET;
  while (NONDET) {
    acquire_thread_id(2, lock); // lock=0 /\ lock'=2 
    x = NONDET;
    release(lock);
  }
}
