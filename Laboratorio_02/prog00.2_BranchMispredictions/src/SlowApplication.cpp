#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

  srand(time(NULL));
  int arraySize = 32768;
  int data[arraySize];

  for (int i = 0; i < arraySize; i++)
    data[i] = rand() % 256;

  /* Los accesos se realizan secuencialmente a un vector con elementos al azar.
   * La rama predictora no puede determinar si
   * Se tomará sucursal o no la mayor parte del tiempo.
   */
  clock_t start = clock();
  long long sum = 0;
  for (int i = 0; i < 100000; i++){
    for (int c = 0; c < arraySize; ++c) {
      if (data[c] >= 128)
        sum += data[c];
    }
  }
  double elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;

  printf ("Tempo total: %lf\n", elapsedTime);
  printf ("Soma: %lld\n", sum);
}
