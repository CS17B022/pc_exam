#include <stdio.h>
#include <omp.h>
int main()
{
  int i = 0; // a shared variable
#pragma omp parallel
  {
    int x; // a variable local or private to each thread
    x = omp_get_thread_num();
#pragma omp critical 
    i++;
#pragma omp barrier
    printf("i = %d thread_id = %d\n", i, x);
  }
  printf("--------------\n");
}
