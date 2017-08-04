/* *Função: Esse programa tem como objetivo calcular os custos de uma viajem
            na estrada, usando o custo de gasolina por quilomêtro rodado e o
            valor dos pedágios encontrados no caminho.

   *Autores: Denilson Higino da Silva  | RGM: 36712
             Fernando Oliveira de Lima | RGM: 36716
   *Data : 07/05/2017
____________________________________________________________________________*/
#include <stdio.h>
#include <math.h>


int main()
{
//Declaração das variaveis
    float C, //Comprimento da estrada
          D, //Intervalo dos pedágios
          CustoTotal,//Custo da viajem
          somaPed=0,//Somador dos valores do pedagios
          ValPed, // Valor de cada pedagio
          CustGas;//Custo gasto da gasolina por KM rodado

    int continuar,//Variavel para o laço de repetição do programa
        QtdPed, //Quatidade de pedagios na estrada
        count;  //Variavel de controle



//Entradas dos dados
   do{
    printf("\tCALCULE O CUSTO DE UMA VIAJEM DE CARRO NA RODOVIA\n");

    //ENTRADA DO COMPRIMENTO DA RODOVIA
    printf("Entre com o comprimeto da rodovia que sera percorrida\n");
    printf("(deve estar entre 1 e 10.000 KM)\n");
    printf("--> ");
       do{ //Verificação da entrada do comprimento
        scanf("%f",&C);
            if ((C<1) || (C>pow(10,4)) ){
                printf("Entrada invalida...digite novamente: ");
            }
       }while((C<1) || (C>pow(10,4)) );
//______________________________________________________________

    //ENTRADA DO INTERVALO DO PEDÁGIOS
    printf("\nEntre com o intervalo em que aparecem os pedagios\n");
    printf("(deve estar entre 1 e 10.000 KM e nao pode ser \n");
    printf(" maior que o comprimento da rodovia)\n");
    printf("--> ");
       do{ //Verificação da entrada do comprimento
        scanf("%f",&D);
            if ((D<1) || (D>pow(10,4)) || (D > C)){
                printf("Entrada invalida...digite novamente: ");
            }
       }while((D<1) || (D>pow(10,4)) || (D > C));
//_____________________________________________________________

    //CALCULO DA QUANTIDADE DE PEDAGIO NA ESTRADA
        QtdPed = floor(C/D);

//_____________________________________________________________

    //ENTRADA DO VALOR GASTO DE GASOLINA DO CARRO POR KM
    printf("\nInsira o valor que seu carro gasta de gasolina por KM\n");
    printf("--> R$ ");
        do{ //Verificação do custo da gasolina para que não seja abaixo de 1 real
            scanf("%f",&CustGas);
            if(CustGas<1){
               printf("Entrada invalida...digite novamente: ");
            }
        }while(CustGas<1);
//________________________________________________________________________

    //ENTRADA DO VALOR POR PEDAGIO
    printf("\nExiste(m) %d pedagio(s) na estrada\n",QtdPed);
    printf("_________________________________________\n");
        for(count=1;count<=QtdPed;count++){
            printf("  Valor do %d%c pedagio: R$ ",count,167);
               do{
                scanf("%f",&ValPed);
                    if(ValPed<=0){
                        printf("Entrada com certeza invalida...digite novamente: ");
                    }
               }while(ValPed<=0);

            somaPed += ValPed;
        }
    printf("_________________________________________\n");

//Processamento dos valores da viajem
        CustoTotal= (CustGas*C)+somaPed;

//Saida
        printf("\n_________________________________________________\n");
        printf("O valor total gasto na viajem %c de: R$ %.2f\n",130,CustoTotal);
        printf("_________________________________________________\n");


        printf("\nFazer calculo para outros valores? SIM[1]-NAO[0]");
            scanf("%d",&continuar);
        system("clear||cls");
   }while(continuar);
    return 0;
}
