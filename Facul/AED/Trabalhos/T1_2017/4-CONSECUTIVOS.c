/* *Função: A função do programa é sortear um numero 'N' e usar este numero
            para reprentar o numero de bolas de um globo de sorte. Cada uma
            das bolas tera um valor atribuido de forma aleatoria e limitada
            de forma que cada bola possa ter valores apenas de 1 a 2. A maior
            sequência representara o total de pontos do participante.

   *Autores: Denilson Higino da Silva  | RGM: 36712
             Fernando Oliveira de Lima | RGM: 36716

   *Data : 07/05/2017
/*============================================================================*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main()
{
/*============================Declaração de variaveis=========================*/
    char c;

    int N,//Valor do numero de bolas da sorte do usuario
        count,//Variavel simples de controle
        Maior=0,//Variavel que receberar a maior sequencia
        bolas,//Variavel que receberar os valores das bolas
        soma=1;//Variavel da soma das sequencias

    char sequencia[10000];//Essa String sera usada para guarda os valor das bolas e posteriormente compara-los  entre si

/*============================ENTRADA DE DADOS===============================*/
    /*O programa não pedirá valores ao usuario, apenas
      pedira que ele de o start inicial com o ENTER
      pois os valore serão todos feitos de forma aleatoria */

    printf("\tGERADOR DE NUMEROS DA SORTE\n");
    printf("Precione ENTER para dar start a sua sorte!!\n\n");
        scanf("%c",&c);

/*============================PROCESSAMENTO==================================*/
    //Atribuindo o valor de N com a função Randomica que sorteará um numero de 1 a 10000
        srand(time(NULL));
    N=1+(rand()%10000);

    //Area onde sera feita a verificação das sequências
    for(count=0;count< N;count++){

            //Funcao que varia o valor de cada bola(de 1 a 2) a cada looping
            bolas = 1+(rand()%2);

            //Transformando o valor da bola em caracter (Somando o 48 que representa o ZERO na tabela ASCII, tornando possivel a conversão)
            sequencia[count]=bolas+48;
        }

      if(N>1){//Se N for maior que zero, sera possivel Existir um sequencia

        for(count=0;count<N;count++){
            //Comparando os termos que cada valor que esta dentro da String
            if(sequencia[count]==sequencia[count+1]){
                soma++;
                if(soma>=Maior){
                    Maior=soma;
                }
            }else{
                soma=1;
            }
        }
      }
/*============================Saida=========================================*/
        printf("O valor do N que representa a quantidade de suas bolas no globo foi de %d",N);
        printf("\nSua pontuacao pontuacao foi= %d\n\n",Maior);

    return 0;
}
