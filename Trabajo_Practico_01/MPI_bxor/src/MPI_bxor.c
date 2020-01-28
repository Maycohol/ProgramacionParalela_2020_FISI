/*
 ============================================================================
 Name        : MPI_bxor.c
 Author      : Maycohol Ayra Herrera
 Description : Funcion MPI_BXOR
 Compile Command:
 $ mpicc -o MPI_bxor MPI_bxor.c
 $ mpiexec -n 4 ./MPI_bxor
 ============================================================================
 */
    #include <stdio.h>
    #include <stdlib.h>
    #include <mpi.h>

    /**
     * Mostraremos cómo usar una operación exclusiva o de reducción de bits.
     * Este programa consiste en una exclusiva o reducción a nivel de bit;
     * cada proceso MPI envía su valor de reducción antes de la exclusiva bit-wise
     * o de estos valores se almacena en el proceso raíz de MPI. Se puede visualizar como
     * sigue, con MPI proceso 0 como root:
     *
     * +-----------+ +-----------+ +-----------+ +-----------+
     * | Process 0 | | Process 1 | | Process 2 | | Process 3 |
     * +-+-------+-+ +-+-------+-+ +-+-------+-+ +-+-------+-+
     *   | Value |     | Value |     | Value |     | Value |
     *   |   0   |     |   1   |     |   3   |     |   8   |
     *   +-------+     +-------+     +-------+     +-------+
     *            \         |           |         /
     *             \        |           |        /
     *              \       |           |       /
     *               \      |           |      /
     *                +-----+-----+-----+-----+
     *                            |
     *                        +---+---+
     *                        |  BXOR |
     *                        +---+---+
     *                            |
     *                        +---+---+
     *                        |   10  |
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
            printf("Este programa está diseñado para ejecutarse con 4 procesos.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        // Determine root's rank
        int root_rank = 0;

        // Get my rank
        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        // Cada proceso MPI envía su rango a reducción, el proceso raíz MPI recoge el resultado
        char all_values[4] = {0, 1, 3, 8};
        char my_value = all_values[my_rank];
        char reduction_result = 0;
        MPI_Reduce(&my_value, &reduction_result, 1, MPI_UNSIGNED_CHAR, MPI_BXOR, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("El lógico(XOR) a nivel de bits es: %d.\n", reduction_result);
        }

        MPI_Finalize();

        return 0;
    }
