# 1 "../c_tests/peterson.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "../c_tests/peterson.c"
int turn;
int x;
int flag1 = 0, flag2 = 0;

void thr1() {
  flag1 = 1;
  turn = 1;
  do {} while (flag2==1 && turn==1);

  x = 0;
  assert(x<=0);

  flag1 = 0;
}

void thr2() {
  flag2 = 1;
  turn = 0;
  do {} while (flag1==1 && turn==0);

  x = 1;
  assert (x>=1);

  flag2 = 0;
}
