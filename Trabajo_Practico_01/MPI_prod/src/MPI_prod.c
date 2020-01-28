/*
 ============================================================================
 Name        : MPI_prod.c
 Author      : Maycohol Ayra Herrera
 Description : Funcion MPI_PROD
 Compile Command:
 $ mpicc -o MPI_prod MPI_prod.c
 $ mpiexec -n 4 ./MPI_prod
 ============================================================================
 */
    #include <stdio.h>
    #include <stdlib.h>
    #include <mpi.h>

    /**
     * Mostraremos cómo usar una operación de reducción de producto.
     * Este programa consiste en una reducción de producto; cada proceso MPI
     * envía su valor de reducción antes de que el producto de estos valores se almacene en
     * El proceso raíz de MPI. Se puede visualizar de la siguiente manera, con el proceso MPI 0 como
     * raíz:
     *
     * +-----------+ +-----------+ +-----------+ +-----------+
     * | Process 0 | | Process 1 | | Process 2 | | Process 3 |
     * +-+-------+-+ +-+-------+-+ +-+-------+-+ +-+-------+-+
     *   | Value |     | Value |     | Value |     | Value |
     *   |   1   |     |   2   |     |   3   |     |   4   |
     *   +-------+     +-------+     +-------+     +-------+
     *            \         |           |         /
     *             \        |           |        /
     *              \       |           |       /
     *               \      |           |      /
     *                +-----+-----+-----+-----+
     *                            |
     *                        +---+---+
     *                        |  PROD |
     *                        +---+---+
     *                            |
     *                        +---+---+
     *                        |   24  |
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
        int my_value = my_rank + 1;
        int reduction_result = 0;
        MPI_Reduce(&my_value, &reduction_result, 1, MPI_INT, MPI_PROD, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("El producto de todos los valores es: %d.\n", reduction_result);
        }

        MPI_Finalize();

        return 0;
    }
