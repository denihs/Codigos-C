#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
  srand(time(NULL));
  int M = 1+(rand()%100),
      N = 1+(rand()%100),
      Mat[M][N],i,j,Maior,

      Linha, coluna;
  for(i=0;i<M;i++){
    for(j=0;j<N;j++){
      Mat[i][j]=1+(rand()%100);
    }
  }
  Maior = Mat[0][0];
  Linha = 0;
  coluna = 0;
  for(i=0;i<M;i++){
    for(j=0;j<N;j++){
        if(Mat[i][j]>Maior){
          Maior = Mat[i][j];
          Linha = i;
          coluna = j;
        }
    }
  }
  printf("Maior: %d\n",Maior);
  printf("Na linha %d\n",Linha);
  printf("Na coluna %d\n",coluna);

  for(i=0;i<M;i++){
    for(j=0;j<N;j++){
        if(Mat[i][j]>Maior){
          Maior = Mat[i][j];
          Linha = i;
          coluna = j;
        }
    }
  }
    printf("\n\n");
    printf("Sua Matriz tem esse cara:\n");
    for(i=0;i<M;i++){
      for(j=0;j<N;j++){
        printf("%3d",Mat[i][j]);
      }
      printf(" PULO\n");
    }
  return 0;
}
