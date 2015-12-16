int g;

void thr() {
  int junk = 0;
  g = 0;
  junk++;
  junk++;
  junk++;
  g++;
  junk++;
  junk++;
  assert(g <=2);
  junk++;
  junk++;
  junk++;
  junk++;
  junk++;
}
