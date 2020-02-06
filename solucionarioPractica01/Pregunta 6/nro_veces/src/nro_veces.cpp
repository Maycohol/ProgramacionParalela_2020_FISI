/*
 ============================================================================
 Name        : nro_veces.c
 Author      : Maycohol Jimmy Ayra Herrera
 Version     :
 Copyright   : Your copyright notice
 Description : Algoritmo que determina el numero de veces que un elemento aparece en un vector
 ============================================================================
 */
#include <iostream>
#include <stdlib.h>

// 6. Calcular cuantas veces se repite un elemento X en un arreglo

using namespace std;

template<typename T>

void Repetidos(T* c, T n, T nro_a_buscar){

	int contadorrp = 0;
	for (int i = 0; i < n; i++) {

		if (nro_a_buscar == c[i])
		{
			contadorrp++;
		}

	}

	cout << "El elemento " << nro_a_buscar << " se repite ";
	cout << contadorrp << " veces.";

}

int main(){
	int a[10] = { 2, 6, 3, 9, 4, 12, 4, 54, 10, 4 };

	int nelem = 10;
	int buscar = 4; // Numero a buscar



	// imprimir arreglo
	for (int i = 0; i < nelem; ++i){
		cout << a[i] << " ";
	}
	cout << endl;


	Repetidos<int>(a, nelem, buscar);
	cout << endl;

	system("pause");
	return 0;
}
