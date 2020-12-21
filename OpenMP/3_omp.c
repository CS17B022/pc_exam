#include <stdio.h>
#include <omp.h>
int main()
{
  int i = 256; // a shared variable
#pragma omp parallel
  {
    // multiple threads here
    // thread number 3;
    int x; // a variable local or private to each thread
    x = omp_get_thread_num();
    // x = 3
    if (x == 1) {
      i = 9;
    }
    // what do I mean by a barrier
    // all threads will wait for the barrier, and then go to the next statement
    // it means all statements before this barrier have been executed by all threads
#pragma omp barrier
    printf("i = %d thread_id = %d\n", i, x);
  }
  printf("--------------\n");
}
