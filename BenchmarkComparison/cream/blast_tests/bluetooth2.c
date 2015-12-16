#include "preamble.h"

int stopped; // global variables
int driverStoppingFlag;
int stoppingEvent;
int pendingIo;
int status1, PIo11, PIo12; // local variables of adder
int PIo21; // local variable of stopper
int pc1, pc2;
int NONDET ;


int main() {
  stopped = 0; driverStoppingFlag = 0; stoppingEvent = 0; pendingIo = 1;
  pc1 = 1; pc2 = 1;
  while (1) {
    if (NONDET) { // thread adder

      switch (pc1) {
      case 1: 
	pendingIo = pendingIo + 1; pc1 = 2; break;
      case 2:
	if (driverStoppingFlag == 1) {
	  pc1 = 3; break;
	} else {
	  pc1 = 8; break;
	}
      case 3:
	PIo11 = pendingIo - 1; pc1 = 4; break;
      case 4:
	pendingIo = pendingIo - 1; pc1 = 5; break;
      case 5:
	if (PIo11 == 0) {
	  pc1 = 6; break;
	} else {
	  pc1 = 7; break;
	}
      case 6:
	stoppingEvent = 1; pc1 = 7; break;
      case 7:
	status1 = 0; pc1 = 9; break;
      case 8:
	status1 = 1; pc1 = 9; break;
      case 9:
	if (status1 == 1) {
	  pc1 = 10; break;
	} else {
	  pc1 = 11; break;
	}
      case 10:
	assert(stopped==0); pc1 = 11; break;
      case 11:
	PIo12 = pendingIo - 1; pc1 = 12; break;
      case 12:
	pendingIo = pendingIo - 1; pc1 = 13; break;
      case 13:
	if (PIo12 == 0) {
	  pc1 = 14; break;
	} else {
	  pc1 = 15; break;
	}
      case 14: 
	stoppingEvent = 1; pc1 = 15; break;
	// case 15: end
      }

    } else {
      if (NONDET) { // thread stopper

	switch (pc2) {
	case 1:
	  driverStoppingFlag = 1; pc2 = 2; break;
	case 2:
	  PIo21 = pendingIo - 1; pc2 = 3; break;
	case 3:
	  pendingIo = pendingIo - 1; pc2 = 4; break;
	case 4:
	  if (PIo21 == 0) {
	    pc2 = 5; break;
	  } else {
	    pc2 = 6; break;
	  }
	case 5: 
	  stoppingEvent = 1; pc2 = 6; break;
	case 6:
	  if (stoppingEvent == 0) {
	    pc2 = 6; break;
	  } else {
	    pc2 = 7; break;
	  }
	case 7:
	  stopped = 1; pc2 = 8; break;
	  // case 8: end
	}

      } else { 
      }
    }
  }
}

