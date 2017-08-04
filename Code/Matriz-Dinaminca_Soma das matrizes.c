/*By DenyHs

*Esse codigo usa a alocação dinâmica de memória para montar as matrizes
somando duas delas para gerar dados a terceira, falta verificação
de entrada negativa e letras ( weofwoefn ) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **aloca(int M);
int **preencher(int **Matriz,int M);
void exibi(int **Matriz,int M);
int ** Liberar_matriz_real(int M,int **Mat);
int **Soma(int **A,int **B,int **C,int M);

int main()
{
  srand(time(NULL));
  int M=2+rand()%10;
  int **Matriz_A,**Matriz_B,**Matriz_C;

  Matriz_A = aloca(M);
  Matriz_B = aloca(M);
  Matriz_C = aloca(M);
  Matriz_A=preencher(Matriz_A,M);
  Matriz_B=preencher(Matriz_B,M);
  Matriz_C=preencher(Matriz_C,M);

  printf("\tMATRIZ A\n");
    exibi(Matriz_A,M);
    printf("\n");
  printf("\tMATRIZ B\n");
    exibi(Matriz_B,M);
    printf("\n");
  Matriz_C = Soma(Matriz_A,Matriz_B,Matriz_C,M);
  printf("\tA SOMA DAS MATRIZES A e B RESULTA EM\n");
    exibi(Matriz_C,M);
  Matriz_A = Liberar_matriz_real(M,Matriz_A);
  Matriz_B = Liberar_matriz_real(M,Matriz_B);
  Matriz_C = Liberar_matriz_real(M,Matriz_C);
  printf("\nM ==== %d\n",M);
  return 0;
}
/*==================FUNÇOES===============*/

/*-------------------ALOCAÇÃO--------------------*/
int **aloca(int M)
{

  int **Matriz,count;
  Matriz  = (int **) malloc(M*sizeof(int*));
  if(Matriz==NULL){printf("Espaco de memoria insuficiente");return NULL;};

  for(count=0;count<M;count++){
    Matriz[count] = (int*) malloc(M*sizeof(int));
    if(Matriz[count]==NULL){printf("Espaco de memoria insuficiente");return NULL;};
  }
  return(Matriz);
}
/*-------------------PREENCHIMENTO--------------------*/
int **preencher(int **Matriz,int M)
{
  int i,j;

  for(i=0;i<M;i++){
    for(j=0;j<M;j++){
      Matriz[i][j] = 2+rand()%20;
    }
  }
  return Matriz;
}
/*-------------------EXIBIÇÃO--------------------*/
void exibi(int **Matriz,int M)
{
  int i,j;
  for(i=0;i<M;i++){
    for(j=0;j<M;j++){
      printf("%3d",Matriz[i][j]);
    }
    printf("\n");
  }
}
/*-------------------LIBERAÇÃO--------------------*/
int ** Liberar_matriz_real(int M,int **Mat)
 {
      if(Mat==NULL){return NULL;};
      int count;
      for(count=0;count<M;count++){free(Mat[count]);}

      free(Mat);
      return(NULL);
}
/*-------------------SOMA DOS VALORES--------------------*/
int **Soma(int **A,int **B,int **C,int M)
{
  int count;

  int i,j;
  for(i=0;i<M;i++){
    for(j=0;j<M;j++){
      C[i][j] = A[i][j] + B[i][j];
    }
  }
  return C;
}
