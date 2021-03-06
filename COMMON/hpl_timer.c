#include "common.h"

static double elapsed_time( void )
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec + 1.0e-6 * t.tv_usec;
}

void timer_clear()
{
  for(int i=0;i<NUM_TIMERS;i++)
    elapsed[i] = 0.0;
}

void timer_start( int n )
{
  start[n] = elapsed_time();
}

void timer_stop( int n )
{
  double now = elapsed_time();
  double t = now - start[n];
  elapsed[n] += t;
}

double timer_read( int n )
{
  return( elapsed[n] );
}

void timer_print(){
  printf("---\n");
  printf("TOTAL     : %6.2f s \n", timer_read(TOTAL));
  printf("---\n");
#define CAT(c_) timer_read(c_), timer_read(c_)/timer_read(TOTAL)*100
#ifdef _BLOCKING
  printf("LU       : %6.2f s (%4.2f%%)\n", CAT(LU));
  printf(" - PANEL   : %6.2f s (%4.2f%%)\n", CAT(PANEL));
  printf("   - PIVOT   : %6.2f s (%4.2f%%)\n", CAT(PANEL_PIVOT));
  printf("   - SWAP    : %6.2f s (%4.2f%%)\n", CAT(PANEL_SWAP));
  printf("   - DSCAL   : %6.2f s (%4.2f%%)\n", CAT(PANEL_DSCAL));
  printf("   - DGER    : %6.2f s (%4.2f%%)\n", CAT(PANEL_DGER));
  printf("   - DTRSM   : %6.2f s (%4.2f%%)\n", CAT(PANEL_DTRSM));
  printf("   - DGEMM   : %6.2f s (%4.2f%%)\n", CAT(PANEL_DGEMM));
  printf(" - SWAP    : %6.2f s (%4.2f%%)\n", CAT(SWAP));
  printf(" - DTRSM   : %6.2f s (%4.2f%%)\n", CAT(DTRSM));
  printf(" - DGEMM   : %6.2f s (%4.2f%%)\n", CAT(DGEMM));
  printf("DSOLVE   : %6.2f s (%4.2f%%)\n", CAT(DSOLVE));
#else
  printf("LU        : %6.2f s (%4.2f%%)\n", CAT(LU));
  printf(" - PIVOT    : %6.2f s (%4.2f%%)\n", CAT(PANEL_PIVOT));
  printf(" - SWAP     : %6.2f s (%4.2f%%)\n", CAT(SWAP));
  printf(" - PANEL    : %6.2f s (%4.2f%%)\n", CAT(PANEL));
  printf(" - UPDATE   : %6.2f s (%4.2f%%)\n", CAT(PANEL_DGER));
  printf("DSOLVE    : %6.2f s (%4.2f%%)\n", CAT(DSOLVE));
#endif
  printf("---\n");
  fflush(stdout);
}

