#include <stdio.h>
#include <omp.h>
#include "mpi.h"

const int nthreads = 4; 

int main (int argc, char **argv) {
  int np;
  int rank;
  int total_threads;
  int tid;

  omp_set_num_threads(nthreads);
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

#pragma omp parallel private(tid) reduction(+:total_threads)
  {
    // here: each process will have 4 threads
    // and the memory among the 4 threads on a particular process is shared
    // but memory among the t0 of p0 and t0 of p1 is NOT shared
    //
    tid = omp_get_thread_num();
    // 4 threads
    // tid = 0, 1, 2, 3
    printf("rank: %d tid: %d\n", rank, tid);
    tid += 1;
    // tid = 1, 2, 3, 4
    total_threads += tid;
    // total on one thread will be 10
  }
  // I want to find out what is the total_total_threads value
  // across processes
  // MPI_Send(total_threads)
  // MPI_Recv
  // the person who received will actually compute the sum
  printf("rank: %d total_threads: %d\n", rank, total_threads);

  MPI_Finalize();
  return 0;
}
