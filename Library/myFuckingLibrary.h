#include <stdio.h>
#include <string.h>

#ifndef CPF_LIBRARY
#define CPF_LIBRARY


/*-----------------------VALIDAÇÃO DE C-----------------------------*/
    int cpfValidoP(char* cpf);//Verifica se o CPF é valido, passando ele ja formatado com os pontos e traços
    int cpfValido(char* cpf);//Verifica se um cpf é valido

/*-----------------------GERAR CPF---------------------------------*/
    void gerarCpf(char *cpf);//Ira colocar no cpf passado um cpf valido
    char geraNumero();//Gera os numeros do CPF
    void obtem_primeiro_digito_verificador(char *cpf);//O nome ja sujere
    void obtem_segundo_digito_verificador(char* cpf);

/*-----------------------PONTUAÇÃO DE CPF---------------------------------*/
    void insere_pontuacao_cpf(char *cpfTemp,char* cpfMain);//Recebe um vetor com um cpf e um vetor com espaço a mais para a pontuação

/*-----------------------EXTENSO DE UM VALOR---------------------------------*/

          /*POR HORA FUNCIONA APENAS PARA VALORES ABAIXO DE 200 MIL*/

    int contAlgarismo(char* valor);//Conta quantos elementos existem em uma string antes do '\0'
    int Char_to_Int(char* valor, int elementos);//Transforma o valor de um numero em uma string para inteiro
    void Extenso(char* valor,int DinheiroOuCedula);//Recebe um valor em String e retorna o valor por extenso
#endif
