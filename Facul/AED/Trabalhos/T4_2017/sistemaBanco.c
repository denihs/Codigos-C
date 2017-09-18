#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Variavel que contara as contas geradas e servira como controle dos CPF's e contas geradas
short int totRegistros;

/*----------------Defines das dos vetores e matrizes---------------------*/
#define TAM_CPF 15
#define TAM_CONTA 10
#define TAM_CPF_TEMP 11
#define TAM_RESGISTRO 1000
/*-----------------------------------------------------------------------*/

/*----------------------ESTRURA DAS CONTAS--------------------------------*/
struct Contas{
  char registroCpf[TAM_CPF];
  char registroConta[TAM_CONTA];
};
typedef struct Contas CONTA;
/*-----------------------------------------------------------------------*/


/*-----------------------Cabeçalhos das funções---------------------------------------*/
void iniciarSistema(CONTA *conta);
int menu(CONTA* conta, char * cpfTemporario);
/*------------------------------------------------------------------------------------*/

int main(){
  srand(time(NULL));
/*----------------------Variaveis,matrizes e vetores---------------------------*/
    int op=1;
    char cpfTemporario[TAM_CPF_TEMP];
    CONTA conta[TAM_RESGISTRO];

    iniciarSistema(conta);
    do{op=menu(conta,cpfTemporario);}while(op);
    return 0;
}
//objetivo: Iniciamos o sitema, zerando as matrizes dos cpf's e das contas, e abastecemos o caixa
//parametros: Vetor que contem todos os registros de CPF e Conta
//retorno: Sem retorno
void iniciarSistema(CONTA *conta)
{
    short int i,j;
    totRegistros = 0;
    for(i=0;i<TAM_RESGISTRO;i++){
        for(j=0;j<TAM_CPF;j++){
            conta[i].registroCpf[j] = '0';
            if(j<7)
            {
              conta[i].registroConta[j]='0';
            }
        }
    }
}
//objetivo: Fazera a função de guiar o usuario pelo sistema e fazera a chamada as funções
//parametros: recebe 2: A estrutura onde sera armazenado todos os CPF's e Contas e um vetor para os cpf sem formatação
//retorno: Retona ZERO caso o usuario opte em sair do sistema e finaliza a aplicação no 'Main'
int menu(CONTA* conta, char * cpfTemporario)
{
    int opcaoI,opcaoII,sair;

      do{
          printf("\t\nMENU PRINCIPAL\n\n");
          printf("1-Cliente\n2-Saque\n3-Relatorio\n4-Finalizar\n-->  ");
          scanf("%d",&opcaoI);
          switch(opcaoI){
              case  1:
                    printf("\t\nMENU CLIENTE\n\n");
                    printf("1-Incluir\n2-Mostrar\n3-Alterar\n4-Excluir\n5-Voltar\n--> ");
                      sair = 1;
                        do{
                            scanf("%d",&opcaoII);
                            switch(opcaoII){
                              case 1:
                                      gera_cpf_valido(cpfTemporario);
                                        obtem_primeiro_digito_verificador(cpfTemporario);
                                        obtem_segundo_digito_verificador(cpfTemporario);
                                      geraContaCorrente(&conta[totRegistros]);
                                      insere_pontuacao_cpf(cpfTemporario,&conta[totRegistros]);
                                      totRegistros++;
                                      sair=0;
                                    break;
                              case 2:
                                    sair=0;
                                    break;
                              case 3:
                                    sair=0;
                                    break;
                              case 4:
                                    sair=0;
                                    break;
                              case 5:
                                    sair=0;
                                    break;
                              default:
                                  printf("\nOpcao nao valida...informe outro valor: ");
                            }
                        }while(sair);
                  break;
            case 2:
                  break;
            case 3:
                  printf("\t\nMENU RELATORIO\n\n");
                  printf("1-Valores sacados\n2-Valor saldo existente\n3-Quantidade de cedulas existentes\n4-Voltar menu principal\n--> ");
                  sair = 1;
                    do{
                        scanf("%d",&opcaoII);
                        switch(opcaoII){
                          case 1:
                                sair=0;;
                                break;
                          case 2:
                                sair=0;
                                break;
                          case 3:
                                sair=0;
                                break;
                          case 4:
                                sair=0;
                                break;
                          case 5:
                                sair=0;
                                break;
                          default:
                              printf("\nOpcao nao valida...informe outro valor: ");
                        }
                    }while(sair);
                break;
            case 4:
                  return 0;
                  break;
          }
      }while(opcaoI!=4);
}

//objetivo:escolhe dentre as letras do alfabeto ('a'..'z') uma letra aleatoriamente
//parametros: nenhum
//retorno:a letra do alfabeto
char geraAlfabeto() {
    int i;
    char letras[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    i=rand()%26;
    return(letras[i]-32);
}

//objetivo:escolhe dentre os numeros ('0'..'9') uma numero aleatoriamente
//parametros: nenhum
//retorno:o numero
char geraNumero() {
    int i;
    char numeros[] = { '0','1','2','3','4','5','6','7','8','9'};

    i=rand()%10;
    return(numeros[i]);
}
//objetivo:verifica se um cpf no formato 999.999.999-99 e valido
//parametros: cpf:cpf a ser verificado
//retorno: 1 se cpf e valido ou 0 se cpf nao e valido
int verifica_cpf_valido(char cpf[]) {
   int valido=1;

   //implemente aqui

   return(valido);
}

//objetivo:insere pontuacoes '.' e '- ' em um cpf
//parametros: cpf_origem:o cpf recebido no format 99999999999
//            cpf_destino:o cpf com as pontuacoes inseridas no formato 999.999.999-99
void insere_pontuacao_cpf(char *cpfTemp,CONTA* conta) {
    int i=0, j;

    for(j=0;j<TAM_CPF-1;j++){
        if(j!=3 && j!=7 && j!=11 )
        {
          conta->registroCpf[j] = cpfTemp[i];
          i++;
        }else{
          if(j==3 || j==7)
          {
            conta->registroCpf[j] = '.';
          }else{
            conta->registroCpf[j] = '-';
          }
        }
    }
    conta->registroCpf[14] = '\0';
}
//objetivo:calcula o primeiro digito verificador de um cpf no formato 999999999
//parametros: cpf:o cpf sem os digitos verificadores
//retorno: sem retorno
void obtem_primeiro_digito_verificador(char *cpf) {
   int digito,soma=0,i,j=0;
      for(i=10;i>1;i--){
          soma += i*(cpf[j]-48);
          j++;
      }
      soma %= 11;
      if(soma<2){//Determinação do primeiro digito
          digito = 0;
      }else{
          digito = 11 - soma;
      }
      cpf[9] = digito+48;
}
//objetivo:calcula o segundo digito verificador de um cpf no formato 999999999
//parametros: cpf:o cpf sem os digitos verificadores
//retorno: o calculo do segundo digito verificador
void obtem_segundo_digito_verificador(char* cpf) {
  int digito,soma=0,i,j=0;
     for(i=11;i>1;i--){
         soma += i*(cpf[j]-48);
         j++;
     }
     soma %= 11;
     if(soma<2){//Determinação do primeiro digito
         digito = 0;
     }else{
         digito = 11 - soma;
     }
     cpf[10] = digito+48;
}
//objetivo:gera aleatoriamente um numero de conta corrente no formato 999.999-X
//parametros: c:onde armazera a conta gerada
//retorno:nenhum
void geraContaCorrente(CONTA* conta) {
    int i,j;

    for(i=0;i<TAM_CONTA;i++){
        if(i!=3 && i!=7 && i!=8)
        {
          conta->registroConta[i] = geraNumero();
        }else{
            if(i==3){
                conta->registroConta[i] = '.';
            }else if(i==7){
                conta->registroConta[i] = '-';
            }else{
                conta->registroConta[i] = geraAlfabeto();
            }
        }
    }
      conta->registroConta[10] = '\0';
}
//objetivo:gera aleatoriamente um cpf valido no formato 999.999.999-99
//parametros: cpf:o cpf onde sera armazenado o cpf valido
//retorno: nenhum
void gera_cpf_valido(char *cpf)
{
    int i,clone,sair=1;
      do{
        clone=0;
        for(i=0;i<9;i++){
          cpf[i]=geraNumero();
            if(i!=0)
            {
              if(cpf[i]==cpf[i-1])
              {
                clone++;
              }
            }
        }
        if(clone!=8){sair=0;}
      }while(sair);
}

