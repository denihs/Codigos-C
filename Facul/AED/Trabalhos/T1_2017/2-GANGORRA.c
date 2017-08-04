/* * Função : Programa com a fução dizer se uma gangorra esta ou não equílibrada,
              levando em consideração o comprimento das extremidades e o peso das pessoas.

   * Autores: Denilson Higino da Silva  | RGM: 36712
              Fernando Oliveira de Lima | RGM: 36716
   * Data : 07/05/2017
________________________________________________________________________________________*/
#include<stdio.h>

int main()
{
/*============================DECLARAÇÃO DAS VARIAVEIS==========================*/
      float C1,C2, //C1 = Comprimento esquerdo | C2 = Comprimento direito
            P1,P2, //P1 = Peso do lado esquerdo | P2 = Peso do lado direito
            LADO1,LADO2;  //LADO1 = Lado esquerdo | LADO2 = lado direito

/*============================ENTRADA DOS DADOS===================================*/
    printf("Veja se a existe um equilibrio entre os dois lados de uma gangorra\n\n");
    printf("\tENTRADA DOS EXTREMOS E OS PESOS\n");

            //ENTRADA DE DADOS DO LADO ESQUERDO DA GANGORRA

    printf("\n\t\tLADO ESQUERDO\n");
    printf("Comprimento (deve ser entre 10 e 100)\n");
    printf("--> ");
       do{ //Verificação da entrada do comprimento
        scanf("%f",&C1);
        if((C1 < 10) || (C1>100)){
            printf("Comprimento invalido\n");
            printf("Digite outro: ");
        }
       }while((C1 < 10) || (C1>100));


    printf("\nPeso da pessoa sentada nesse extremo\n");
    printf("(peso entre 10 e 100)\n");
    printf("--> ");
         do{ //Verificação da entrada do peso
            scanf("%f",&P1);
            if((P1 < 10) || (P1>100)){
                printf("Peso invalido\n");
                printf("Digite outro: ");
            }
        }while((P1 < 10) || (P1>100));

    LADO1 = C1*P1;//Colocando peso em função do comprimento
                  //para obter o valor resultante do lado esquedo.
   //-------------------------------------------------------------------

        //ENTRADA DE DADOS DO LADO DIREITO DA GANGORRA

    printf("\t\tLADO DIREITO\n");
    printf("Comprimento (deve ser entre 10 e 100)\n");
    printf("--> ");
       do{ //Verificação da entrada do comprimento
        scanf("%f",&C2);
        if((C2 < 10) || (C2>100)){
            printf("Comprimento invalido\n");
            printf("Digite outro: ");
        }
       }while((C2 < 10) || (C2>100));


    printf("\nPeso da pessoa sentada nesse extremo\n");
    printf("(peso entre 10 e 100)\n");
    printf("--> ");
         do{ //Verificação da entrada do peso
            scanf("%f",&P2);
            if((P2 < 10) || (P2>100)){
                printf("Peso invalido\n");
                printf("Digite outro: ");
            }
        }while((P2 < 10) || (P2>100));

    LADO2 = C2*P2;//Colocando peso em função do comprimento
                  //para obter o valor resultante do lado direito.
   //-------------------------------------------------------------------------------------

/*============================SAIDA DOS DADOS=====================================*/
            //Verificação do equilibrido da gangorra
       if(LADO1==LADO2){
            printf("\n--> 0 ");
       }else if(LADO1>LADO2){
            printf("\n-->  -1");
       }else{
            printf("\n-->  1");
       }


    return 0;
}
