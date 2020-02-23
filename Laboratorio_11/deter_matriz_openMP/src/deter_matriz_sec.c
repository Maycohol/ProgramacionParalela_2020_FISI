/*
 ============================================================================
 Name        : deter_matriz_sec.c
 Author      : Maycohol Jimmy Ayra Herrera
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
int i,j,k,l,m,n ;
float a[100][100];
float det;
printf("Introducir el orden de la matriz N = " );
scanf("%d",&n);
m=n-1;


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

	det=a[1][1];
	for(k=1;k<=m;k++)
	{ l=k+1;
	for(i=l;i<=n;i++)
	{ for(j=l;j<=n;j++)
		a[i][j] = ( a[k][k]*a[i][j]-a[k][j]*a[i][k] )/a[k][k]; }
	det=det*a[k+1][k+1];
	}
	printf("\n");
	printf("DETERMINANTE = %f",det);

return 0;
}
