#include "common.h"

int main(int argc, char *argv[])
{
  int n, ld, nb;

  set_params(argc, argv, &n, &nb, &ld);
  
  /* malloc A[n+1][ld] */
  double (*A)[ld] = malloc(sizeof(double) * (n+1) * ld);

  /* A[n][0..n-1] is x[0..n-1] */
  double *b = &A[n][0];

  set_value(n, ld, A, b);

  timer_clear();
  timer_start(TOTAL);
  lu_decomp(n, nb, ld, A, b);
  lu_solve(n, nb, ld, A, b);
  timer_stop(TOTAL);

  timer_print();
  print_performance(n);

  //print_mat(n, ld, A);
  //  print_sol(n, b);
  verification(n, ld, A, b);

  free(A);
  return 0;
}