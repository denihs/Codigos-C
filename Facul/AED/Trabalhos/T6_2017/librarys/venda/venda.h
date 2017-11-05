#ifndef VENDA_H
#define VENDA_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct VENDA {
  char cpf_venda[15];
  char placa_venda[9];
};
typedef struct VENDA _VENDA;

#include "../carro/carro.h"
#include "../cliente/cliente.h"

FILE* open_VENDA(char* nome_arq, char* c);
void close_VENDA( FILE* f, char* nome_arq );

int insereVenda( _CARRO* carro, _CLIENTE* cliente, int TOT_CLIENTE, int TOT_CARROS, float* valor);
int excluir_VENDA(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS, float* valor);

void listaFabricante(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente, int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS);
void listagenFabricante(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente, int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS,int escolha);

void listaModelo(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS);
void modeloPuma(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS);
void modeloPeugeot(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS);
void modeloRenault(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS);
void modeloNissan(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS);
void modeloFiat(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS);
void modeloFord(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS);
void modeloVolkswagen(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS);
void modeloChevrolet(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS);

void listagenModelo(_VENDA* venda, _CARRO* carro, _CLIENTE* cliente,int TOT_VENDAS, int TOT_CLIENTE, int TOT_CARROS,int fabricante,int escolha);

#endif
