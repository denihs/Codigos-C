#include <stdio.h>
#include <stdlib.h>
#include <time.h>

short int Id;

#define TAM_LINHA_CPF 1000
#define TAM_COLUNA_CPF 14

#define TAM_LINHA_CONTA 1000
#define TAM_COLUNA_CONTA 9

#define TAM_VET_CHAR 1000
#define TEMP 11


void iniciarSistema(char *registroCpf,char *registroConta);
int menu(char *registroCpf,char *registroConta,char *cpfTemporario,char *letra);


int main(){
  srand(time(NULL));
    int op=1,i,j;
    char registroCpf[TAM_LINHA_CPF][TAM_COLUNA_CPF];
    char registroConta[TAM_LINHA_CONTA][TAM_COLUNA_CONTA];
    char cpfTemporario[TEMP];
    char letra[TAM_VET_CHAR];
    iniciarSistema(registroCpf,registroConta);
    do{op=menu(registroCpf,registroConta,cpfTemporario,letra);}while(op);
  return 0;
}
//objetivo: Iniciamos o sitema, zerando as matrizes dos cpf's e das contas, e abastecemos o caixa
//parametros: recebe 2: A matriz com todos os cpf's, a matriz com todos os numeros de contas
//retorno: Sem retorno
void iniciarSistema(char registroCpf[][TAM_COLUNA_CPF],char registroConta[][TAM_COLUNA_CONTA])
{
    short int i,j;
    Id = 0;
    for(i=0;i<TAM_LINHA_CPF;i++){
        for(j=0;j<TAM_COLUNA_CPF;j++){
            registroCpf[i][j] = '0';
            if(j<7)
            {
              registroConta[i][j]='0';
            }
        }
    }
}
//objetivo: Fazera a função de guiar o usuario pelo sistema e fazera a chamada as funções
//parametros: recebe 4: A matriz com todos os cpf's, a matriz com todos os numeros de contas, um vetor para os cpf sem formatação e um vetor com as letras das contas
//retorno: Retona ZERO caso o usuario opte em sair do sistema e finaliza a aplicação no 'Main'
int menu(char registroCpf[][TAM_COLUNA_CPF],char registroConta[][TAM_COLUNA_CONTA],char *cpfTemporario,char *letra)
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
                                      geraContaCorrente(registroConta);
                                      Id++;
                                      insere_pontuacao_cpf(cpfTemporario,registroCpf);
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

    i=rand()%27;
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
void insere_pontuacao_cpf(char* cpfTemp, char registroCpf[][TAM_COLUNA_CPF]) {
    int i=0, j;

    for(j=0;j<TAM_COLUNA_CPF;j++){
        if(j!=3 && j!=7 && j!=11 )
        {
          registroCpf[Id-1][j] = cpfTemp[i];
          i++;
        }else{
          if(j==3 || j==7)
          {
            registroCpf[Id-1][j] = '.';
          }else{
            registroCpf[Id-1][j] = '-';
          }
        }
    }
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
void geraContaCorrente(char registroConta[][TAM_COLUNA_CONTA]) {
    int i,j;

    for(i=0;i<TAM_COLUNA_CONTA;i++){
        if(i!=3 && i!=7 && i!=8)
        {
          registroConta[Id][i] = geraNumero();
        }else{
            if(i==3){
                registroConta[Id][i] = '.';
            }else if(i==7){
                registroConta[Id][i] = '-';
            }else{
                registroConta[Id][i] = geraAlfabeto();
            }
        }
    }

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
