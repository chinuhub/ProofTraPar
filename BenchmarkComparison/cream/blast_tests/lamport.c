#include "preamble.h"

int x, y, b1, b2; // global variables
int X;
int pc1, pc2;
int NONDET ;

int main() {
  pc1 = 1; pc2 = 1;
  while (1) {
    if (NONDET) { // thread thr1

      switch (pc1) {
      case 1: // beginning of outer loop
	b1 = 1; pc1 = 3; break;
      case 3:
	x = 1; pc1 = 4; break;
      case 4:
	if (y != 0) { pc1 = 5; break; } else { pc1 = 8; break; }
      case 5:
	b1 = 0; pc1 = 6; break;
      case 6:
	if (y != 0) { pc1 = 6; break; } else { pc1 = 1; break; }
      case 8:
	y = 1; pc1 = 9; break;
      case 9:
	if (x != 1) { pc1 = 10; break; } else { pc1 = 14; break; }
      case 10:
	b1 = 0; pc1 = 11; break;
      case 11:
	if (b2 == 1) { pc1 = 11; break; } else { pc1 = 12; break; }
      case 12:
	if (y != 1) { pc1 = 13; break; } else { pc1 = 14; break; }
      case 13:
	if (y != 0) { pc1 = 13; break; } else { pc1 = 1; break; }
      case 14: // enter critical section
	X = 0; pc1 = 15; break;
      case 15:
	assert(X <= 0); pc1 = 16; break;
      case 16:
	y = 0; pc1 = 17; break;
      case 17:
	b1 = 0; pc1 = 18; break;
	//case 18: dead end
      }

    } else { // thread thr2

      switch (pc2) {
      case 1: // beginning of outer loop
	b2 = 1; pc2 = 3; break;
      case 3:
	x = 2; pc2 = 4; break;
      case 4:
	if (y != 0) { pc2 = 5; break; } else { pc2 = 8; break; }
      case 5:
	b2 = 0; pc2 = 6; break;
      case 6:
	if (y != 0) { pc2 = 6; break; } else { pc2 = 1; break; }
      case 8:
	y = 2; pc2 = 9; break;
      case 9:
	if (x != 2) { pc2 = 10; break; } else { pc2 = 14; break; }
      case 10:
      	b2 = 0; pc2 = 11; break;
      case 11:
	if (b1 == 1) { pc2 = 11; break; } else { pc2 = 12; break; }
      case 12:
	if (y != 2) { pc2 = 13; break; } else { pc2 = 14; break; }
      case 13:
	if (y != 0) { pc2 = 13; break; } else { pc2 = 1; break; }
      case 14: // enter critical section
	X = 1; pc2 = 15; break;
      case 15:
	X = 0; pc2 = 16; break;
      case 16:
	y = 0; pc2 = 17; break;
      case 17:
	b2 = 0; pc2 = 18; break;
	//case 18: dead end
      }

    }
  }
}
