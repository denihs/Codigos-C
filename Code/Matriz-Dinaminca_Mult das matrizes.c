/*By DenyHs

*Esse codigo usa a alocação dinâmica de memória para montar as matrizes
multiplicando duas delas para gerar dados a terceira, falta verificação
de entrada negativa e letras ( weofwoefn ) 
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu(int *m,int *n,int *p,int *q);
int **Aloca(int row,int col);
int **preencher(int **Matriz,int row,int col,int verificar);
int **Multicacao(int **A,int **B,int **C,int m,int n,int q);
void exibir(int **Matriz,int row,int col);
int **Liberacao(int **Matriz,int row);

int main()
{
  srand(time(NULL));
  int m=0,n=0,p=0,q=0;
  int **Matriz_A,**Matriz_B,**Matriz_C;

  menu(&m,&n,&p,&q);

  Matriz_A = Aloca(m,n);
  Matriz_B = Aloca(p,q);
  Matriz_C = Aloca(m,q);


  Matriz_A=preencher(Matriz_A,m,n,1);
  Matriz_B=preencher(Matriz_B,p,q,2);
  Matriz_C=preencher(Matriz_C,m,q,0);

  Matriz_C = Multicacao(Matriz_A, Matriz_B, Matriz_C,m,n,q);

  printf("\nMATRIZ A\n");
    exibir(Matriz_A,m,n);

    printf("\nMATRIZ B\n");
      exibir(Matriz_B,p,q);

      printf("\nA MULTIPLICACAO RESULTA EM \n");
        exibir(Matriz_C,m,q);

  printf("\nM=%d N=%d P=%d Q=%d\n",m,n,p,q);

  Matriz_A =Liberacao(Matriz_A,m);
  Matriz_B =Liberacao(Matriz_B,p);
  Matriz_C =Liberacao(Matriz_C,m);

  return 0;
}
/*===================FUNÇÕES==========================*/
/*------------------MENU--------------------*/
void menu(int *m,int *n,int *p,int *q)
{
    printf("Insira o numero de linhas da primeira matriz: ");
      scanf("%d",m);
    printf("Insira o numero de colunas da primeira matriz: ");
      scanf("%d",n);
    printf("Insira o numero de linhas da segunda matriz: ");
      scanf("%d",p);
        if(*n!=*p){//Bloco contendo texto e correção automatica para o usuario
          printf("\nO numero de linhas da segunda Matriz\n");
          printf("deve ser igual o numero de colunas da primeira\n");
          printf("nesse caso sendo: %d\n",*n);
          printf("E ja atribuimos este valor para voce o deixando igual ;)\n\n");
          *p =  *n;
        }

    printf("Insira o numero de colunas da segunda matriz: ");
      scanf("%d",q);
}
/*------------------ALOCAÇÃO DAS MATRIZES A e B--------------------*/
int **Aloca(int row,int col)
{
  int **Mat=NULL,count;
   Mat = (int**) malloc(row*sizeof(int*)) ;
  if(Mat==NULL){printf("Espaco de memoria insuficiente\n"); return NULL;}

  for(count=0;count<row;count++){
    Mat[count]=(int*) malloc(col*sizeof(int));
    if(Mat[count]==NULL){printf("Espaco de memoria insuficiente\n"); return NULL;}
  }
  return(Mat);
}
/*------------------PREENCHIMENTO DAS MATRIZES--------------------*/
int **preencher(int **Matriz,int row,int col,int verificar)
{
  int i,j;
  if(verificar){
    for(i=0;i<row;i++){
      for(j=0;j<col;j++){
        Matriz[i][j]=rand()%6;
      }
    }
  }
  else{//preencher a Matriz C com zeros
    for(i=0;i<row;i++){
      for(j=0;j<col;j++){
        Matriz[i][j]=0;
      }
    }
  }
  return Matriz;
}
/*------------------MULTIPLICAÇÃO DAS MATRIZES--------------------*/
int **Multicacao(int **A,int **B,int **C,int m,int n,int q)
{
  int i,j,x,y;
  for(i=0;i<m;i++){
    x=0;
    y=0;
    do{
      for(j=0;j<n;j++){
        C[i][x]+=A[i][j]*B[j][y];
      }
      x++;
      y++;
    }while(x!=q);
  }
  return C;
}
/*------------------EXIBINDO AS MATRIZES--------------------*/
void exibir(int **Matriz,int row,int col)
{
  int i,j;
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      printf("%3d",Matriz[i][j]);
    }
    printf("\n");
  }

}
/*------------------LIBERANDO AS MATRIZES--------------------*/
int **Liberacao(int **Matriz,int row)
{
  int count;
  if(Matriz==NULL){return NULL;}

  for(count=0;count<row;count++){
    free(Matriz[count]);
  }
  free(Matriz);
  return NULL;
}
