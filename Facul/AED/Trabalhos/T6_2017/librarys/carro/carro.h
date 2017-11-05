#ifndef CARRO_H
#define CARRO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TAM 50

struct CARRO {
 int status;
 char placa[9]; //AAA-1234
 char modelo[TAM]; //gol, celta, palio, ...
 char fabricante[TAM]; //chevrolet, fiat, ...
 int ano_fabricacao; //1980 à 2017
 int ano_modelo; //1980 à 2018
 char combustivel[TAM]; //alcool, gasolina, flex, diesel
 char cor[TAM]; //branca, prata, preta
 int opcional[9]; //ver matriz opcionais
 float preco_compra;
};
typedef struct CARRO _CARRO;


void Insere_Carro(_CARRO* carro);

void fabricante(_CARRO* carro);
void modelo_carro(_CARRO* carro, int rande);
void anoFrabr_anoMod(_CARRO* carro);
void cor(_CARRO* carro);
void combustivel(_CARRO* carro);
void valor_carro(_CARRO* carro);
void placa(_CARRO* carro);
void opcionais(_CARRO* carro);
int sem_repeticao(int* vet,int arg,int x);
void exibi_opcionais(_CARRO* carro);

int exibi(_CARRO* carro,int inicio, int TOT_CARROS, int path);
int excluir(_CARRO* carro, int TOT_CARROS);
void ordena(_CARRO* carro,int TOT_CARROS);
void exibiCarroOpcionais(_CARRO* carro,int* opcao, int qtd ,int TOT_CARROS);
void exibiCarroData(_CARRO* carro,int dataInicial, int dataFinal ,int TOT_CARROS);
#endif
