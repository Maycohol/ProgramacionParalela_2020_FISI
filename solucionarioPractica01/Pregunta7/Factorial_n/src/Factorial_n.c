/*
 ============================================================================
 Name        : Factorial_n.c
 Author      : Maycohol Jimmy Ayra Herrera
 Version     :
 Copyright   : Your copyright notice
 Description : Algoritmo en MPI, utilizando p procesadores para calcular n!
 ============================================================================
 */
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    int myRank;
    int size;
    int fact;
    int lower,upper;
    int i;
    double local_result = 1.0;
    double total;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(myRank==0){
        printf("Ingrese un nùmero:");
        scanf("%d",&fact);
    }
   //El proceso con rango 0 tiene la entrada, debemos pasarlo a todos los procesos
    MPI_Bcast(&fact,1,MPI_INT,0,MPI_COMM_WORLD);

    //Calculamos los limites inferior y superiror de cada proceso
    if(myRank==0){
        lower = 1;
    }else
        lower = myRank * (fact / size) + 1;
    if(myRank==(size-1))
        upper = fact;
    else
        upper = (myRank + 1) * (fact / size);

    //Hacemos la multiplicacion
    for(i=lower;i<=upper;i++){
        local_result = local_result * (double)i;
    }

//Combinamos todos los resultados multiplicandolos
    MPI_Reduce(&local_result,&total,1,MPI_DOUBLE,MPI_PROD,0,MPI_COMM_WORLD);

   //Mostramos por salida
    if(myRank==0){
        printf("El factorial de  %d es %lf, y se calculo usando %d procesos\n",fact,total,size);
    }

    MPI_Finalize();
    return 0;
}
