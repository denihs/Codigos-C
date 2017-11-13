/* *Função: Objetivo é decodificar um arquivo txt com numeros ASCII
            e em cima do arquivo decodificado fazer operações.
   *Autor: Denilson Higino da Silva  | RGM: 36712
   *Data de inicio: 11/11/2017
   *Data de finalização: 13/11/2017
===============================================================================*/

#include <stdio_ext.h>
#include <stdlib.h>


FILE * open(char * filename, char* modo);
void close(FILE* f, char* filename);
void menu();
void decifrar();
void arqLinha();
int verificacao();
void contaLinha();
void contaChar();
void search();
void zerar(char * c);

int main()
{
  menu();
  return 0;
}

//Objetivo: Abrir um arquivo
//parâmetros: Um caminho para o arquivo e o mode de arbetura
//retorno: O endereço do arquivo criado
FILE * open(char * filename, char* modo)
{
  FILE* ptr;
  if( (ptr = fopen(filename, modo)) == NULL ){
      printf("\n\n\t\033[31mFALHA AO ABRIR O ARQUIVO %s\033[m\n\n", filename);
      exit(1);
  }
  return(ptr);
}

//Objetivo: Fechar um arquivo aberto
//parâmetros: Um caminho para o arquivo e o endereço do arquivo aberto
//retorno: Sem retorno
void close(FILE* f, char* filename)
{
  if( fclose(f) == EOF ){
    printf("\n\n\t\033[31mFALHA AO FECHAR O ARQUIVO %s\033[m\n\n", filename);
    exit(1);
  }
}


//Objetivo: Menu de navegação do sistema
//parâmetros: Sem parametro
//retorno: Sem retorno
void menu()
{
  char op;
  do{
      printf("\n\n1-Decifra arquivo\n2-Grava numero linha arquivo\n3-Quantas linhas o arquivo tem\n4-Qual a maior linha\n5-Pesquisa uma palavra\n0-Encerrar\n\nQual opcao: ");
      __fpurge(stdin);
      scanf("%c",&op );
      switch (op) {
        case '1':
                decifrar();
                printf("\n\n\tDECIFRADO COM SUCESSO\n\n");
                break;
        case '2':
                    if(verificacao()){
                       arqLinha();
                       printf("\n\n\tSUCESSO NA INCLUSAO DAS LINHAS\n\n");
                    }else{
                        printf("\n\n\t\033[31mPrimeiro decifrer o codigo\033[m\n\n");
                    }
                break;
        case '3':
                    if(verificacao()){
                       contaLinha();
                    }else{
                        printf("\n\n\t\033[31mPrimeiro decifrer o codigo\033[m\n\n");
                    }
                break;
        case '4':
                    if(verificacao()){
                       contaChar();
                    }else{
                        printf("\n\n\t\033[31mPrimeiro decifrer o codigo\033[m\n\n");
                    }
                break;
        case '5':
                    if(verificacao()){
                       search();
                    }else{
                        printf("\n\n\t\033[31mPrimeiro decifrer o codigo\033[m\n\n");
                    }
                break;
        case '0':
                break;
        default:
                printf("\n\nEntrada invalida\n\n");
      }
    }while(op != '0');
}

//Objetivo: Decifra o codigo com os numeros ASCII
//parâmetros: Sem parametros
//retorno: Sem retorno
void decifrar()
{
  char* readCode = "readme.code.txt";
  char* decifraCode = "readme.decifra.txt";

  FILE* readC;
  FILE* decifraC;

  int num;
  char a, p;
  readC = open(readCode, "r");
          decifraC = open(decifraCode, "w");
              //Lendo de forma formatada, recuperando um numero e colocando ele na um novo arquivo
              while( (fscanf(readC, "%c%d%c",&a,&num,&p) ) != EOF )
                  fputc(num, decifraC);
          close(decifraC, decifraCode);
  close(readC, readCode);
}

//Objetivo: Criar um arquivo com o numero de linhas
//parâmetros: Sem parametros
//retorno: Sem retorno
void arqLinha()
{
  char* decifraCode = "readme.decifra.txt";
  char* nLinesCode = "readme.nlines.txt";
  char line[100];
  int i;

  for(i = 0; i < 100; i++){
    line[i] = '\0';
  }

  i = 1;

  FILE* decifraC;
  FILE* nLines;

  decifraC = open(decifraCode, "r");
      nLines = open(nLinesCode, "w");
          while( (fgets(line, sizeof(line), decifraC) ) != NULL ){
              fprintf(nLines,"[linha:%3d]%s", i, line);
              i++;
          }
      close(nLines, nLinesCode);
  close(decifraC, decifraCode);
}

//Objetivo: Verifica se o arquivo com os codigos ja foram decodificados
//parâmetros: Sem parametros
//retorno: Retorna 1 se ele foi aberto
 int verificacao()
 {
   char* decifraCode = "readme.decifra.txt";
   FILE* decifraC;
   if( (decifraC = fopen(decifraCode, "r")) != NULL ){
     return 1;
   }
    return 0;
 }

 //Objetivo: Conta a quatidade de linhas que um arquivo possui
 //parâmetros: Sem parametros
 //retorno: Sem retorno
void contaLinha()
{
  char* decifraCode = "readme.decifra.txt";
  char line[100];
  int i=0;


  FILE* decifraC;

  decifraC = open(decifraCode, "r");
    while( (fgets(line, sizeof(line), decifraC) ) != NULL ){
          i++;
    }
    printf("\n\nO arquivo %s tem %d linhas", decifraCode, i);
  close(decifraC, decifraCode);
}

//Objetivo: Verifica qual a linha que possui mais caracteres
//parâmetros: Sem parametros
//retorno: Sem retorno
void contaChar()
{
  char* decifraCode = "readme.decifra.txt";
  char line[100];
  int i=0, linha = 1, auxLinha = 0, maior = 0;

  for(i = 0; i < 100; i++){
    line[i] = '\0';
  }
  i=0;

  FILE* decifraC;

  decifraC = open(decifraCode, "r");


    while( (fgets(line, sizeof(line), decifraC) ) != NULL ){
        while(line[i] != '\0' ){
          i++;
        }
        if(i > maior){
          maior = i;
          auxLinha = linha;
        }
        linha++;
        i = 0;
    }
    printf("\n\nA linha %d e a maior com %d caracteres", auxLinha, maior-1);
  close(decifraC, decifraCode);
}

//Objetivo: Busca na uma palavra no texto decodificado
//parâmetros: Sem parametros
//retorno: Sem retorno
void search()
{
  char* decifraCode = "readme.decifra.txt";
  char line[100];
  char secWord[20];
  char word[20];
  int i=0, linha = 1, j = 0, ocorre = 0, auxLinha = -1;

  zerar(word);
  zerar(secWord);

  printf("\nInforme a palavra de pesquisa: ");
    __fpurge(stdin);
    scanf ( "%19[^\n]", secWord);

  FILE* decifraC;

  decifraC = open(decifraCode, "r");
    printf("\nAs linha em que a palavra \"%s\" ocorre:\n\n ",secWord);
    while( (fgets(line, sizeof(line), decifraC) ) != NULL ){//Pega uma linha
      while(line[i] != '\0' ){
          if(line[i] == secWord[j] && line[i] != ' ' ){
              word[j] = secWord[j];
              j++;
          }else{
              j = 0;
          }
          i++;

          if ( !strcmp(word, secWord) ){
            if(auxLinha != linha){ printf("[linha: %d] %s", linha, line); }
            zerar(word);
            ocorre++;
            auxLinha = linha;
            j = 0;
          }
      }
      linha++;
      auxLinha = -1;
      i = 0;
      j = 0;
    }
    if( !ocorre ){
      printf("\n\n\t\033[31mSem ocorrencia da palavra \"%s\"\033[m\n\n", secWord);
    }else{
      printf("\n\ne tem %d ocorrencia(s)", ocorre);
    }
  close(decifraC, decifraCode);
}

//Objetivo: Instancia um vetor com '\0'
//parâmetros: Recebe um vetor de caracter
//retorno: Sem retorno
void zerar(char * c)
{
  int i;
  for(i = 0; i < 20; i++){
    c[i] = '\0';
  }
}
