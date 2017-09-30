/* *Função: Sistema com o intuito de simular todo o codigo basico envolvido
            por tras de um caixa eletronico, trazendo funcionalidades como:
            Saque, alteração ou exclusão de cadastros no sistema alem de gerar
            relatorios de movimentação dos dados do caixa, como por exemplo,
            atualização simuntanea das notas retiradas ou ate os saques feito
            por cada um dos cadastrados .
   *Autor: Denilson Higino da Silva  | RGM: 36712
   *Data de inicio: 18/09/2017
   *Data de finalização: 30/09/2017
===============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

short int totRegistros;//Variavel que contara as contas geradas e servira como controle dos CPF's e contas geradas
short int totSaques;//Variavel que contara quantos saques foram feitos.
int VALOR_TOTAL_CAIXA;//Armazena o valor presente no caixa e decrementa conforme forem existindo saques
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
/*Registro que armazena todas as contas registradas no caixa*/
struct Contas{
  char registroCpf[TAM_CPF];
  char registroConta[TAM_CONTA];
};
typedef struct Contas CONTA;
/*Guadas as quantias de cedulas atuais de cada cedula em um vetor */
struct Cedulas{
   short int C[TIPOS_CEDULAS];
};
typedef struct Cedulas CEDULAS;
/*Armazena todos os saques e as quantidades dos saques feitos no sistema*/
struct Saques{
   int saques[ID_SAQUE_LIN][ID_SAQUE_COL];
};
typedef struct Saques SAQUES;

/*-----------------------------------------------------------------------*/


/*-----------------------Cabeçalhos das funções---------------------------------------*/
void iniciarSistema(CONTA *conta,CEDULAS* cedulas,SAQUES* saque);
void iniciaVetores(char * valor);
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
void Reajuste_Saques(SAQUES* saque,int id);
void Excluir(CONTA* contas,SAQUES* saque);
int Vericador_Saques(SAQUES* saque,int id);
void Saque(CONTA* conta,SAQUES* saque,CEDULAS* cedulas );
void Manipulador_cedulas(int valor,CEDULAS* cedulas);
int Busca(int key,int *Ids,int cont);
void Relatorio_Valor_Total_Sacado(CONTA* contas,SAQUES* saque);
void Relatorio_Valor_Total_Caixa();
void Relatorio_Valor_Total_Cedulas(CEDULAS* cedulas);
int Cont_Elementos(char* valor);
int Valor_Saque(char* valor, int elementos);
void Extenso(char* valor,int DinheiroOuCedula);
/*------------------------------------------------------------------------------------*/

int main(){
  srand(time(NULL));
    int op=1; // Variavel de auxilio
    char cpfTemporario[TAM_CPF_TEMP]; //Cria um vetor para auxilia a a geração dos cpf's validos para as contas
    CONTA conta[TAM_RESGISTRO];//Cria um vetor com espaço para mil contas
    SAQUES saques;//Cria uma variavel de SAQUES onde ficaram armazenados todos os saques
    CEDULAS cedulas;//Cria uma variavel de cedudas onde seram armazenada as cedulas existentes no caixa

    iniciarSistema(conta,&cedulas,&saques);
    do{
        op=menu(conta,cpfTemporario,&saques,&cedulas);
    }while(op);
    return 0;
}

//objetivo: Iniciamos o sitema, zerando as matrizes dos cpf's e das contas, e abastecemos o caixa
//parametros: Vetor que contem todos os registros de CPF e Conta e a variavel com  todos os valores de cedulas
//retorno: Sem retorno
void iniciarSistema(CONTA *conta,CEDULAS* cedulas,SAQUES* saque)
{
    short int i,j;
    totRegistros = 0;
    totSaques = 0;
    //Zera o todas os cpf's e contas que seram geradas antes das primeiras iterações com o sistema
    for(i=0;i<TAM_RESGISTRO;i++){
      strcpy(conta[i].registroCpf,"00000000000");
      strcpy(conta[i].registroConta,"000000000");
    }
    //Tambem iniciamos a variavel de saques com '-1' para evitar futuros problemas
    for(i=0;i<ID_SAQUE_LIN;i++){
      saque->saques[i][0] = -1;
    }
    //Iniciando caixa tanto notas como o primeiro valor do caixa
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
//objetivo: Zerar os vetores que seram usados para mostrar os valores por extenso no sistema
//parametros: Um vetor de char que no caso é o vetor que sera armazenada a quantida em forma de String
//retorno: Sem retorno
void iniciaVetores(char * valor)
{
  int i;
  for(i=0;i<8;i++)
  {
    valor[i] = '\0';
  }
}
//objetivo: Fazerá a função de guiar o usuario pelo sistema e fazer a chamada as funções
//parametros: recebe 4-> A estrutura onde sera armazenado todos os CPF's e Contas, um vetor para os cpf sem formatação, a variavel com todos valores das cedulas e a variavel com todos os saques feitos
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
                              case '1'://Caso escolha incluir um cadastro
                                      if(totRegistros<1000){//É verificado se existem menos de mil contas ja registradas
                                            do{
                                                gera_cpf_valido(cpfTemporario);//Gera os 9 primeiros digitos do cpf
                                                  obtem_primeiro_digito_verificador(cpfTemporario);//Obtem o 10° digito
                                                  obtem_segundo_digito_verificador(cpfTemporario);//Obtem o 11° digito
                                                geraContaCorrente(&conta[totRegistros]);//Gera uma conta corrente
                                                insere_pontuacao_cpf(cpfTemporario,&conta[totRegistros]);//Coloca as pontuacoes no cpf
                                            }while( !igualdadeCpf(conta) && !igualdadeConta(conta) );//E por fim verifica se a conta ou o cpf ja existem no sistema, caso exitam o algoritmo repete o processo
                                            //Se a conta foi gerada apresentamos os dados gerados para o usuario
                                            printf("\n\nConta adionada com sucesso!\n");
                                            printf("Dados da conta:\n");
                                            printf("%s  %s\n",conta[totRegistros].registroConta,conta[totRegistros].registroCpf);
                                            totRegistros++;
                                      }else{//Caso ja tenhamos mil contas no sitema
                                        printf("\n\nO total de contas abertas ja atingiu seu limite!\nCaso queira adicinar uma conta nova, exclua alguma ja existente.\n");
                                      }
                                        sair='0';
                                    break;
                              case '2': //Caso a opção de exibir as contas ja existente seja chamada
                                        Exibir(conta);
                                        sair='0';
                                    break;
                              case '3'://Chamada a alteração de uma conta ou cpf
                                      validarAlteracao(conta);
                                      sair='0';
                                    break;
                              case '4'://Chamada a exclusão de um registro no sistema
                                      Excluir(conta,saques);
                                      sair='0';
                                    break;
                              case '5'://Apenas sai do menu
                                    sair='0';
                                    break;
                              default:
                                  printf("\nOpcao nao valida...informe outro valor: ");
                            }
                        }while(sair!='0');
                  break;
            case '2'://Caso seja optado por fazer um saque
                      Saque(conta,saques,cedulas);
                  break;
            case '3'://Menu para gerar os relatorios
                  printf("\t\nMENU RELATORIO\n\n");
                  printf("1-Valores sacados\n2-Valor saldo existente\n3-Quantidade de cedulas existentes\n4-Voltar menu principal\n--> ");
                  sair = '1';
                    do{
                        __fpurge(stdin);
                        scanf("%c",&opcaoII);
                        switch(opcaoII){
                          case '1'://Opcao de valore sacas ate o momento
                                if(saques->saques[0][0]!=-1){//Caso existe saques feitos no sistema chamamos a função de alteção
                                  Relatorio_Valor_Total_Sacado(conta,saques);
                                }else{
                                  printf("\n\nNenhum saque feito ate o momento\n\n");
                                }
                                sair='0';
                                break;
                          case '2'://Relatorio de saque existente
                                  if(VALOR_TOTAL_CAIXA!=0){//So chamamos a função exista dinheiro no caixa
                                    Relatorio_Valor_Total_Caixa();
                                  }else{
                                    printf("\n\nCAIXA VAZIO!\n\n");
                                  }
                                  sair='0';
                                break;
                          case '3'://Relatorio das cedulas existentes no caixa
                                sair='0';
                                  Relatorio_Valor_Total_Cedulas(cedulas);
                                break;
                          case '4'://Sai do sistema
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
//Retorno:  nenhum
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
//parametros: Recebe o endereço de uma casa onde reside a variavel das contas
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
//objetivo:gera aleatoriamente um cpf valido no formato 99999999999
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
        //dificultando que tenhamos um cpf com todos os valores iguais
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
      for(i=0;i<totRegistros;i++){//Apenas fazemos uma buscas comparando todas as strings ja cadastradas
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
      for(i=0;i<totRegistros;i++){//Apenas fazemos uma buscas comparando todas as strings ja cadastradas
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
    int i=0,sair=1,cont;//Variaveis de controle
    char str[TAM_CONTA],//Recebera a conta digitada tanto para acessar o menu quanto para altera-lo
         CPF[TAM_CPF],//Recebera o CPF que sera alterado
         op;
      if(totRegistros!=0)//Se existem registro poderemos fazer alterações
      {
          printf("\n\n              MENU DE ALTERACOES\n");
          printf("Informe sua conta atual no formato correto (999.999-X)\n");//Para alterar algum dado o cliente deve informar sua conta
          printf("--> ");
          __fpurge(stdin);
          scanf ( "%9[^\n]", str);
          do{
            if(!strcmp(str,contas[i].registroConta)){//Verificamos se a conta inserida acima existe no sistema
                do{
                    printf("\nO que deseja alterar?\n1 - CONTA\n2 - CPF\n0 - CANCELAR\n--> ");
                    __fpurge(stdin);
                    scanf("%c",&op);
                    switch(op){
                      case '1'://Alterar CONTA
                              printf("Insira a nova conta no formato correto (999.999-X)\n--> ");
                              __fpurge(stdin);
                              scanf ( "%9[^\n]", str);
                              if (islower(str[8])){ str[8]=toupper(str[8]);}//Antes de passarmos a conta para a verificação deixamos a letra da conta Maiuscula caso não seja
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
//objetivo: Reajusta os indices da variavel que contem todos os saques no caixa apos uma exclusão
//parametros:  A variavel com os saques registrados e o id da conta excluita
//retorno: Sem retorno
void Reajuste_Saques(SAQUES* saque,int id)
{
    int i;
    for(i=0;i<totSaques;i++)
    {
        if(saque->saques[i][0]>id)//Caso exista no na variavel um indice que seja maior que o id passado nos decrementamos este id
        {
          saque->saques[i][0]--;
        }
    }
}
//objetivo: Excluir uma conta conta do sistema
//parametros:  O registro com todas as contas, e a variavel com todos os saques
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
                      if(Vericador_Saques(saque,i)){//Vericamos seja foram feitos saques na conta
                          if(i != totRegistros - 1)
                          {
                            Reajuste_Saques(saque,i);//Reajustamos os indices na variavel de saque

                              do{//A exclusão sera feita com a troca de Variaveis, a conta que o cliente escolher sera jogada para a
                                  //ultima posição do vetor, e conforme forem sendo add novas contas, as excluidas seram sobrepostas
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
//objetivo: Responsavel por fazer uma busca na variavel de saques em busca que alguma transição feita
//parametros:  A variavel que armazena todos os saques e o id pelo qual ele deve procurar
//retorno: Sem retorno
int Vericador_Saques(SAQUES* saque,int id)
{
  int i;

  for(i=0;i<totSaques;i++){
    if(saque->saques[i][0]==id){//Caso exista um id na variavel compativel com o passado pelo sistema retornamos ZERO
      return 0;
    }
  }
  return 1;
}
//objetivo: Faz as vericações e alteções nas variaveis necessarias para os saques
//parametros:  O registro de contas cadastradas, a variavel com os saque e a variavel com as cedulas
//retorno: Sem retorno
void Saque(CONTA* contas,SAQUES* saque,CEDULAS* cedulas )
{
  int i=0,sair=1, elementos,j;//Variaveis de controle
  char str[TAM_CONTA],//Recebera a conta digitada tanto para acessar o menu quanto para altera-lo
        vSaque[7];//Receberá o valor de saque pelo usuario
  int valor;//Auxiliara nas especificações do sistema
    if(totRegistros!=0)//Caso existam registros
    {
        printf("\t\n\n               MENU DE SAQUE\n");
        printf("Informe a conta que sera efetuado o saque (999.999-X)\n");//Para alterar algum dado o cliente deve informar sua conta
        printf("--> ");
        __fpurge(stdin);
        scanf ( "%9[^\n]", str);
        do{
              if(!strcmp(str,contas[i].registroConta)){//Verificamos se a conta existe no sistema
                  printf("\nInforme o valor do saque\n--> ");
                  if(VALOR_TOTAL_CAIXA!=0){//Caso tenhamos dinheiro caixa entramos
                        do{
                            iniciaVetores(vSaque);

                            __fpurge(stdin);
                            scanf ( "%6[^\n]", vSaque);//Leremos o valor de saque como String

                            elementos = Cont_Elementos(vSaque);//Contamos os elementos do valor de saque
                            valor = Valor_Saque(vSaque,elementos);//Transformamos os valores inseridos pelo usuario em formato de string para inteiro

                            for(j=0;j<strlen(vSaque);j++){
                              if(!isdigit(vSaque[j])){//Verificamos se foram inseridos apenas digitos pelo usuario
                                printf("O valor inserido é invado");
                                valor = -1;//Caso não exista apenas digitos atribuimos menos 1 a variavel 'valor' o que ocorrera em falso no while abaixo
                              }
                            }
                            if(valor < 0){
                               printf("\n\nValor inserido invalido\n-->");
                             }else  if( valor > VALOR_TOTAL_CAIXA){
                               printf("\n\nValor alem do existente em caixa! Insira outro\n-->");
                             }
                        }while(valor<0||valor>VALOR_TOTAL_CAIXA);//So saimos quando existir um valor compativel com o especificado

                        if(valor!=0){//Caso tudo tenha ocorrido bem acima e o valor seja diferente de zero fazemos o saque
                            Manipulador_cedulas(valor,cedulas);//Mostramos as notas que seram entregues
                            printf("\nSaque executado com sucesso! Valor do saque:\nR$ %d,00 ",valor);//Mostramos o valor solicitado
                              Extenso(vSaque,1);//Mostramos o valor por extenso
                              saque->saques[totSaques][0] = i;//Inserimos o Id que foi Responsavel pelo saque
                              saque->saques[totSaques][1] = valor;//e o valor sacado pelo Id
                              VALOR_TOTAL_CAIXA-=valor;//Decrementamos o valor sacado do Valor total presente no caixa
                              totSaques++;//E por fim incrementamos a variavel global que tem a quantidades de saques registrados
                            printf("\n=============================================================\n");
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
//objetivo: Quando chamado a finção ira mostrar  as notas entregues ao usuario e decrementar a quantia da variavel de cedulas
//parametros:  O valor do saque e a variavel de cedulas
//retorno: Sem retorno
void Manipulador_cedulas(int valor,CEDULAS* cedulas)
{
  int min,max,aux,j=0,qtd ;
  int espelho[9] = {200,100,50,40,20,10,5,2,1};//Vetor que reflete o valor que cada uma das notas do sistema
  printf("\n\n=============================================================\n");
  printf("\n        SAIDA CEDULAS\n");
      min = 100000,max = 1000000;//Variaveis que são responsaveis em ver o intervalo que o valor sacado esta
      do{
        aux = valor;
          if(valor>=min && valor<max)//Verificamos o intervalo do valor
          {
              do{
                valor-=min;//Decrementamos do valor o min
              }while(valor>=min);
                  do{
                    qtd = 0;
                    //Caso o valor de 'Aux' menos o valor da nota forem maiores que zero e existerem notas desse valor disponiveis no sistema entramos na condição
                      if(aux-espelho[j]>=0 && cedulas->C[j]!=0){
                        do{
                          cedulas->C[j]--;//Decrementamos uma unidade da cedula que sera entregue
                          qtd++;//incrementamos a variavel de quantidade
                          aux -= espelho[j];// Da variavel 'aux' decrementamos seu valor, com o valor da nota que foi entregue
                        }while(cedulas->C[j] > 0 && aux>=espelho[j]);//E repetimos o processo ate que o numero de cedulas seja igual a zero ou ate que 'aux' seja menor que zero
                        printf("%d nota(s) de %d\n",qtd,espelho[j]);//Imprimimos ao fim, a quantide de notas entre e seus respectivos valores
                      }
                      j++;
                  }while(j<9);//A verificação é feita para todas as notas
          }
        min /= 10;//Dividimos as variaveis 'min' e 'max', assim é verificado qualquer valor entre 0 e 1 milhão
        max /= 10;
        if(j!=0){valor=0;}//Quando 'valor' é zerado saimos do laço
      }while(valor!=0);
  printf("\n=============================================================\n");
}
//objetivo: Função que busca na variavel de saque um Id igual a passado como parametro para ele
//parametros:  O id que sera procurado, a variavel com os saques, e uma variavel contadora
//retorno: retorna Zero caso ele ache um id igual ao  outro e um caso não
int Busca(int key,int *Ids,int cont)
{
  int i=0;
    do{
        if(key==Ids[i]){//Busca na variavel de saque um Id igual ao passado
          return 0;
        }
        i++;
    }while(i<cont);
    return 1;
}
//objetivo: Gera o relatorio de todos saques feitos separados e individualmente separados por casa conta
//parametros: O registro com todas as contas e a variavel com todos os saques
//retorno: sem retorno
void Relatorio_Valor_Total_Sacado(CONTA* contas,SAQUES* saque)
{
    char valor[7];//Recebe o valor de saque quando for chamado a função  'Extenso'
    int i,j=1,
        id,soma,geralSoma=0,contadorIds=1,trocaExtrato;
    int Ids[TAM_RESGISTRO];//Este vetor receberá todos os ids que tiveram saques feitos, porem não haverá nenhum repetido

    Ids[0] = saque->saques[0][0];//Colocamos o primeiro id registrado como um chute inicial

    for(i=0;i<totSaques;i++){//Fazemos uma busca no sistema por Ids, passando Id por Id da variavel de saques, para a função 'Busca'
        if(Busca(saque->saques[i][0],Ids,contadorIds))
        {
            Ids[j] = saque->saques[i][0]; //Caso não exista nenhum igual atribumos o valor para o vetor 'Ids' numa posição j
            contadorIds++;//Incrementamos esse variavel para que o sistema saiba que o vetor 'Ids' creceu e ele tem que verificar na proxima chamada de 0 ate  'contadorIds'
            j++;//Incrementamos 'j'
        }
    }
    printf("\n\n---------------------------------------------------------------------------------------\n");
    printf("Relatorio 'Valores sacados'");
    printf("\n---------------------------------------------------------------------------------------\n");
    i=0;
    do{
      id = Ids[i];//Vamor imprimir os saques por id
      soma = 0;
      j=0;
      trocaExtrato = 0;//Esta variavel ira auxiliar no tipo de printf que seja imprimido no laço abaixo

          printf("Conta corrente: %s ___ CPF: %s  ",contas[id].registroConta,contas[id].registroCpf);//O algoritmo busca no sistema a conta registrada com o respectivo id passado
              do{
                  if(trocaExtrato){//Se 'trocaExtrato' for diferente de zero sera imprimido o valor do saque em um printf com mais espaços
                      if(id==saque->saques[j][0]){//Varremos o vetor de saque em busca dos Ids iguais ao registrado
                        printf("                                                      R$ %d,00\n",saque->saques[j][1]);
                        soma += saque->saques[j][1];//Somamos os valores no imprimidos a esta variavel de soma para apresentar o valor total sacado por um cliente mais abaixo
                      }
                    }else{//Caso seja o primeiro valor mostrado pelo sistema tera um printf com menos espaços
                        if(id==saque->saques[j][0]){
                          printf("   R$ %d,00\n",saque->saques[j][1]);
                          soma += saque->saques[j][1];
                          trocaExtrato = 1;//Agora caso se tenha mais saques registrados eles seram imprimos em um printf com mais espaços
                        }
                    }
                j++;
              }while(j<totSaques);//Depois de imprimimos todos os saques de forma individual, mostramos a soma total daquele dado usuario
              printf("                                                                Total: R$ %d,00\n\n",soma);
        i++;
        geralSoma += soma;//Essa variavel recebe a soma de total de todas as contas que ja fizeram saques
    }while(i<contadorIds);
    printf("---------------------------------------------------------------------------------------\n");
    printf("Valor total geral: R$ %d,00  ",geralSoma);
    iniciaVetores(valor);//Iniciamos o a string  'valor'
    sprintf(valor, "%i", geralSoma);//Passamos o valor inteiro do 'geralSoma' para um string
    Extenso(valor,1);//Imprimimos a soma de todas as contas por Extenso
    printf("\n---------------------------------------------------------------------------------------\n");
}
//objetivo: Mostra o valor presente no caixa em decimal e por Extenso
//parametros: Nenhum
//retorno: Sem retorno
void Relatorio_Valor_Total_Caixa()
{
  char valor[7];//Vetor que recebe o valor total do caixa em forma de string

  printf("\n\n---------------------------------------------------------------------------------------\n");
  printf("Relatorio 'Valores do saldo existente'");
  printf("\n---------------------------------------------------------------------------------------\n");
  printf("Total em caixa: R$ %d,00  ",VALOR_TOTAL_CAIXA);
  iniciaVetores(valor);
  sprintf(valor, "%i", VALOR_TOTAL_CAIXA);
  Extenso(valor,1);

  printf("\n---------------------------------------------------------------------------------------\n\n");
}
//objetivo: Relatorio dos valor de notas presentes no sistema
//parametros:  A variavel com todas as cedulas
//retorno: Sem retorno
void Relatorio_Valor_Total_Cedulas(CEDULAS* cedulas)
{
  int espelho[9] = {200,100,50,40,20,10,5,2,1}, i,value;
  char valor[7];
    iniciaVetores(valor);
    printf("\n\n---------------------------------------------------------------------------------------\n");
    printf("Relatorio 'Quantidade de cedulas existentes'");
    printf("\n---------------------------------------------------------------------------------------\n");
    printf("                     QUANTIDADE DE CADA CEDULA\n\n");
    for(i=0;i<TIPOS_CEDULAS;i++){
        printf("Cedula de %4d ---->  %4d        ",espelho[i],cedulas->C[i]);//Imprimimos o valor da nota e sua Quantidade
        value = cedulas->C[i];
        sprintf(valor, "%i", value);//Passamos o valor para string e o apresentamos em seguida
        Extenso(valor,0);
        printf("\n");
    }

  printf("\n---------------------------------------------------------------------------------------\n\n");
}

//objetivo: Conta quantos elementos tem uma string
//parametros:  Uma string
//retorno: Retona a quantidade de elementos
int Cont_Elementos(char* valor)
{
    int elementos=0,i;
    for(i=0;i<strlen(valor);i++)
    {
      elementos++;
    }
    return (elementos);
}
//objetivo: Passa o valor de que uma String para inteiro
//parametros:  Uma string
//retorno: Retona o valor em forma de inteiro
int Valor_Saque(char* valor, int elementos)
{
  int soma=0,i,multiplo;

  switch (elementos) {//Ve qual o tamanho de algarismos do numero passado
    case 6:
          multiplo = 100000;
          break;
    case 5:
          multiplo = 10000;
          break;
    case 4:
          multiplo = 1000;
          break;
    case 3:
          multiplo = 100;
          break;
    case 2:
          multiplo = 10;
          break;
    case 1:
          multiplo = 1;
          break;
  }

    for(i=0;i<elementos;i++)
    {//Usa algarismo a algarismo fazendo somas e divisões sucetivas para obter o valor
      soma += (valor[i]-48)*multiplo;
      multiplo /= 10;
    }
    return soma;
}
//objetivo: Quando chamado imprime o valor de um numero em extenso
//parametros:  Uma variavel com o valor e um valor (0 ou  1) que indentifica se esta sendo solicitado o extenso de dinheiro ou de cedulas
//retorno: sem retorno
void Extenso(char* valor,int DinheiroOuCedula)
{
  int valorSaque,dig,elementos,i=0;
    /*Valor que podem ser impressos*/
  char UM_NOVE[9][9] = {{"UM"},{"DOIS"},{"TRES"},{"QUATRO"},{"CINCO"},{"SEIS"},{"SETE"},{"OITO"},{"NOVE"}};
  char C_UM_NOVE[9][9] = {{"UMA"},{"DUAS"},{"TRES"},{"QUATRO"},{"CINCO"},{"SEIS"},{"SETE"},{"OITO"},{"NOVE"}};

  char ONZE_DEZENOVE[9][15] = {{"ONZE"},{"DOZE"},{"TREZE"},{"QUATORZE"},{"QUINZE"},{"DEZESSEIS"},{"DEZESSETE"},{"DEZOITO"},{"DEZENOVE"}};

  char DEZ_NOVENTA[9][15] = {{"DEZ"},{"VINTE"},{"TRINTA"},{"QUARENTA"},{"CINQUENTA"},{"SESSENTA"},{"SETENTA"},{"OITENTA"},{"NOVENTA"}};

  char CEM_NOVECENTOS[9][15] = {{"CENTO"},{"DUZENTOS"},{"TREZENTOS"},{"QUATROCENTOS"},{"QUINHETOS"},{"SEISCENTOS"},{"SETECENTOS"},{"OITOCENTOS"},{"NOVECENTOS"}};
  char C_CEM_NOVECENTOS[9][15] = {{"CENTO"},{"DUZENTAS"},{"TREZENTAS"},{"QUATROCENTAS"},{"QUINHETAS"},{"SEISCENTAS"},{"SETECENTAS"},{"OITOCENTAS"},{"NOVECENTAS"}};

  char CONECTIVOS[7][11] = {{"CENTO"},{" E "},{" MIL "},{"REAIS"},{"CEDULAS"},{"REAL"},{"CEDULA"}};

  printf("( ");
  elementos = Cont_Elementos(valor);//Contamos quantos elementos tem o valor
  valorSaque = Valor_Saque(valor,elementos);//Depois obtemos  o inteiro deste valor
/*
  A logica toda toda por tras do codigo abaixo é simples:

    Supondo que o valor passado pela string seja 45812, no vetor ele esta da seguinte forma: |'4'|'5'|'8'|'1'|'2'|'\0'|'\0'| (Ja que todo vetor passado para cá tem 7 posições)
  Como acima foram pegos a quantidade de elementos e o valor de saque por inteiro, ele sabera qua na primeira interação para este valor ele devera entrar no case 5 do switch abaixo
  então ele verifica se o valor inteiro dividido por 10 mil esta entre 1 e 2, se estiver significa que só pode ser um valor entre 11 e 19 mil, nesse caso o teste dará falso,
  então seu proximo passo é verificar se o numero tem um valor que seja inteiro como: 10 mil reias, 20 mil reais etc. neste tambem dará falso então é verficado se o valor é do tipo
  45 mil e alguma coisa ou 40 Mil e alguma coisa, em nosso caso dara a primeira opção, então ele pega o valor do numero na casa, neste caso seria valor[0], multiplica ele por 10 mil
  e em seguida decrementa ele do valor inicial e no fim ele decrementa o numero de elementos e troca as proximas posições que serão verificadas no vetor.

    A curto modo é basicamente isso, que ele faz até sair do laço, existe alem desse testes sitados, teste para saber se o sistema que gramatica para as cedulas ou para o  dinheiro
  ja que existe umas pequenas variações e isto é checado em varias partes do algoritmo com operadores ternarios
*/
  if(valorSaque){//Se o valor for diferente de ZERO entramos no laço
      do{
          switch (elementos) {
            case 6://Caso o valor tenha seis elementos significa que ele é maior ou igual a 100 mil
                      if(valorSaque/100000.00 == 1.00)
                      {
                        printf("CEM MIL %s", DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);//Teste que verifica foi solicitado dinheiro ou cedula
                        elementos=0;
                      }
                      else if( valor[1] != '0' || valor[2] != '0')
                            {
                              printf("CENTO E ");
                            }
                      else{
                              printf("CEM MIL E ");
                      }
                      valorSaque -= 100000;
                  break;
            case 5://Caso o valor tenha cinco elementos significa que ele é maior ou igual a 10 mil
                    if(valorSaque/10000>0){
                        //Verifica valores entre 11 e 19  MIL
                        if(valorSaque/10000.00>1 && valorSaque/10000.00<2)
                        {
                          if(valorSaque/1000.00 == (float)(valor[i+1]-48)+10 )
                          {
                            printf("%s MIL %s",ONZE_DEZENOVE[(valor[i+1]-48)-1], DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                            elementos=0;
                            valorSaque -= 10000 + 1000*(valor[i+1]-48);
                          }else{
                            printf("%s MIL E ",ONZE_DEZENOVE[(valor[i+1]-48)-1]);
                            valorSaque -= (10000 + 1000*(valor[i+1]-48));
                          }
                        }
                        //Verifica valores entre 10 e 90  MIL
                        else  if(valorSaque/10000.00==(float)valor[i]-48)
                        {
                          printf("%s MIL %s",DEZ_NOVENTA[(valor[i]-48)-1], DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                          valorSaque -= 10000 * (valor[i]-48);
                        }
                        else if( valor[i+1] == '0')
                              {
                                printf("%s MIL E ",DEZ_NOVENTA[(valor[i]-48)-1]);
                                valorSaque -= 10000 * (valor[i]-48);
                              }
                        else if( valor[i] != '0'){
                                printf("%s E ",DEZ_NOVENTA[(valor[i]-48)-1]);
                                valorSaque -= 10000 * (valor[i]-48);
                        }
                    }
                  break;
            case 4:
                    if(valorSaque/1000>0){
                        if(valorSaque/1000.00==(float)valor[i]-48)
                        {
                          printf("%s MIL %s",DinheiroOuCedula ? UM_NOVE[(valor[i]-48)-1]:C_UM_NOVE[(valor[i]-48)-1],
                                             DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                          valorSaque -= 1000 * (valor[i]-48);
                        }
                        else if(valorSaque/1000>0){
                          printf("%s MIL E ",DinheiroOuCedula ? UM_NOVE[(valor[i]-48)-1]:C_UM_NOVE[(valor[i]-48)-1]);
                          valorSaque -= 1000 * (valor[i]-48);
                        }
                    }
                  break;
            case 3:
                    if(valorSaque/100>0){
                        if(valorSaque/100.00==1.00)
                        {
                          printf("CEM %s",DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                          valorSaque -= 100 * (valor[i]-48);
                        }
                        else if(valorSaque/100.00== (float)(valor[i]-48))
                        {
                          printf("%s %s",DinheiroOuCedula ? CEM_NOVECENTOS[(valor[i]-48)-1] : C_CEM_NOVECENTOS[(valor[i]-48)-1],
                                         DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                          valorSaque -= 100 * (valor[i]-48);
                        }
                        else if(valorSaque/100>0){
                          printf("%s E ",DinheiroOuCedula ? CEM_NOVECENTOS[(valor[i]-48)-1] : C_CEM_NOVECENTOS[(valor[i]-48)-1]);
                          valorSaque -= 100 * (valor[i]-48);
                        }
                    }
                  break;
            case 2:
                    if(valorSaque/10>0){
                        if(valorSaque/10.00>1 && valorSaque/10.00<2)
                        {
                            printf("%s %s",ONZE_DEZENOVE[(valor[i+1]-48)-1], DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                            elementos=0;
                        }
                        else  if(valorSaque/10.00 == (float)(valor[i]-48))
                        {
                          printf("%s %s",DEZ_NOVENTA[(valor[i]-48)-1],DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                        }
                        else if(valorSaque/10>0)
                        {
                          printf("%s E ",DEZ_NOVENTA[(valor[i]-48)-1]);
                          valorSaque -= 100* (valor[i]-48);
                        }
                    }
                  break;
            case 1:
                        if(!i && valor[i]-48 == 1){
                            printf("%s %s",DinheiroOuCedula?UM_NOVE[(valor[i]-48)-1]:C_UM_NOVE[(valor[i]-48)-1],
                                            DinheiroOuCedula ? CONECTIVOS[5] : CONECTIVOS[6]);
                        }else{
                          printf("%s %s",DinheiroOuCedula?UM_NOVE[(valor[i]-48)-1]:C_UM_NOVE[(valor[i]-48)-1],
                                          DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                        }
                  break;
          }
          elementos--;
          i++;
      }while(elementos>0);
    }else{//Caso o valor passo sera zero
      printf(" ZERADO ");
    }
  printf(" )");
}
/*---------------------------------------------------------------------------------THE END----------------------------------------------------------------------------------------------*/
