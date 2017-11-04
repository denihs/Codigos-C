#include "librarys/carro/carro.h"

int total_carros; //Total de carros registrados
int total_clientes;//Total de clientes registrados
int total_vendas;//Total de vendas registradas


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
FILE* open(char* nome_arq, char* c);
void close( FILE* f, char* nome_arq );

void iniciar_sistema();
FILE* fIniciaSistema(char* c);
void updateSistema(FILE* p);
void readInit(FILE* p);

void menu_principal();

void menu_carro();
void cadastro_carro(FILE* p);
void mostraCarro(FILE* p);
void _excluir();
void _ordena();
void _exibi(FILE* f);
void _exibiCarroOpcionais(FILE* f);
void _exibiCarroData(FILE* f);

void menu_cliente();
void menu_venda();
//-----------FUNCOES REFERENTES AOS CARROS---------//

/*-=--=--=--=--=--=--=--=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=--=--=--=--=--=--=--=--=--=-*/


int main()
{
  srand(time(NULL));


  char init[] = {"file/init.dat"};
  FILE* inicio;

  inicio = fIniciaSistema(init);
  if(inicio == NULL){
    iniciar_sistema();
    inicio = open(init, "wb");
  }else{
    readInit(inicio);
  }

  menu_principal();

  close(inicio, init);
  inicio = open(init, "wb");
    updateSistema(inicio);
  close(inicio, init);


  return 0;
}

FILE* open(char* nome_arq, char* c)
{
  FILE* pfile;
  if ( ( pfile = fopen(nome_arq, c) ) == NULL ){
    printf("\n\n\t\033[31mFALHA AO ABRIR O ARQUIVO %s\033[m\n\n", nome_arq);
    exit(1);
  }
  return(pfile);
}

void close( FILE* f, char* nome_arq )
{
    if( fclose(f) == EOF ){
      printf("\n\n\t\033[31mFALHA AO FECHAR O ARQUIVO %s\033[m\n\n", nome_arq);
      exit(1);
    }
}


void updateSistema(FILE* p)
{

  fwrite(&total_carros, sizeof(int), 1, p);
  fwrite(&total_clientes, sizeof(int) , 1, p);
  fwrite(&total_vendas, sizeof(int) , 1, p);

}

FILE* fIniciaSistema(char* c)
{
  FILE* p = fopen(c , "r");
  return(p);
}

void readInit(FILE* p)
{
    fseek(p, 0 , SEEK_SET);

    fread(&total_carros, sizeof(int) , 1, p);
    fread(&total_clientes, sizeof(int) , 1, p);
    fread(&total_vendas, sizeof(int) , 1, p);
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
void menu_principal()
{
    /*char cliente[] = {"file/cliente.dat"};
    char venda[] = {"file/venda.dat"};
    FILE* fCliente;
    FILE* fVenda;

    fCliente = open(cliente,"a+b");
    fVenda = open(venda, "a+b");


    close(fCliente, cliente);
    close(fVenda, venda); */
    char opI;
    do{
      printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- \033[7mMENU PRINCIPAL\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
      printf("1. Carro\n2. Cliente\n3. Venda\n4. Sair programa\n--> ");
        __fpurge(stdin);
        scanf("%c",&opI);

      switch (opI) {
        case '1':
                menu_carro();
                break;
        case '2':
                menu_cliente();
                break;
        case '3':
                menu_venda();
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
void menu_carro()
{
  char carro[] = {"file/carro.dat"};
  FILE* fCarro;
  char op,sair = '1';
  int i;
    do{
      printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- \033[7mMENU CARRO\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
      printf("a. Inserir um carro no cadastro\nb. Excluir um carro do cadastro\nc. Listar os carros disponíveis para a venda em ordem crescente por fabricante e modelo\nd. Listar os carros disponíveis para a venda por seleção de um ou mais opcionais\ne. Listar os carros disponíveis para a venda por seleção da faixa de ano de fabricação\nf. Sair\n--> ");
            __fpurge(stdin);
            scanf("%c",&op);
      switch (op) {
        case 'a':
        case 'A':
              if(total_carros < TAM){
                //Abrindo para adicionar um cadastro
                fCarro = open(carro,"ab");
                  cadastro_carro(fCarro);
                close(fCarro, carro);
                    total_carros++;
                //Abrindo para ler os dados do cadastro inserido
                fCarro = open(carro,"rb");
                  mostraCarro(fCarro);
                close(fCarro, carro);
              }else{
                printf("\n\n\t\033[31mDesculpe mas o limite de cadastros ja foi atingido\033[m\n\n");
              }
              break;
        case 'b':
        case 'B':
                if(total_carros){
                      _excluir(fCarro);
                      total_carros--;
                }else{
                  printf("\n\n\t\033[31mNao ha carros para serem excluidos.\033[m\n\n");
                }
              break;
        case 'c':
        case 'C':
                _ordena();
                fCarro = open(carro,"rb");
                    _exibi(fCarro);
                close(fCarro, carro);
              break;
        case 'd':
        case 'D':
                    fCarro = open(carro,"rb");
                        total_carros ? _exibiCarroOpcionais(fCarro) : printf("\n\n\t\033[31mNao existe nenhum carro cadastrado ate o momento\033[m\n\n");
                    close(fCarro, carro);
              break;
        case 'e':
        case 'E':
                  fCarro = open(carro,"r");
                    total_carros ? _exibiCarroData(fCarro) : printf("\n\n\t\033[31mNao existe nenhum carro cadastrado ate o momento\033[m\n\n");
                  close(fCarro, carro);
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

void cadastro_carro(FILE* p)
{
  _CARRO carro;
    Insere_Carro( &carro );
    fwrite(&carro, sizeof(carro), 1, p);
}

void mostraCarro(FILE* p)
{
    int i;
    _CARRO carro[total_carros];
        fseek(p, 0, SEEK_SET);
        for(i = 0; i < total_carros; i++){
          fread(&carro[i], sizeof(carro[i]), 1, p);
        }
      exibi(carro,total_carros -1 , total_carros, 0);
}

void _excluir()
{
  char carro[] = {"file/carro.dat"};
  FILE* f;

  int i;
  _CARRO carros[total_carros];

  f = open(carro,"rb");
      fseek(f, 0, SEEK_SET);
      for(i = 0; i < total_carros; i++){
        fread(&carros[i], sizeof(carros[i]), 1, f);
      }
    excluir(carros,total_carros);
  close(f, carro);

  f = open(carro,"wb");
      for(i = 0; i < total_carros; i++){
        fwrite(&carros[i], sizeof(carros[i]), 1, f);
      }
  close(f, carro);

}

void _ordena()
{
  char carro[] = {"file/carro.dat"};
  FILE* f;

  int i;
  _CARRO carros[total_carros];

  f = open(carro,"rb");
      fseek(f, 0, SEEK_SET);
      for(i = 0; i < total_carros; i++){
        fread(&carros[i], sizeof(carros[i]), 1, f);
      }
    ordena(carros,total_carros);
  close(f, carro);

  f = open(carro,"wb");
      for(i = 0; i < total_carros; i++){
        fwrite(&carros[i], sizeof(carros[i]), 1, f);
      }
  close(f, carro);
}

void _exibi(FILE* f)
{
  int i;
  _CARRO carro[total_carros];
      fseek(f, 0, SEEK_SET);
      for(i = 0; i < total_carros; i++){
        fread(&carro[i], sizeof(carro[i]), 1, f);
      }
    exibi(carro,0 , total_carros, 0);
}

void _exibiCarroOpcionais(FILE* f)
{
      int quantidade, i, aux, verifica = 1;
      int opcoes[8];
      _CARRO carro[total_carros];
      printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- \033[7mSelecao por opcoes\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("Informe a quantidade de opcoes que seram buscadas (Entre 1 e 8): ");
        do{
          scanf("%d",&quantidade);
          if (quantidade < 0 || quantidade > 8)
              printf("\n\nValor informado é invalido, ele deve ser entre 1 e 8 (0 para cancelar a busca)\n--> ");
        }while(quantidade < 0 || quantidade > 8);

      if(quantidade){
        printf("\nQual das opcoes voce deseja? \n");
        printf("1 -> 4 Portas\n2 -> Cambio Automatico\n3 -> Vidros Eletricos\n4 -> Abs\n5 -> air.bag\n6  -> Ar Condicionado\n7 -> Banco Couro\n8 -> Sensor Estacionamento");
        for(i = 0; i < quantidade; i++){
            printf("\nOpcao %d--> ",i + 1);
            do{
              scanf("%d",&aux);
              opcoes[i] = aux - 1;
              if(opcoes[i] < 0 || opcoes[i] > 7){
                printf("\nOs valores das opcoes devem ser de 1 a 8: ");
              }
              if( !sem_repeticao(opcoes, aux - 1, i) ){
                  printf("\n\n\t\033[31mEste valor ja foi digitado\033[m\n\nInsira outra das opcoes--> ");
                  verifica = 1;
              }else{
                  verifica = 0;
              }
            }while( (opcoes[i] < 0 || opcoes[i] > 7) || verifica);
        }
        fseek(f, 0, SEEK_SET);
        for(i = 0; i < total_carros; i++){
          fread(&carro[i], sizeof(carro[i]), 1, f);
        }
        exibiCarroOpcionais(carro, opcoes, quantidade, total_carros);
      }else{
        printf("\n\n\t\033[31mOperacao cancelada\033[m\n\n");
      }
}

void _exibiCarroData(FILE* f)
{
  int i, dataInicial, dataFinal;
  _CARRO carro[total_carros];
  printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- \033[7mSelecao por faixa de ano\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Data inicial (1980 - 2017 ): ");
      do{
          scanf("%d",&dataInicial);
          if( dataInicial < 1980 || dataInicial > 2017 ){
            printf("O ano deve ser entre 1980 e 2017: ");
          }
      }while(dataInicial < 1980 || dataInicial > 2017);
    printf("Data final (1980 - 2017 ): ");
      do{
          scanf("%d",&dataFinal);
          if( dataFinal < 1980 || dataFinal > 2017 ){
            printf("O ano deve ser entre 1980 e 2017: ");
          }else
          if( dataInicial > dataFinal ){
            printf("A data final deve ser maior ou igual em relacao a data inicial inserida que em seu caso foi: %d\n",dataInicial);
            printf("--> ");
          }
      }while(dataFinal < 1980 || dataFinal > 2017 || dataInicial > dataFinal);
      fseek(f, 0, SEEK_SET);
      for(i = 0; i < total_carros; i++){
        fread(&carro[i], sizeof(carro[i]), 1, f);
      }
      exibiCarroData(carro, dataInicial, dataFinal, total_carros);
}



//objetivo: Gerenciar a escolha do usuario referente apenas a um cliente
//parametros: Um vetor que contem os registro dos clientes
//retorno: Sem retorno
void menu_cliente()
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
void menu_venda()
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
