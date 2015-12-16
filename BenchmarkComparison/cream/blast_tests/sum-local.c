#include "preamble.h"

int g, g1, g2;
int l1, l2;
int pc1, pc2, pc3;
int NONDET ;



int main() {
  g1 = 0; g2 = 0; l1 = 0; l2 = 0; pc1 = 1; pc2 = 1; pc3 =1;
  assume(g > 0);
  while (1) {
    if (NONDET) { // thread main
      switch (pc1) {
      case 1: assert(g1+g2 <= g+g); pc1 = 2; break;
      }
    } else {
      if (NONDET) { // thread thr1
	switch (pc2) {
	case 1:
	  if (l1<g) {
	    pc2 = 2; break;
	  } else {
	    pc2 = 3; break;
	  }
	case 2: l1 = l1+1; pc2 = 1; break;
	case 3: g1 = l1; pc2 = 4; break;
	}
      } else { // thread thr2
	switch (pc3) {
	case 1:
	  if (l2<g) {
	    pc3 = 2; break;
	  } else {
	    pc3 = 3; break;
	  }
	case 2: l2 = l2+1; pc3 = 1; break;
	case 3: g2 = l2; pc3 = 4; break;
	}
      }
    }
  }
}

