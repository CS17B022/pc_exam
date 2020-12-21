#include <stdio.h>
#include <omp.h>
#define N 100000
int main(void) { 
  float a[N], b[N], c[N];
  int i;

  /* Initialize arrays a and b */
  for (i = 0; i < N; i++) {
    a[i] = i * 2.0;
    b[i] = i * 3.0;
  }

  // till here only 1 thread
  /* Compute values of array c = a + b in parallel. */
  // launch threads here
  // divide the work (am I leaving some computation?)
  // maintain locks etc
//#pragma omp parallel shared(a, b, c) private(i)
  { 
#pragma omp for             
    for (i = 0; i < N; i++) {
      c[i] = a[i] + b[i];
    }
  }
  // threads are joined
  // implicit join
  // so now only 1 thread  
  for (i = 0; i < 10; i++) {
    printf("c[%d]: %f\n", i, c[i]);
  }

  return 0;
}
