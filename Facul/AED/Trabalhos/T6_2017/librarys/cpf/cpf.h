#ifndef CPF_LIBRARY
#define CPF_LIBRARY

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*-----------------------VALIDAÇÃO DE C-----------------------------*/
    int cpfValidoP(char* cpf);//Verifica se o CPF é valido, passando ele ja formatado com os pontos e traços
    int cpfValido(char* cpf);//Verifica se um cpf é valido

/*-----------------------GERAR CPF---------------------------------*/
    void gerarCpf(char *cpf);//Ira colocar no cpf passado um cpf valido
    char geraNumero();//Gera os numeros do CPF
    void obtem_primeiro_digito_verificador(char *cpf);
    void obtem_segundo_digito_verificador(char* cpf);

/*-----------------------PONTUAÇÃO DE CPF---------------------------------*/
    void insere_pontuacao_cpf(char *cpfTemp,char* cpfMain);//Recebe um vetor com um cpf e um vetor com espaço a mais para a pontuação


#endif
