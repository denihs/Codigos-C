/*By DenyHS
*A tarefa deste codigo é fazer repetidas combinações nas casas de uma matriz
ate ela encontrar uma matriz identidade*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  srand(time(NULL));
  int M = 3;//Trocar este valor para obter tempos de procurar diferentes
  int matriz[M][M],i,j,identidade = 0,diagonal=0,casa=0,tentativa=0,mili=1;

  do{
    for(i=0;i<M;i++){
      for(j=0;j<M;j++){
        matriz[i][j]=rand()%2;
      }
    }
    for(i=0;i<M;i++){
      for(j=0;j<M;j++){
        if(i==j&&matriz[i][j]==1){
          diagonal++;
        }
        if(i!=j&&matriz[i][j]==0){
          casa++;
        }
      }
    }
    if(diagonal==M&&casa==(M*M)-M){
      identidade = 1;
    }
    diagonal=0;
    casa=0;
    tentativa++;

    printf(".");
    if(tentativa==1000*mili){
      printf("%d",mili);
      mili++;
    }


  }while(!identidade);

printf("\n");

  for(i=0;i<M;i++){
    for(j=0;j<M;j++){
      printf("%3d",matriz[i][j]);
    }
    printf("\n");
  }
  printf("Em (%d) tentativas",tentativa);

  return 0;
}
