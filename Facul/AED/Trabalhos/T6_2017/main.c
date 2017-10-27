#include <stdio.h>
#include <stdlib.h>
#define TAM 50

int total_carros; //Total de carros registrados
int total_clientes;//Total de clientes registrados
int total_vendas;//Total de vendas registradas

char opcionais[][TAM]={ {"4.portas"}, {"cambio.automatico"}, {"vidros.eletricos"}, {"abs"}, {"air.bag"}, {"ar.condicionado"},
 {"banco.couro"}, {"sensor.estacionamento"}};

/*-=--=--=--=--=--=--=--=--=-CADASTRO CARRO-=--=--=--=--=--=--=--=--=--=--=-*/
struct CARRO {
 char placa[9]; //AAA-1234
 char modelo[TAM]; //gol, celta, palio, ...
 char fabricante[TAM]; //chevrolet, fiat, ...
 int ano_fabricacao; //1980 à 2017
 int ano_modelo; //1980 à 2018
 char combustivel[TAM]; //alcool, gasolina, flex, diesel
 char cor[TAM]; //branca, prata, preta
 int opcional[8]; //ver matriz opcionais
 float preco_compra;
};
typedef struct CARRO _CARRO;
/*----------------------------------------------------------------------------*/

/*-=--=--=--=--=--=--=--=--=-CADASTRO CLIENTE-=--=--=--=--=--=--=--=--=--=--=-*/
struct ENDERECO {
 char rua[TAM];
 int numero;
 char bairro[TAM];
 char cidade[TAM];
 char estado[3];
 char cep[11]; //99.999-999
};

struct TELEFONE {
 char telefone[14]; //99 99999-9999
};

struct CLIENTE {
 char nome[TAM];
 char cpf[15]; //999.999.999-99
 struct ENDERECO endereco;
 struct TELEFONE residencial;
 struct TELEFONE celular[5];
 float renda_mensal;
};
typedef struct CLIENTE _CLIENTE;
/*----------------------------------------------------------------------------*/

/*-=--=--=--=--=--=--=--=--=-CADASTRO VENDA-=--=--=--=--=--=--=--=--=--=--=-*/
struct DATA {
 int dia, mes, ano;
};

struct VENDA_CARRO {
 char placa_car[9];
 char cpf_cli[15];
 float preco_venda;
 struct DATA data_venda;
};
typedef struct VENDA_CARRO _VENDA_CARRO;
/*----------------------------------------------------------------------------*/

/*-=--=--=--=--=--=--=--=--=-CHAMADA AS FUNÇÕES-=--=--=--=--=--=--=--=--=--=--=-*/
//------------------MENUS-----------//
void iniciar_sistema();
void menu_principal(_CARRO* Carro, _CLIENTE* Cliente, _VENDA_CARRO* Venda);
void menu_carro(_CARRO* Carro);
void menu_cliente(_CLIENTE* Cliente);
void menu_venda(_VENDA_CARRO* Venda);
//-----------FUNCOES REFERENTES AOS CARROS---------//
void Insere_Carro(_CARRO* CARRO);
/*-=--=--=--=--=--=--=--=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=--=--=--=--=--=--=--=--=--=-*/


int main()
{
  _CARRO Carro[TAM];
  _CLIENTE Cliente[TAM];
  _VENDA_CARRO Venda[TAM];

  iniciar_sistema();
  menu_principal(Carro, Cliente, Venda);

  return 0;
}

//objetivo: Iniciar as variaveis contadoras no sistema
//parametros: Nenhum
//retorno: Sem retorno
void iniciar_sistema()
{
  total_carros = 0;
  total_clientes = 0;
  total_vendas = 0;
}
//objetivo: Gerenciar os sub-menus de carro, cliente e venda
//parametros: 3 veteres, um que contem os registro dos carros, outro com o registros dos cliente e outro com o registro de vendas
//retorno: Sem retorno
void menu_principal(_CARRO* Carro, _CLIENTE* Cliente, _VENDA_CARRO* Venda)
{
    char opI;
    do{
      printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- \033[7mMENU PRINCIPAL\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
      printf("1. Carro\n2. Cliente\n3. Venda\n4. Sair programa\n--> ");
        __fpurge(stdin);
        scanf("%c",&opI);

      switch (opI) {
        case '1':
                menu_carro(Carro);
                break;
        case '2':
                menu_cliente(Cliente);
                break;
        case '3':
                menu_venda(Venda);
                break;
        case '4':
                break;
        default:
              printf("\n\nValor invalido! Informe outro ");
      }

    }while(opI != '4');
}

//objetivo: Gerenciar a escolha do usuario referente apenas a um carro
//parametros: Um vetor que contem os registro dos carros
//retorno: Sem retorno
void menu_carro(_CARRO* Carro)
{
  char op,sair = '1';
    do{
      printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- \033[7mMENU CARRO\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
      printf("a. Inserir um carro no cadastro\nb. Excluir um carro do cadastro\nc. Listar os carros disponíveis para a venda em ordem crescente por fabricante e modelo\nd. Listar os carros disponíveis para a venda por seleção de um ou mais opcionais\ne. Listar os carros disponíveis para a venda por seleção da faixa de ano de fabricação\nf. Sair\n--> ");
            __fpurge(stdin);
            scanf("%c",&op);
      switch (op) {
        case 'a':
        case 'A':
              Insere_Carro(Carro);
              break;
        case 'b':
        case 'B':

              break;
        case 'c':
        case 'C':

              break;
        case 'd':
        case 'D':

              break;
        case 'e':
        case 'E':

              break;
        case 'f':
        case 'F':
              sair = '0';
              break;
        default:
              printf("\n\nValor invalido! Informe outro ");

      }
    }while(sair != '0');
}
//objetivo: Gerenciar a escolha do usuario referente apenas a um cliente
//parametros: Um vetor que contem os registro dos clientes
//retorno: Sem retorno
void menu_cliente(_CLIENTE* Cliente)
{
  char op,sair = '1';
    do{
      printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- \033[7mMENU CLIENTE\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
      printf("a. Inserir um cliente no cadastro\nb. Excluir um cliente do cadastro\nc. Listar os clientes do cadastro em ordem crescente pelo nome\nd. Listar os clientes do cadastro em ordem crescente pelo nome e por seleção de faixa de renda salarial mensal\ne. Sair\n--> ");
            __fpurge(stdin);
            scanf("%c",&op);
      switch (op) {
        case 'a':
        case 'A':

              break;
        case 'b':
        case 'B':

              break;
        case 'c':
        case 'C':

              break;
        case 'd':
        case 'D':

              break;
        case 'e':
        case 'E':
              sair = '0';
              break;
        default:
              printf("\n\nValor invalido! Informe outro ");
      }
    }while(sair != '0');
}
//objetivo: Gerenciar a escolha do usuario referente apenas a uma venda
//parametros: Um vetor que contem os registro das vendas
//retorno: Sem retorno
void menu_venda(_VENDA_CARRO* Venda)
{
  char op,sair = '1';
    do{
      printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- \033[7mMENU VENDA\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
      printf("a. Inserir uma venda\nb. Excluir uma venda\nc. Listar os carros vendidos de um determinado fabricante, em ordem crescente pelo modelo\nd. Listar os carros vendidos de um determinado modelo, em ordem crescente pelo ano de fabricação\ne. Informar a quantidade de carros vendidos com o valor totalizado dos preços vendidos\nf. Informar o lucro total das vendas\ng. Sair\n--> ");
            __fpurge(stdin);
            scanf("%c",&op);
      switch (op) {
        case 'a':
        case 'A':

              break;
        case 'b':
        case 'B':

              break;
        case 'c':
        case 'C':

              break;
        case 'd':
        case 'D':

              break;
        case 'e':
        case 'E':

              break;
        case 'f':
        case 'F':

              break;
        case 'g':
        case 'G':
              sair = '0';
              break;
        default:
              printf("\n\nValor invalido! Informe outro ");

      }
    }while(sair != '0');
}

//objetivo: Inserir carro no registro de cadastro
//parametros: Um vetor que contem os registro dos carros registrados
//retorno: Sem retorno

void Insere_Carro(_CARRO* CARRO)
{
    
}
