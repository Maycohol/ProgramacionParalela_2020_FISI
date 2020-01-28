/*
 ============================================================================
 Name        : MPI_land.c
 Author      : Maycohol Ayra Herrera
 Description : Funcion MPI_LAND
 Compile Command:
 $ mpicc -o MPI_land MPI_land.c
 $ mpiexec -n 4 ./MPI_land
 ============================================================================
 */
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <mpi.h>

    /**
     * Mostraremos cómo usar una operación lógica y de reducción.
     * Este programa consiste en una lógica y reducción; cada proceso MPI
     * envía su valor de reducción antes de que el lógico y de estos valores se almacene en
     * El proceso raíz de MPI. Se puede visualizar de la siguiente manera, con el proceso MPI 0 como
     * raíz:
     *
     * +-----------+ +-----------+ +-----------+ +-----------+
     * | Process 0 | | Process 1 | | Process 2 | | Process 3 |
     * +-+-------+-+ +-+-------+-+ +-+-------+-+ +-+-------+-+
     *   | Value |     | Value |     | Value |     | Value |
     *   |  true |     |  true |     |  true |     | false |
     *   +-------+     +-------+     +-------+     +-------+
     *            \         |           |         /
     *             \        |           |        /
     *              \       |           |       /
     *               \      |           |      /
     *                +-----+-----+-----+-----+
     *                            |
     *                        +---+---+
     *                        |  LAND |
     *                        +---+---+
     *                            |
     *                        +---+---+
     *                        | false |
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

        // Determinar el rango de la raíz
        int root_rank = 0;

        // Obtengo mi rango
        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        // Cada proceso MPI envía su rango a reducción, el proceso raíz MPI recoge el resultado
        bool my_value = (my_rank != 3);
        bool reduction_result = false;
        MPI_Reduce(&my_value, &reduction_result, 1, MPI_C_BOOL, MPI_LAND, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("El lógico(AND) de todos los valores es: %s.\n", reduction_result ? "true" : "false");
        }

        MPI_Finalize();

        return 0;
    }
