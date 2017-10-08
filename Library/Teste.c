#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "myFuckingLibrary.h"

int main()
{
  srand(time(NULL));

  int i;

  char cpfTeste[12];
  char cpfTesteI[15];

  //É ideal que este vetor de valores seja iniciado com finalizadores de string
  char valor[7];

  for(i=0;i<8;i++){
    valor[i]  = '\0';
  }

printf("\n\n----------------TESTES PARA OS CPF's----------------------\n");

  gerarCpf(cpfTeste);
  printf("Sem pontuacao: %s\n",cpfTeste);

  if( cpfValido( cpfTeste ) )
  {
    printf("CPF valido\n\n");
  }else{
    printf("CPF invalido\n\n");
  }

  insere_pontuacao_cpf(cpfTeste,cpfTesteI);
  printf("Com pontuacao: %s\n",cpfTesteI);

  if( cpfValidoP( cpfTesteI ) )
  {
    printf("CPF valido\n\n");
  }else{
    printf("CPF invalido\n\n");
  }

printf("----------------TESTES PARA O EXTENSO----------------------\n");

  strcpy(valor, "659");
  printf("Valor passado: %s\n\n",valor);

  printf("*extenso em REAL: ");
    Extenso(valor , 1);
  printf("\n*extenso em CEDULAS: ");
    Extenso(valor , 0);
  printf("\n\n");
  return 0;
}
