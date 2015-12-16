int g;
int g1 = 0;
int g2 = 0;

void thr1() {
  int l1;
  int junk = 0;
  glb_init(l1==0);
  junk++;
  junk++;
  junk++;
  junk++;
  junk++;
  while (l1 < g) {
    l1 = l1 + 1;
  }
  junk++;
  junk++;
  junk++;
  junk++;
  junk++;
  g1 = l1;
}

void thr2() {
  int l2;
  int junk = 0;
  glb_init(l2==0);
  junk++;
  junk++;
  junk++;
  junk++;
  junk++;
  while (l2 < g) {
    l2 = l2 + 1;
  }
  junk++;
  junk++;
  junk++;
  junk++;
  junk++;
  g2 = l2;
}

int main() {
  glb_init(g>0);
  assert(g1 <= g);
  assert(g2 <= g);
  assert(g1+g2 <= 2*g);
}
