/*
 ============================================================================
 Name        : MPI_sum.c
 Author      : Maycohol Ayra Herrera
 Description : Funcion MPI_SUM
 Compile Command:
 $ mpicc -o MPI_sum MPI_sum.c
 $ mpiexec -n 4 ./MPI_sum
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

    /**
     *Mostramos cómo usar una operación de reducción de suma.
     *Este programa consiste en una reducción de suma; cada proceso MPI
     *envía su rango de reducción antes de que la suma de estos rangos se almacene en el
     *proceso de MPI raíz. Se puede visualizar de la siguiente manera, con el proceso MPI 0 como
     * raíz:
     * +-----------+ +-----------+ +-----------+ +-----------+
     * | Process 0 | | Process 1 | | Process 2 | | Process 3 |
     * +-+-------+-+ +-+-------+-+ +-+-------+-+ +-+-------+-+
     *   | Value |     | Value |     | Value |     | Value |
     *   |   0   |     |   1   |     |   2   |     |   3   |
     *   +-------+     +-------+     +-------+     +-------+
     *            \         |           |         /
     *             \        |           |        /
     *              \       |           |       /
     *               \      |           |      /
     *                +-----+-----+-----+-----+
     *                            |
     *                        +---+---+
     *                        |  SUM  |
     *                        +---+---+
     *                            |
     *                        +---+---+
     *                        |   6   |
     *                      +-+-------+-+
     *                      | Process 0 |
     *                      +-----------+
     **/
    int main(int argc, char* argv[])
    {
        MPI_Init(&argc, &argv);

        // Obtenga el número de procesos y verifique que solo se utilicen 4.
        int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        if(size != 4)
        {
            printf("Este programa esta diseñado para ejecutarse con 4 procesos.\n");
            MPI_Abort(MPI_COMM_WORLD,1);
        }
        // Determinar el rango de la raíz
        int root_rank = 0;

        // Obtén mi rango
        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        // Cada proceso MPI envía su rango a reducción, el proceso raíz MPI recoge el resultado
        int reduction_result = 0;
        MPI_Reduce(&my_rank, &reduction_result, 1, MPI_INT, MPI_SUM, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("La suma de todos los elementos es: %d.\n", reduction_result);
        }

        MPI_Finalize();

        return 0;
    }
