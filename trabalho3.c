// Alunos: Igor Veludo            13/0028240
//         Joao Pedro Mota Jardim 16/0031982

//para rodar com a time, compile o programa com time ./projeto.2
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 40

int mostraMenu();
void preencheVet(int *vetor);
void shellSort(int *vetor);
void bucketSort(int *vetor);
void quickSort(int *vetor, int inicio, int fim);
void troca(int *vetor, int i, int j);
int particiona(int *vetor, int inicio, int fim);
int geraPivoRandomico(int *vetor, int inicio, int fim);
void imprimeVet(int *vetor);
void imprimeGrafico(int *vetor);

clock_t clock(void);

int main(void){
  time_t start = time(NULL);
  time_t diff = time(NULL) - start;
  srand(time(NULL));
  int numeros[MAX] = {0};
  int tamanhoVet = sizeof(numeros) / sizeof(int);
  int opcao;

  do{
    opcao = mostraMenu();
    switch(opcao){
      case 1:
        preencheVet(numeros);
        break;
      case 2:
        shellSort(numeros);
        break;
      case 3:
        bucketSort(numeros);
        break;
      case 4:
        quickSort(numeros, 0, tamanhoVet - 1);
        printf("Vetor ordenado com Quick Sort:\n");
        imprimeVet(numeros);
        break;
      case 5:
        imprimeGrafico(numeros);
    }
  }while(opcao != 0);

  return 0;
}

int mostraMenu(){
  int opcao;
  //system("clear");
  printf("\n");
  printf(" ========================================\n");
  printf("|         >>>>>>>>> Menu <<<<<<<<<       |\n");
  printf("| 1 - Gerar Vetor Aleatorio              |\n");
  printf("| 2 - Ordenar Vetor Shell Sort           |\n");
  printf("| 3 - Ordenar Vetor Bucket Sort          |\n");
  printf("| 4 - Ordenar Vetor Quick Sort           |\n");
  printf("| 5 - Imprimir grafico                   |\n");
  printf("| 0 - Sair                               |\n");
  printf(" ========================================\n");
  printf("Sua opcao: ");
  scanf("%d",&opcao);
  return opcao;
}

void preencheVet(int *vetor){
  int i = 0;
  for(i = 0 ; i < MAX ; i++){
    vetor[i] = rand() % MAX;
  }
  printf("Vetor Aleatorio:\n");
  imprimeVet(vetor);
}

void shellSort(int *vetor){
    int n = MAX,h = n/2, c,j;
    while(h > 0){
      for (int i = h;i < n;i++){
        c = vetor[i];
        j = i;
        while (j >= h && vetor[j - h] > c){
          vetor[j] = vetor[j-h];
          j = j-h;
        }
        vetor[j] = c;
      }
      h = h/2;
      sleep(1);
      system("clear");
      imprimeGrafico(vetor);
    }
  printf("Vetor ordenado com Shell Sort:\n");
  imprimeVet(vetor);
  //printf("numero de iteracoes: %d",iteracoes);
}

void bucketSort(int *vetor){

    sleep(1);
    system("clear");
    imprimeGrafico(vetor);
  printf("Vetor ordenado com Bucket Sort:\n");
  imprimeVet(vetor);
  //printf("numero de iteracoes: %d",iteracoes);
}

void quickSort(int *vetor, int inicio, int fim){
  if(inicio < fim){
    int pivoIndice = geraPivoRandomico(vetor, inicio, fim);
    quickSort(vetor, inicio, pivoIndice - 1);
    quickSort(vetor, pivoIndice + 1, fim);
  }
    //  sleep(1); DEIXA SAPORRAS ONDE?
    //  system("clear");
    //  imprimeGrafico(vetor);

  //printf("Vetor ordenado com Quick Sort:\n"); TIREI ESSE PRINT E O IMPRIMEVET E COLOQUEI DEPOIS DA CHAMADA NO CASE
  //imprimeVet(vetor);
  //printf("numero de iteracoes: %d",iteracoes);
}

  //funcao que troca a posicao de dois elementos pro quick sort
void troca(int *vetor, int i, int j){
  int aux = vetor[i];
  vetor[i] = vetor[j];
  vetor[j] = aux;
}

  //particiona e retorna o indice do pivo do quick sort
int particiona(int *vetor, int inicio, int fim){
  int pivo, pivoIndice, i;

  pivo = vetor[fim]; // o pivo é sempre o ultimo elemento
  pivoIndice = inicio;

  for(i = inicio ; i < fim ; i++){
    //verifica se o elemento é <= ao pivo
    if(vetor[i] <= pivo){
      troca(vetor, i, pivoIndice);
      pivoIndice++;
    }
  }
  //troca o pivo
  troca(vetor, pivoIndice, fim);

  return pivoIndice;
}

int geraPivoRandomico(int *vetor, int inicio, int fim){
  //srand(time(NULL));
  //seleciona um pivo aleatorio no vetor
  int pivoIndice = (rand() % (fim - inicio + 1)) + inicio;
  //coloca o pivo no fim
  troca(vetor, pivoIndice, fim);
  return particiona(vetor, inicio, fim);
}

void imprimeVet(int *vetor){
  int i;
  for(i = 0 ; i < MAX ; i++)
    printf("%d ", vetor[i]);
    printf("\n");
}
void imprimeGrafico(int *vetor){
  int linha,coluna;
  char matriz[MAX+1][MAX+1];
  //prenche todos os espacos da matriz com espa�os em brancos
  for(linha = 0; linha < MAX+1;linha++){
    for(coluna = 0; coluna < MAX+1;coluna++){
       matriz[linha][coluna] = ' ';
    }
  }
  //preenche a a primeira coluna da matriz com | para ser o eixo y
  for(linha = 0; linha < MAX+1;linha++){
    matriz[linha][0] = '|';
  }
  //o cruzamento do eixo x e y do grafico
  matriz[0][0] = 'L';
  //preenchendo a primeira linha com _ para ser o eixo X
  for(coluna = 1; coluna < MAX+1;coluna++){
    matriz[0][coluna] = '_';
  }
  //a linha de numero igual ao valor do vetor nessa posi��o recebe um *
  for(linha = 0; linha < MAX;linha++){
    matriz[vetor[linha]+1][linha+1] = '*';
  }
  //print do grafico
  for(linha = MAX; linha >= 0;linha--){
    //primeira parte imprime os numeros do eixo y
    if (linha - 1 >= 10){
      printf("%d",linha-1);
    }
    else if(linha - 1 >= 0){
      printf(" %d",linha-1);
    }
    //para nao imprimir o -1
    else{
      printf("  ");
    }
    for(coluna = 0; coluna < MAX+1;coluna++){
       printf("%c ",matriz[linha][coluna]);
    }
    printf("\n");
  }
}
