#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{

  int rank;
  int np;
  

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  int var[100];

  int i;

  if (rank == 0) {
    // initialized var
    for (int i = 0; i < 100; i++) 
      var[i] = i * 2;
  }
  if (rank != 0) {
    // initialized var
    for (int i = 0; i < 100; i++) 
      var[i] = 0;
  }
  // Now I want to send 100 data elements in var from rank 0 to rank 1

  MPI_Bcast(var, 100, MPI_INT, 0, MPI_COMM_WORLD);
  
  // if (rank == 0) {
  //   MPI_Send(var, 100, MPI_INT, 1, 0, MPI_COMM_WORLD);
  //   // Yet to see are what is Tag, and communicator and status
  // }
  // if (rank == 1) {
  //   //MPI_Recv(var, 100, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  // }
  
  i = 3;
  printf("In rank: %d var[%d]: %d\n", rank, i, var[i]);
  MPI_Finalize();

  return 0;
}
