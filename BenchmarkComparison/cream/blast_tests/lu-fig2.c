#include "preamble.h"

int mThread;
int start_main;
int __CNT__;
int PR_CreateThread__RES;
int self;
int rv;
int pc1, pc2;
int NONDET ;

int main() {
  mThread = 0; start_main = 0; __CNT__ = 0; pc1 = 1; pc2 = 1;
  while (1) {
    if (NONDET) { // thread thr1

      switch (pc1) {
      case 1: 
	PR_CreateThread__RES = 1; pc1 = 2; break;
      case 2:
	start_main = 1; pc1 = 3; break;
      case 3:
	{__blockattribute__((atomic))
	    if (__CNT__ == 0) {
	      mThread = PR_CreateThread__RES;
	      __CNT__ = __CNT__ + 1;
	    } else {
	      assert(0);
	    }
	}; pc1 = 4; break;
      case 4:
	if (mThread == 0) {
	  pc1 = 5; break;
	} else {
	  pc1 = 5; break;
	}
      }
	

    } else { // thread thr2
      switch (pc2) {
      case 1:
	self = mThread; pc2 = 2; break;
      case 2:
	if (start_main == 0) {
	  pc2 = 2; break;
	} else {
	  pc2 = 3; break;
	}
      case 3:
	{__blockattribute__((atomic))
	  rv = self;
	  __CNT__ = __CNT__ + 1;
	}; pc2 = 4; break;
      }

    }
  }
}
