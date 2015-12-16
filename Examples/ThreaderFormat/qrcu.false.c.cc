# 1 "../../Examples/ThreaderFormat/qrcu.false.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "../../Examples/ThreaderFormat/qrcu.false.c"



int idx;
int ctr1, ctr2;
int readerprogress1, readerprogress2;
int mutex;
int NONDET;

void* qrcu_reader1() {
  int myidx;


  while (1) {
    myidx = idx;
    if (NONDET) {
      { __blockattribute__((atomic))
 assume(myidx <= 0);
 assume(ctr1>0);
 ctr1++;
      }
      break;
    } else {
      if (NONDET) {
 { __blockattribute__((atomic))
   assume(myidx > 0);
   assume(ctr2>0);
   ctr2++;
 }
 break;
      } else {}
    }
  }
# 46 "../../Examples/ThreaderFormat/qrcu.false.c"
  readerprogress1 = 1;
  readerprogress1 = 2;


  { __blockattribute__((atomic))
      if (myidx <= 0) { ctr1--; }
      else { ctr2--; }
  }
}
# 66 "../../Examples/ThreaderFormat/qrcu.false.c"
void* qrcu_updater() {
  int i;
  int readerstart1=1;
  int readerstart2=1;
  int sum;

  glb_init(idx==0);
  glb_init(ctr1==1);
  glb_init(ctr2==0);
  glb_init(readerprogress1==0);
  glb_init(readerprogress2==0);
  glb_init(mutex==0);







  if (NONDET) { sum = ctr1; sum = sum + ctr2; } else { sum = ctr2; sum = sum + ctr1; };
  if (sum <= 1) { if (NONDET) { sum = ctr1; sum = sum + ctr2; } else { sum = ctr2; sum = sum + ctr1; }; }
  if (sum > 1) {
    acquire(mutex);
    if (idx <= 0) { ctr2++; idx = 1; ctr1--; }
    else { ctr1++; idx = 0; ctr2--; }
    if (idx <= 0) { while (ctr2 > 0); }
    else { while (ctr1 > 0); }
    release(mutex);
  }


  { __blockattribute__((atomic))
      if (NONDET) {
 assume(readerstart1 == 1);
 assume(readerprogress1 == 1);
 assert(0);
      } else {
 if (NONDET) {
   assume(readerstart2 == 1);
   assume(readerprogress2 == 1);
   assert(0);
 } else { }
      }
  }
# 120 "../../Examples/ThreaderFormat/qrcu.false.c"
}

void* qrcu_reader2() {
  int myidx;


  while (1) {
    myidx = idx;
    if (NONDET) {
      { __blockattribute__((atomic))
 assume(myidx <= 0);
 assume(ctr1>0);
 ctr1++;
      }
      break;
    } else {
      if (NONDET) {
 { __blockattribute__((atomic))
   assume(myidx > 0);
   assume(ctr2>0);
   ctr2++;
 }
 break;
      } else {}
    }
  }

  readerprogress2 = 1;
  readerprogress2 = 2;


  { __blockattribute__((atomic))
      if (myidx <= 0) { ctr1--; }
      else { ctr2--; }
  }
}
