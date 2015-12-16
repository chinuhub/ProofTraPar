#include "preamble.h"

int choosing1, choosing2; // global variables
int number1, number2;
int x;
int tmp1; // local variables of thr1
int tmp2; // local variables of thr2
int pc1, pc2;
int NONDET ;

int main() {
  choosing1 = 0; choosing2 = 0; number1 = 0;
  number2 = 0; pc1 = 1; pc2 = 1;
  while (1) {
    if (NONDET) { // thread thr1

      switch (pc1) {
      case 1:
	choosing1 = 1; pc1 = 2; break;
      case 2: 
	tmp1 = number2 + 1; pc1 = 3; break;
      case 3:
	number1 = tmp1; pc1 = 4; break;
      case 4:
	choosing1 = 0; pc1 = 5; break;
      case 5:
	if (choosing2 != 0) {
	  pc1 = 5; break;
	} else {
	  pc1 = 6; break;
	}
      case 6:
	if (number1 >= number2 && number2 != 0) {
	  pc1 = 6; break;
	} else {
	  pc1 = 7; break;
	}
      case 7:
	x = 0; pc1 = 8; break;
      case 8:
	assert(x <= 0); pc1 = 9; break;
      case 9:
	number1 = 0; pc1 = 10; break;
      }

    } else { // thread thr2

      switch (pc2) {
      case 1:
	choosing2 = 1; pc2 = 2; break;
      case 2: 
	tmp2 = number1 + 1; pc2 = 3; break;
      case 3:
	number2 = tmp2; pc2 = 4; break;
      case 4:
	choosing2 = 0; pc2 = 5; break;
      case 5:
	if (choosing1 != 0) {
	  pc2 = 5; break;
	} else {
	  pc2 = 6; break;
	}
      case 6:
	if (number2 >= number1 && number1 != 0) {
	  pc2 = 6; break;
	} else {
	  pc2 = 7; break;
	}
      case 7:
	x = 1; pc2 = 8; break;
      case 8:
	x = 0; pc2 = 9; break;
      case 9:
	number2 = 0; pc2 = 10; break;
      }

    }
  }
}
