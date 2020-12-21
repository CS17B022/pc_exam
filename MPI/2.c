/*
 *
 * var: 833
 * 0 -> 1 (var + rank) -> 2 (var + rank) -> n .... -> 0
 */
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{

  int rank;
  int np;
  

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);


  int var[2];
  int i;

  var[0] = 2;

  if (rank == 0) {
    // initialized var
    var[0] = 833;
  }


  if (rank == 0) {
    MPI_Send(var, 1, MPI_INT, ((rank + 1) % np), 0, MPI_COMM_WORLD);
    MPI_Recv(var, 1, MPI_INT, (np - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  else {
    MPI_Recv(var, 1, MPI_INT, (rank - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    var[0] += rank;
    MPI_Send(var, 1, MPI_INT, ((rank + 1) % np), 0, MPI_COMM_WORLD);
  }

  i = 0;
  printf("In rank: %d var[%d]: %d\n", rank, i, var[i]);
  MPI_Finalize();

  return 0;
}
