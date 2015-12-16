int lock=0;
int x;

void thr1() {
  int t;
  acquire(lock);
  while (x>0) {
    t = x-1;
    x = t;
  }
  release(lock);
}

void thr2() {
  int NONDET;
  while (NONDET) {
    acquire(lock);
    x = NONDET;
    release(lock);
  }
}
