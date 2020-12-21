#include <stdio.h>
#include "omp.h"
int main()
{
  // till here there is only 1 thread
#pragma omp parallel
  {
    printf("E is the second vowel\n");
  }
  // from here again there is only 1 thread
}
