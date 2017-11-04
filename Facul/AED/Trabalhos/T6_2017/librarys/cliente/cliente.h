#ifndef CLIENTE_H
#define CLIENTE_H

#include "../registros/registros.h"
#include "../cpf/cpf.h"

void insereCliente(_CLIENTE*  cliente);
void nome(_CLIENTE* cliente);
void cpf(char* cpf);

void endereco(_CLIENTE* cliente);
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

#endif
