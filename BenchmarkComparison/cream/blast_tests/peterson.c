#include "preamble.h"

int turn; // integer variable to hold the ID of the thread whose turn is it
int x; // variable to test mutual exclusion
int flag1, flag2;
int pc1, pc2;
int NONDET ;


int main() {
  turn = 0; pc1 = 1; pc2 = 1;
  while (1) {
    if (NONDET) { // thread thr1

      switch (pc1) {
      case 1: 
	flag1 = 1; pc1 = 2; break;
      case 2:
	turn = 1; pc1 = 3; break;
      case 3:
	if (flag1 && turn == 1) {
	  pc1 = 3; break;
	} else {
	  pc1 = 4; break;
	}
      case 4:
	x = 0; pc1 = 5; break;
      case 5:
	assert(x<=0); pc1 = 6; break;
      case 6:
	flag1 = 0; pc1 = 7; break;
      }

    } else { // thread thr2

      switch (pc2) {
      case 1: 
	flag2 = 1; pc2 = 2; break;
      case 2:
	turn = 1; pc2 = 3; break;
      case 3:
	if (flag2 && turn == 0) {
	  pc2 = 3; break;
	} else {
	  pc2 = 4; break;
	}
      case 4:
	x = 0; pc2 = 5; break;
      case 5:
	x=1; pc2 = 6; break;
      case 6:
	flag2 = 0; pc2 = 7; break;
      }

    }
  }
}
