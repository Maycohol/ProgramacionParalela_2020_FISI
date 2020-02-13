/*
 ============================================================================
 Name        : prog00_HelloWord.c
 Author      : Maycohol Jimmy Ayra Herrera
 Version     :
 Copyright   : Your copyright notice
 Description : HelloWord con pthread
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // contiene las declaraciones de utilizadas para la programacion multithread

//Global variable: accessible to all threads
int thread_count; // Variable global: para guardar cantidad de hilos que va a usar nuestra aplicacion, esta puede ser utilizada por todos los hilos de nuestra aplicacion,

void* Hello(void* rank); // Thread_function

int main(int argc, char* argv[]) {
	long thread; //Use long in case of a 64−bit system
	pthread_t* thread_handles;

	// Get number of threads from command line
	thread_count = strtol(argv[1], NULL, 10);

	thread_handles = malloc(thread_count * sizeof(pthread_t));

	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], // tenemos un vector porque vamos a utilizar mas de un thread
				NULL,
				Hello,// Funcion Hello
				(void*) thread);

	printf("Hello from the main thread\n");

	for (thread = 0; thread < thread_count; thread++) //hace un barrido
		pthread_join(thread_handles[thread], NULL);  // une los thread en orden de llegada

	free(thread_handles);
	return 0;
} // main

void* Hello(void* rank) {
	long my_rank = (long) rank;
// Use long in case of 64−bit system

	printf("Hello from thread %ld of %d\n", my_rank, thread_count);

	return NULL;
} // Hello
