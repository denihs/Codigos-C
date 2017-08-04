/* * Função : Programa com a fução de informar o numero de acessos que um determinado link
              teve em função de um outro.
   * Autores:Denilson Higino da Silva  | RGM:36712
             Fernando Oliveira de Lima | RGM 36716
   * Data : 07/05/2017
_________________________________________________________________________________________*/
#include <stdio.h>

int main()
{
/*============================DECLARAÇÃO DAS VARIAVEIS==========================*/
    int t;//t = Numero de pessoas que acessaram o terceiro link.
    float result;

/*============================ENTRADA DE DADOS==================================*/
    printf("\tVERIFIQUE OS CLIQUES EM UM LINK EM RELA%c%cO A OUTRO\n",128,182);
    printf("Entre com o numero de pessoas que acessaram o terceiro link: \n");
    printf("(O numero deve estar entre 1 e 1000)\n");
    printf("--> ");
       do{ //Verificação do numero de entrada
        scanf("%d",&t);
        if((t<1) || (t>1000)){
            printf("O valor inserido %c invalido\n",130);
            printf("Digite outro: ");
        }
       }while((t < 1)||(t > 1000));

/*============================PROCESSANDO DADOS============================*/
    result = t * 4;

/*==========================SAIDA DOS DADOS===============================*/
    printf("\n____________________________________________________\n");
        //Ajuste da concordância verbal
        if(t==1){
            printf("  Para 1 pessoa que clicou no terceiro link\n");
        }else{
            printf("  Para %d pessoas que clicaram no terceiro link\n",t);
        }
    printf("  %.0f pessoas clicaram no primeiro.",result);
    printf("\n____________________________________________________\n");
    return 0;
}
