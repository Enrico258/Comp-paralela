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
int size = sizeof(vet)/sizeof(vet[0]);

//Print matriz
void printMatriz(int *matriz, int len){
  printf("[");
for (int i = 0; i < len; i++){
	if(i != len-1){printf("%d ", matriz[i]);
}else{printf("%d", matriz[i]);}}
  printf("]\n");
}

//Ler linhas
void* lerLinhas(void* args){
  int *index = (int*)args;
  int i = *index;
  for (int j = 0; j < size; j++){
    vetResult[i] += matriz[i][j] * vet[j];
  }
  printMatriz(vetResult, size);
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
      printf("%dª Thread criada com sucesso!\n", i+1);
    }
    pthread_join(threads[i], NULL);
  }

  //Print resultado
  printf("Resultado da multiplicação da matriz: ");
  printf("[");
  for(int k = 0; k < size; k++){
    if(k == size-1){
      printf("%d", vetResult[k]);
    }
    else{
    printf("%d,", vetResult[k]);
    }
  }
  printf("]\n");
  return 0;
}
