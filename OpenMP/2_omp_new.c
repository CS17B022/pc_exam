#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "omp.h"
int main()
{
  int i = 5;
#pragma omp parallel
  {
    printf("E is equal to %d\n",i);
  }
}
