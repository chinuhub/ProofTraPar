# 1 "../c_tests/lamport.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "../c_tests/lamport.c"
int x;
int y;
int b1, b2;
int X;

void thr1() {
  while (1) {
    b1 = 1;
    x = 1;
    if (y != 0) {
      b1 = 0;
      while (y != 0) {};
      continue;
    }
    y = 1;
    if (x != 1) {
      b1 = 0;
      while (b2 >= 1) {};
      if (y != 1) {
 while (y != 0) {};
 continue;
      }
    }
    break;
  }

  X = 0;
  assert(X <= 0);

  y = 0;
  b1 = 0;
}

void thr2() {
  while (1) {
    b2 = 1;
    x = 2;
    if (y != 0) {
      b2 = 0;
      while (y != 0) {};
      continue;
    }
    y = 2;
    if (x != 2) {
      b2 = 0;
      while (b1 >= 1) {};
      if (y != 2) {
 while (y != 0) {};
 continue;
      }
    }
    break;
  }

  X = 1;
  assert(X >= 1);

  y = 0;
  b2 = 0;
}
