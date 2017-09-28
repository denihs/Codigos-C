#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
//Variavel que contara as contas geradas e servira como controle dos CPF's e contas geradas
short int totRegistros;
short int totSaques;
int VALOR_TOTAL_CAIXA;
/*----------------Defines das dos vetores e matrizes---------------------*/
#define TAM_CPF 15
#define TAM_CONTA 10
#define TAM_CPF_TEMP 11
#define TAM_RESGISTRO 1000
#define ID_SAQUE_COL 2
#define ID_SAQUE_LIN 6800
#define TIPOS_CEDULAS 9
/*-----------------------------------------------------------------------*/

/*----------------------ESTRURA DAS CONTAS--------------------------------*/
struct Contas{
  char registroCpf[TAM_CPF];
  char registroConta[TAM_CONTA];
};
typedef struct Contas CONTA;

struct Cedulas{
   short int C[TIPOS_CEDULAS];
};
typedef struct Cedulas CEDULAS;

struct Saques{
  short int saques[ID_SAQUE_LIN][ID_SAQUE_COL];
};
typedef struct Saques SAQUES;

/*-----------------------------------------------------------------------*/


/*-----------------------Cabeçalhos das funções---------------------------------------*/
void iniciarSistema(CONTA *conta,CEDULAS* cedulas);
int menu(CONTA* conta, char * cpfTemporario,SAQUES* saques,CEDULAS* cedulas);
void Exibir(CONTA *contas);
char geraAlfabeto();
char geraNumero();
void insere_pontuacao_cpf(char *cpfTemp,CONTA* conta);
void obtem_primeiro_digito_verificador(char *cpf);
void obtem_segundo_digito_verificador(char* cpf);
void geraContaCorrente(CONTA* conta);
void gera_cpf_valido(char *cpf);
int igualdadeCpf(CONTA *contas);
int igualdadeConta(CONTA *contas);
int validarAlteracao(CONTA* contas);
int checkCPF(char* conta,CONTA* contas);
int verifica_cpf_valido(char* cpf);
int checkConta(char* conta,CONTA* contas);
void Excluir(CONTA* contas,SAQUES* saque);
int Vericador_Saques(SAQUES* saque,int id);
void Saque(CONTA* conta,SAQUES* saque,CEDULAS* cedulas );
void Manipulador_cedulas(int valor,CEDULAS* cedulas);
int Busca(int key,int *Ids,int cont);
void Relatorio_Valor_Total_Sacado(CONTA* contas,SAQUES* saque);
void Relatorio_Valor_Total_Caixa();
void Relatorio_Valor_Total_Cedulas(CEDULAS* cedulas);
void Extenso(int* valor,int DinheiroOuCedula);
/*------------------------------------------------------------------------------------*/

int main(){
  srand(time(NULL));
/*----------------------Variaveis,matrizes e vetores---------------------------*/
    int op=1;
    char cpfTemporario[TAM_CPF_TEMP];
    CONTA conta[TAM_RESGISTRO];
    SAQUES saques;
    CEDULAS cedulas;

    iniciarSistema(conta,&cedulas);
    do{op=menu(conta,cpfTemporario,&saques,&cedulas);}while(op);
    return 0;
}
//objetivo: Iniciamos o sitema, zerando as matrizes dos cpf's e das contas, e abastecemos o caixa
//parametros: Vetor que contem todos os registros de CPF e Conta
//retorno: Sem retorno
void iniciarSistema(CONTA *conta,CEDULAS* cedulas)
{
    short int i,j;
    totRegistros = 0;
    totSaques = 0;
    for(i=0;i<TAM_RESGISTRO;i++){
        for(j=0;j<TAM_CPF;j++){
            conta[i].registroCpf[j] = '0';
            if(j<7)
            {
              conta[i].registroConta[j]='0';
            }
        }
    }
    cedulas->C[0] = 100;
    cedulas->C[1] = 200;
    cedulas->C[2] = 400;
    cedulas->C[3] = 500;
    cedulas->C[4] = 600;
    cedulas->C[5] = 700;
    cedulas->C[6] = 800;
    cedulas->C[7] = 1500;
    cedulas->C[8] = 2000;
    VALOR_TOTAL_CAIXA = 108000;
}
//objetivo: Fazera a função de guiar o usuario pelo sistema e fazera a chamada as funções
//parametros: recebe 2: A estrutura onde sera armazenado todos os CPF's e Contas e um vetor para os cpf sem formatação
//retorno: Retona ZERO caso o usuario opte em sair do sistema e finaliza a aplicação no 'Main'
int menu(CONTA* conta, char * cpfTemporario,SAQUES* saques,CEDULAS* cedulas)
{
    char opcaoI,opcaoII,sair;

      do{
          printf("\n\n           MENU PRINCIPAL\n\n");
          printf("1-Cliente\n2-Saque\n3-Relatorio\n4-Finalizar\n-->  ");
          __fpurge(stdin);
          scanf("%c",&opcaoI);
          switch(opcaoI){
              case  '1':
                    printf("\n\n           MENU CLIENTE\n\n");
                    printf("1-Incluir\n2-Mostrar\n3-Alterar\n4-Excluir\n5-Voltar\n--> ");
                      sair = '1';
                        do{
                            __fpurge(stdin);
                            scanf("%c",&opcaoII);
                            switch(opcaoII){
                              case '1':
                                      if(totRegistros<1000){
                                            do{
                                                gera_cpf_valido(cpfTemporario);
                                                  obtem_primeiro_digito_verificador(cpfTemporario);
                                                  obtem_segundo_digito_verificador(cpfTemporario);
                                                geraContaCorrente(&conta[totRegistros]);
                                                insere_pontuacao_cpf(cpfTemporario,&conta[totRegistros]);
                                            }while( !igualdadeCpf(conta) && !igualdadeConta(conta) );
                                            printf("\n\nConta adionada com sucesso!\n");
                                            printf("Dados da conta:\n");
                                            printf("%s  %s\n",conta[totRegistros].registroConta,conta[totRegistros].registroCpf);
                                            totRegistros++;
                                      }else{
                                        printf("\n\nO total de contas abertas ja atingiu seu limite!\nCaso queira adicinar uma conta nova, exclua alguma ja existente.\n");
                                      }
                                        sair='0';
                                    break;
                              case '2':
                                        Exibir(conta);
                                        sair='0';
                                    break;
                              case '3':
                                      validarAlteracao(conta);
                                      sair='0';
                                    break;
                              case '4':
                                      Excluir(conta,saques);
                                      sair='0';
                                    break;
                              case '5':
                                    sair='0';
                                    break;
                              default:
                                  printf("\nOpcao nao valida...informe outro valor: ");
                            }
                        }while(sair!='0');
                  break;
            case '2':
                  Saque(conta,saques,cedulas);
                  break;
            case '3':
                  printf("\t\nMENU RELATORIO\n\n");
                  printf("1-Valores sacados\n2-Valor saldo existente\n3-Quantidade de cedulas existentes\n4-Voltar menu principal\n--> ");
                  sair = '1';
                    do{
                        __fpurge(stdin);
                        scanf("%c",&opcaoII);
                        switch(opcaoII){
                          case '1':
                                if(totRegistros!=0){
                                  Relatorio_Valor_Total_Sacado(conta,saques);
                                }else{
                                  printf("\n\nCaixa sem cadastros! Nao existe relatorio que possa ser gerado\n\n");
                                }
                                sair='0';
                                break;
                          case '2':
                                  if(VALOR_TOTAL_CAIXA!=0){
                                    Relatorio_Valor_Total_Caixa();
                                  }else{
                                    printf("\n\nCAIXA VAZIO!\n\n");
                                  }
                                  sair='0';
                                break;
                          case '3':
                                sair='0';
                                  Relatorio_Valor_Total_Cedulas(cedulas);
                                break;
                          case '4':
                                sair='0';
                                break;
                          default:
                              printf("\nOpcao nao valida...informe outro: ");
                        }
                    }while(sair!='0');
                break;
            case '4':
                  return 0;
                  break;
          }
      }while(opcaoI!='4');
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

//objetivo:insere pontuacoes '.' e '- ' em um cpf
//parametros: cpf_origem:o cpf recebido no format 99999999999
//            cpf_destino:o cpf com as pontuacoes inseridas no formato 999.999.999-99
void insere_pontuacao_cpf(char *cpfTemp,CONTA* conta) {
    int i=0, j;

    for(j=0;j<TAM_CPF;j++){
        if(j!=3 && j!=7 && j!=11 )
        {//Quando o 'j' é diferente de 3, 7 e 11 colocamos os numeros do vetor 'cpfTemp' em seus intervalos
           conta->registroCpf[j] = cpfTemp[i];
          i++;
        }else{
          if(j==3 || j==7)
          {//Se 'j' for 3 ou 7 colocamos um ponto (.) na casa
            conta->registroCpf[j] = '.';
          }else{//Na casa 11 colocamos o traço
            conta->registroCpf[j] = '-';
          }
        }
    }
    //No fim da linha colocamos o terminador de String
    conta->registroCpf[14] = '\0';
}
//objetivo:calcula o primeiro digito verificador de um cpf no formato 999999999
//parametros: cpf:o cpf sem os digitos verificadores
//retorno: sem retorno
void obtem_primeiro_digito_verificador(char *cpf) {
   int digito,soma=0,i,j=0;
      for(i=10;i>1;i--){
          soma += i*(cpf[j]-48);//Subtrai o valor 48 do caracter para fazer a conversão do caracter para inteiro
          j++;
      }
      soma %= 11;
      if(soma<2){//Determinação do primeiro digito
          digito = 0;
      }else{
          digito = 11 - soma;
      }
      //Soma 48 para transforma o inteiro em caracter novamente
      cpf[9] = digito+48;
}
//objetivo:calcula o segundo digito verificador de um cpf no formato 999999999
//parametros: cpf:o cpf sem os digitos verificadores
//retorno: o calculo do segundo digito verificador
void obtem_segundo_digito_verificador(char* cpf) {
  int digito,soma=0,i,j=0;
     for(i=11;i>1;i--){
         soma += i*(cpf[j]-48);//Subtrai o valor 48 do caracter para fazer a conversão do caracter para inteiro
         j++;
     }
     soma %= 11;
     if(soma<2){//Determinação do primeiro digito
         digito = 0;
     }else{
         digito = 11 - soma;
     }
       //Soma 48 para transforma o inteiro em caracter novamente
     cpf[10] = digito+48;
}
//objetivo:gera aleatoriamente um numero de conta corrente no formato 999.999-X
//parametros: Recebe o endereço de uma casa do registro 'CONTA'
//retorno:nenhum
void geraContaCorrente(CONTA* conta) {
    int i,j;

    for(i=0;i<TAM_CONTA;i++){
        if(i!=3 && i!=7 && i!=8)
        {//Quando i é diferente de 3, 7 e 8 colocamos no 'registroConta' de um dado registro numeros aleatorios
          conta->registroConta[i] = geraNumero();
        }else{
            if(i==3){
                conta->registroConta[i] = '.';
            }else if(i==7){
                conta->registroConta[i] = '-';
            }else{//Quando i é igual a 8 colocamos uma letra na casa do 'registroConta'
                conta->registroConta[i] = geraAlfabeto();
            }
        }
    }
      //Adicionamos o terminador de String no fim do conjunto
      conta->registroConta[9] = '\0';
}
//objetivo:gera aleatoriamente um cpf valido no formato 999.999.999-99
//parametros: cpf:o cpf onde sera armazenado o cpf valido
//retorno: nenhum
void gera_cpf_valido(char *cpf)
{
    int i,
        clone,//Variavel que é incrementada toda vez que temos um numero igual ao anterior
        sair=1;
      do{
        clone=0;
        for(i=0;i<9;i++){
          cpf[i]=geraNumero();
              if(cpf[i]==cpf[i-1])
              {
                clone++;
              }
        }
        if(clone!=8){sair=0;}
        //Enquanto os ele gerar os 8 valores iguais o programa ficara em looping
        //evitando que tenhamos um cpf com todos os valores iguais
      }while(sair);
}
//objetivo:Mostrar os todos os dados de cpf e contas criados até o momento
//parametros: O vetor com todos os dados
//retorno: nenhum
void Exibir(CONTA *contas){
  int i;
  if(totRegistros==0)
  {
    printf("\n\nNenhum conta foi adiconada até o momento\n\n");
  }else{
    printf("\n\n\t   DADOS REGISTRADOS:\n");
    printf("        CONTA(s)         CPF(s):\n");
    for(i=0;i<totRegistros;i++){
      printf("%4d - %s ___ %s\n",i+1,contas[i].registroConta,contas[i].registroCpf);
    }
  }
}
//objetivo: Garante que não exista dois CPF's iguais no sistema
//parametros:  Os CPF's salvos no sistema
//retorno: Retorna 1 senão existir CPF's iguais, e ZERO caso exista
int igualdadeCpf(CONTA *contas)
{
  int i;
  if(totRegistros){
      for(i=0;i<totRegistros;i++){
        if(!strcmp(contas[totRegistros].registroCpf,contas[i].registroCpf)){
            return 0;
        }
      }
  }
  return 1;
}
//objetivo: Garante que não exista dois contas iguais no sistema
//parametros:  As contas salvos no sistema
//retorno: Retorna 1 senão existir contas iguais, e ZERO caso exista
int igualdadeConta(CONTA *contas)
{
  int i;
  if(totRegistros){
      for(i=0;i<totRegistros;i++){
        if(!strcmp(contas[totRegistros].registroConta,contas[i].registroConta)){
            return 0;
        }
      }
  }
  return 1;
}
//objetivo: Ser um 'Sub-Menu' para a parte de alteração tanto do CPF quando da conta
//parametros:  O resgistro com as contas e CPFs
//retorno: Retorna 1 se tudo ocorrer bem
int validarAlteracao(CONTA* contas)
{
    int i=0,sair=1,cont;
    char str[TAM_CONTA],//Recebera a conta digitada tanto para acessar o menu quanto para altera-lo
         CPF[TAM_CPF],//Recebera o CPF que sera alterado
         op;
      if(totRegistros!=0)
      {
          printf("\n\n              MENU DE ALTERACOES\n");
          printf("Informe sua conta atual no formato correto (999.999-X)\n");//Para alterar algum dado o cliente deve informar sua conta
          printf("--> ");
          __fpurge(stdin);
          scanf ( "%9[^\n]", str);
          do{
            if(!strcmp(str,contas[i].registroConta)){//Verificamos se a conta existe no sistema
                do{
                    printf("\nO que deseja alterar?\n1 - CONTA\n2 - CPF\n0 - CANCELAR\n--> ");
                    __fpurge(stdin);
                    scanf("%c",&op);
                    switch(op){
                      case '1'://Alterar CONTA
                              printf("Insira a nova conta no formato correto (999.999-X)\n--> ");
                              __fpurge(stdin);
                              scanf ( "%9[^\n]", str);
                              if (islower(str[8])){ str[8]=toupper(str[8]);}//Antes de passarmos a conta para a verificação deixamos a letra da conta Maiuscula
                                if(checkConta(str,contas)){
                                    strcpy(contas[i].registroConta, str);//Se a funcao 'checkConta' retorna 1 nos trocamos o valor da conta
                                    printf("\n\nConta alterada com sucesso!\n\n");
                                    return 1;
                                }
                              break;
                      case '2'://Alterar CPF
                              printf("Insira um novo CPF no formato correto (999.999.999-99)\n--> ");
                              __fpurge(stdin);
                              scanf ( "%14[^\n]", CPF);
                                  if(checkCPF(CPF,contas)){
                                      strcpy(contas[i].registroCpf, CPF);//Se a funcao 'checkCPF' retorna 1 nos trocamos o valor da conta
                                      printf("\n\nCPF alterado com sucesso!\n\n");
                                      return 1;
                                  }
                              break;
                      case '0':
                              sair = 0;
                              break;
                      default:
                            printf("Opcao invalida!\n--> ");
                    }
                  }while(sair);
            }else if(i==totRegistros){//Caso não tenha a conta no sistema apresentamos esta mensagem
              printf("\n\nDesculpe, esta conta nao consta em nosso sistema.\n\n");
              sair = 0;
            }
            i++;
          }while(sair);
    }else{
      printf("\n\nNao ha contas para serem alteradas!\n\n");
    }
      return 1;
}
//objetivo: Fazer toda a verificação necessaria em cima do CPF
//parametros:  O CPF inserido pelo usuario e o registro de contas e CPFs
//retorno: Retorna 1 se tudo ocorrer bem
int checkCPF(char* conta,CONTA* contas)
{
  int cont;
    if(verifica_cpf_valido(conta)){//Primeiro é verificado se o CPF é  valido
        for(cont=0;cont<totRegistros;cont++){
              if(!strcmp(conta,contas[cont].registroCpf)){//Não deixamos que exista dois CPFs iguais
                  printf("\n\nEste CPF ja pertence a outra conta\n\n");
                  return 0;
              }
        }
        for(cont=0;cont<TAM_CPF-1;cont++){
            if(cont!= 3 && cont != 7 && cont!= 11)
            {
//Verifica se existe numeros onde deve ter, apenas para ter certeza, pois tecnicamente sera desnecessario ja que para chegar aqui o codigo deve passar pela primeira verificacao
              if(!isdigit(conta[cont])){
                  printf("\n\nFalha na alteração, falta de um numero na posicao %d\n\n",cont+1);
                  return 0;
              }
            }
//Verifica se existe os pontos no lugar correto
            else  if(cont==3 || cont == 7)
                  {
                    if(conta[cont] != '.'){
                      printf("\n\nFalha na alteração! Formato de entrada incorreto\n\n");
                    return 0;
                    }
                  }
//Verifica se existe o traco no lugar correto
            else  if(cont==11)
                  {
                      if(conta[cont]!='-'){
                          printf("\n\nFalha na alteração! Formato de entrada incorreto\n\n");
                        return 0;
                      }
                  }
        }
        return 1;
  }else{//Caso o CPF seja valido
      printf("\n\nCPF invalido\n\n");
      return 0;
  }
  return 1;
}
//objetivo: Verifica se o CPF é valido
//parametros: O cpf inserido pelo usuario
//retorno: 1 se cpf e valido ou 0 se cpf nao e valido
int verifica_cpf_valido(char* cpf)
{
  int digito,soma=0,i,j=0,igualdade = 0;;
  char cpfTemp[TAM_CPF_TEMP];

//Passamos apenas os numeros do CPF digitado pelo usuario para um 'cpf temporario'
      for(i=0;i<TAM_CPF-1;i++){
          if(i != 3 && i != 7 && i != 11)
          {
              cpfTemp[j] = cpf[i];
              j++;
          }
      }
/*Nesta função abaixo sera feita a verificação termo a termo,
 *para que não exista um CPF com todos os termos iguais*/
		 for(i=0;i<strlen(cpfTemp);i++){
				if(cpfTemp[i]==cpfTemp[0]){
					igualdade++;
				}
			}
      if(igualdade==11){ return 0; }
//Determinação do primeiro digito e o verifica com o digitado pelo usuario
     j = 0;
     for(i=10;i>1;i--){
         soma += i*(cpfTemp[j]-48);
         j++;}
     soma %= 11;
     if(soma<2){
         digito = 0;
     }else{
         digito = 11 - soma;
     }
     if(digito != cpfTemp[9]-48){ return 0; }
//Determinação do segundo digito e o verifica com o digitado pelo usuario
     soma=0,j=0;
     for(i=11;i>1;i--){
         soma += i*(cpfTemp[j]-48);
         j++;}
     soma %= 11;
     if(soma<2){
         digito = 0;
     }else{
         digito = 11 - soma;
     }
     if(digito != cpfTemp[10]-48){ return 0; }

     return 1;
}
//objetivo: Verifica a conta inserida pelo usuario para que ela esteja no formato correto
//parametros:  A conta digitada pelo usuario e o registro de Contas
//retorno: Retorna 1 se tudo estiver correto ou zero caso algo esteja errado
int checkConta(char* conta,CONTA* contas)
{
  int cont;
  for(cont=0;cont<totRegistros;cont++){//Não deixa que exista duas contas iguais no sistema
        if(!strcmp(conta,contas[cont].registroConta)){
            printf("\n\nEsta conta ja esta cadastrada no sistema\n\n");
            return 0;
        }
  }
  for(cont=0;cont<TAM_CONTA-1;cont++){
      if(cont!= 3 && cont != 7 && cont != 8)
      {
        if(!isdigit(conta[cont])){//Verifica se existe numeros onde deve ter
            printf("\n\nFalha na alteração, falta de um numero na posicao %d\n\n",cont+1);
            return 0;
        }
      }
      else  if(cont==3)
            {
              if(conta[cont] != '.'){//Verifica se existe um ponto no lugar correto
              printf("\n\nFalha na alteração! Formato de entrada incorreto\n\n");
              return 0;
              }
            }
      else  if(cont==7)
            {
              if(conta[cont]!='-'){//Verifica se existe um traco no lugar correto
                printf("\n\nFalha na alteração! Formato de entrada incorreto\n\n");
                return 0;
              }
            }
      else  if(cont==8)
            {
              if(!isalpha(conta[cont])){////Verifica se existe uma letra na ultima posicao da conta digitada
                printf("\n\nFalha na alteração! O ultimo digito deve ser uma letra\n\n");
                return 0;
              }
            }
  }
  return 1;
}
//objetivo: Excluir uma conta conta do sistema
//parametros:  O registro com todas as contas
//retorno: Sem retorno
void Excluir(CONTA* contas,SAQUES* saque)
{
  int i=0,sair=1;
  char str[TAM_CONTA];//Recebera a conta digitada tanto para acessar o menu quanto para altera-lo
  CONTA aux;
    if(totRegistros!=0)
    {
        printf("\t\n\n               MENU DE EXCLUSAO\n");
        printf("Informe a conta que sera excluida no formato correto (999.999-X)\n");//Para alterar algum dado o cliente deve informar sua conta
        printf("--> ");
        __fpurge(stdin);
        scanf ( "%9[^\n]", str);
            do{
                  if(!strcmp(str,contas[i].registroConta)){//Verificamos se a conta existe no sistema
                      if(Vericador_Saques(saque,i)){
                          if(i != totRegistros - 1)
                          {
//A exclusão sera feita com a troca de Variaveis, a conta que o cliente escolher sera jogada para a ultima posição do vetor, e conforme forem sendo add novas contas, as excluidas seram sobrepostas
                              do{
                                  if(i!=totRegistros)
                                  {
                                      aux = contas[i];
                                      contas[i] = contas[i+1];
                                      contas[i+1] = aux;
                                      i++;
                                  }
                              }while(i<totRegistros);
                              totRegistros--;
                          }else{//Caso seja escolhido a ultima conta para ser excluida, nos apenas decrementamos a variavel que conta os registro
                             totRegistros--;
                          }
                          sair = 0;
                          printf("\n\nConta excluida com sucesso!\n\n");
                    }else{
                        printf("\n\nExistem saques registrados nesta conta, ela não podera ser excluida.\n\n");
                        sair = 0;
                    }
                  }else if(i==totRegistros){//Caso não tenha a conta no sistema apresentamos esta mensagem
                      printf("\n\nDesculpe, esta conta nao consta em nosso sistema.\n\n");
                      sair = 0;
                  }
                  i++;
            }while(sair);
      }else{
        printf("\n\nNao existe contas para serem excluidas\n\n");
      }
}
//objetivo: Excluir uma conta conta do sistema
//parametros:  O registro com todas as contas
//retorno: Sem retorno
int Vericador_Saques(SAQUES* saque,int id)
{
  int i;

  for(i=0;i<totSaques;i++){
    if(saque->saques[i][0]==id){
      return 0;
    }
  }
  return 1;
}
//objetivo: Excluir uma conta conta do sistema
//parametros:  O registro com todas as contas
//retorno: Sem retorno
void Saque(CONTA* contas,SAQUES* saque,CEDULAS* cedulas )
{
  int i=0,sair=1;
  char str[TAM_CONTA];//Recebera a conta digitada tanto para acessar o menu quanto para altera-lo
  int valorSaque;
    if(totRegistros!=0)
    {
        printf("\t\n\n               MENU DE SAQUE\n");
        printf("Informe a conta que sera efetuado o saque (999.999-X)\n");//Para alterar algum dado o cliente deve informar sua conta
        printf("--> ");
        __fpurge(stdin);
        scanf ( "%9[^\n]", str);
        do{
              if(!strcmp(str,contas[i].registroConta)){//Verificamos se a conta existe no sistema
                  printf("\nInforme o valor do saque\n--> ");
                  if(VALOR_TOTAL_CAIXA!=0){
                        do{
                            scanf("%d",&valorSaque);
                            if(valorSaque < 0 || valorSaque > VALOR_TOTAL_CAIXA){
                               printf("\n\nValor inserido invalido\n-->");}
                        }while(valorSaque<0||valorSaque>VALOR_TOTAL_CAIXA);

                        if(valorSaque!=0){
                            Manipulador_cedulas(valorSaque,cedulas);
                            printf("\nSaque executado com sucesso! Valor do saque:\nR$ %d,00 ",valorSaque);
                            Extenso(&valorSaque,1);
                            saque->saques[totSaques][0] = i;
                            saque->saques[totSaques][1] = valorSaque;
                            VALOR_TOTAL_CAIXA-=valorSaque;
                            totSaques++;
                        }else{
                          printf("\n\nNenhum valor sacado! Operacao cancelada\n\n");
                        }
                    }else{
                        printf("\n\nCAIXA VAZIO!\n\n");
                    }
                  sair=0;
              }else if(i==totRegistros){//Caso não tenha a conta no sistema apresentamos esta mensagem
                  printf("\n\nDesculpe, esta conta nao consta em nosso sistema.\n\n");
                  sair = 0;
              }
              i++;
        }while(sair);
    }else{
        printf("\n\nSaque nao pode ser realizado ate que existe ao menos uma conta no sistema\n\n");
    }
}
//objetivo: Excluir uma conta conta do sistema
//parametros:  O registro com todas as contas
//retorno: Sem retorno
void Manipulador_cedulas(int valor,CEDULAS* cedulas)
{
  int min,max,aux,j=0,qtd ;
  int espelho[9] = {200,100,50,40,20,10,5,2,1};
  printf("\n\n=============================================================\n");
  printf("\n        SAIDA CEDULAS\n");
      min = 100000,max = 1000000;
      do{
        aux = valor;
          if(valor>=min && valor<max)
          {
              do{
                valor-=min;
              }while(valor>=min);
                  do{
                    qtd = 0;
                      if(aux-espelho[j]>=0 && cedulas->C[j]!=0){
                        do{
                          cedulas->C[j]--;
                          qtd++;
                          aux -= espelho[j];
                        }while(cedulas->C[j] > 0 && aux>=espelho[j]);
                        printf("%d nota(s) de %d\n",qtd,espelho[j]);
                      }
                      j++;
                  }while(j<9);
          }
        min /= 10;
        max /= 10;
        if(j!=0){valor=0;}
      }while(valor!=0);
  printf("\n=============================================================\n");
}
//objetivo: Excluir uma conta conta do sistema
//parametros:  O registro com todas as contas
//retorno: Sem retorno
int Busca(int key,int *Ids,int cont)
{
  int i=0;
    do{
        if(key==Ids[i]){
          return 0;
        }
        i++;
    }while(i<cont);
    return 1;
}

void Relatorio_Valor_Total_Sacado(CONTA* contas,SAQUES* saque)
{
    int i,j=1,
        id,soma,geralSoma,contadorIds=1,trocaExtrato;
    int Ids[TAM_RESGISTRO];

    Ids[0] = saque->saques[0][0];

    for(i=0;i<totSaques;i++){
        if(Busca(saque->saques[i][0],Ids,contadorIds))
        {
            Ids[j] = saque->saques[i][0];
            contadorIds++;
            j++;
        }
    }
    printf("\n\n---------------------------------------------------------------------------------------\n");
    printf("Relatorio 'Valores sacados'");
    printf("\n---------------------------------------------------------------------------------------\n");
    i=0;
    do{
      id = Ids[i];
      soma = 0;
      j=0;
      trocaExtrato = 0;

          printf("Conta corrente: %s ___ CPF: %s  ",contas[id].registroConta,contas[id].registroCpf);
              do{
                  if(trocaExtrato){
                      if(id==saque->saques[j][0]){
                        printf("                                                      R$ %d,00\n",saque->saques[j][1]);
                        soma += saque->saques[j][1];
                      }
                    }else{
                        if(id==saque->saques[j][0]){
                          printf("   R$ %d,00\n",saque->saques[j][1]);
                          soma += saque->saques[j][1];
                          trocaExtrato = 1;
                        }
                    }
                j++;
              }while(j<totSaques);
              printf("                                                                Total: R$ %d,00\n\n",soma);
        i++;
        geralSoma += soma;
    }while(i<contadorIds);
    printf("---------------------------------------------------------------------------------------\n");
    printf("Valor total geral: R$ %d,00  ",geralSoma);
    Extenso(&geralSoma,1);
    printf("\n---------------------------------------------------------------------------------------\n");
}
//objetivo: Excluir uma conta conta do sistema
//parametros:  O registro com todas as contas
//retorno: Sem retorno
void Relatorio_Valor_Total_Caixa()
{
  printf("\n\n---------------------------------------------------------------------------------------\n");
  printf("Relatorio 'Valores do saldo existente'");
  printf("\n---------------------------------------------------------------------------------------\n");
  printf("Total em caixa: R$ %d,00  ",VALOR_TOTAL_CAIXA);
  Extenso(&VALOR_TOTAL_CAIXA,1);

  printf("\n---------------------------------------------------------------------------------------\n\n");
}
//objetivo: Excluir uma conta conta do sistema
//parametros:  O registro com todas as contas
//retorno: Sem retorno
void Relatorio_Valor_Total_Cedulas(CEDULAS* cedulas)
{
  int espelho[9] = {200,100,50,40,20,10,5,2,1}, i,value;
    printf("\n\n---------------------------------------------------------------------------------------\n");
    printf("Relatorio 'Quantidade de cedulas existentes'");
    printf("\n---------------------------------------------------------------------------------------\n");
    printf("                     QUANTIDADE DE CADA CEDULA\n\n");
    for(i=0;i<TIPOS_CEDULAS;i++){
        printf("Cedula de %4d ---->  %4d        ",espelho[i],cedulas->C[i]);
        value = cedulas->C[i];
        Extenso(&value,0);
        printf("\n");
    }

  printf("\n---------------------------------------------------------------------------------------\n\n");
}

//objetivo: Excluir uma conta conta do sistema
//parametros:  O registro com todas as contas
//retorno: Sem retorno
void Extenso(int* valor,int DinheiroOuCedula)
{
  int valorSaque = *valor,dig,min,max,concordancia=1,onze_dezenove=0;

  char UM_NOVE[9][9] = {{"UM"},{"DOIS"},{"TRES"},{"QUATRO"},{"CINCO"},{"SEIS"},{"SETE"},{"OITO"},{"NOVE"}};
  char ONZE_DEZENOVE[9][15] = {{"ONZE"},{"DOZE"},{"TREZE"},{"QUATORZE"},{"QUINZE"},{"DEZESSEIS"},{"DEZESSETE"},{"DEZOITO"},{"DEZENOVE"}};
  char DEZ_NOVENTA[9][15] = {{"DEZ"},{"VINTE"},{"TRINTA"},{"QUARENTA"},{"CINQUENTA"},{"SESSENTA"},{"SETENTA"},{"OITENTA"},{"NOVENTA"}};
  char CEM_NOVECENTOS[9][15] = {{"CENTO"},{"DUZENTOS"},{"TREZENTOS"},{"QUATROCENTOS"},{"QUINHETOS"},{"SEISCENTOS"},{"SETECENTOS"},{"OITOCENTOS"},{"NOVECENTOS"}};
  char CONECTIVOS[5][11] = {{"CENTO"},{" E "},{" MIL "},{" REAIS "},{" CEDULAS "}};

  min = 100000,max = 1000000;
  if(valorSaque==1){concordancia=0;};
  printf("( ");
  do{
    if(valorSaque>=11 && valorSaque<20){onze_dezenove=1;}
    if(valorSaque>=min && valorSaque<max)
    {
      dig = 0;
      do{
        valorSaque-=min;
          dig++;
      }while(valorSaque>=min);
        if(min>=100000){
            if(valorSaque==0){
              printf("CEM MIL REAIS");
            }else{
              printf("%s%s",CONECTIVOS[0],CONECTIVOS[1]);
            }
          }else
              if(valorSaque>=1000 && valorSaque<10000){
                printf("%s",ONZE_DEZENOVE[(valorSaque/1000)-dig]);
                valorSaque -= (valorSaque/1000) * 1000;
                valorSaque != 0 ? printf("%s%s",CONECTIVOS[2],CONECTIVOS[1]) : printf("%s%s",CONECTIVOS[2],CONECTIVOS[3]);

        }else
            if(min>=10000){
              if(valorSaque>=1000){
                printf("%s",DEZ_NOVENTA[dig-1]);
                valorSaque != 0 ? printf("%s",CONECTIVOS[1]) : printf("%s",DinheiroOuCedula ? CONECTIVOS[3]:CONECTIVOS[4]);
              }else
                  if(valorSaque==0){
                      printf("%s MIL REAIS",DEZ_NOVENTA[dig-1]);
                  }else{
                      printf("%s%s",DEZ_NOVENTA[dig-1],CONECTIVOS[2]);
                  }
        }else
            if(min>=1000){
                if(valorSaque>0 && valorSaque<100)
                {
                  printf("%s%s",UM_NOVE[dig-1],CONECTIVOS[2]);
                  valorSaque != 0 ? printf("%s",CONECTIVOS[1]) : printf("%s",DinheiroOuCedula ? CONECTIVOS[3]:CONECTIVOS[4]);
                }else{
                  printf("%s%s",UM_NOVE[dig-1], CONECTIVOS[2]);
                  valorSaque != 0 ? printf(" ") : printf("%s",DinheiroOuCedula ? CONECTIVOS[3]:CONECTIVOS[4]);
                }
        }else
            if(min>=100){
              if(dig==1&&valorSaque==0){
                printf("CEM %s",DinheiroOuCedula ? CONECTIVOS[3]:CONECTIVOS[4]);
              }else{
                printf("%s",CEM_NOVECENTOS[dig-1]);
                valorSaque != 0 ? printf("%s",CONECTIVOS[1]) : printf("%s",DinheiroOuCedula ? CONECTIVOS[3]:CONECTIVOS[4]);
              }
        }else
            if(valorSaque>=1 && valorSaque<10 && onze_dezenove){
              printf("%s",ONZE_DEZENOVE[valorSaque-dig]);
              valorSaque = 0;
              valorSaque != 0 ? printf(" ") : printf("%s",DinheiroOuCedula ? CONECTIVOS[3]:CONECTIVOS[4]);
        }else
            if(min>=10){
              printf("%s",DEZ_NOVENTA[dig-1]);
              valorSaque != 0 ? printf("%s",CONECTIVOS[1]) : printf("%s",DinheiroOuCedula ? CONECTIVOS[3]:CONECTIVOS[4]);
        }else
            if(min>=1&&concordancia){
              printf("%s%s",UM_NOVE[dig-1],DinheiroOuCedula ? CONECTIVOS[3]:CONECTIVOS[4]);
            }else{
              printf("UM REAL");
            }
    }
    min /= 10;
    max /= 10;
  }while(valorSaque!=0);
  printf(" )");
}
