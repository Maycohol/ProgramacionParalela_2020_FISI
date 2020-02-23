/*
 ============================================================================
 Name        : promedio_vectores_openMP.c
 Author      : Maycohol Jimmy Ayra Herrera
 Version     :
 Copyright   : Your copyright notice
 Description : promedio de vectores en openMP
 ============================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argc, char *argv[]){

    int n,i;
    int vector[100];

    printf("Introducir la cantidad del vector N = ");
    scanf("%d", &n);
    for(i=0;i<n;i++){
    vector[i]= (rand()%40)+1;
    printf("%4.1d ",vector[i]);
    }
    printf("\n");


#pragma omp parallel
{
	int id = omp_get_thread_num();
	int nt = omp_get_num_threads();
	int size = n/ nt;
	int ini = id * size;
	int fin = ini + size;
    	double suma = 0;
    	double promedio;
        for (int i = ini; i < fin; i++){
        suma = suma + vector[i];
        }
        promedio= suma / size;
        printf("El promedio es: %.2f\n", promedio);
}
return 0;

}



