/*
 ============================================================================
 Name        : deter_matriz_openMP.c
 Author      : Maycohol Jimmy Ayra Herrera
 Version     :
 Copyright   : Your copyright notice
 Description : Determinante de una matriz con openMP
 ============================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

int main()
{
int i,j,k,l,n ;
float a[100][100];
float det;
double tInicio, // Tiempo en el que comienza la ejecucion
       tFin; // Tiempo en el que acaba la ejecucion
printf("Introducir el orden de la matriz N = " );
scanf("%d",&n);
//m=n-1;


//Elementos random de la matriz
srand(time(0));
for(i=1;i<=n;i++)
{ for(j=1;j<=n;j++)
{a[i][j]=(rand()%20)+1;}}

//Leemos los elementos de la matriz
for(i=1;i<=n;i++)
{ for(j=1;j<=n;j++)
printf("\t\t\tA(%d,%d) =%8.4f\n",i,j,a[i][j] );
}


/*****Calculo de la determinate de la matriz*****/
#pragma omp parallel
{
	tInicio = omp_get_wtime();// Inicio de medicion de tiempo
	int id = omp_get_thread_num();
	int nt = omp_get_num_threads();
	int size = n/ nt;
	int ini = id * size +1;
	int fin = ini + size-2;


	det=a[1][1];
	for(k=ini;k<=fin;k++)
	{ l=k+1;
	for(i=l;i<=n;i++)
	{ for(j=l;j<=n;j++)
		a[i][j] = ( a[k][k]*a[i][j]-a[k][j]*a[i][k] )/a[k][k]; }
	det=det*a[k+1][k+1];
	}
	printf("\n");
	printf("DETERMINANTE = %f",det);

	tFin=omp_get_wtime();// fin de medicion de tiempo
	printf("\n");
	printf("El tiempo tardado ha sido %f segundos",tFin-tInicio);
}
return 0;
}
