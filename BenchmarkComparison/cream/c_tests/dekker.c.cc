# 1 "../c_tests/dekker.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "../c_tests/dekker.c"


int flag1 = 0, flag2 = 0;
int turn = 0;
int x;

void thr1() {
  flag1 = 1;
  while (flag2 >= 1) {
    if (turn != 0) {
      flag1 = 0;
      while (turn != 0) {};
      flag1 = 1;
    }
  }

  x = 0;
  assert(x<=0);

  turn = 1;
  flag1 = 0;
}

void thr2() {
  flag2 = 1;
  while (flag1 >= 1) {
    if (turn != 1) {
      flag2 = 0;
      while (turn != 1) {};
      flag2 = 1;
    }
  }

  x = 1;
  assert(x>=1);

  turn = 1;
  flag2 = 0;
}
