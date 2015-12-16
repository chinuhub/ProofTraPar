int x=1, m=0;

#define acquire_thread_id(tid, l) \
  { __blockattribute__((atomic)) \
    assume(l==0); \
    l = tid; \
  } \

void thr1() {
  acquire_thread_id(1, m); // m=0 /\ m'=1
  x = 0;
  x = 1;
  assert(x>=1);
  release(m);
}

void thr2() {
  acquire_thread_id(2, m); // m=0 /\ m'=2
  x = 0;
  x = 1;
  assert(x>=1);
  release(m);
}

