
/* *Função: O programa tem a intensão de verificar qual a media de tempera
            em um sequencia de mesmo intervalo de tempo na lua. Então, apos
            ter obtido os dados ele fará todos os calculos necessarios para
            obter a media no intervalo de minutos correto.
   *Autor: Denilson Higino da Silva  | RGM: 36712
   *Data de inicio: 25/08/2017
   *Data de finalização: 26/08/2017
===============================================================================
*/

#include <stdio.h>
#include <math.h>
#define DIM 1000//Definindo uma constante para o tamanho do vetor

/*----------------------CHAMADAS DAS FUNÇÕES-------------------------------*/
void Iniciando_Vetor(int vetor[],int vetor_testes[]);
void Preencher(int vetor[]);
void N_M(int vetor[], int posicao);
int Media_Temperatura(int vetor_temperaturas[],int vetor_testes[]);
void exibir(int vetor[],int Tot_Testes);
/*-----------------------------------------------------------------------*/

int main()
{
  //Chamadas da funções
  int vetor[DIM],testes[DIM],Tot_Testes;
  Iniciando_Vetor(vetor,testes);
  Preencher(vetor);
  Tot_Testes=Media_Temperatura(vetor,testes);
  exibir(testes,Tot_Testes);

  return 0;
}
/*----------------------------------------------------------------------------------------------------*/
/*
  objetivo: Preencher todo o vetor de temperaturas com 1 (para não existir a chance de um endereço iniciar com
            ZERO sem que o usuario deseje isso) e todo o vetor de testes com ZERO
  parâmetro: Receberá dois vetores
  retorno: Sem retorno
*/
void Iniciando_Vetor(int vetor[],int vetor_testes[])
{
  int i;
  for(i=0;i<DIM;i++){
    vetor[i]=1;
  }
  for(i=0;i<DIM;i++){
    vetor_testes[i]=0;
  }
}

/*----------------------------------------------------------------------------------------------------*/
//objetivo: Preencher um vetor com os N's , M's e temperaturas dadas pelo usuario
//parâmetro: Receberá um vetor que sera colocado todos os dados
//retorno: Sem retorno
void Preencher(int vetor[])
{

  int posicao = 0,//Iniciando esta variavel para chamar a função N_M
      i,//Variavel de controle do FOR
      j,//Variavel responsavel em deslocar as linhas para o preencimento das temperaturas
      continuar=1;//Variavel que indicarar quando encerrar o laço
  do{
      N_M(vetor,posicao);//Chamada a função que define o N e M
      if(vetor[posicao]!=0){
        j=2;
        for(i=0;i<vetor[posicao];i++){
          do{//Impondo as condições de entrada das temperaturas
              scanf("%d",&vetor[posicao+j]);
              if(vetor[posicao+j]<-200 || vetor[posicao+j]>200){printf("\nA tempera deve estar entre -200 e 200: ");}
          }while(vetor[posicao+j]<-200 || vetor[posicao+j]>200);

          j++;
        }
        posicao+=vetor[posicao]+2;//O numero de casas deslocados é N + 2, para ser colocado o proximo valor do N
      }else{
        continuar = 0;
      }
  }while(continuar);


}


/*----------------------------------------------------------------------------------------------------*/
//objetivo: Preencher no vetor o N e o M de uma sequencia
//parâmetro: Receberá um vetor e o a posição em que sera colocado o N
//retorno: Sem retorno
void N_M(int vetor[], int posicao)
{
  //Leitura o validação do que sera o N
  do{//Impondo as condições de entrada em N (0<=N<=800)
      scanf("%d",&vetor[posicao]);
      if(vetor[posicao]<0 || vetor[posicao]>800){printf("\nN deve estar entre 0 e 800: ");}
  }while(vetor[posicao]<0 || vetor[posicao]>800);

  //Leitura o validação do que sera o M
  if(vetor[posicao]!=0){//Garantindo que o M atenda a especificação de ser 1<=M<=N
      do{//Impondo as condições de entrada em M (0<=M<=N)
        scanf("%d",&vetor[posicao+1]);
        if(vetor[posicao+1]<1 || vetor[posicao+1]>vetor[posicao]){printf("\nM deve estar entre 1 e N: ");}
      }while(vetor[posicao+1]<1 || vetor[posicao+1]>vetor[posicao]);

  }else{
      /*
        *Caso o N seja ZERO obrigatoriamente o M tambem deve ser, sera
        *redundante pedir ao usuario para digitar,
        *logo o programa fara automaticamente
      */
      vetor[posicao+1] = 0;
  }
}

/*----------------------------------------------------------------------------------------------------*/
//objetivo: Fazer a media das temporatura e colocar as medidas em um outro vetor
//parâmetro: Receberá dois vetores, um com todas as  temperaturas e numeros de linhas, e outro para registrar as medias dos testes
//retorno: Retorna a quantidade de testes feitos
int Media_Temperatura(int vetor_temperaturas[],int vetor_testes[])
{
/*-------------------Variaveis-------------------------*/
  /*(As variveis seram sendo explicadas ao decorrer do codigo)*/
    int N,M,i=0,cont,j=2,Somatoria,x=0,
        chute=1,
        sair = 0,
        padrao = 0,
        Ctrl_Deslocamento,
        Aux_Ctrl,
       Controle = 1,
        Tot_Testes=0;

/*-------------------Testes e atribuições-------------------------*/
    do{
        N = vetor_temperaturas[i];//Recuperando o valor do N
        M = vetor_temperaturas[i+1];//Recuperando o valor do M
      if(N!=0){//Enquanto N seja diferente de Zero fazemos a medias
        Ctrl_Deslocamento=2;//Esta variavel começa com dois para que não use os valores de N e M
        Aux_Ctrl= 0; // Esta varivel que Auxilia a variavel 'Ctrl_Deslocamento' no deslocamento dela pelo vetor
        padrao = N-M; // Aqui pegamos o padrão de quantas casas a frente seram usadas na Somatoria
          do{
            Somatoria = 0; // Variavel que recebe toda as somas das casas dos vetores, e é zerada a cada encerramento do pardrão
            j=1;//Essa variavel, faz o controle detro do laço a baixo para que ele faça a soma apenas do tanto de casas que foi definido pelo usuario
              do{
                /*
                  Esse teste verifica se é a primeira soma de uma sequência, caso seja, ele somará o valor da posição 1 do vetor com a 2,
                  caso a variavel 'Controle' seja ZERO, nos apenas somamos as proximas casas ate que se encerre o laço
                */
                  if(Controle){
                    Somatoria = vetor_temperaturas[i+Ctrl_Deslocamento] + vetor_temperaturas[i+(Ctrl_Deslocamento+1)];
                    Controle = 0;//Zeramos 'Controle' para que ele não entre novamente aqui na mesma sequencia
                  }else{
                    Somatoria += vetor_temperaturas[i+(Ctrl_Deslocamento+1)];
                  }
                  Ctrl_Deslocamento++;//Deslocamos a casa dos vetores com esta variavel
                  j++;//Controlamos o laço
              }while(j<M);
              Controle = 1;// 'Controle' novemente recebe 1 para que em uma nova Somatoria, a primeira soma seja o vetor na posição 1 com a 2
              Aux_Ctrl++;
            /*
              Auxiamos a variavel 'Ctrl_Deslocamento' para que ela desloque para a poxima casa do vetor.
              Assim sera possivel fazer uma sequencia de somatias como: 1 com 2, 2 com 3, 3 com 4, etc...
            */
              Ctrl_Deslocamento = 2 + Aux_Ctrl;
             /*
               O objetivo desse teste é apenas verificar de uma sequencia de medias quem é a maior e que é a menor
               A cada bateria de testes é separada duas casas de um vetor (vetor_testes), um recebera a maior media e a outra a menor
             */
              if(chute==1){//Caso seja a primeira rodada de um teste, damos um chute inial de quem é a maior e a menor media
                vetor_testes[x]=(int)Somatoria/M;//Arredondando o valor da media com um simples cast, deixando assim apenas parte inteira
                vetor_testes[x+1]=(int)Somatoria/M;
                chute=0;
              }else// Caso não seja a primeira rodada, simplismente verificamos que é a maior e quem é a menor
              if(Somatoria/M>vetor_testes[x]){
                vetor_testes[x]=(int)Somatoria/M;
              }else if(Somatoria/M<vetor_testes[x+1]){
                vetor_testes[x+1]=(int)Somatoria/M;
              }
              /*
                Essa variavel abaixo, vai sendo incrementada para que quando atingir o padrão + 1,
                significa que foi terminada uma sequencia de testes e o algoritmo ja tem o que precisa,
                então saimos do laço, zeramos as variaveis adequadamente até que dadas as baterias de testes acabem
              */
              sair++;
          }while(sair!=padrao+1);
          //Encrementamos essa variavel para saber a quantidades de testes feitos, e retornamos ela no final para exibir as maiores e menores medias
          Tot_Testes++;
          /*
            Quando a variavel abaixo é incrementada (X), significa que uma bateria de testes foi finalizada,
            então sera reservado mais duas casas do vetor de teste para a proxima sequencia
          */
          x+=2;
          /* 'Chute' é incrementada para que na proxima sequencia de testes tenhamos um chute inicial*/
          chute = 1;
          /*'Sair' é zerada para a proxima sequencia de testes*/
          sair = 0;
          /*Em 'i' somamos o valor do ultimo N + 2 para que la em cima quando N receber um novo valor sera o proximo N de uma sequencia localizada no vetor*/
          i+=vetor_temperaturas[i]+2;
     }else{
       return Tot_Testes;
     }
   }while(Tot_Testes);
}


/*--------------------------------------------------------*/
//objetivo: Exibir os resuntados dos testes feitos
//parâmetro: Recebera o vetor dos testes de temperatura
//retorno: Sem retorno

void exibir(int vetor[],int Tot_Testes)
{
  int cont=0,i;
    for(i=0;i<Tot_Testes;i++){
      printf("Teste %d\n",i+1);
      printf("%d   %d\n",vetor[cont+1],vetor[cont]);
      printf("\n");
      cont +=2;//Incrementamos aqui de 2 em 2 para que seja usada as casas corretas do vetor dos testes
    }
}
