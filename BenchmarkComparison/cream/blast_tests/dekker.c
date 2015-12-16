#include "preamble.h"

int flag1, flag2; // N boolean flags 
int turn; // integer variable to hold the ID of the thread whose turn is it
int x; // variable to test mutual exclusion
int pc1, pc2;
int NONDET ;

int main() {
  flag1 = 0; flag2 = 0; turn = 0; pc1 = 1; pc2 = 1;
  while (1) {
    if (NONDET) { // thread thr1

      switch (pc1) {
      case 1: 
	flag1 = 1; pc1 = 2; break;
      case 2: 
	if (flag2 == 1) {
	  pc1 = 3; break;
	} else {
	  pc1 = 7; break;
	}
      case 3: 
	if (turn!=0) {
	  pc1 = 4; break;
	} else {
	  pc1 = 2; break;
	}
      case 4:
	flag1 = 0; pc1 = 5; break;
      case 5:
	if (turn != 0) {
	  pc1 = 5; break;
	} else {
	  pc1 = 6; break;
	}
      case 6:
	flag1 = 1; pc1 = 2; break;
      case 7:
	x = 0; pc1 = 8; break;
      case 8:
	assert(x<=0); pc1 = 9; break;
      case 9:
	turn = 1; pc1 = 10; break;
      case 10:
	flag1 = 0; pc1 = 11; break;
      }

    } else { // thread thr2

      switch (pc2) {
      case 1: 
	flag2 = 1; pc2 = 2; break;
      case 2: 
	if (flag1 == 1) {
	  pc2 = 3; break;
	} else {
	  pc2 = 7; break;
	}
      case 3: 
	if (turn != 0) {
	  pc2 = 4; break;
	} else {
	  pc2 = 2; break;
	}
      case 4:
	flag2 = 0; pc2 = 5; break;
      case 5:
	if (turn != 0) {
	  pc2 = 5; break;
	} else {
	  pc2 = 6; break;
	}
      case 6:
	flag2 = 1; pc2 = 2; break;
      case 7:
	x = 1; pc2 = 8; break;
      case 8:
	x = 1; pc2 = 9; break;
      case 9:
	turn = 1; pc2 = 10; break;
      case 10:
	flag2 = 0; pc2 = 11; break;
      }

    }
  }
}
