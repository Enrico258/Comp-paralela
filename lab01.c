#include <stdio.h>
#include <pthread.h>

//Define a matriz
int matriz[3][3] = {
{1,2,3},
{4,5,6},
{7,8,9}
};

//Definição dos vetores
int vet[3] = {1,2,3}; //Vetor que será multiplicado pela matriz

int vetResult[3] = {0,0,0}; //Vetor resultados
int tamanho = sizeof(vet)/sizeof(vet[0]);

//Print matriz
void printMatriz(int *matriz, int len){
  printf("[");
  for(int i =0; i<len; i++) printf(" %d ", matriz[i]);
  printf("]\n");
}

//Ler linhas
void* lerLinhas(void* args){
  int *index = (int*)args;
  int i = *index;
  for(int j = 0; j < size; j++){
    result[i] += A[i][j] * vet[j];
  }
  printaVetorThread(result, size);
}

int main(void) {

  //definir pthreads
  pthread_t threads[size];

  for(int i = 0; i < size; i++){
    //Verifica criação das threads
    if(pthread_create(&threads[i], NULL, lerLinhas, &i) != 0){
      printf("Erro ao criar threads");
      break;
    }else{
      printf("Thread %d criada com sucesso!\n", i);
    }
    pthread_join(threads[i], NULL);
  }

  //Print resultado
  printf("Resultado: ");
  printf("[");
  for(int i = 0; i < size; i++){
    if(i == size-1){
      printf("%d", result[i]);
    }
    else{
    printf("%d,", result[i]);
    }
  }
  printf("]\n");
  return 0;
}
