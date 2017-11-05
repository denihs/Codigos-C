/* *Função: Sistema que simula um software de um revendedora de carros
            permite que sejam armazenadas em arquivos informações como:
            O resgistro de um carro vendido, dados de um cliente cadastrado
            quando e valor dos carros vendidos.
   *Autor: Denilson Higino da Silva  | RGM: 36712
   *Data de inicio: 25/10/2017
   *Data de finalização: 05/11/2017
===============================================================================*/

#include "librarys/carro/carro.h"
#include "librarys/cliente/cliente.h"
#include "librarys/venda/venda.h"

int total_carros; //Total de carros registrados
int total_clientes;//Total de clientes registrados
int total_vendas;//Total de vendas registradas
float TOTAL_VENDAS;//Valor bruto das vendas


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
int _excluir();
void _ordena();
void _exibi(FILE* f);
void _exibiCarroOpcionais(FILE* f);
void _exibiCarroData(FILE* f);

void menu_cliente();
void cadastro_cliente(FILE* p);
void mostraCliente(FILE* p);
int _excluir_CLIENTE();
void _ordena_CLIENTE();
void _exibi_CLIENTE(FILE* f);
void _ordenaNomeSalario_CLIENTE();

void menu_venda();
void insereVenda_CLIENTE();
void _excluir_VENDA();
void _listagemFabricante();
void _listagemModelo();
void totalVendas();
void lucroGeral();
//-----------FUNCOES REFERENTES AOS CARROS---------//

/*-=--=--=--=--=--=--=--=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=--=--=--=--=--=--=--=--=--=-*/


int main()
{
  srand(time(NULL));


  char init[] = {"file/init.dat"};
  FILE* inicio;
  //Verificando se o arquivo que contem as variaveis com a quantidade de vendas, clientes e carros esta criado
  //Se caso não estiver ele cria o arquivo e inicializa as variavei
  inicio = fIniciaSistema(init);
  if(inicio == NULL){
    iniciar_sistema();
    inicio = open(init, "wb");
  }else{
    readInit(inicio);
  }

  menu_principal();

  //Faz uma atualização nos valores das variaveis de controle de cliente, venda etc...
  close(inicio, init);
  inicio = open(init, "wb");
    updateSistema(inicio);
  close(inicio, init);


  return 0;
}


//objetivo: Abrir arquivos para consulta, escrita etc..
//parametros: O caminho e nome do arquivo terá  e  o modo de abertura
//retorno: Retorna o endereço do arquivo na memoria
FILE* open(char* nome_arq, char* c)
{
  FILE* pfile;
  if ( ( pfile = fopen(nome_arq, c) ) == NULL ){
    printf("\n\n\t\033[31mFALHA AO ABRIR O ARQUIVO %s\033[m\n\n", nome_arq);
    exit(1);
  }
  return(pfile);
}

//objetivo: Fechar os arquivos abertos
//parametros: O enderço do arquivo aberto e o nome/caminho do arquivo
//retorno: Sem retorno
void close( FILE* f, char* nome_arq )
{
    if( fclose(f) == EOF ){
      printf("\n\n\t\033[31mFALHA AO FECHAR O ARQUIVO %s\033[m\n\n", nome_arq);
      exit(1);
    }
}

//objetivo: Faz a atualização das variaveis que contem o total de carro, cliente, vendas, e o valor bruto das vendas
//parametros: O endereco do arquivo
//retorno: Sem retorno
void updateSistema(FILE* p)
{

  fwrite(&total_carros, sizeof(int), 1, p);
  fwrite(&total_clientes, sizeof(int) , 1, p);
  fwrite(&total_vendas, sizeof(int) , 1, p);
  fwrite(&TOTAL_VENDAS, sizeof(float) , 1, p);

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
    fread(&TOTAL_VENDAS, sizeof(float) , 1, p);
}

//objetivo: Iniciar as variaveis contadoras no sistema
//parametros: Nenhum
//retorno: Sem retorno
void iniciar_sistema()
{
  total_carros = 0;
  total_clientes = 0;
  total_vendas = 0;
  TOTAL_VENDAS = 0.0;
}
//objetivo: Gerenciar os sub-menus de carro, cliente e venda
//parametros: Sem parametros
//retorno: Sem retorno
void menu_principal()
{

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
//parametros: Sem parametros
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
                printf("\n\n\t\033[31mDesculpe mas o limite de cadastros para carros ja foi atingido\033[m\n\n");
              }
              break;
        case 'b':
        case 'B':
                if(total_carros){
                    if(  _excluir()){
                      total_carros--;
                    }
                }else{
                  printf("\n\n\t\033[31mNao ha carros para serem excluidos.\033[m\n\n");
                }
              break;
        case 'c':
        case 'C':
                if(total_carros){
                    _ordena();
                    fCarro = open(carro,"rb");
                        _exibi(fCarro);
                    close(fCarro, carro);
                }else{
                    printf("\n\n\t\033[31mNao existe nenhum carro cadastrado ate o momento\033[m\n\n");
                }
              break;
        case 'd':
        case 'D':
                  if(total_carros)  {
                    fCarro = open(carro,"rb");
                       _exibiCarroOpcionais(fCarro);
                    close(fCarro, carro);
                  }else{
                      printf("\n\n\t\033[31mNao existe nenhum carro cadastrado ate o momento\033[m\n\n");
                  }
              break;
        case 'e':
        case 'E':
                  if(total_carros)  {
                    fCarro = open(carro,"rb");
                      _exibiCarroData(fCarro);
                    close(fCarro, carro);
                  }else{
                      printf("\n\n\t\033[31mNao existe nenhum carro cadastrado ate o momento\033[m\n\n");
                  }
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
//objetivo:  Adiciona um carro cadastrado no arquivo que contem os cadastros do carros
//parametros: O endereço do arquivo
//retorno: Sem retorno
void cadastro_carro(FILE* p)
{
  _CARRO carro;
    Insere_Carro( &carro );
    fwrite(&carro, sizeof(carro), 1, p);
}

//objetivo: Ler no arquivo os carros cadastrados e mostra as informações do carro que acabou de ser cadastrado
//parametros: O endereço do arquivo
//retorno: Sem retorno
void mostraCarro(FILE* p)
{
    int i;
    _CARRO carro[total_carros];
        fseek(p, 0, SEEK_SET);
        for(i = 0; i < total_carros; i++){
          fread(&carro[i], sizeof(carro[i]), 1, p);
        }
      exibi(carro,total_carros -1 , total_carros, 1);
}

//objetivo: Fazer a exclusão de um carro do sistema
//parametros: Sem parametro
//retorno: retorna 1 se a exclusão foi bem sucessedida e ZERO caso contrario
int _excluir()
{
  int resposta;
  char carro[] = {"file/carro.dat"};
  FILE* f;

  int i;
  _CARRO carros[total_carros];
  //Recuperamos todos os carros cadastrados
  f = open(carro,"rb");
      fseek(f, 0, SEEK_SET);
      for(i = 0; i < total_carros; i++){
        fread(&carros[i], sizeof(carros[i]), 1, f);
      }
    resposta = excluir(carros,total_carros);//Recuperamos o numero 1 se existiu a exclusão
  close(f, carro);
  //Escrevemos no arquivo os novos dados
  f = open(carro,"wb");
      for(i = 0; i < total_carros; i++){
        fwrite(&carros[i], sizeof(carros[i]), 1, f);
      }
  close(f, carro);
  return resposta;
}

//objetivo: Vai recuperar os cadastros no sistema e depois chamar a função responsavel por ordenar a biblioteca "carro"
//parametros: Sem parametro
//retorno: Sem retorno
void _ordena()
{
  char carro[] = {"file/carro.dat"};
  FILE* f;

  int i;
  _CARRO carros[total_carros];
  //Recuperação de todos os carros registrados
  f = open(carro,"rb");
      fseek(f, 0, SEEK_SET);
      for(i = 0; i < total_carros; i++){
        fread(&carros[i], sizeof(carros[i]), 1, f);
      }
    ordena(carros,total_carros);//Chamada a c função de ordenação na biblioteca de "carro"
  close(f, carro);
  //Reeescrevemos os dados no arquivos do carro
  f = open(carro,"wb");
      for(i = 0; i < total_carros; i++){
        fwrite(&carros[i], sizeof(carros[i]), 1, f);
      }
  close(f, carro);
}
//objetivo: Recuperar os cadastros de carros no sistema para exibi - los na tela
//parametros: O endereço do arquivo
//retorno: sem retorno
void _exibi(FILE* f)
{
  int i;
  _CARRO carro[total_carros];
  //Recuperação dos dados
      fseek(f, 0, SEEK_SET);
      for(i = 0; i < total_carros; i++){
        fread(&carro[i], sizeof(carro[i]), 1, f);
      }
    exibi(carro,0 , total_carros, 0);
}


//objetivo: Permitir que o usuario determine um carro com um certa quantidade de acessorio no carro
//parametros: O endereço do arquivo que contem os carros
//retorno: sem retorno
void _exibiCarroOpcionais(FILE* f)
{
      int quantidade, i, aux, verifica = 1;
      int opcoes[8];
      _CARRO carro[total_carros];
      printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- \033[7mSelecao por opcoes\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("Informe a quantidade de opcoes que seram buscadas (Entre 1 e 8): ");
        do{//Le a quantidade de opcionais
          scanf("%d",&quantidade);
          if (quantidade < 0 || quantidade > 8)
              printf("\n\nValor informado é invalido, ele deve ser entre 1 e 8 (0 para cancelar a busca)\n--> ");
        }while(quantidade < 0 || quantidade > 8);

      if(quantidade){//Tendo a quantidade de opcionais sera lido quais os opcionais ele deseja
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
              if( !sem_repeticao(opcoes, aux - 1, i) ){//Impedimos que seja pedido um mesmo opcional mais que uma vez
                  printf("\n\n\t\033[31mEste valor ja foi digitado\033[m\n\nInsira outra das opcoes--> ");
                  verifica = 1;
              }else{
                  verifica = 0;
              }
            }while( (opcoes[i] < 0 || opcoes[i] > 7) || verifica);
        }
        //Lemos o arquivo de carro e pegamos todos os cadastros para chama a função que exibe os carros disponiveis com o desejado
        fseek(f, 0, SEEK_SET);
        for(i = 0; i < total_carros; i++){
          fread(&carro[i], sizeof(carro[i]), 1, f);
        }
        exibiCarroOpcionais(carro, opcoes, quantidade, total_carros);
      }else{
        printf("\n\n\t\033[31mOperacao cancelada\033[m\n\n");
      }
}

//objetivo: Recuperar os cadastros de carros no sistema para exibi - los na tela por uma faixa de ano
//parametros: O endereço do arquivo
//retorno: sem retorno
void _exibiCarroData(FILE* f)
{
  int i, dataInicial, dataFinal;
  _CARRO carro[total_carros];
  printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- \033[7mSelecao por faixa de ano\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Data inicial (1980 - 2017 ): ");
      do{//Lemos a faixa inicial
          scanf("%d",&dataInicial);
          if( dataInicial < 1980 || dataInicial > 2017 ){
            printf("O ano deve ser entre 1980 e 2017: ");
          }
      }while(dataInicial < 1980 || dataInicial > 2017);
    printf("Data final (1980 - 2017 ): ");
      do{//Lemos a faixa final
          scanf("%d",&dataFinal);
          if( dataFinal < 1980 || dataFinal > 2017 ){
            printf("O ano deve ser entre 1980 e 2017: ");
          }else
          if( dataInicial > dataFinal ){
            printf("A data final deve ser maior ou igual em relacao a data inicial inserida que em seu caso foi: %d\n",dataInicial);
            printf("--> ");
          }
      }while(dataFinal < 1980 || dataFinal > 2017 || dataInicial > dataFinal);
      //Recuperação dos cadastros de carros
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
  FILE* fCliente;
  char cliente[] = {"file/cliente.dat"};

  fCliente = open(cliente,"a+b");
  close(fCliente, cliente);
    do{
      printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- \033[7mMENU CLIENTE\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
      printf("a. Inserir um cliente no cadastro\nb. Excluir um cliente do cadastro\nc. Listar os clientes do cadastro em ordem crescente pelo nome\nd. Listar os clientes do cadastro em ordem crescente pelo nome e por seleção de faixa de renda salarial mensal\ne. Sair\n--> ");
            __fpurge(stdin);
            scanf("%c",&op);
      switch (op) {
        case 'a':
        case 'A':
            if(total_clientes < TAM){
                  //Abrindo para adicionar um cadastro
                  fCliente = open(cliente,"ab");
                    cadastro_cliente(fCliente);
                  close(fCliente, cliente);
                      total_clientes++;
                  //Abrindo para ler os dados do cadastro inserido
                  fCliente = open(cliente,"rb");
                    mostraCliente(fCliente);
                  close(fCliente, cliente);
                }else{
                  printf("\n\n\t\033[31mDesculpe mas o limite de cadastros para clientes ja foi atingido\033[m\n\n");
                }
              break;
        case 'b':
        case 'B':
                if(total_clientes){
                      if( _excluir_CLIENTE(fCliente) ){
                        total_clientes--;
                      }
                }else{
                  printf("\n\n\t\033[31mNao ha clientes para serem excluidos.\033[m\n\n");
                }
              break;
        case 'c':
        case 'C':
                if(total_clientes){
                    _ordena_CLIENTE();
                    fCliente = open(cliente,"rb");
                      _exibi_CLIENTE(fCliente);
                    close(fCliente, cliente);
                }else{
                    printf("\n\n\t\033[31mNao existe nenhum cliente cadastrado ate o momento\033[m\n\n");
                }
              break;
        case 'd':
        case 'D':
                    total_clientes ? _ordenaNomeSalario_CLIENTE() : printf("\n\n\t\033[31mNao existe nenhum cliente cadastrado ate o momento\033[m\n\n");
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
//objetivo: Adicina um registro de um cliente no sistema
//parametros: O endereço do arquivo dos clientes
//retorno: sem retorno
void cadastro_cliente(FILE* p)
{
  _CLIENTE cliente;
    insereCliente( &cliente );
    fwrite(&cliente, sizeof(cliente), 1, p);
}

//objetivo: Recupera os clientes para mostrar o ultimo cadastrado
//parametros: O endereço do arquivo
//retorno: sem retorno
void mostraCliente(FILE* p)
{
    int i;
    _CLIENTE cliente[total_clientes];
        fseek(p, 0, SEEK_SET);
        for(i = 0; i < total_clientes; i++){
          fread(&cliente[i], sizeof(cliente[i]), 1, p);
        }
      exibi_CLIENTE(cliente,total_clientes -1 , total_clientes, 1);
}

//objetivo: Vai excluir um registro de cliente do sistema
//parametros: Sem parametros
//retorno: retorna 1 caso tenhamos obtido sucesso e ZERO caso contrario
int _excluir_CLIENTE()
{
  int resposta;
  char cliente[] = {"file/cliente.dat"};
  FILE* f;

  int i;
  _CLIENTE clientes[total_clientes];
//Recuperamos todos os cadastros de clientes
  f = open(cliente,"rb");
      fseek(f, 0, SEEK_SET);
      for(i = 0; i < total_clientes; i++){
        fread(&clientes[i], sizeof(clientes[i]), 1, f);
      }
      //Excluimos o cliente
    resposta = excluir_CLIENTE(clientes,total_clientes);
  close(f, cliente);
//Gravamos os novos daods no registro
  f = open(cliente,"wb");
      for(i = 0; i < total_clientes; i++){
        fwrite(&clientes[i], sizeof(clientes[i]), 1, f);
      }
  close(f, cliente);
  return resposta;
}

//objetivo: Recuperar os cadastros dos clientes para depois chamar a funcao na biblioteca de cliente responsavel por ordenar-los
//parametros: Sem parametros
//retorno: sem retorno
void _ordena_CLIENTE()
{
  char cliente[] = {"file/cliente.dat"};
  FILE* f;

  int i;
  _CLIENTE clientes[total_clientes];
  //Recuperação de todos os cadastros do sistema
  f = open(cliente,"rb");
      fseek(f, 0, SEEK_SET);
      for(i = 0; i < total_clientes; i++){
        fread(&clientes[i], sizeof(clientes[i]), 1, f);
      }
      //Chamada a função responsavel pela ordenação
    ordena_CLIENTE(clientes,total_clientes);
  close(f, cliente);

  //Escrevendo o novo conjunto de informações no sistema
  f = open(cliente,"wb");
      for(i = 0; i < total_clientes; i++){
        fwrite(&clientes[i], sizeof(clientes[i]), 1, f);
      }
  close(f, cliente);
}

//objetivo: Recuperar os cadastros dos clientes do arquivo e exibi-los na tela
//parametros: O endereço do arquivo
//retorno: sem retorno
void _exibi_CLIENTE(FILE* f)
{
  int i;
  _CLIENTE clientes[total_clientes];
      fseek(f, 0, SEEK_SET);
      for(i = 0; i < total_clientes; i++){
        fread(&clientes[i], sizeof(clientes[i]), 1, f);
      }
    //Chamada a função responsavel em mostrar os clientes cadastrados no sistema
    exibi_CLIENTE(clientes,0 , total_clientes, 0);
}

//objetivo: Recuperar os cadastros de clientes no arquivo e depois os ordena
//parametros: O endereço do arquivo
//retorno: sem retorno
void _ordenaNomeSalario_CLIENTE()
{
  char cliente[] = {"file/cliente.dat"};
  FILE* f;
  int i;
  _CLIENTE clientes[total_clientes];
  //Abre o arquivo e pega seus registros
  f = open(cliente,"rb");
      fseek(f, 0, SEEK_SET);
      for(i = 0; i < total_clientes; i++){
        fread(&clientes[i], sizeof(clientes[i]), 1, f);
      }
    //Chama a função que ordena eles por nome
    ordenaNomeSalario_CLIENTE(clientes, total_clientes);
  close(f, cliente);
  //Mostra os dados apos a ordenação
  exibi_CLIENTE(clientes,0 , total_clientes, 0);

  //Grava os dados ordenados no arquivo
    f = open(cliente,"wb");
        for(i = 0; i < total_clientes; i++){
          fwrite(&clientes[i], sizeof(clientes[i]), 1, f);
        }
    close(f, cliente);
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
                if(total_clientes && total_carros){
                  insereVenda_CLIENTE();
                }else{
                  printf("\n\n\t\033[31mDeve ao menos um cliente e um carro para fazer uma venda!\033[m\n\n");
                }
              break;
        case 'b':
        case 'B':
                if(total_vendas){
                    _excluir_VENDA();
                }else{
                  printf("\n\n\t\033[31mNao existe vendas para serem excluidas!\033[m\n\n");
                }
              break;
        case 'c':
        case 'C':
                if(total_vendas){
                    _listagemFabricante();
                }else{
                  printf("\n\n\t\033[31mNao existe vendas para serem listadas!\033[m\n\n");
                }
              break;
        case 'd':
        case 'D':
                if(total_vendas){
                    _listagemModelo();
                }else{
                  printf("\n\n\t\033[31mNao existe vendas para serem listadas!\033[m\n\n");
                }
              break;
        case 'e':
        case 'E':
                if(total_vendas){
                    totalVendas();
                }else{
                  printf("\n\n\t\033[31mNenhum carro vendido ate o momento!\033[m\n\n");
                }
              break;
        case 'f':
        case 'F':
                if(total_vendas){
                    lucroGeral();
                }else{
                  printf("\n\n\t\033[31mNenhum carro vendido ate o momento!\033[m\n\n");
                }
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

//objetivo: Inserir uma venda no sistema
//parametros: Sem parametros
//retorno: Sem retorno
void insereVenda_CLIENTE()
{
  int i;

  _CARRO carros[total_carros];
  _CLIENTE clientes[total_clientes];

  char carro[] = {"file/carro.dat"};
  char cliente[] = {"file/cliente.dat"};
  FILE* fCarro;
  FILE* fCliente;

  //Recupera todos os carros cadastrados no arquivo
  fCarro = open(carro, "rb");
    fseek(fCarro, 0, SEEK_SET);
    for(i = 0; i < total_carros; i++){
      fread(&carros[i], sizeof(carros[i]), 1, fCarro );
    }
  close(fCarro, carro);

  //Recupera todos os clientes cadastrados no arquivo
  fCliente = open(cliente, "rb");
      //Exibe todos os clientes cadatrados no sistema
      _exibi_CLIENTE(fCliente);
    fseek(fCliente, 0, SEEK_SET);
    for(i = 0; i < total_clientes; i++){
      fread(&clientes[i], sizeof(clientes[i]), 1, fCliente );
    }
  close(fCliente, cliente);

  //Chama a funcao respondavel por inserir o cliente no sistema, na biblioteca "vendas"
   if( insereVenda(carros, clientes, total_clientes, total_carros, &TOTAL_VENDAS) ){
      //Se ouve sucesso na inclusão incrementamos a variavel que contem o total de vendas
      total_vendas++;
      //Registramos alterações feitas nos registros dos carros e dos clientes
     fCarro = open(carro, "wb");
       for(i = 0; i < total_carros; i++){
         fwrite(&carros[i], sizeof(carros[i]), 1, fCarro );
       }
     close(fCarro, carro);

     fCliente = open(cliente, "wb");
       for(i = 0; i < total_clientes; i++){
         fwrite(&clientes[i], sizeof(clientes[i]), 1, fCliente );
       }
     close(fCliente, cliente);
   }

}

//objetivo: Excluir uma venda do cadastros
//parametros: Sem parametro
//retorno: Sem retorno
void _excluir_VENDA()
{
  int i;

  _CARRO carros[total_carros];
  _CLIENTE clientes[total_clientes];
  _VENDA vendas[total_vendas];

  char carro[] = {"file/carro.dat"};
  char cliente[] = {"file/cliente.dat"};
  char venda[] = {"file/venda.dat"};
  FILE* fCarro;
  FILE* fCliente;
  FILE* fVenda;
  //Recuperamos os cadastros dos carros
  fCarro = open(carro, "rb");
    fseek(fCarro, 0, SEEK_SET);
    for(i = 0; i < total_carros; i++){
      fread(&carros[i], sizeof(carros[i]), 1, fCarro );
    }
  close(fCarro, carro);

  //Recuperamos os cadatros dos clientes
  fCliente = open(cliente, "rb");
    fseek(fCliente, 0, SEEK_SET);
    for(i = 0; i < total_clientes; i++){
      fread(&clientes[i], sizeof(clientes[i]), 1, fCliente );
    }
  close(fCliente, cliente);

  //Recuperamos os cadastros das vendas
  fVenda = open(venda, "rb");
    fseek(fCliente, 0, SEEK_SET);
    for(i = 0; i < total_vendas; i++){
      fread(&vendas[i], sizeof(vendas[i]), 1, fVenda );
    }
  close(fVenda, venda);

  //Chamamos a função respondavel em excluir um venda
  if( excluir_VENDA(vendas, carros, clientes, total_vendas, total_clientes, total_carros, &TOTAL_VENDAS) ){

      //Caso exista sucesso na exclusão escrevemos as alterações feiras nos respectivos arquivos e a decrementação de uma venda a menos

    total_vendas--;
    //Salvando alterações no arquivos dos carros
    fCarro = open(carro, "wb");
      for(i = 0; i < total_carros; i++){
        fwrite(&carros[i], sizeof(carros[i]), 1, fCarro );
      }
    close(fCarro, carro);
    //Salvando alterações no arquivos dos clientes
    fCliente = open(cliente, "wb");
      for(i = 0; i < total_clientes; i++){
        fwrite(&clientes[i], sizeof(clientes[i]), 1, fCliente );
      }
    close(fCliente, cliente);
    //Salvando alterações no arquivos das vendas
    fVenda = open(venda, "wb");
      for(i = 0; i < total_vendas; i++){
        fwrite(&vendas[i], sizeof(vendas[i]), 1, fVenda );
      }
    close(fVenda, venda);

    printf("\n\nExclusão concluida com sucesso\n\n");

  }
}

//objetivo: Auxiliar a listagem da venda de um carro para um determinado fabricante
//parametros: Sem parametro
//retorno: Sem retorno
void _listagemFabricante()
{
  int i;

  _CARRO carros[total_carros];
  _CLIENTE clientes[total_clientes];
  _VENDA vendas[total_vendas];

  char carro[] = {"file/carro.dat"};
  char cliente[] = {"file/cliente.dat"};
  char venda[] = {"file/venda.dat"};
  FILE* fCarro;
  FILE* fCliente;
  FILE* fVenda;
  //Recupera os carros
  fCarro = open(carro, "rb");
    fseek(fCarro, 0, SEEK_SET);
    for(i = 0; i < total_carros; i++){
      fread(&carros[i], sizeof(carros[i]), 1, fCarro );
    }
  close(fCarro, carro);
  //Recupera os clientes
  fCliente = open(cliente, "rb");
    fseek(fCliente, 0, SEEK_SET);
    for(i = 0; i < total_clientes; i++){
      fread(&clientes[i], sizeof(clientes[i]), 1, fCliente );
    }
  close(fCliente, cliente);
  //Recupera as vendas
  fVenda = open(venda, "rb");
    fseek(fCliente, 0, SEEK_SET);
    for(i = 0; i < total_vendas; i++){
      fread(&vendas[i], sizeof(vendas[i]), 1, fVenda );
    }
  close(fVenda, venda);
  //Chama a função responsavel por mostrar a listagem
  listaFabricante(vendas, carros, clientes, total_vendas, total_clientes, total_carros);
}


//objetivo: Auxiliar a listagem da venda de um carro para um determinado modelo
//parametros: Sem parametro
//retorno: Sem retorno
void _listagemModelo()
{
  int i;

  _CARRO carros[total_carros];
  _CLIENTE clientes[total_clientes];
  _VENDA vendas[total_vendas];

  char carro[] = {"file/carro.dat"};
  char cliente[] = {"file/cliente.dat"};
  char venda[] = {"file/venda.dat"};
  FILE* fCarro;
  FILE* fCliente;
  FILE* fVenda;
  //Recupera os carros
  fCarro = open(carro, "rb");
    fseek(fCarro, 0, SEEK_SET);
    for(i = 0; i < total_carros; i++){
      fread(&carros[i], sizeof(carros[i]), 1, fCarro );
    }
  close(fCarro, carro);
  //Recupera os clientes
  fCliente = open(cliente, "rb");
    fseek(fCliente, 0, SEEK_SET);
    for(i = 0; i < total_clientes; i++){
      fread(&clientes[i], sizeof(clientes[i]), 1, fCliente );
    }
  close(fCliente, cliente);
  //Recupera as vendas
  fVenda = open(venda, "rb");
    fseek(fCliente, 0, SEEK_SET);
    for(i = 0; i < total_vendas; i++){
      fread(&vendas[i], sizeof(vendas[i]), 1, fVenda );
    }
  close(fVenda, venda);
  //Chama a função responsavel em lista os carros por modelo
  listaModelo(vendas, carros, clientes, total_vendas, total_clientes, total_carros);
}


//objetivo: AApresenta o relatorio de quantas vendas e o todas das vendas no presente momento
//parametros: Sem parametro
//retorno: Sem retorno
void totalVendas()
{
  printf("\n\n=-==-==-==-==-==-==-==-==-RELATORIO DE VENDAS==-==-==-==-==-==-==-==-==-=\n");
  printf("QUANTIDADE DE CARROS VENDIDOS ATE O MOMENTO: %d\n", total_vendas);
  printf("VALOR TOTAL BRUTO DOS CARROS VENDIDOS: R$ %.2f\n",TOTAL_VENDAS);
}

//objetivo: Faz o calculo do lucro usando a relação do que ja tem em caixa com o total de dispezas informado
//parametros: Sem parametro
//retorno: Sem retorno
void lucroGeral()
{
  float dispesas;
  printf("\n\n=-==-==-==-==-==-==-==-==-LUCRO GERAL COM AS VENDAS==-==-==-==-==-==-==-==-==-=\n");
  printf("Seu ganho bruto ate o momento eh R$ %.2f\n", TOTAL_VENDAS);
  printf("Qual o valor total de suas despesas? ");
  do{
    scanf("%f", &dispesas);
    if(dispesas < 0)
        printf("\n\n\t\033[31mO valor de dispesas deve ser maior ou igual a ZERO!\033[m\n");
        printf("--> ");
  }while(dispesas < 0);
  printf("Seu lucro total eh de R$ %.2f\n", TOTAL_VENDAS - dispesas);

}
