#include "myFuckingLibrary.h"
#define TAM_CPF_TEMP 12
#define TAM_CPF 15

//objetivo: Verifica se o CPF é valido, passando ele ja formatado com os pontos e traços
//parametros: O cpf inserido pelo usuario
//retorno: 1 se cpf e valido ou 0 se cpf nao e valido
int cpfValidoP(char* cpf)
{
  int digito,soma=0,i,j=0,igualdade = 0;;
  char cpfTemp[TAM_CPF_TEMP];

//Passamos apenas os numeros do CPF digitado pelo usuario para um 'cpf temporario'
      for(i=0;i<TAM_CPF-1;i++){
          if(i != 3 && i != 7 && i != 11)
          {
              cpfTemp[j] = cpf[i];
              j++;
          }
      }
/*Nesta função abaixo sera feita a verificação termo a termo,
 *para que não exista um CPF com todos os termos iguais*/
		 for(i=0;i<strlen(cpfTemp);i++){
				if(cpfTemp[i]==cpfTemp[0]){
					igualdade++;
				}
			}
      if(igualdade==11){ return 0; }
//Determinação do primeiro digito e o verifica com o digitado pelo usuario
     j = 0;
     for(i=10;i>1;i--){
         soma += i*(cpfTemp[j]-48);
         j++;}
     soma %= 11;
     if(soma<2){
         digito = 0;
     }else{
         digito = 11 - soma;
     }
     if(digito != cpfTemp[9]-48){ return 0; }
//Determinação do segundo digito e o verifica com o digitado pelo usuario
     soma=0,j=0;
     for(i=11;i>1;i--){
         soma += i*(cpfTemp[j]-48);
         j++;}
     soma %= 11;
     if(soma<2){
         digito = 0;
     }else{
         digito = 11 - soma;
     }
     if(digito != cpfTemp[10]-48){ return 0; }

     return 1;
}

//objetivo: Verifica se o CPF é valido, sem a formatação
//parametros: O cpf inserido pelo usuario
//retorno: 1 se cpf e valido ou 0 se cpf nao e valido
int cpfValido(char* cpf)
{
  int digito,soma=0,i,j=0,igualdade = 0;;

/*Nesta função abaixo sera feita a verificação termo a termo,
 *para que não exista um CPF com todos os termos iguais*/
		 for(i=0;i<strlen(cpf);i++){
				if(cpf[i]==cpf[0]){
					igualdade++;
				}
			}
      if(igualdade==11){ return 0; }
//Determinação do primeiro digito e o verifica com o digitado pelo usuario
     j = 0;
     for(i=10;i>1;i--){
         soma += i*(cpf[j]-48);
         j++;}
     soma %= 11;
     if(soma<2){
         digito = 0;
     }else{
         digito = 11 - soma;
     }
     if(digito != cpf[9]-48){ return 0; }
//Determinação do segundo digito e o verifica com o digitado pelo usuario
     soma=0,j=0;
     for(i=11;i>1;i--){
         soma += i*(cpf[j]-48);
         j++;}
     soma %= 11;
     if(soma<2){
         digito = 0;
     }else{
         digito = 11 - soma;
     }
     if(digito != cpf[10]-48){ return 0; }

     return 1;
}

//objetivo:gera aleatoriamente um cpf valido no formato 99999999999
//parametros: cpf:o cpf onde sera armazenado o cpf valido
//retorno: nenhum
void gerarCpf(char *cpf)
{
    int i,
        clone,//Variavel que é incrementada toda vez que temos um numero igual ao anterior
        sair=1;
      do{
        clone=0;
        for(i=0;i<9;i++){
          cpf[i]=geraNumero();
              if(cpf[i]==cpf[i-1])
              {
                clone++;
              }
        }
        if(clone!=8){sair=0;}
        //Enquanto os ele gerar os 8 valores iguais o programa ficara em looping
        //dificultando que tenhamos um cpf com todos os valores iguais

        obtem_primeiro_digito_verificador(cpf);//Obtem o 10° digito
        obtem_segundo_digito_verificador(cpf);//Obtem o 11° digito
      }while(sair);
}

//objetivo:escolhe dentre os numeros ('0'..'9') uma numero aleatoriamente
//parametros: nenhum
//retorno:o numero
char geraNumero() {
    int i;
    char numeros[] = { '0','1','2','3','4','5','6','7','8','9'};

    i=rand()%10;
    return(numeros[i]);
}


//objetivo:calcula o primeiro digito verificador de um cpf no formato 999999999
//parametros: cpf:o cpf sem os digitos verificadores
//retorno: sem retorno
void obtem_primeiro_digito_verificador(char *cpf) {
   int digito,soma=0,i,j=0;
      for(i=10;i>1;i--){
          soma += i*(cpf[j]-48);//Subtrai o valor 48 do caracter para fazer a conversão do caracter para inteiro
          j++;
      }
      soma %= 11;
      if(soma<2){//Determinação do primeiro digito
          digito = 0;
      }else{
          digito = 11 - soma;
      }
      //Soma 48 para transforma o inteiro em caracter novamente
      cpf[9] = digito+48;
}
//objetivo:calcula o segundo digito verificador de um cpf no formato 999999999
//parametros: cpf:o cpf sem os digitos verificadores
//retorno: o calculo do segundo digito verificador
void obtem_segundo_digito_verificador(char* cpf) {
  int digito,soma=0,i,j=0;
     for(i=11;i>1;i--){
         soma += i*(cpf[j]-48);//Subtrai o valor 48 do caracter para fazer a conversão do caracter para inteiro
         j++;
     }
     soma %= 11;
     if(soma<2){//Determinação do primeiro digito
         digito = 0;
     }else{
         digito = 11 - soma;
     }
       //Soma 48 para transforma o inteiro em caracter novamente
     cpf[10] = digito+48;
}

//objetivo:insere pontuacoes '.' e '- ' em um cpf
//parametros: cpf_origem:o cpf recebido no format 99999999999
//            cpf_destino:o cpf com as pontuacoes inseridas no formato 999.999.999-99
//Retorno:  nenhum
void insere_pontuacao_cpf(char *cpfTemp,char* cpfMain) {
    int i=0, j;

    for(j=0;j<TAM_CPF;j++){
        if(j!=3 && j!=7 && j!=11 )
        {//Quando o 'j' é diferente de 3, 7 e 11 colocamos os numeros do vetor 'cpfTemp' em seus intervalos
           cpfMain[j] = cpfTemp[i];
          i++;
        }else{
          if(j==3 || j==7)
          {//Se 'j' for 3 ou 7 colocamos um ponto (.) na casa
            cpfMain[j] = '.';
          }else{//Na casa 11 colocamos o traço
            cpfMain[j] = '-';
          }
        }
    }
}

//objetivo: Conta quantos elementos tem um numero passado por uma string
//parametros:  Uma string
//retorno: Retona a quantidade de elementos
int contAlgarismo(char* valor)
{
    int elementos=0,i;
    for(i=0;i<strlen(valor);i++)
    {
      elementos++;
    }
    return (elementos);
}

//objetivo: Passa o valor de que uma String para inteiro
//parametros:  Uma string
//retorno: Retona o valor em forma de inteiro
int Char_to_Int(char* valor, int elementos)
{
  int soma=0,i,multiplo;

  switch (elementos) {//Verificar qual o tamanho de algarismos do numero passado
    case 6:
          multiplo = 100000;
          break;
    case 5:
          multiplo = 10000;
          break;
    case 4:
          multiplo = 1000;
          break;
    case 3:
          multiplo = 100;
          break;
    case 2:
          multiplo = 10;
          break;
    case 1:
          multiplo = 1;
          break;
  }

    for(i=0;i<elementos;i++)
    {//Usa algarismo a algarismo fazendo somas e divisões sucetivas para obter o valor
      soma += (valor[i]-48)*multiplo;
      multiplo /= 10;
    }
    return soma;
}



//objetivo: Quando chamado imprime o valor de um numero em extenso
//parametros:  Uma variavel com o valor e um valor (0 ou  1) que indentifica se esta sendo solicitado o extenso de dinheiro ou de cedulas
//retorno: sem retorno
void Extenso(char* valor,int DinheiroOuCedula)
{
  int valorSaque,dig,elementos,i=0;
    /*Valor que podem ser impressos*/
  char UM_NOVE[9][9] = {{"UM"},{"DOIS"},{"TRES"},{"QUATRO"},{"CINCO"},{"SEIS"},{"SETE"},{"OITO"},{"NOVE"}};
  char C_UM_NOVE[9][9] = {{"UMA"},{"DUAS"},{"TRES"},{"QUATRO"},{"CINCO"},{"SEIS"},{"SETE"},{"OITO"},{"NOVE"}};

  char ONZE_DEZENOVE[9][15] = {{"ONZE"},{"DOZE"},{"TREZE"},{"QUATORZE"},{"QUINZE"},{"DEZESSEIS"},{"DEZESSETE"},{"DEZOITO"},{"DEZENOVE"}};

  char DEZ_NOVENTA[9][15] = {{"DEZ"},{"VINTE"},{"TRINTA"},{"QUARENTA"},{"CINQUENTA"},{"SESSENTA"},{"SETENTA"},{"OITENTA"},{"NOVENTA"}};

  char CEM_NOVECENTOS[9][15] = {{"CENTO"},{"DUZENTOS"},{"TREZENTOS"},{"QUATROCENTOS"},{"QUINHETOS"},{"SEISCENTOS"},{"SETECENTOS"},{"OITOCENTOS"},{"NOVECENTOS"}};
  char C_CEM_NOVECENTOS[9][15] = {{"CENTO"},{"DUZENTAS"},{"TREZENTAS"},{"QUATROCENTAS"},{"QUINHETAS"},{"SEISCENTAS"},{"SETECENTAS"},{"OITOCENTAS"},{"NOVECENTAS"}};

  char CONECTIVOS[7][11] = {{"CENTO"},{" E "},{" MIL "},{"REAIS"},{"CEDULAS"},{"REAL"},{"CEDULA"}};

  printf("(");
  elementos = contAlgarismo(valor);//Contamos quantos elementos tem o valor
  valorSaque = Char_to_Int(valor,elementos);//Depois obtemos  o inteiro deste valor
/*
  A logica toda toda por tras do codigo abaixo é simples:

    Supondo que o valor passado pela string seja 45812, no vetor ele esta da seguinte forma: |'4'|'5'|'8'|'1'|'2'|'\0'|'\0'| (Ja que todo vetor passado para cá tem 7 posições)
  Como acima foram pegos a quantidade de elementos e o valor de saque por inteiro, ele sabera qua na primeira interação para este valor ele devera entrar no case 5 do switch abaixo
  então ele verifica se o valor inteiro dividido por 10 mil esta entre 1 e 2, se estiver significa que só pode ser um valor entre 11 e 19 mil, nesse caso o teste dará falso,
  então seu proximo passo é verificar se o numero tem um valor que seja inteiro como: 10 mil reias, 20 mil reais etc. neste tambem dará falso então é verficado se o valor é do tipo
  45 mil e alguma coisa ou 40 Mil e alguma coisa, em nosso caso dara a primeira opção, então ele pega o valor do numero na casa, neste caso seria valor[0], multiplica ele por 10 mil
  e em seguida decrementa ele do valor inicial e no fim ele decrementa o numero de elementos e troca as proximas posições que serão verificadas no vetor.

    A curto modo é basicamente isso, que ele faz até sair do laço, existe alem desse testes sitados, teste para saber se o sistema que gramatica para as cedulas ou para o  dinheiro
  ja que existe umas pequenas variações e isto é checado em varias partes do algoritmo com operadores ternarios
*/
  if(valorSaque){//Se o valor for diferente de ZERO entramos no laço
      do{
          switch (elementos) {
            case 6://Caso o valor tenha seis elementos significa que ele é maior ou igual a 100 mil
                      if(valorSaque/100000.00 == 1.00)
                      {
                        printf("CEM MIL %s", DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);//Teste que verifica foi solicitado dinheiro ou cedula
                        elementos=0;
                      }
                      else if( valor[1] != '0' || valor[2] != '0')
                            {
                              printf("CENTO E ");
                            }
                      else{
                              printf("CEM MIL E ");
                      }
                      valorSaque -= 100000;
                  break;
            case 5://Caso o valor tenha cinco elementos significa que ele é maior ou igual a 10 mil
                    if(valorSaque/10000>0){
                        //Verifica valores entre 11 e 19  MIL
                        if(valorSaque/10000.00>1 && valorSaque/10000.00<2)
                        {
                          if(valorSaque/1000.00 == (float)(valor[i+1]-48)+10 )
                          {
                            printf("%s MIL %s",ONZE_DEZENOVE[(valor[i+1]-48)-1], DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                            elementos=0;
                            valorSaque -= 10000 + 1000*(valor[i+1]-48);
                          }else{
                            printf("%s MIL E ",ONZE_DEZENOVE[(valor[i+1]-48)-1]);
                            valorSaque -= (10000 + 1000*(valor[i+1]-48));
                          }
                        }
                        //Verifica valores entre 10 e 90  MIL
                        else  if(valorSaque/10000.00==(float)valor[i]-48)
                        {
                          printf("%s MIL %s",DEZ_NOVENTA[(valor[i]-48)-1], DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                          valorSaque -= 10000 * (valor[i]-48);
                        }
                        else if( valor[i+1] == '0')
                              {
                                printf("%s MIL E ",DEZ_NOVENTA[(valor[i]-48)-1]);
                                valorSaque -= 10000 * (valor[i]-48);
                              }
                        else if( valor[i] != '0'){
                                printf("%s E ",DEZ_NOVENTA[(valor[i]-48)-1]);
                                valorSaque -= 10000 * (valor[i]-48);
                        }
                    }
                  break;
            case 4:
                    if(valorSaque/1000>0){
                        if(valorSaque/1000.00==(float)valor[i]-48)
                        {
                          printf("%s MIL %s",DinheiroOuCedula ? UM_NOVE[(valor[i]-48)-1]:C_UM_NOVE[(valor[i]-48)-1],
                                             DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                          valorSaque -= 1000 * (valor[i]-48);
                        }
                        else if(valorSaque/1000>0){
                          printf("%s MIL E ",DinheiroOuCedula ? UM_NOVE[(valor[i]-48)-1]:C_UM_NOVE[(valor[i]-48)-1]);
                          valorSaque -= 1000 * (valor[i]-48);
                        }
                    }
                  break;
            case 3:
                    if(valorSaque/100>0){
                        if(valorSaque/100.00==1.00)
                        {
                          printf("CEM %s",DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                          valorSaque -= 100 * (valor[i]-48);
                        }
                        else if(valorSaque/100.00== (float)(valor[i]-48))
                        {
                          printf("%s %s",DinheiroOuCedula ? CEM_NOVECENTOS[(valor[i]-48)-1] : C_CEM_NOVECENTOS[(valor[i]-48)-1],
                                         DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                          valorSaque -= 100 * (valor[i]-48);
                        }
                        else if(valorSaque/100>0){
                          printf("%s E ",DinheiroOuCedula ? CEM_NOVECENTOS[(valor[i]-48)-1] : C_CEM_NOVECENTOS[(valor[i]-48)-1]);
                          valorSaque -= 100 * (valor[i]-48);
                        }
                    }
                  break;
            case 2:
                    if(valorSaque/10>0){
                        if(valorSaque/10.00>1 && valorSaque/10.00<2)
                        {
                            printf("%s %s",ONZE_DEZENOVE[(valor[i+1]-48)-1], DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                            elementos=0;
                        }
                        else  if(valorSaque/10.00 == (float)(valor[i]-48))
                        {
                          printf("%s %s",DEZ_NOVENTA[(valor[i]-48)-1],DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                        }
                        else if(valorSaque/10>0)
                        {
                          printf("%s E ",DEZ_NOVENTA[(valor[i]-48)-1]);
                          valorSaque -= 100* (valor[i]-48);
                        }
                    }
                  break;
            case 1:
                        if(!i && valor[i]-48 == 1){
                            printf("%s %s",DinheiroOuCedula?UM_NOVE[(valor[i]-48)-1]:C_UM_NOVE[(valor[i]-48)-1],
                                            DinheiroOuCedula ? CONECTIVOS[5] : CONECTIVOS[6]);
                        }else{
                          printf("%s %s",DinheiroOuCedula?UM_NOVE[(valor[i]-48)-1]:C_UM_NOVE[(valor[i]-48)-1],
                                          DinheiroOuCedula ? CONECTIVOS[3] : CONECTIVOS[4]);
                          elementos=0;
                        }
                  break;
          }
          elementos--;
          i++;
      }while(elementos>0);
    }else{//Caso o valor passo sera zero
      printf(" ZERADO ");
    }
  printf(")");
}
