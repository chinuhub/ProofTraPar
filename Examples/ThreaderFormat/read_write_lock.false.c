int w, r, x, y;

void thr1() { //writer
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

void thr2() { //reader
int l;
  { __blockattribute__((atomic))
    assume(w==0);
    r = r+1;
  }
  y = x;
  assert(y == x);
  l = r-1;
  r = l;/** Breaking this atomic operation r=r-1 to two should cause assertions to fail*/
}


void thr3() { //writer
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

void thr4() { //reader
int l;
  { __blockattribute__((atomic))
    assume(w==0);
    r = r+1;
  }
  y = x;
  assert(y == x);
  l = r-1;
  r = l;/*Breaking this atomic operation r=r-1 to two should cause assertions to fail*/
}
