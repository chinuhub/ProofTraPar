int x=0, m=0;
int can_start = 0;
int done = 0;

void thr1() {
  { __blockattribute__((atomic))
    can_start = can_start - 1;
    assume(can_start >= 0);
  }
  acquire(m); // m=0 /\ m'=1
  x = 2;
  release(m);
  done = done + 1;
}

void thr2() {
  { __blockattribute__((atomic))
    can_start = can_start - 1;
    assume(can_start >= 0);
  }
  acquire(m); // m=0 /\ m'=1
  if (x == 0) { x = x + 2; }
  release(m);
  done = done + 1;
}

int main() {
  int x_out_1;
  int x_in_1 = x;
  can_start = 2; // fork thr1(); fork thr2();
  assume(done >= 2); // join
  x_out_1 = x;
  x = x_in_1;
  can_start = 2; // fork thr1(); fork thr2();
  assume(done >= 4); // join
  assert(x_out_1 == x);
}

