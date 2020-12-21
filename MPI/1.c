#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{

  int rank;
  int np;
  
  int shared_variable = 0;
  // NOT shared variable!!!!

  MPI_Init(&argc, &argv);

  // rank is junk
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // After this, if my rank is 3 then rank variable will have 3

  MPI_Comm_size(MPI_COMM_WORLD, &np);
  // Will get the number of processes

  //sleep(5000);
  printf("Hello World! My rank is: %d in number_processes: %d\n", rank, np);

  if (rank == 1) {
    shared_variable = 88;
  }
  printf("Shared_variable is %d in rank: %d\n", shared_variable, rank);

  MPI_Finalize();

  return 0;
}
