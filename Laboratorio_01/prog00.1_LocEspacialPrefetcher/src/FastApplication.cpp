#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ONE_K 1024
#define ONE_M ONE_K * ONE_K

#define VSIZE (500 * ONE_M)
#define ITERS (10 * ONE_M)

int main() {

  srand(time(NULL));

  //Vector con 100 MB
  unsigned char *vec = (unsigned char *) malloc (VSIZE);
  for (int i = 0; i < VSIZE; i++) {
    vec[i] = rand() % 256;
  }

  /* Aunque dibujamos números aleatorios en este caso,
   * Los accesos son secuenciales. Favorecen al prefetcher y tienen una buena
   * ubicación espacial.
   */
  clock_t start = clock();
  unsigned int sum = 0;
  for (int i = 0; i < ITERS; i++) {
    int pos = rand() % VSIZE;
    if (pos > VSIZE)
      printf("Imposible. Solo para forzarte a mantener la posición");
    else
      sum += vec[i]; // Accedemos a cada elemento tomando en cuenta su indice
  }
  double elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf ("Tiempo total: %lf\n", elapsedTime);

  return 0;
}
