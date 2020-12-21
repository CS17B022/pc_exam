#include <stdio.h>
#include<mpi.h>
#include <utmpx.h>

int main( int argc , char **argv )
{
MPI_Init(&argc, &argv);
printf( "cpu = %d\n", sched_getcpu() );
MPI_Finalize();
return 0;
}