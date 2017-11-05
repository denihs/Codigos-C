#include "venda.h"

//objetivo: Abrir o arquivo de clientes
//parametros: O caminho e o modo de abertura do arquivo
//retorno: O endereço do arquivo na memoria
FILE* open_VENDA(char* nome_arq, char* c)
{
  FILE* pfile;
  if ( ( pfile = fopen(nome_arq, c) ) == NULL ){
    printf("\n\n\t\033[31mFALHA AO ABRIR O ARQUIVO %s\033[m\n\n", nome_arq);
    exit(1);
  }
  return(pfile);
}

//objetivo: Fecha o arquivo de venda
//parametros: O endereço do arquivo na memoria e caminho do arquivo
//retorno: sem retorno
void close_VENDA( FILE* f, char* nome_arq )
{
    if( fclose(f) == EOF ){
      printf("\n\n\t\033[31mFALHA AO FECHAR O ARQUIVO %s\033[m\n\n", nome_arq);
      exit(1);
    }
}

//objetivo: Inserir uma venda no sistema
//parametros: Todos os carros cliente,  e os total de cada um deles ja cadastrados e um variavel com o montante do valor bruto arrecadado em vendas ate o momento
//retorno: retorna 1 se houve sua sucesso e ZERO caso contrario
int insereVenda( _CARRO* carro, _CLIENTE* cliente, int TOT_CLIENTE, int TOT_CARROS, float* valor)
{
  int i, verifica = 0, posI,posII, carroDisponivel;
  char cpf[14];

  printf("\n\nInsira o CPF do cliente (\033[31mFORMATO:\033[m 999.999.999-99): ");
  __fpurge(stdin);
  fgets(cpf,15,stdin);
  //Busca o CPF informado nos registro
  for(i = 0; i < TOT_CLIENTE; i++){
    if( !strcmp( cpf, cliente[i].cpf ) )
    {
        verifica = 1;
        posI = i;
    }
  }
  if( verifica ){//Caso exista o cliente informado
      carroDisponivel = exibi(carro, 0, TOT_CARROS, 0 );
      verifica = 0;
      char placa[9], sair = 'S';
      char venda[] = {"file/venda.dat"};
      FILE* fVenda;
    if(carroDisponivel){
      do{
          printf("\n\nInsira a placa do carro (\033[31mFORMATO:\033[m ABC-1234): ");
          __fpurge(stdin);
          fgets(placa,9,stdin);
            //Vai ser lido e procurado uma placa nos registrode carros
            for(i = 0; i < TOT_CARROS; i++){
              if( !strcmp( placa, carro[i].placa ) )
              {
                  verifica = 1;
                  posII = i;
              }
            }
            //Se Existir o Cliente e o Carro a venda sera concluida
            if( verifica ){
                  _VENDA vendas;
                  strcpy(vendas.cpf_venda, cpf);
                  strcpy(vendas.placa_venda, placa);
                  //Mudamos os status do cliente e do carro
                  cliente[posI].status = 0;
                  carro[posII].status = 0;
                  *valor += carro[posII].preco_compra;//Somando o valor do carro vendido ao total geral
                  //Registamos a venda, salvamos o cpf e placa informada
                  fVenda = open_VENDA(venda, "ab");
                      fwrite(&vendas, sizeof(vendas), 1, fVenda);
                  close_VENDA(fVenda, venda);

                  printf("\n\n\tVENDA CONCLUIDA COM SUCESSO!\n\n");
                sair = 'n';
                return 1;
            }
            else{//Tratamente caso o usuario tenho inserido algum dado invalido
              printf("\n\n\t\033[31mNao existe registro da placa informada.\033[m\n\n");
              printf("Tentar novamente? S/s ou N/n: ");
                do{
                  __fpurge(stdin);
                  scanf("%c",&sair);
                  if(sair != 'S' && sair != 's' && sair != 'N' && sair != 'n')
                      printf("Informe S ou s para continuar  ou\nN ou n para sair\n->> ");
                }while(sair != 'S' && sair != 's' && sair != 'N' && sair != 'n');
            }
      }while(sair == 'S' || sair == 's');
        printf("\n\n\t\033[31mOperacao cancelada!\033[m\n\n");
      return 0;
    }
  }
  else{
    printf("\n\n\t\033[31mNao registro de cliente para o cpf informado.\033[m\n\n");
  }
}

//objetivo: Exclui uma venda do sistema
//parametros: Todos as vendas, carros, clientes, o total de cada um no sistema e um variavel com o montante do valor bruto arrecadado em vendas ate o momento
//retorno: Retorna 1 se tudo ocorreu bem
int excluir_VENDA(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS, float* valor)
{
  int i, pos , tot_compras = 0, j;
  int verifica = 0;
  char placa[9];
  _VENDA vendas;


      printf("\n\nInsira a placa do carro que sera excluida a venda (\033[31mFORMATO:\033[m ABC-1234): ");
      __fpurge(stdin);
      fgets(placa,9,stdin);
        //Busca a placa informada nos carros cadastrados
        for(i = 0; i < TOT_VENDAS; i++){
          if( !strcmp( placa, venda[i].placa_venda ) )
          {
            verifica = 1;
            pos = i;
            break;
          }
        }
        if(verifica){//Se existe o carro solicitado ou esta disponivel

          for(i = 0; i < TOT_CLIENTE; i++){
              //É procurado o cliente que fez a compra
              if( !strcmp(venda[pos].cpf_venda, cliente[i].cpf) ){
                  for(j = 0; j < TOT_VENDAS; j++){
                      //Apos achar o cliente ele verifica quantas compras existem no nome desse cliente
                      if( !strcmp(venda[j].cpf_venda, cliente[i].cpf) ){
                          tot_compras++;
                      }
                  }
                  //Se existirem mais de uma não habilitamos o cliente para ser excluido do sistema
                  if(tot_compras < 2){
                    cliente[i].status = 1;
                    break;
                  }
              }
          }
          //habilitamos o carro novamente para ser excluido ou vendido
          for(i = 0; i < TOT_CARROS; i++){
              if( !strcmp(venda[pos].placa_venda, carro[i].placa) ){
                carro[i].status = 1;
                *valor -= carro[i].preco_compra;
                break;
              }
          }
          //Fazemos a exclusão
          vendas = venda[TOT_VENDAS - 1];
          venda[TOT_VENDAS - 1] = venda[pos];
          venda[pos] = vendas;
          return 1;
      }else{
        printf("\n\n\t\033[31mNenhum carro vendido que tenha essa placa.\033[m\n\n");
        return 0;
      }
}

//objetivo: Lista os carro vendidos a partir de um fabricante
//parametros: Todos as vendas, carros, clientes, o total de cada um no sistema
//retorno: Sem retorno
void listaFabricante(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente, int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;
  int i, qtd[8];

    for(i = 0; i < 8; i++){
      qtd[i] = 0;
    }
    contagemFabricante(qtd, carro,TOT_CARROS);
  do{
    printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-LISTAGEM POR FABICANTE-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Aponte o fabricante: \n");
    printf("1 - Volkswagen [%d]\n", qtd[0]);
    printf("2 - Chevrolet  [%d]\n", qtd[1]);
    printf("3 - Ford       [%d]\n", qtd[2]);
    printf("4 - Fiat       [%d]\n", qtd[3]);
    printf("5 - Nissan     [%d]\n", qtd[4]);
    printf("6 - Renault    [%d]\n", qtd[5]);
    printf("7 - Peugeot    [%d]\n", qtd[6]);
    printf("8 - Puma       [%d]\n", qtd[7]);
    printf("0 - SAIR\n--> ");
    __fpurge(stdin);
    scanf("%c", &op);
    switch (op) {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
              listagenFabricante(venda, carro, cliente, TOT_VENDAS,TOT_CLIENTE, TOT_CARROS, (op - 48) - 1);
              break;
      case '0':
              break;
      default:
              printf("\n\n\t\033[31mOpcao invalida\033[m\n\n");
    }
  }while(op != '0');
}

//objetivo: Imprime os carros disponiveis para o fabricante escolhido
//parametros: Todos as vendas, carros, clientes, o total de cada um no sistema e a escolha do usuario
//retorno: Sem retorno
void listagenFabricante(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS,int escolha)
{
  char fabricante[][TAM] = {"Volkswagen","Chevrolet","Ford","Fiat","Nissan","Renault","Peugeot","Puma"};
  int i, verifica = 0, j = 1, x, y;
  printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=- %s =-=-=-=-=-=-=-=-=-=-=-\n", fabricante[escolha]);
  for(i = 0; i < TOT_CARROS; i++){
    if( !carro[i].status ){//Se o carro foi vendido e o fabricante dele coincide com o escolhido pelo usuario ele é mostrado
      if( !strcmp(carro[i].fabricante, fabricante[escolha] )  ){
          printf("=-=-=-=-=-=-=-=-=-=-=-=- %d =-=-=-=-=-=-=-=-=-=-=-\n", j);
          printf("* MODELO:          %s\n", carro[i].modelo);
          printf("* PLACA:           %s\n", carro[i].placa);
          printf("* ANO FABRICACAO:  %d\n", carro[i].ano_fabricacao);
          for(x = 0; x < TOT_VENDAS; x++){
              if( !strcmp(carro[i].placa, venda[x].placa_venda )){
                for(y = 0; y < TOT_VENDAS; y++){
                  if( !strcmp(venda[x].cpf_venda, cliente[y].cpf ) ){
                    printf("* CLIENTE:         %s\n", cliente[y].nome);
                    break;
                  }
                }
              }
          }
          j++;
          verifica = 1;
      }
    }
  }
  if(!verifica){
    printf("\n\n\t\033[31mNenhum modelo vendidos da fabricante %s.\033[m\n\n", fabricante[escolha]);
  }
}

//objetivo: Lista os carro vendidos a partir de um Modelo
//parametros: Todos as vendas, carros, clientes, o total de cada um no sistema
//retorno: Sem retorno
void listaModelo(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{

    char op;
    int i, qtd[8];

      for(i = 0; i < 8; i++){
        qtd[i] = 0;
      }
      contagemFabricante(qtd, carro,TOT_CARROS);

  do{
    printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-LISTAGEM POR FABICANTE-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Aponte o fabricante: \n");
    printf("1 - Volkswagen [%d]\n", qtd[0]);
    printf("2 - Chevrolet  [%d]\n", qtd[1]);
    printf("3 - Ford       [%d]\n", qtd[2]);
    printf("4 - Fiat       [%d]\n", qtd[3]);
    printf("5 - Nissan     [%d]\n", qtd[4]);
    printf("6 - Renault    [%d]\n", qtd[5]);
    printf("7 - Peugeot    [%d]\n", qtd[6]);
    printf("8 - Puma       [%d]\n", qtd[7]);
    printf("0 - SAIR\n--> ");
    __fpurge(stdin);
    scanf("%c", &op);
    switch (op) {
      case '1':
              printf("\n\n=-==-==-==-==-==-==Modelos Volkswagen-==-==-==-==-==-==-==-=");
              modeloVolkswagen(venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS);
              break;
      case '2':
              printf("\n\n=-==-==-==-==-==-==Modelos Chevrolet-==-==-==-==-==-==-==-=");
              modeloChevrolet(venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS);
              break;
      case '3':
              printf("\n\n=-==-==-==-==-==-==Modelos Ford-==-==-==-==-==-==-==-=");
              modeloFord(venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS);
              break;
      case '4':
              printf("\n\n=-==-==-==-==-==-==Modelos FIAT-==-==-==-==-==-==-==-=");
              modeloFiat(venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS);
              break;
      case '5':
              printf("\n\n=-==-==-==-==-==-==Modelos Nissan-==-==-==-==-==-==-==-=");
              modeloNissan(venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS);
              break;
      case '6':
              printf("\n\n=-==-==-==-==-==-==Modelos Renault-==-==-==-==-==-==-==-=");
              modeloRenault(venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS);
              break;
      case '7':
              printf("\n\n=-==-==-==-==-==-==Modelos Peugeot-==-==-==-==-==-==-==-=");
              modeloPeugeot(venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS);
              break;
      case '8':
              printf("\n\n=-==-==-==-==-==-==Modelos Puma-==-==-==-==-==-==-==-=");
              modeloPuma(venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS);
              break;
      case '0':
              break;
      default:
              printf("\n\n\t\033[31mOpcao invalida\033[m\n\n");
    }
  }while(op != '0');
}
/*
  Apos o usuario decidir qual o fabricante da marca escolhida
  Sera apresentado a ele as marcas desse fabricante.

  Abaixo temos apenas menus de cada uma das fabricantes acima
  e apartir deles serão mostradas as venda feitas para um modelo
  chamando a função resposvel por apresentalas

  então não ha necessidade de comenta-las
*/

void modeloPuma(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;
  int i, qtd[10] ;
  for(i = 0; i < 10; i++){
    qtd[i] = 0;
  }
  contagemModelo(qtd, carro, TOT_CARROS, 7);

  do{
    printf("\n\nS - SAIR\n");
    printf("0 - GT4R        [%d]\n",qtd[0]);
    printf("1 - Puma P8     [%d]\n",qtd[1]);
    printf("2 - Puma Spyder [%d]\n",qtd[2]);
    printf("3 - GTE         [%d]\n",qtd[3]);
    printf("4 - GTS         [%d]\n",qtd[4]);
    printf("5 - GTB         [%d]\n",qtd[5]);
    printf("6 - GTB S2      [%d]\n",qtd[6]);
    printf("7 - GTB S3      [%d]\n",qtd[7]);
    printf("8 - GTB S4      [%d]\n",qtd[8]);
    printf("9 - GTC         [%d]\n",qtd[9]);
    printf("--> ");
      __fpurge(stdin);
      scanf("%c", &op);
      switch (op) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
                listagenModelo( venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS, 7, op - 48);
                break;
        case 'S':
        case 's':
                break;
        default:
              printf("\n\n\t\033[31mOpcao invalida\033[m\n\n");
      }
  }while(op != 'S' && op != 's');
}

void modeloPeugeot(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;
  int i, qtd[10] ;
  for(i = 0; i < 10; i++){
    qtd[i] = 0;
  }
  contagemModelo(qtd, carro, TOT_CARROS, 6);


  do{

    printf("\n\nS - SAIR\n");
    printf("0 - Peugeot 206             [%d]\n",qtd[0]);
    printf("1 - Peugeot 206 SW          [%d]\n",qtd[1]);
    printf("2 - Peugeot 206+            [%d]\n",qtd[2]);
    printf("3 - Peugeot 207 Passion     [%d]\n",qtd[3]);
    printf("4 - Peugeot 207 SW          [%d]\n",qtd[4]);
    printf("5 - Peugeot 208             [%d]\n",qtd[5]);
    printf("6 - Peugeot 2008            [%d]\n",qtd[6]);
    printf("7 - Peugeot Hoggar          [%d]\n",qtd[7]);
    printf("8 - Peugeot 308 Hybride HDi [%d]\n",qtd[8]);
    printf("9 - Peugeot 308 SW Prologue [%d]\n",qtd[9]);
    printf("--> ");
      __fpurge(stdin);
      scanf("%c", &op);
      switch (op) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
                listagenModelo( venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS, 6, op - 48);
                break;
        case 'S':
        case 's':
                break;
        default:
              printf("\n\n\t\033[31mOpcao invalida\033[m\n\n");
      }
  }while(op != 'S' && op != 's');
}


void modeloRenault(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;
  int i, qtd[10] ;
  for(i = 0; i < 10; i++){
    qtd[i] = 0;
  }
  contagemModelo(qtd, carro, TOT_CARROS, 5);
  do{
    printf("\n\nS - SAIR\n");
    printf("0 - Captur             [%d]\n",qtd[0]);
    printf("1 -  Clio              [%d]\n",qtd[1]);
    printf("2 -  Clio Sedan        [%d]\n",qtd[2]);
    printf("3 -  Duster            [%d]\n",qtd[3]);
    printf("4 -  Duster Oroch      [%d]\n",qtd[4]);
    printf("5 -  Logan             [%d]\n",qtd[5]);
    printf("6 -  Mégane Grand Tour [%d]\n",qtd[6]);
    printf("7 -  Mégane Sedan      [%d]\n",qtd[7]);
    printf("8 -   Sandero          [%d]\n",qtd[8]);
    printf("9 -   Scéni            [%d]\n",qtd[9]);
    printf("--> ");
      __fpurge(stdin);
      scanf("%c", &op);
      switch (op) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
                listagenModelo( venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS, 5, op - 48);
                break;
        case 'S':
        case 's':
                break;
        default:
              printf("\n\n\t\033[31mOpcao invalida\033[m\n\n");
      }
  }while(op != 'S' && op != 's');
}

void modeloNissan(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;
  int i, qtd[10] ;
  for(i = 0; i < 10; i++){
    qtd[i] = 0;
  }
  contagemModelo(qtd, carro, TOT_CARROS, 4);
  do{
    printf("\n\nS - SAIR\n");
    printf("0 - Nissan Frontier      [%d]\n", qtd[0]);
    printf("1 - Nissan Presage       [%d]\n", qtd[1]);
    printf("2 - Nissan 240SX         [%d]\n", qtd[2]);
    printf("3 - Nissan 300ZX         [%d]\n", qtd[3]);
    printf("4 -  Nissan 350Z         [%d]\n", qtd[4]);
    printf("5 -  Nissan 370Z         [%d]\n", qtd[5]);
    printf("6 - Nissan Stagea        [%d]\n", qtd[6]);
    printf("7 - Nissan Serena        [%d]\n", qtd[7]);
    printf("8 -  Nissan Skyline GT-R [%d]\n", qtd[8]);
    printf("9 - Nissan Stanza        [%d]\n", qtd[9]);
    printf("--> ");
      __fpurge(stdin);
      scanf("%c", &op);
      switch (op) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
                listagenModelo( venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS, 4, op - 48);
                break;
        case 'S':
        case 's':
                break;
        default:
              printf("\n\n\t\033[31mOpcao invalida\033[m\n\n");
      }
  }while(op != 'S' && op != 's');
}
void modeloFiat(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;
  int i, qtd[10] ;
  for(i = 0; i < 10; i++){
    qtd[i] = 0;
  }
  contagemModelo(qtd, carro, TOT_CARROS, 3);
  do{
    printf("\n\nS - SAIR\n");
    printf("0 - Fiat 147 [%d]\n", qtd[0]);
    printf("1 - City     [%d]\n", qtd[1]);
    printf("2 - Brava    [%d]\n", qtd[2]);
    printf("3 - Bravo    [%d]\n", qtd[3]);
    printf("4 - Doblò    [%d]\n", qtd[4]);
    printf("5 - Fiorino  [%d]\n", qtd[5]);
    printf("6 - Prêmio   [%d]\n", qtd[6]);
    printf("7 - Punto    [%d]\n", qtd[7]);
    printf("8 - Stilo    [%d]\n", qtd[8]);
    printf("9 - Tempra   [%d]\n", qtd[9]);
    printf("--> ");
      __fpurge(stdin);
      scanf("%c", &op);
      switch (op) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
                listagenModelo( venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS, 3, op - 48);
                break;
        case 'S':
        case 's':
                break;
        default:
              printf("\n\n\t\033[31mOpcao invalida\033[m\n\n");
      }
  }while(op != 'S' && op != 's');
}

void modeloFord(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;
  int i, qtd[10] ;
  for(i = 0; i < 10; i++){
    qtd[i] = 0;
  }
  contagemModelo(qtd, carro, TOT_CARROS, 2);
  do{
    printf("\n\nS - SAIR \n");
    printf("0 - Belina             [%d]\n", qtd[0]);
    printf("1 - Corcel             [%d]\n", qtd[1]);
    printf("2 - Del Rey            [%d]\n", qtd[2]);
    printf("3 - Escort conversível [%d]\n", qtd[3]);
    printf(" 4- F-1000             [%d]\n", qtd[4]);
    printf("5 - Fiesta             [%d]\n", qtd[5]);
    printf("6 - Jeep               [%d]\n", qtd[6]);
    printf("7 - Galaxie            [%d]\n", qtd[7]);
    printf("8 - Ka                 [%d]\n", qtd[8]);
    printf("9 - Pampa              [%d]\n", qtd[9]);
    printf("--> ");
      __fpurge(stdin);
      scanf("%c", &op);
      switch (op) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
                listagenModelo( venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS, 2, op - 48);
                break;
        case 'S':
        case 's':
                break;
        default:
              printf("\n\n\t\033[31mOpcao invalida\033[m\n\n");
      }
  }while(op != 'S' && op != 's');
}

void modeloVolkswagen(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;
  int i, qtd[10] ;
  for(i = 0; i < 10; i++){
    qtd[i] = 0;
  }
  contagemModelo(qtd, carro, TOT_CARROS, 0);
  do{
    printf("\n\nS - SAIR \n");
    printf("0 - Brasilia               [%d]\n", qtd[0]);
    printf("1 - Fox                    [%d]\n", qtd[1]);
    printf("2 - Fusca                  [%d]\n", qtd[2]);
    printf("3 - Gol                    [%d]\n", qtd[3]);
    printf("4 - Golf                   [%d]\n", qtd[4]);
    printf("5 - Jetta                  [%d]\n", qtd[5]);
    printf("6 - Parati                 [%d]\n", qtd[6]);
    printf("7 - Passat                 [%d]\n", qtd[7]);
    printf("8 - Saveiro                [%d]\n", qtd[8]);
    printf("9 - Karmann Ghia Cabriolét [%d]\n", qtd[9]);
    printf("--> ");
      __fpurge(stdin);
      scanf("%c", &op);
      switch (op) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
                listagenModelo( venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS, 0, op - 48);
                break;
        case 'S':
        case 's':
                break;
        default:
              printf("\n\n\t\033[31mOpcao invalida\033[m\n\n");
      }
  }while(op != 'S' && op != 's');
}

void modeloChevrolet(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;
  int i, qtd[10] ;
  for(i = 0; i < 10; i++){
    qtd[i] = 0;
  }
  contagemModelo(qtd, carro, TOT_CARROS, 1);
  do{

    printf("\n\nS - SAIR \n");
    printf("0 - Alvorada     [%d]\n", qtd[0]);
    printf("1 - D-20         [%d]\n", qtd[1]);
    printf("2 - Monza hatch  [%d]\n", qtd[2]);
    printf("3 - S10          [%d]\n", qtd[3]);
    printf("4- Omega Suprema [%d]\n", qtd[4]);
    printf("5 - Gran Blazer  [%d]\n", qtd[5]);
    printf("6 - Cruze        [%d]\n", qtd[6]);
    printf("7 - Opala coupé  [%d]\n", qtd[7]);
    printf("8 - Prisma       [%d]\n", qtd[8]);
    printf("9 - Blazer       [%d]\n", qtd[9]);
    printf("--> ");
      __fpurge(stdin);
      scanf("%c", &op);
      switch (op) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
                listagenModelo( venda, carro, cliente, TOT_VENDAS, TOT_CLIENTE, TOT_CARROS, 1, op - 48);
                break;
        case 'S':
        case 's':
                break;
        default:
              printf("\n\n\t\033[31mOpcao invalida\033[m\n\n");
      }
  }while(op != 'S' && op != 's');
}

//objetivo: Lista os carro vendidos a partir de um modelo
//parametros: Todos as vendas, carros, clientes, o total de cada um no sistema e a escolha do cliente no sistema
//retorno: Sem retorno
void listagenModelo(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS,int fabricante,int escolha)
{
  char modelo[TAM];
  char L1[][TAM] = {"Brasilia", "Fox", "Fusca", "Gol", "Golf","Jetta","Parati","Passat","Saveiro","Karmann Ghia Cabriolét"};
  char L2[][TAM] = {"Alvorada","D-20","Monza hatch","S10","Omega Suprema","Gran Blazer","Cruze","Opala coupé","Prisma","Blazer"};
  char L3[][TAM] = {"Belina", "Corcel", "Del Rey ", "Escort conversível", "F-1000", "Fiesta", "Jeep", "Galaxie", "Ka", "Pampa"};
  char L4[][TAM] = {"Fiat 147", "City", "Brava", "Bravo", "Doblò", "Fiorino", "Prêmio", "Punto", "Stilo", "Tempra"};
  char L5[][TAM] = {"Nissan Frontier", "Nissan Presage", "Nissan 240SX", "Nissan 300ZX ", "Nissan 350Z ", "Nissan 370Z", "Nissan Stagea", "Nissan Serena ", "Nissan Skyline GT-R", "Nissan Stanza"};
  char L6[][TAM] = {"Captur", "Clio", "Clio Sedan", "Duster", "Duster Oroch", "Logan", "Mégane Grand Tour", "Mégane Sedan", "Sandero", "Scénic"};
  char L7[][TAM] = {"Peugeot 206", "Peugeot 206 SW", "Peugeot 206+", "Peugeot 207 Passion", "Peugeot 207 SW ", "Peugeot 208", "Peugeot 2008", "Peugeot Hoggar","Peugeot 308 Hybride HDi","Peugeot 308 SW Prologue"};
  char L8[][TAM] =  {"GT4R", "Puma P8", "Puma Spyder", "GTE", "GTS", "GTB", "GTB S2", "GTB S3", "GTB S4", "GTC"};
  switch (fabricante) {
    case 0:
          strcpy(modelo, L1[escolha]);
        break;
    case 1:
          strcpy(modelo, L2[escolha]);
        break;
    case 2:
          strcpy(modelo, L3[escolha]);
        break;
    case 3:
          strcpy(modelo, L4[escolha]);
        break;
    case 4:
          strcpy(modelo, L5[escolha]);
        break;
    case 5:
          strcpy(modelo, L6[escolha]);
        break;
    case 6:
          strcpy(modelo, L7[escolha]);
        break;
    case 7:
          strcpy(modelo, L8[escolha]);
        break;
  }

  int i, verifica = 0, j = 1, x, y;

  printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=- %s =-=-=-=-=-=-=-=-=-=-=-\n", modelo);
  for(i = 0; i < TOT_CARROS; i++){
    if( !carro[i].status ){
      if( !strcmp(carro[i].modelo, modelo ) ) {
          printf("=-=-=-=-=-=-=-=-=-=-=-=- %d =-=-=-=-=-=-=-=-=-=-=-\n", j);
          printf("* ANO FABRICACAO:  %d\n", carro[i].ano_fabricacao);
          printf("* PLACA:           %s\n", carro[i].placa);

          for(x = 0; x < TOT_VENDAS; x++){
              if( !strcmp(carro[i].placa, venda[x].placa_venda )){
                for(y = 0; y < TOT_CLIENTE; y++){
                  if( !strcmp(venda[x].cpf_venda, cliente[y].cpf ) ){
                    printf("* CLIENTE:         %s\n", cliente[y].nome);
                    break;
                  }
                }
              }
          }
          j++;
          verifica = 1;
      }
    }
}
  if(!verifica){
    printf("\n\n\t\033[31mNenhum modelo vendidos do modelo %s.\033[m\n\n", modelo);
  }
}

//objetivo: Contar quais fabricantes teve um carro vendido
//parametros: O vetor que recebera a contagem, os carros registrados, o total de carros registrados
//retorno: Sem retorno
void contagemFabricante(int * qtd, _CARRO* carro, int TOT_CARROS)
{
  int i, j;
  char montadora[][TAM] = {"Volkswagen","Chevrolet","Ford","Fiat","Nissan","Renault","Peugeot","Puma"};
    for(i = 0; i < TOT_CARROS; i++){
        if( !carro[i].status ){
          for(j = 0; j < 8; j++){
            if ( !strcmp(carro[i].fabricante, montadora[j]) ){ qtd[j]++; }
          }
        }
    }
}

//objetivo: Contar quais modelos teve um carro vendido
//parametros: O vetor que recebera a contagem, os carros registrados, o total de carros registrados e o fabricante
//retorno: Sem retorno
void contagemModelo(int * qtd, _CARRO* carro, int TOT_CARROS, int fabricante)
{
  int i, j;
  char L1[][TAM] = {"Brasilia", "Fox", "Fusca", "Gol", "Golf","Jetta","Parati","Passat","Saveiro","Karmann Ghia Cabriolét"};
  char L2[][TAM] = {"Alvorada","D-20","Monza hatch","S10","Omega Suprema","Gran Blazer","Cruze","Opala coupé","Prisma","Blazer"};
  char L3[][TAM] = {"Belina", "Corcel", "Del Rey ", "Escort conversível", "F-1000", "Fiesta", "Jeep", "Galaxie", "Ka", "Pampa"};
  char L4[][TAM] = {"Fiat 147", "City", "Brava", "Bravo", "Doblò", "Fiorino", "Prêmio", "Punto", "Stilo", "Tempra"};
  char L5[][TAM] = {"Nissan Frontier", "Nissan Presage", "Nissan 240SX", "Nissan 300ZX ", "Nissan 350Z ", "Nissan 370Z", "Nissan Stagea", "Nissan Serena ", "Nissan Skyline GT-R", "Nissan Stanza"};
  char L6[][TAM] = {"Captur", "Clio", "Clio Sedan", "Duster", "Duster Oroch", "Logan", "Mégane Grand Tour", "Mégane Sedan", "Sandero", "Scénic"};
  char L7[][TAM] = {"Peugeot 206", "Peugeot 206 SW", "Peugeot 206+", "Peugeot 207 Passion", "Peugeot 207 SW ", "Peugeot 208", "Peugeot 2008", "Peugeot Hoggar","Peugeot 308 Hybride HDi","Peugeot 308 SW Prologue"};
  char L8[][TAM] =  {"GT4R", "Puma P8", "Puma Spyder", "GTE", "GTS", "GTB", "GTB S2", "GTB S3", "GTB S4", "GTC"};

  switch (fabricante) {
    case 0:
            for(i = 0; i <  TOT_CARROS; i++){
                if( !carro[i].status ){
                  for(j = 0; j < 10; j++){
                    if ( !strcmp(carro[i].modelo, L1[j]) ){ qtd[j]++; }
                  }
                }
            }
          break;
    case 1:
            for(i = 0; i <  TOT_CARROS; i++){
                if( !carro[i].status ){
                  for(j = 0; j < 10; j++){
                    if ( !strcmp(carro[i].modelo, L2[j]) ){ qtd[j]++; }
                  }
                }
            }
          break;
    case 2:
            for(i = 0; i <  TOT_CARROS; i++){
                if( !carro[i].status ){
                  for(j = 0; j < 10; j++){
                    if ( !strcmp(carro[i].modelo, L3[j]) ){ qtd[j]++; }
                  }
                }
            }
          break;
    case 3:
            for(i = 0; i <  TOT_CARROS; i++){
                if( !carro[i].status ){
                  for(j = 0; j < 10; j++){
                    if ( !strcmp(carro[i].modelo, L4[j]) ){ qtd[j]++; }
                  }
                }
            }
          break;
    case 4:
            for(i = 0; i <  TOT_CARROS; i++){
                if( !carro[i].status ){
                  for(j = 0; j < 10; j++){
                    if ( !strcmp(carro[i].modelo, L5[j]) ){ qtd[j]++; }
                  }
                }
            }
          break;
    case 5:
            for(i = 0; i <  TOT_CARROS; i++){
                if( !carro[i].status ){
                  for(j = 0; j < 10; j++){
                    if ( !strcmp(carro[i].modelo, L6[j]) ){ qtd[j]++; }
                  }
                }
            }
          break;
    case 6:
            for(i = 0; i <  TOT_CARROS; i++){
                if( !carro[i].status ){
                  for(j = 0; j < 10; j++){
                    if ( !strcmp(carro[i].modelo, L7[j]) ){ qtd[j]++; }
                  }
                }
            }
          break;
    case 7:
            for(i = 0; i <  TOT_CARROS; i++){
                if( !carro[i].status ){
                  for(j = 0; j < 10; j++){
                    if ( !strcmp(carro[i].modelo, L8[j]) ){ qtd[j]++; }
                  }
                }
            }
          break;
  }
}
