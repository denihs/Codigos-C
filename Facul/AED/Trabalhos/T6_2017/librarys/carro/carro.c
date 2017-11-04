#include "carro.h"

//objetivo: Inserir carro no registro de cadastro
//parametros: Um vetor que contem os registro dos carros registrados
//retorno: Sem retorno
void Insere_Carro(_CARRO* carro)
{
  int i;
  for(i = 0; i < 9; i++){
    carro->opcional[i] = -1;
  }


  carro->status = 1;
  fabricante(carro);
  anoFrabr_anoMod(carro);
  cor(carro);
  combustivel(carro);
  valor_carro(carro);
  placa(carro);
  opcionais(carro);

}

void fabricante(_CARRO* carro)
{
    int x = rand() % 8;
    char montadora[][TAM] = {"Volkswagen","Chevrolet","Ford","Fiat","Nissan","Renault","Peugeot","Puma"};
    strcpy(carro->fabricante, montadora[x]);
    modelo_carro(carro, x);
}

void modelo_carro(_CARRO* carro, int rande)
{
  char Volkswagen[][TAM] = {"Brasilia", "Fox", "Fusca", "Gol", "Golf","Jetta","Parati","Passat","Saveiro","Karmann Ghia Cabriolét"};
  char Chevrolet[][TAM] = {"Alvorada","D-20","Monza hatch","S10","Omega Suprema","Gran Blazer","Cruze","Opala coupé","Prisma","Blazer"};
  char Ford[][TAM] = {"Belina", "Corcel", "Del Rey ", "Escort conversível", "F-1000", "Fiesta", "Jeep", "Galaxie", "Ka", "Pampa"};
  char Fiat[][TAM] = {"Fiat 147", "City", "Brava", "Bravo", "Doblò", "Fiorino", "Prêmio", "Punto", "Stilo", "Tempra"};
  char Nissan[][TAM] = {"Nissan Frontier", "Nissan Presage", "Nissan 240SX", "Nissan 300ZX ", "Nissan 350Z ", "Nissan 370Z", "Nissan Stagea", "Nissan Serena ", "Nissan Skyline GT-R", "Nissan Stanza"};
  char Renault[][TAM] = {"Captur", "Clio", "Clio Sedan", "Duster", "Duster Oroch", "Logan", "Mégane Grand Tour", "Mégane Sedan", "Sandero", "Scénic"};
  char Peugeot[][TAM] = {"Peugeot 206", "Peugeot 206 SW", "Peugeot 206+", "Peugeot 207 Passion", "Peugeot 207 SW ", "Peugeot 208", "Peugeot 2008", "Peugeot Hoggar","Peugeot 308 Hybride HDi","Peugeot 308 SW Prologue"};
  char Puma[][TAM] = {"GT4R", "Puma P8", "Puma Spyder", "GTE", "GTS", "GTB", "GTB S2", "GTB S3", "GTB S4", "GTC"};

  int x = rand() % 10;
  switch (rande) {
    case 0:
          strcpy(carro->modelo, Volkswagen[x]);
          break;
    case 1:
          strcpy(carro->modelo, Chevrolet[x]);
          break;
    case 2:
          strcpy(carro->modelo, Ford[x]);
          break;
    case 3:
          strcpy(carro->modelo, Fiat[x]);
          break;
    case 4:
          strcpy(carro->modelo, Nissan[x]);
          break;
    case 5:
          strcpy(carro->modelo, Renault[x]);
          break;
    case 6:
          strcpy(carro->modelo, Peugeot[x]);
          break;
    case 7:
          strcpy(carro->modelo, Puma[x]);
          break;
  }
}

void anoFrabr_anoMod(_CARRO* carro)
{
    int x = rand() % 2;
    int anoFrab = 1980 + (rand() % 38);
    carro->ano_fabricacao = anoFrab;
    carro->ano_modelo = anoFrab + x;
}

void cor(_CARRO* carro){
  char palheta[][TAM] = {"Branca", "Preta", "Prata ", "Verde ", "Vermelho", "Azul","Amarelo", "Rosa ", "Marrom Metalico"};
  int x = rand () % 9;
  strcpy( carro->cor, palheta[x] );
}

void combustivel(_CARRO* carro)
{
  char comb[][TAM] = {"Alcool","Gasolina","Flex","Diesel"};
  int x = rand() % 4;
  strcpy( carro->combustivel, comb[x] );
}

void valor_carro(_CARRO* carro)
{
  int x = 5 + (rand() % 46);
  int y = rand() % 10;
  carro->preco_compra = (1000 * x) + (100 * y);
}

void placa(_CARRO* carro)
{
   int i,x;
   char alpha[24] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'W', 'Y', 'Z'};
   char num[10] = {'1','2','3','4','5','6','7','8','9','0'};

   for(i = 0; i < 3; i++){
     x = rand() % 23;
     carro->placa[i] = alpha[x];
   }

   carro->placa[3] = '-';


   for(i = 4; i < 8; i++){
     x = rand() % 9;
     carro->placa[i] = num[x];
   }
   carro->placa[8] = '\0';
}

void opcionais(_CARRO* carro)
{
  int x = rand() % 9, i, y;

  carro->opcional[8] = x;
    if(x){
      for(i = 0; i < x; i++ ){
          y = rand() % 8;
          if( sem_repeticao( carro->opcional, y, i ) ){
            carro->opcional[i] = y;
          }
      }
    }
}

int sem_repeticao(int* vet,int arg,int x)
{
    int i;
    for(i = 0; i < x; i++){
      if(arg == vet[i]){
          return 0;
      }
    }
    return 1;
}

void exibi_opcionais(_CARRO* carro)
{
  char opcionais[][TAM]={ {"4.portas"}, {"cambio.automatico"}, {"vidros.eletricos"}, {"abs"}, {"air.bag"}, {"ar.condicionado"}, {"banco.couro"}, {"sensor.estacionamento"}};
  int quantidade = carro->opcional[8];
  int i;
  if(quantidade){
    for(i = 0; i < quantidade; i++){
      if(carro->opcional[i] != -1)
        printf("\t-%s\n", opcionais[ carro->opcional[i] ]);
    }
  }else{
    printf("\tSem opicionais\n");
  }

}
int excluir(_CARRO*  carro, int TOT_CARROS)
{
  _CARRO tmp;
  int i, verifica = 0, pos;
  char placa[9];
  printf("\n\nInsira a placa do carro que sera excluido (\033[31mFORMATO:\033[m ABC-1234): ");
  __fpurge(stdin);
  fgets(placa,9,stdin);

  for(i = 0; i < TOT_CARROS; i++){
    if( !strcmp( placa, carro[i].placa ) )
    {
        verifica = 1;
        pos = i;
    }
  }

  if( verifica ){
    if(carro[pos].status){
        tmp = carro[TOT_CARROS - 1];
        carro[TOT_CARROS - 1] = carro[pos];
        carro[pos] = tmp;
        printf("\n\n\tCarro excluido com sucesso! \n\n");
        return 1;
      }else{
        printf("\n\n\t\033[31mEste carro não esta disponivel para exclusão pois ja foi vendido.\033[m\n\n");
      }
  }
  else{
    printf("\n\n\t\033[31mNao existe registro da placa informada.\033[m\n\n");
  }
  return 0;
}

void exibi(_CARRO* carro,int inicio, int TOT_CARROS, int path)
{
  int j = 0,i,verifica = 0;

  if(!path){
    printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=- \033[7mCARROS DISPONIVEIS PARA VENDA\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  }

  for(i = inicio; i < TOT_CARROS; i++){
    if( carro[i].status ){
      if(!path){
        printf("\n\n=-=-=-=-=-=-=-=- %d -=-=-=-=-=-=-=-=\n",j+ 1);
      }else{
        printf("\n\n=-=-=-=-=-=-=-=- CARRO INSERIDO -=-=-=-=-=-=-=-=\n");
      }
      printf("* Fabricante:  %s\n",carro[i].fabricante);
      printf("* Modelo:      %s\n", carro[i].modelo);
      printf("* Placa:       %s\n",carro[i].placa);
      printf("* Cor:         %s\n",carro[i].cor);
      printf("* Combustivel: %s\n",carro[i].combustivel);
      printf("* Valor do carro: R$ %.2f\n",carro[i].preco_compra);
      printf("* Ano de fabricacao: %d - Modelo: %d\n",carro[i].ano_fabricacao, carro[i].ano_modelo);
      printf("* Opcionais: \n"); exibi_opcionais(&carro[i]);
      verifica = 1;
      j++;
    }
  }
  if( !verifica )
      printf("\n\n\t\033[31mNao existe carro disponivel para venda.\033[m\n\n");
}

void ordena(_CARRO* carro,int TOT_CARROS)
{
  int count, i;
  _CARRO tmp;
  for(count = 0; count < TOT_CARROS; count++){
    for(i = 1 + count; i < TOT_CARROS; i++){
        if(strcmp(carro[count].fabricante, carro[i].fabricante) > 0){
          tmp = carro[count];
          carro[count] = carro[i];
          carro[i] = tmp;
        }
    }
  }
  for(count = 0; count < TOT_CARROS; count++){
    for(i = 1 + count; i < TOT_CARROS; i++){
        if(!strcmp( carro[count].fabricante, carro[i].fabricante ) ){
          if(strcmp(carro[count].modelo, carro[i].modelo) > 0){
            tmp = carro[count];
            carro[count] = carro[i];
            carro[i] = tmp;
          }
        }else{
          continue;
        }
    }
  }
}

void exibiCarroOpcionais(_CARRO* carro,int* opcao, int qtd ,int TOT_CARROS)
{
  int i,j,x, w = 0, verifica = 0, Qprint = 0, Qops;
  if(qtd){
      for(i = 0; i < TOT_CARROS; i++){

        Qops = carro[i].opcional[8];
        for(x = 0; x < carro[i].opcional[8]; x++){
          if(carro[i].opcional[x] == -1 )
            Qops--;
        }
        if( carro[i].status  && Qops == qtd ){
              for(x = 0; x < qtd; x++){
                for(j = 0; j < carro[i].opcional[8]; j++){
                   if(opcao[x] == carro[i].opcional[j]){
                      verifica++;
                    }
                }
              }
              if( qtd == verifica ){
                 !w ? printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=- \033[7mCARROS DISPONIVEIS PARA VENDA\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-") : 0;
                  printf("\n\n=-=-=-=-=-=-=-=- %d -=-=-=-=-=-=-=-=\n",w+ 1);
                  printf("* Fabricante:  %s\n",carro[i].fabricante);
                  printf("* Modelo:      %s\n", carro[i].modelo);
                  printf("* Placa:       %s\n",carro[i].placa);
                  printf("* Cor:         %s\n",carro[i].cor);
                  printf("* Combustivel: %s\n",carro[i].combustivel);
                  printf("* Valor do carro: R$ %.2f\n",carro[i].preco_compra);
                  printf("* Ano de fabricacao: %d - Modelo: %d\n",carro[i].ano_fabricacao, carro[i].ano_modelo);
                  printf("* Opcionais: \n"); exibi_opcionais(&carro[i]);
                  Qprint = 1;
                  w++;
             }
             verifica = 0;
        }
      }
      if(!Qprint){
        printf("\n\n\t\033[31mNenhum carro disponivel com essas opcoes.\033[m\n\n");
      }
    }
}

void exibiCarroData(_CARRO* carro,int dataInicial, int dataFinal ,int TOT_CARROS)
{
  int i,w=0, verifica = 0;
    for(i = 0; i < TOT_CARROS; i++){
      if(carro[i].ano_fabricacao >= dataInicial && carro[i].ano_fabricacao <= dataFinal ){
        !w ? printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=- \033[7mCARROS DISPONIVEIS PARA VENDA\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-") : 0;
         printf("\n\n=-=-=-=-=-=-=-=- %d -=-=-=-=-=-=-=-=\n",w+ 1);
         printf("* Fabricante:  %s\n",carro[i].fabricante);
         printf("* Modelo:      %s\n", carro[i].modelo);
         printf("* Placa:       %s\n",carro[i].placa);
         printf("* Cor:         %s\n",carro[i].cor);
         printf("* Combustivel: %s\n",carro[i].combustivel);
         printf("* Valor do carro: R$ %.2f\n",carro[i].preco_compra);
         printf("* Ano de fabricacao: %d - Modelo: %d\n",carro[i].ano_fabricacao, carro[i].ano_modelo);
         printf("* Opcionais: \n"); exibi_opcionais(&carro[i]);
         w++;
         verifica =  1;
      }
    }
    if(!verifica){
      printf("\n\n\t\033[31mNenhum carro disponivel na faixa requisitada\033[m\n\n");
    }
}
