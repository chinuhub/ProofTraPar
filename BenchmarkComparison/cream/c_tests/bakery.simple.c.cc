# 1 "c_tests/bakery.simple.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "c_tests/bakery.simple.c"
int t1=0, t2=0;
int x;

thr1() {
  while (1) {
    t1 = t2 + 1;
    while( t1 >= t2 && ( t2 > 0 ) ) {};
    x=0;
    assert(x <= 0);
    t1 = 0;
  }
}

thr2() {
  while (1) {
    t2 = t1 + 1;
    while( t2 >= t1 && ( t1 > 0 ) ) {};
    x = 1;
    assert(x >= 1);
    t2 = 0;
  }
}
