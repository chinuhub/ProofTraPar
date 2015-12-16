#ifdef BLAST
#define NONDET __BLAST_NONDET
#define assume(b) {__blockattribute__((assume(b)))}
#define assert(b) if((b)==0){ ERROR: goto ERROR; }
#endif

