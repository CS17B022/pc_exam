#include <stdio.h>
#include <omp.h>
int main()
{
  int i = 0; // a shared variable
#pragma omp parallel
  {
    // in this case there will be 4 threads running concurrently (atleast assume so)
    int x; // a variable local or private to each thread
    x = omp_get_thread_num();
    // if I use critical, only one thread can enter the code block
#pragma omp critical
    i++;
#pragma omp barrier
    printf("i = %d thread_id = %d\n", i, x);
  }
  printf("--------------\n");
}
