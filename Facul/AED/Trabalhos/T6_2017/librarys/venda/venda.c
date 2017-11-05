#include "venda.h"


FILE* open_VENDA(char* nome_arq, char* c)
{
  FILE* pfile;
  if ( ( pfile = fopen(nome_arq, c) ) == NULL ){
    printf("\n\n\t\033[31mFALHA AO ABRIR O ARQUIVO %s\033[m\n\n", nome_arq);
    exit(1);
  }
  return(pfile);
}

void close_VENDA( FILE* f, char* nome_arq )
{
    if( fclose(f) == EOF ){
      printf("\n\n\t\033[31mFALHA AO FECHAR O ARQUIVO %s\033[m\n\n", nome_arq);
      exit(1);
    }
}

int insereVenda( _CARRO* carro, _CLIENTE* cliente, int TOT_CLIENTE, int TOT_CARROS, float* valor)
{
  int i, verifica = 0, posI,posII, carroDisponivel;
  char cpf[14];

  printf("\n\nInsira o CPF do cliente (\033[31mFORMATO:\033[m 999.999.999-99): ");
  __fpurge(stdin);
  fgets(cpf,15,stdin);
  for(i = 0; i < TOT_CLIENTE; i++){
    if( !strcmp( cpf, cliente[i].cpf ) )
    {
        verifica = 1;
        posI = i;
    }
  }
  if( verifica ){
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

                  cliente[posI].status = 0;
                  carro[posII].status = 0;
                  *valor += carro[posII].preco_compra;

                  fVenda = open_VENDA(venda, "ab");
                      fwrite(&vendas, sizeof(vendas), 1, fVenda);
                  close_VENDA(fVenda, venda);

                  printf("\n\n\tVENDA CONCLUIDA COM SUCESSO!\n\n");
                sair = 'n';
                return 1;
            }
            else{
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

int excluir_VENDA(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS, float* valor)
{
  int i, pos;
  int verifica = 0;
  char placa[9];
  _VENDA vendas;

      printf("\n\nInsira a placa do carro que sera excluida a venda (\033[31mFORMATO:\033[m ABC-1234): ");
      __fpurge(stdin);
      fgets(placa,9,stdin);

        for(i = 0; i < TOT_VENDAS; i++){
          if( !strcmp( placa, venda[i].placa_venda ) )
          {
            verifica = 1;
            pos = i;
            break;
          }
        }
        if(verifica){
          for(i = 0; i < TOT_CLIENTE; i++){
              if( !strcmp(venda[i].cpf_venda, cliente[i].cpf) ){
                cliente[i].status = 1;
                break;
              }
          }
          for(i = 0; i < TOT_CARROS; i++){
              if( !strcmp(venda[i].placa_venda, carro[i].placa) ){
                carro[i].status = 1;
                *valor -= carro[i].preco_compra;
                break;
              }
          }
          vendas = venda[TOT_VENDAS - 1];
          venda[TOT_VENDAS - 1] = venda[pos];
          venda[pos] = vendas;

          return 1;
      }else{
        printf("\n\n\t\033[31mNenhum carro vendido que tenha essa placa.\033[m\n\n");
        return 0;
      }
}

void listaFabricante(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente, int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;
  do{
    printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-LISTAGEM POR FABICANTE-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Aponte o fabricante: \n");
    printf("1 - Volkswagen\n2 - Chevrolet\n3 - Ford\n4 - Fiat\n5 - Nissan\n6 - Renault\n7 - Peugeot\n8 - Puma\n0 - SAIR\n--> ");
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

void listagenFabricante(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS,int escolha)
{
  char fabricante[][TAM] = {"Volkswagen","Chevrolet","Ford","Fiat","Nissan","Renault","Peugeot","Puma"};
  int i, verifica = 0, j = 1, x, y;
  printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=- %s =-=-=-=-=-=-=-=-=-=-=-\n", fabricante[escolha]);
  for(i = 0; i < TOT_CARROS; i++){
    if( !carro[i].status ){
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

void listaModelo(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;

  do{
    printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-LISTAGEM POR MODELO-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Aponte o fabricante do modelo: \n");
    printf("1 - Volkswagen\n2 - Chevrolet\n3 - Ford\n4 - Fiat\n5 - Nissan\n6 - Renault\n7 - Peugeot\n8 - Puma\n0 - SAIR\n--> ");
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


void modeloPuma(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS)
{
  char op;
  do{
    printf("\n\nS - SAIR\n0 - GT4R\n1 - Puma P8\n2 - Puma Spyder\n3 - GTE\n4 - GTS\n5 - GTB\n6 - GTB S2\n7 - GTB S3\n8 - GTB S4\n9 - GTC\n--> ");
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
  do{

    printf("\n\nS - SAIR\n0 - Peugeot 206\n1 - Peugeot 206 SW\n2 - Peugeot 206+\n3 - Peugeot 207 Passion\n4 - Peugeot 207 SW \n5 - Peugeot 208\n6 - Peugeot 2008\n7 - Peugeot Hoggar\n8 - Peugeot 308 Hybride HDi\n9 - Peugeot 308 SW Prologue\n--> ");
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
  do{
    printf("\n\nS - SAIR\n0 - Captur\n1 -  Clio\n2 -  Clio Sedan\n3 -  Duster\n4 -  Duster Oroch\n5 -  Logan\n6 -  Mégane Grand Tour\n7 -  Mégane Sedan\n8 -   Sandero\n9 -   Scéni\n--> ");
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
  do{
    printf("\n\nS - SAIR\n0 - Nissan Frontier\n1 - Nissan Presage\n2 - Nissan 240SX\n3 - Nissan 300ZX\n4 -  Nissan 350Z\n5 -  Nissan 370Z\n6 - Nissan Stagea\n7 - Nissan Serena\n8 -  Nissan Skyline GT-R\n9 - Nissan Stanza\n--> ");
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
  do{
    printf("\n\nS - SAIR\n0 - Fiat 147 \n1 - City \n2 - Brava \n3 - Bravo  \n4 - Doblò \n5 - Fiorino \n6 - Prêmio \n7 - Punto \n8 - Stilo \n9 - Tempra\n--> ");
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
  do{
    printf("\n\nS - SAIR\n0 - Belina \n1 - Corcel \n2 - Del Rey \n3 - Escort conversível \n 4- F-1000 \n5 - Fiesta \n6 - Jeep \n7 - Galaxie \n8 - Ka \n9 - Pampa\n->");
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
  do{
    printf("\n\nS - SAIR\n0 - Brasilia \n1 - Fox \n2 - Fusca \n3 - Gol \n4 - Golf \n5 - Jetta \n6 - Parati \n7 - Passat \n8 - Saveiro \n9 - Karmann Ghia Cabriolét\n-> ");
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
  do{

    printf("\n\nS - SAIR\n0 - Alvorada \n1 - D-20 \n2 - Monza hatch \n3 - S10 \n4- Omega Suprema \n5 - Gran Blazer \n6 - Cruze \n7 - Opala coupé \n8 - Prisma \n9 - Blazer\n-> ");
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

          for(x = 0; x < TOT_CLIENTE; x++){
              if( !strcmp(carro[i].placa, venda[x].placa_venda )){
                for(y = 0; y < TOT_VENDAS; y++){
                  if( !strcmp(venda[x].cpf_venda, cliente[y].cpf ) ){
                    printf("* CLIENTE:         %s\n", cliente[x].nome);
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
