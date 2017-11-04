#include "cpf.h"
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
