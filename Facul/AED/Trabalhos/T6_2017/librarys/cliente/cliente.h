#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TAM 50

#include "../cpf/cpf.h"

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
  int quantCelular;
  char telefone[14]; //99 99999-9999
};

struct CLIENTE {
  int status;
 char nome[TAM];
 char cpf[15]; //999.999.999-99
 struct ENDERECO endereco;
 struct TELEFONE residencial;
 struct TELEFONE celular[5];
 float renda_mensal;
};
typedef struct CLIENTE _CLIENTE;

void insereCliente(_CLIENTE*  cliente);
void nome(_CLIENTE* cliente);
void cpf(char* cpf);

void estado(_CLIENTE* cliente);
void cidade(_CLIENTE* cliente, int x);

void bairro_MS(_CLIENTE* cliente, int x);
void rua_MS(_CLIENTE* cliente, int x, int y);
void cep_MS(_CLIENTE* cliente, int x, int y);

void bairro_SP(_CLIENTE* cliente, int x);
void rua_SP(_CLIENTE* cliente, int x, int y);
void cep_SP(_CLIENTE* cliente, int x, int y);

void bairro_RJ(_CLIENTE* cliente, int x);
void rua_RJ(_CLIENTE* cliente, int x, int y);
void cep_RJ(_CLIENTE* cliente, int x, int y);

void bairro_MT(_CLIENTE* cliente, int x);
void rua_MT(_CLIENTE* cliente, int x, int y);
void cep_MT(_CLIENTE* cliente, int x, int y);

void bairro_PR(_CLIENTE* cliente, int x);
void rua_PR(_CLIENTE* cliente, int x, int y);
void cep_PR(_CLIENTE* cliente, int x, int y);

void numero(_CLIENTE* cliente);

void telResidencial(_CLIENTE* cliente, int Est);
void _telResidencial(_CLIENTE* cliente);

void telCelular(_CLIENTE* cliente, int Est);
void _telCelular(_CLIENTE* cliente, int x);
void salario(_CLIENTE* cliente);

void exibi_CLIENTE(_CLIENTE* cliente,int inicio, int TOT_CLIENTE, int path);
int excluir_CLIENTE(_CLIENTE*  cliente, int TOT_CLIENTE);
void ordena_CLIENTE(_CLIENTE* cliente,int TOT_CLIENTE);
void ordenaNomeSalario_CLIENTE(_CLIENTE* cliente,int TOT_CLIENTE);
#endif
