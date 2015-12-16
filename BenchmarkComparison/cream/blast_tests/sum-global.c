#include "preamble.h"

int g, g1, g2;
int pc1, pc2, pc3;
int NONDET ;



int main() {
  g1 = 0; g2 = 0; pc1 = 1; pc2 = 1; pc3 = 1;
  assume(g>0);
  while (1) {
    if (NONDET) { // thread main
      switch (pc1) {
      case 1: assert(g1+g2 <= g+g); pc1 = 2; break;
      }
    } else {
      if (NONDET) { // thread thr1
	switch (pc2) {
	case 1:
	  if (g1<g) {
	    pc2 = 2; break;
	  } else {
	    pc2 = 3; break;
	  }
	case 2: g1 = g1+1; pc2 = 1; break;
	}
      } else { // thread thr2
	switch (pc3) {
	case 1:
	  if (g2<g) {
	    pc3 = 2; break;
	  } else {
	    pc3 = 3; break;
	  }
	case 2: g2 = g2+1; pc3 = 1; break;
	}
      }
    }
  }
}

