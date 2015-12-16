# 1 "../../Examples/ThreaderFormat/read_write_lock.false.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "../../Examples/ThreaderFormat/read_write_lock.false.c"
int w, r, x, y;

void thr1() {
  glb_init(w==0);
  glb_init(r==0);
  { __blockattribute__((atomic))
    assume(w==0);
    assume(r==0);
    w = 1;
  }
  x = 3;
  w = 0;
}

void thr2() {
int l;
  { __blockattribute__((atomic))
    assume(w==0);
    r = r+1;
  }
  y = x;
  assert(y == x);
  l = r-1;
  r = l;
}


void thr3() {
  glb_init(w==0);
  glb_init(r==0);
  { __blockattribute__((atomic))
    assume(w==0);
    assume(r==0);
    w = 1;
  }
  x = 3;
  w = 0;
}

void thr4() {
int l;
  { __blockattribute__((atomic))
    assume(w==0);
    r = r+1;
  }
  y = x;
  assert(y == x);
  l = r-1;
  r = l;
}
