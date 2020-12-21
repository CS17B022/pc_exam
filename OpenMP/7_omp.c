#include <stdio.h>
#include <omp.h>
#define N 100
int main(void) { 
  float a[N], b[N], c[N];
  int i = 0;
  float total = 0.0;

  /* Initialize arrays a and b */
  for (int i = 0; i < N; i++) {
    a[i] = i * 2.0;
    b[i] = i * 3.0;
  }

  // till here only 1 thread
  /* Compute values of array c = a + b in parallel. */
#pragma omp parallel for
  for (i = 0; i < N; i++) {
    // the issue is that you are serializing the code
    // so no use of parallelism!! :(
    total += a[i] + b[i];
  }
  // implicit join
  // so now only 1 thread  

  printf ("total = %lf\n", total);
  return 0;
}
