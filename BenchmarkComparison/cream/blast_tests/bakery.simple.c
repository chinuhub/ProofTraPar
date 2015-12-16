#include "preamble.h"

int t1, t2; // N integer tickets
int x; // variable to test mutual exclusion
int pc1, pc2;
int NONDET ;

int main() {
  t1 = 0; t2 = 0; pc1 = 1; pc2 = 1;
  while (1) {
    if (NONDET) { // thread thr1

      switch (pc1) {
      case 1: 
	t1 = t2 + 1; pc1 = 2; break;
      case 2:
	if (t1 >= t2 && t2 != 0) {
	  pc1 = 2; break;
	} else {
	  pc1 = 3; break;
	}
      case 3:
	x = 0; pc1 = 4; break;
      case 4:
	assert(x <= 0); pc1 = 5; break;
      case 5:
	t1 = 0; pc1 = 1; break;
      }

    } else { // thread thr2

      switch (pc2) {
      case 1:
	t2 = t1 + 1; pc2 = 2; break;
      case 2:
	if (t2 >= t1 && t1 != 0) {
	  pc2 = 2; break;
	} else {
	  pc2 = 3; break;
	}
      case 3:
	x = 0; pc2 = 4; break;
      case 4: 
	x = 1; pc2 = 5; break;
      case 5:
	t2 = 0; pc2 = 1; break;
      }

    }
  }
}
