#include <stdio.h>
#include <pthread.h>

//Definir matriz
int A[3][3] = {
{2,4,6},
{1,2,3},
{5,7,9}
};

//Definir vetores
int vet[3] = {1,2,3}; //Vetor que será multiplicado pela matriz
int result[3] = {0,0,0}; //Vetor que guardará os resultados

//Tamanho do vetor
int tamanho = sizeof(vet)/sizeof(vet[0]);

//Função que imprime o vetor A para visualização da operação
void printaVetorThread(int *A, int len){
  printf("[");
  for(int i =0; i<len; i++) printf(" %d ", A[i]);
  printf("]\n");
}

//Função que faz os cálculos por linhas
void* calcula_linha(void* args){
  int *index = (int*)args;
  int i = *index;
  for(int j = 0; j < tamanho; j++){
    result[i] += A[i][j] * vet[j];
  }
  printaVetorThread(result, tamanho);
}

int main(void) {
  //Criar pthreads
  pthread_t threads[tamanho];
  for(int i = 0; i < tamanho; i++){
    //Verifica se a criação das threads foi bem sucedida
    if(pthread_create(&threads[i], NULL, calcula_linha, &i) != 0){
      printf("Erro ao criar threads");
      break;
    }else{
      printf("Thread %d criada com sucesso!\n", i);
    }
    pthread_join(threads[i], NULL); //Espera conclusão das threads
  }

  //Printa resultado
  printf("Vetor resultado: ");
  printf("[");
  for(int i = 0; i < tamanho; i++){
    if(i == tamanho-1){
      printf("%d", result[i]);
    }
    else{
    printf("%d,", result[i]);
    }
  }
  printf("]\n");
  return 0;
}
