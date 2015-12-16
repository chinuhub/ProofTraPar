int x=1;
int y=0;

void thr1() {
  while (x=1) {
    y = y+1;
  }
  while (y>0) {
    y = y-1;
  }
}

void thr2() {
  x = 0;
}
