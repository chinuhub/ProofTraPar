int x, y;

void thr1() {
  while (x>0 && y>0) {
    { __blockattribute__((atomic))
      x = x-1;
      y = x;
    } 
  }
}    

void thr2() {
  while (x>0 && y>0) {
    { __blockattribute__((atomic))
      x = y-2;
      y = x+1;
    } 
  }
}
