#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{

  int rank;
  int np;
  

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);



  int arr[10];
  // this arr had different memory address in different process
  // is allocated in 2 processes (if I lauch on 2 processes)
  // but the data is *NOT* shared
  for (int i = 0; i < 10; i++) {
    arr[i] = i * rank;
  }
  if (rank == 1) arr[2] = 3;

  printf("rank: %d addr: %p arr[2]: %d\n", rank, arr, arr[2]);
  // rank 0; arr = { 0 }
  // rank 1; arr = ( 0, 1, ... }

  int sum  = 0;
  // local sum

  for (int i = 0; i < 10; i++) {
    sum += arr[i];
  }

  int total_sum = 0;
  MPI_Reduce(&sum, &total_sum, 1, MPI_INT, MPI_MAX /* Operator */, 0 /* destination rank */, MPI_COMM_WORLD);
  // on rank 0 (destination rank)
  // total_sum = sum + (operator) (from all ranks including itself)


  printf("In rank: %d sum: %d total_sum: %d\n", rank, sum, total_sum);
  MPI_Finalize();

  return 0;
}
