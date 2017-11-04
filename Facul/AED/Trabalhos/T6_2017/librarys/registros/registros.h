#ifndef REGISTROS_H
#define REGISTROS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TAM 50


/*-=--=--=--=--=--=--=--=--=-CADASTRO CARRO-=--=--=--=--=--=--=--=--=--=--=-*/
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

#endif
