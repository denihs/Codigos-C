
/* *Função: Simular lutas entre dois vampiros. As lutas se encerram com
            o fim do total de turnos, ou quando a energia vital de um dos
            vampiros chega ao fim. A energia vital é tirada em cada turno
            e de forma randomica, em função de um 'Dado'  que é lançado a
            cada rodada. O perdedor é quem tiver toda a vida zerada ou quem
            tiver menos pontos de energia vital, no fim dos turnos

   *Autor: Denilson Higino da Silva  | RGM: 36712
   *Data de inicio: 26/08/2017
   *Data de finalização: 27/08/2017
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DIM 1000//Definindo uma constante para o tamanho do vetor

/*----------------------CHAMADAS DAS FUNÇÕES-------------------------------*/
void iniciar_vetor(int vetor[]);
int Preencher(int Vetor[]);
void Resultados(int vetor[],int Testes);
int Vencedor_Turno(int AT,int Dado);
int Dado();
/*-----------------------------------------------------------------------*/
int main()
{
  srand(time(NULL));
  int Vetor[DIM],Caso_Testes;

  iniciar_vetor(Vetor);
   Caso_Testes=Preencher(Vetor);
   Resultados(Vetor,Caso_Testes);

  return 0;
}

/*----------------------------------------------------------------------------------------------------*/
//objetivo: iniciamos o vetor com 1 em todas as posicões, evitando assim, problemas na hora de preencher o vetor com os dados inseridos pelo usuario
//parâmetro: Receberá um vetor que sera colocado os valores
//retorno: Sem retorno
void iniciar_vetor(int vetor[])
{
  int i;
  for(i=0;i<DIM;i++){
    vetor[i] = 1;
  }
}


/*----------------------------------------------------------------------------------------------------*/
//objetivo: Preencher um vetor com todas as sequencias nessessarias
//parâmetro: Receberá um vetor que sera colocado todos os dados
//retorno: Retorna a quantidade de Casos

int Preencher(int vetor[])
{
  int controle = 0,//Controla o switch
      sair=0,//Variavel que controlará a saida do laço
      i = 0,//Desloca o vetor
      Caso_Testes = 0;//Conta quantos teste nos temos
  do{
      switch (controle) {//Lê - mos o 'controle'
        case 0:
              if(i==0){//Se caso for a primeira entrada, o usuario não podera digitar o valor ZERO
                  do{
                    scanf("%d",&vetor[i]);
                    if(vetor[i] < 1 || vetor [i]> 10){
                      printf("EV1 deve ser entre 1 e 10--> ");
                    }
                  }while(vetor[i] < 1 || vetor [i]> 10);
              }else{//Caso não seja a primeira entrada, então podera ser digitado ZERO
                  do{
                    scanf("%d",&vetor[i]);
                    if(vetor[i] < 0 || vetor [i]> 10){
                      printf("EV1 deve ser entre 1 e 10(ou zero para encerra)--> ");
                    }
                  }while(vetor[i] < 0 || vetor [i]> 10);
              }
              i++;//Deslocamos o vetor para a proxima casa
              controle++;//Adicionamos mais um em  'controle' para que ele entre no proximo CASE
              break;
              //E todo se repete ate o CASE quatro
        case 1:
                do{
                  scanf("%d",&vetor[i]);
                  if(vetor[i] < 1 || vetor [i]> 10){
                      printf("EV2 deve ser entre 1 e 10--> ");
                  }
                }while(vetor[i] < 1 || vetor [i]> 10);
              i++;
              controle++;
              break;
      case 2:
            do{
                scanf("%d",&vetor[i]);
                  if(vetor[i] < 1 || vetor [i]> 5){
                    printf("AT deve ser entre 1 e 5--> ");
                  }
            }while(vetor[i] < 1 || vetor [i]> 5);
            i++;
            controle++;
            break;
      case 3:
            do{
                scanf("%d",&vetor[i]);
                  if(vetor[i] < 1 || vetor [i]> 10){
                    printf("D deve ser entre 1 e 10--> ");
                  }
            }while(vetor[i] < 1 || vetor [i]> 10);
            i++;
            controle++;
            break;
      case 4:
            do{
                scanf("%d",&vetor[i]);
                  if(vetor[i] < 1 || vetor [i]> 100){
                    printf("T deve ser entre 1 e 100--> ");
                  }
            }while(vetor[i] < 1 || vetor [i]> 100);
            i++;
            controle++;
            break;

      case 5:
                //Aqui deixamos o usuario digitar o 'separador' dos turnos, mas caso ele digite um numero diferente, atribuimos automaticamente
                scanf("%d",&vetor[i]);
                if(vetor[i]!=0){
                    printf(":/ Aqui é o separedor dos turnos, o valor deveria ser zero...Vamos atribuir automaticamente\n");
                    vetor[i] = 0;
                  }
            i++;
            controle=0;//Zeramos controle para que o 'controle' volte la em cima
            Caso_Testes++;
            break;
      }
      /*
        Se o 'controle' for igual a ZERO então, somanos 6 a variavel  'sair'.
        Desta forma sera verificada apenas a coluna que mantem o valor do EV1
      */
        if(!controle){sair += 6;}
  }while(vetor[sair]!=0);
  return Caso_Testes;
}
/*----------------------------------------------------------------------------------------------------*/
//objetivo: Computar e mostrar os resultados de todos os casos de testes
//parâmetro: Recebe o vetor com os dados, e a quantidade de casos de teste
//retorno: Sem retorno
void Resultados(int vetor[],int Testes)
{
  int controle = 0,//Controla o fim da função
      i,//Controle do laço FOR
      Cont=0,//Variavel de controle do laço mais interno
      Seis=0,//Esta varivel é incrementa da 6 em 6, com ela os laços poderam acessar as casas corretas do vetor
      DADO, //Recebe o valor retornado pela função 'Dado'
      VENCEDOR, //Recebe o valor retornado pela função 'Vencedor_Turno'
      Sair = 1; // Zerada quando um dos Vampiros tem a EV igual ou melhor que ZERO
  do{
    printf("\nEV1  EV2   AT   D    T   DADO  Quem_Venceu\n");//Imprimimos as colunas que seram mostrado os valores
      do{
            if(!Cont){//Se for a primeira interação apenas Imprimimos os valores dados pelo usuario
                for(i=0;i<5;i++){
                  printf("%2d   ",vetor[i+Seis]);
                }
                printf("\n");
            }else{//Caso não seja, começamos a fazer os testes
                      /*
                      =======Legenda dos dados======
                          vetor[0+Seis] = EV1
                          vetor[1+Seis] = EV2
                          vetor[2+Seis] = AT
                          vetor[3+Seis] = D
                          vetor[4+Seis] = T
                      */
                DADO = Dado();//Recebemos o valor do dado
                VENCEDOR =  Vencedor_Turno(vetor[2+Seis],DADO);//E o vencedor do turno
                /*Com o valor da variavel 'Vencedor fazemos as devidas trocas de Energia Vital'*/
                if(VENCEDOR){
                  vetor[0+Seis]-=vetor[3+Seis];
                  vetor[1+Seis]+=vetor[3+Seis];
                }else{
                  vetor[1+Seis]-=vetor[3+Seis];
                  vetor[0+Seis]+=vetor[3+Seis];
                }
                /*Apos as incrementações de energia vital, mostramos os valores de: EV1,EV2,AT e D*/
                  for(i=0;i<4;i++){
                    printf("%2d   ",vetor[i+Seis]);
                  }
                /*No lugar de T, sera mostrado os valores da variavel 'Cont'*/
                  printf("%2d   ",Cont);
                /*A frente sera mostrado o valor do Dado*/
                  printf("%2d   ",DADO);
                /*E a seguir o vencedor do turno*/
                  if(VENCEDOR){
                    printf(" vampiro_2");
                  }else{
                    printf(" vampiro_1");
                  }
                  printf("\n");
            }
/*Então fazemos começamos os testes a cada turno para saber se saiu um vencedor*/
            /* Esses são os casos que a energia vital de um dos vampiros acaba*/
            if(vetor[0+Seis]<=0){
              printf("vampiro_2 venceu!\n");
              Sair = 0;//Zeramos 'Sair' para parar o laço
            }else
            if(vetor[1+Seis]<=0){
              printf("vampiro_1 venceu!\n");
              Sair = 0;
            }
            /* Esses são os casos em que os turnos acabam antes da eneria vital*/
            if(Cont==vetor[(4+Seis)]&&Sair){
              if(vetor[0+Seis]>vetor[1+Seis]){
                printf("vampiro_1 venceu!\n");
              }else
              if(vetor[1+Seis]>vetor[0+Seis]){
                  printf("vampiro_2 venceu!\n");
              }else
              if(vetor[0+Seis]==vetor[1+Seis]){
                  printf("O vampiro_1 e o vampiro_2 empataram\n");
              }
            }
          Cont++;//Encrementamos essa variavel para poder sair do laço em função dos Turnos
      }while( Cont < vetor[(4+Seis)]+1 && Sair);
    Seis+=6;//Somamos 6 aqui para que sejam acessado os valores das proximas colunas do vetor
    controle++;//Incrementamos 'controle' para que saia quando acabar os testes
    Sair = 1;//'Sair' volta com 1 para o caso te termos outra bateria de testes
    Cont=0;//Zeramos 'Cont'
  }while(controle<Testes);
}

/*----------------------------------------------------------------------------------------------------*/
//objetivo: Decidir o vencedor do turno
//parâmetro: Recebe o ATa energia vital de um dos vampiros acaba
//retorno: Retornar o vencedor
int Vencedor_Turno(int AT, int Dado)
{
   if(Dado<=AT){
     return 0;//Se retornar ZERO o Vampiro 1 vence
   }else{
     return 1;//Se retorar UM o Vampiro 2 vence
   }
}

/*----------------------------------------------------------------------------------------------------*/
//objetivo: Retornar randomicamente um valor entre 1 e 6
//parâmetro: Sem parâmetro
//retorno: Retornar o rand

int Dado()
{
  return 1+rand()%6;
}
