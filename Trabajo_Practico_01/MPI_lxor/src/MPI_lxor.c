/*
 ============================================================================
 Name        : MPI_lxor.c
 Author      : Maycohol Ayra Herrera
 Description : Funcion MPI_LXOR
 Compile Command:
 $ mpicc -o MPI_lxor MPI_lxor.c
 $ mpiexec -n 4 ./MPI_lxor
 ============================================================================
 */
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <mpi.h>

    /**
     * Mostraremos cómo utilizar una operación lógica exclusiva o de reducción.
     * Este programa consiste en una lógica exclusiva o reducción; cada
     * El proceso MPI envía su valor de reducción antes de la lógica exclusiva o de
     * estos valores se almacenan en el proceso raíz de MPI. Se puede visualizar como
     * sigue, con MPI proceso 0 como root:
     *
     * +-----------+ +-----------+ +-----------+ +-----------+
     * | Process 0 | | Process 1 | | Process 2 | | Process 3 |
     * +-+-------+-+ +-+-------+-+ +-+-------+-+ +-+-------+-+
     *   | Value |     | Value |     | Value |     | Value |
     *   | false |     | false |     | false |     | true  |
     *   +-------+     +-------+     +-------+     +-------+
     *            \         |           |         /
     *             \        |           |        /
     *              \       |           |       /
     *               \      |           |      /
     *                +-----+-----+-----+-----+
     *                            |
     *                        +---+---+
     *                        |  LXOR |
     *                        +---+---+
     *                            |
     *                        +---+---+
     *                        |  true |
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
        bool my_value = (my_rank == 3);
        bool reduction_result = false;
        MPI_Reduce(&my_value, &reduction_result, 1, MPI_C_BOOL, MPI_LXOR, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("El lógico(XOR) de todos los valores es: %s.\n", reduction_result ? "true" : "false");
        }

        MPI_Finalize();

        return 0;
    }
