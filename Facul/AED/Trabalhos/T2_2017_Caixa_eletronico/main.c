/* *Função: Programa com o intuito de simular todo o codigo basico envolvido
            por tras de um caixa eletronico, trazendo funcionalidades como:
            Saque por parte de um cliente ou depositos por parte do gerente
            alem de todo um controle que o gerente tera apenas entrando em
            opções como, valor total de saque desde a abertura do sistema ou
            quantidade de cédulas existentes no caixa, alem de ver o total de
            dinheiro ainda existente depois de um deposito.

   *Autor: Denilson Higino da Silva  | RGM: 36712

   *Data de inicio: 21/05/2017
   *Data de finalização: 08/06/2017
===============================================================================*/


#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include<conio.h>
#include <locale.h>


int main(void){

/*=======================Declaração de variaveis==================================*/

/*-------------Variaveis da navegação do menu-------------*/
int opc1=0;//controle das opcoes do menu principal
int opc2=0;//controle das opcoes do menu gerente
int opc3=0;//controle das opcoes do menu abastecer caixa


/*-------------Variaveis da validação do CPF-------------*/
int Dig1,Dig2,Dig3,Dig4,Dig5,Dig6,//Variaveis que receberam os digitos do CPF
    Dig7,Dig8,Dig9,Dig10,Dig11,      //Variaveis que receberam os digitos do CPF
    soma=0,//Variavel que recebera o somatorio dos digitos do CPF
    DigitoValido1=0,//Variavel que recebe o primero digito do somatoria que sera comparado com o decimo digito do CPF
    DigitoValido2=0;//Variavel que recebe o segundo digito do somatoria que sera comparado com o decimo primero digito do CPF
char Retorno;//Varivel usada apenas para ele a decisão do cliente, mostrando para qual tela ele deseja voltar
int count=0,//Variavel contadora que sera usada em praticamente todos os laços de repetição
    CountDigito;//Variavel contadora para os digitos inseridos

/*----------------------Variaveis do cliente----------------------------------*/
  float Vsaque=0;//Valor do saque do cliente
  int controle=0;//Varieval para controle das divisões
  int inteiro=0; //Variavel que garante que o cliente não exigira moedas ao caixa;
  int SaqueAlto=0;//Variavel que auxliara no os testes condicionais caso o cliente peça uma valor acima de 50 mil reais


/*-------------Variaveis da quantia de dinheiro inserida no caixa-------------*/
float C500=0, C150=0, C50=0, C20=0,//Esta como float, pois se caso o gerente entre com um numero não inteiro, ele ira aceitar mas em seguida mostrara uma mensagem de erro
	C10=0,C5=0, C2=0, C1=0;//Variaveis para a atribução da quantidade de celulas inseridas pelo gerente

int QtdC500=0, QtdC150=0, QtdC50=0, QtdC20=0,
	QtdC10=0, QtdC5=0, QtdC2=0, QtdC1=0;//Variaveis somadoras, responsaveis em controlar a quantidade de cada nota existente no caixa

float Tot500=0,Tot150=0,Tot50=0,Tot20=0,
	  Tot10=0,Tot5=0,Tot2=0,Tot1=0;//Variaveis que recebem o produto da quantidade de celulas que seram inseridas pelo valor de cada célula.

int NotaDisponivel = 1;//Variavel responsavel em verificar se o caixa tem nota disponivel para o valor solicitado

/*---------------------------Variavel que ganhar as quantidades absolutas do caixa---------------------------*/
int QtdTotCed=0;//Quantidade total de cédulas no caixa
float QtdTotSac=0;//Quantidade total de dinheiro sacado do caixa
float QuantTotal=0,//Variavel responsavel por guardar a quantidade de dinheiro depositado
	  QtdTotalExtenso=0;//Variavel de se modificara para mostra a quantidade total de dinheiro no caixa por extenso

/*-------------------Variaveis responsaveis em dar os valores sacados ou depositados por extenso------------*/
float QuantiaDinheiro = 0,//Quantia que recebera as divisões
	  AuxResto=0;//Variavel que recebe o valor decimal da divisão

int Resto = 0,//Variavel que recebe o resto da divisão para entrar nos testes condicionais
	I=0,//Esta variavel vai ser usada dentro de alguns laços de testes condicionais para que o programa não repita varias vezes uma palavra
	Concordancia=0,//Variavel responsavel em fazer ajuste na concordancia verbal de algumas palavras
	AuxInteiro=0,  //Variavel que ira arrendondar a variavel "AuxResto" em alguns trechos do código para evitar futuros problemas.
	VarCount=0;    //Sera usada em um dos testes condicionais para substituir a variavel "Count" em algumas divisões

/*------------------------------------Variavel de AJUSTE--------------------------------------------------*/

/*Existiram alguns problemas da IDE com as divisões, por algum motivo uma variavel float estava recebendo
  0,00000002 a mais após o calcula, ou as vezes a mesmo, fazendo com que certos teste logicos no meio do
  programa falhacem. Então criei essa variavel para se somar a variavel "AUXRESTO" em alguns trechos do
  código, corrigindo desta forma eventuais problemas.*/
float Ajuste=0.00000200;





/*==============================Menú de entradaa=====================================*/
setlocale(LC_ALL,"");
do {
	opc1=0;
	MenuPrin: system("cls");//MenuPrin = Chamada ao menu principal
	printf("\nMENU PRINCIPAL");
	printf("\n\n(1) Saque");
	printf("\n(2) Gerente");
	printf("\n(3) Finalizar");
	printf("\n\nDigite a opção: ");
	scanf("%d",&opc1);
	if((opc1!=1) && (opc1!=2) && (opc1!=3)) {
		printf("\nOpção inválida!\n");
		system("pause");
	}
/*=============================Configurações de saque==========================*/
	else {
		if(opc1==1) {
			printf("\nVocê escolheu SAQUE!\n");
			system("pause");
			ValSaq:Return:system("clear || cls");//Return sendo usado para a função GOTO no caso do usuario digitar o CPF errado em algum momento

				/*Sera mostrado para o cliente quais tipos de notas estão disponiveis no momento
				  para que não exista frustrações caso ele deseje um valor e o caixa não tenho nota
				  para dar ao cliente*/
                    if(QuantTotal){
                        printf("\tCaso deseje voltar ao menu pricipal entre com este CPF(00000000000)\n\n\n");
					}
					if(QuantTotal){printf("VALORES DE NOTAS DISPONIVEIS MOMENTO: \n");}
					if(QtdC500){printf("R$ 500,00\n");}
					if(QtdC150){printf("R$ 150,00\n");}
					if(QtdC50){printf("R$ 50,00\n");}
					if(QtdC20){printf("R$ 20,00\n");}
					if(QtdC10){printf("R$ 10,00\n");}
					if(QtdC5){printf("R$ 5,00\n");}
					if(QtdC2){printf("R$ 2,00\n");}
					if(QtdC1){printf("R$ 1,00\n");}
//.........................Entrada do CPF e sua Validação..........................................
			//Mostrando a quantidade de cédulas existentes no caixa para o cliente
				if(QuantTotal<=0){ //Verificando se o caixa tem dinheiro
						printf("Caixa completamente VAZIO!\n");
						printf("O gerente deve abastece-lo\n");
						system("pause");
				}else{
				//Entrada do CPF

				printf("\nPor questão de segurança\n");
				printf("Entre com o CPF: ");
        //_______________________________Leitura de cada digito_________________________________//
                do{
                    /*O CPF  sera reiniciado toda vez que passar por este ponto*/
                    CountDigito=0;
                    Dig1=-38,Dig2=-38,Dig3=-38,Dig4=-38,Dig5=-38,Dig6=-38,
                    Dig7=-38,Dig8=-38,Dig9=-38,Dig10=-38,Dig11=-38;
                    /*Leremos os digitos usando o GETCHAR. O teste feito usando "\n-48"
                      nos retorna um inteiro -38, por isso as variaveis a cima são iniciadas
                      com este valor, desta maneira é possivel detectar quando o usuario digita
                      um numero a menos */
                    fflush(stdin);//Se faz necessario limpar o buffer nesse ponto
                    Dig1=getchar()-48;CountDigito++;//O programa ira pegar o caracter do que foi digitado no teclado e subtrai por 48 para obter o inteiro desse caracter
                    if(Dig1!='\n'-48){Dig2=getchar()-48;CountDigito++;}
                    if(Dig2!='\n'-48){Dig3=getchar()-48;CountDigito++;}
                    if(Dig3!='\n'-48){Dig4=getchar()-48;CountDigito++;}
                    if(Dig4!='\n'-48){Dig5=getchar()-48;CountDigito++;}
                    if(Dig5!='\n'-48){Dig6=getchar()-48;CountDigito++;}
                    if(Dig6!='\n'-48){Dig7=getchar()-48;CountDigito++;}
                    if(Dig7!='\n'-48){Dig8=getchar()-48;CountDigito++;}
                    if(Dig8!='\n'-48){Dig9=getchar()-48;CountDigito++;}
                    if(Dig9!='\n'-48){Dig10=getchar()-48;CountDigito++;}
                    if(Dig10!='\n'-48){Dig11=getchar()-48;CountDigito++;}

                    if(CountDigito!=11){//Mensagem de erro caso falte um numero
                        printf("O CPF deve conter 11 digitos\n");
                        system("pause");
                        goto Return;
                    }
                }while(CountDigito!=11);
//__________________________________________________________________________________________________//
                //Vericação cado o cliente deseje retorna ao menu principal
                if(Dig1==0&&Dig2==0&&Dig3==0&&Dig4==0&&Dig5==0&&Dig6==0&&Dig7==0&&Dig8==0&&Dig9==0&&Dig10==0&&Dig11==0){
                    printf("Retornando ao menu principal...\n\n");
                    system("pause");
                    goto MenuPrin;
                }

                //Teste para verificar se os termos digitados são todos iguais
				if((Dig1==Dig2)&&(Dig2==Dig3)&&(Dig3==Dig4)&&(Dig4==Dig5)&&(Dig5==Dig6)&&(Dig6==Dig7)&&(Dig7==Dig8)&&(Dig8==Dig9)&&(Dig9==Dig10)&&(Dig10==Dig11)){
					printf("CPF inválido, não existe CPF com todos os termos iguais\n");
					system("pause");
					goto Return;
				}
				else{//Caso esta tudo okay acima começaremos a verificar os digitos

			  //Verificando digito 1..................................................................................
					DigitoValido1=0;
					soma=0;//Zeramos esta variavel e de cima toda vez que o programa passa por aqui

                    //Em seguida é feito um somatorio e pegamos o resto do somatorio dividido por onze
					soma += (10*Dig1)+(9*Dig2)+(8*Dig3)+(7*Dig4)+(6*Dig5)+(5*Dig6)+(4*Dig7)+(3*Dig8)+(2*Dig9);
                    soma %= 11;
                    if(soma<2){//Determinação do primeiro digito
                        DigitoValido1 = 0;
                    }else{
                        DigitoValido1 = 11 - soma;
                    }
                    if(DigitoValido1!=Dig10){//Caso o primeiro digito de falso, o programa mostra uma mensagem de erro
						Dig1False: system("clear || cls");
							printf("Desculpe, CPF invalido.\n\n");
							printf("1-Digitar novamente\n");
							printf("2-Retornar ao menu principal\n");
							printf("--> ");
									fflush(stdin);
									scanf("%c",&Retorno);
							switch(Retorno)
							{
							case '2':
								goto MenuPrin;//Retorna para o menu
							case '1':
								goto Return;//Retorna para a digitação do CPF
							default:
								printf("Opção inexistente");
									system("pause");
									goto Dig1False;
							}
						}
                    /*O mesmo é feito abaixo, porem, se o digito um é verdadeiro, então ele sera usado nos teste abaixo*/

                //Verificando digito 2....................................................................................
					  DigitoValido2=0;
					  soma=0;

                      soma += (11*Dig1)+(10*Dig2)+(9*Dig3)+(8*Dig4)+(7*Dig5)+(6*Dig6)+(5*Dig7)+(4*Dig8)+(3*Dig9)+(2*Dig10);
                      soma %= 11;
                        if(soma<2){
                            DigitoValido2 = 0;
                        }else{
                            DigitoValido2 = 11 - soma;
                        }
                        if(DigitoValido2!=Dig11){
                            Dig2False: system("clear || cls");
                                printf("Desculpe, CPF invalido.\n\n");
                                printf("1-Digitar novamente\n");
                                printf("2-Retornar ao menu principal\n");
                                printf("--> ");
									fflush(stdin);
									scanf("%c",&Retorno);
							switch(Retorno)
							{
							case '2':
								goto MenuPrin;
							case '1':
								goto Return;
							default:
								printf("Opção inexistente");
									system("pause");
									goto Dig2False;
							}
						}
		 /*=====================================================================================================================*/
					  /*Se o CPF for valido, o código entrará nesse ponto. Aqui o cliente entrada com o valor do saque, que só
						será feito se a quantia for acima de zero e abaixo da quantidade total de dinheiro existente no caixa,
						alem de claro, não poder pedir moedas ao caixa, apenas valore inteiros.
						Alem disso, seram feitas atribuições ao valor total de saque, e descontos na quantidade total de dinheiro
						do caixa e na quantia de cada cédula sacada.*/
						else{
							printf("CPF VALIDO\n\n");
							printf("Valor do saque: R$ ");
							  do{
								scanf("%f",&Vsaque);
								QuantiaDinheiro = Vsaque;//Colocando o valor do saque em QuantiaDinheiro para adiante seja passado o valor por extenso
								inteiro=Vsaque;//Atribuição do valor inteiro para checar se é pedido moeda
								if(Vsaque!=inteiro){
									printf("Desculpe, o caixa não fornece moedas\n");
									printf("Informe outro valor: ");
								}else if(Vsaque>QuantTotal){
									printf("Desculpe..O valor inserido é maior que o valor disponivel no caixa\n");
									printf("Digite outro valor: ");
								}else if(Vsaque<0){
									printf("Você não pode fazer um saque negativo\n");
									printf("Informe outra quantia: ");
								}
							 }while(Vsaque<0||Vsaque>QuantTotal||Vsaque!=inteiro);

                    /*AQUI SERA VERIFICADO QUAIS CÉDULAS SERAM ENTREGUES PARA O CLIENTE*/
			/*===========================================================================================*/
							printf("\n");//Estetico
							printf("______________NOTAS_ENTREGUES_______________\n");

						//_______Verificando a necessidade das notas de 500__________//
							/*Esse teste fara com que, se o valor de saque solicitado for acima de 50 mil,
							  ele ainda entrara nos teste condicionais */
							if(Vsaque>50000){SaqueAlto = 1;}

                            I = 0;//Fara o controle de atribuição de valor no Total sacado e no total existente

							 /*Primeiro é verificado quantas notas o caixa tem
							disponivel em relação da quantia desejada pelo cliente*/
							 if((Vsaque >= 500 && (QtdC500*500)>= Vsaque) ||SaqueAlto){
								   controle= QtdC500;//Colocamos a quantidade de notas de 500 em uma valiriavel de controle
							/*Se temos notas disponiveis, devemos verificar se a quantidade de notas vezes seu
							  valor é maior que o desejado pelo cliente, se for maior usaremos
							  um "WHILE" que será responsavel em tirar uma unidade de nota, ate que
							  a multiplicação seja menor ou igual ao valor desejado*/

							   if(controle>0){//Garantindo que ele mostre a quantidade de notas entreges apenas se ela for maior que zero
                                    if((500*controle)>Vsaque){
                                        while((500*controle)>Vsaque){
                                            controle--;
                                        }
                                    }
                                    if(SaqueAlto){
										/*Se o valor valor for acima de 50000 mil devemos garantir que o
										  programa adicione ao total sacado, ou tire do total do caixa
										  mais do que o limite de cada nota*/
                                        if(!I){
                                            QtdTotSac +=Vsaque;
                                            QuantTotal-=Vsaque;
                                            I=1;
                                        }
									}else if(!I){
										QtdTotSac += Vsaque;           //Atribuindo o valor de saque
										QuantTotal-=Vsaque;            //Subtraimos da quantia total do banco o valor do saque
                                        I=1;
									}
										NotaDisponivel = 0;            //Atribuindo 0 nesta variavel para que no ultimo teste condicinal desta parte do programa de falso e ele siga normalmente
										Vsaque-=(500*controle);        //Tiramos do valor do saque inserido pelo cliente o produto do valor da nota pela variavel de controle
										QtdC500-=controle;             //Aqui é tirado a quantidade de cédulas dadas ao cliente da quantidade de cédula total da respectiva nota
										QtdTotCed-=controle;           //Aqui é tirado a quantidade de cédulas dadas ao cliente da quantidade total do caixa

											printf("%d nota(s) de R$ 500,00\n",controle);//Apos o processo é mostrado a quantidade de notas dadas ao cliente
								}
							 }
							 /*OS ACONTECIMENTOS DESCRITOS ACIMA ACONTECERAM EXATAMENTE COM TODOS OS VALORES ABAIXO,
							  *POREM COM AS VALORES REAJUSTADOS PARA SUAS RESPECTIVAS NOTAS
							  *LOGO SE TORNARIA REDUNDANTE DESCREVER OS PROCESSOS NOVAMENTE*/

                //_______________Verificando a necessidade das notas de 150_______________//

							 if((Vsaque >= 150 &&QtdC150*150>= Vsaque)||SaqueAlto){
								   controle= QtdC150;
								if(controle>0){
                                    if((150*controle)>Vsaque){
                                        while((150*controle)>Vsaque){
                                            controle--;
								   }
								}
                                if(SaqueAlto){
                                    if(!I){
                                        QtdTotSac +=Vsaque;
                                        QuantTotal-=Vsaque;
                                        I=1;
                                    }
                                }else if(!I){
										QtdTotSac += Vsaque;
										QuantTotal-=Vsaque;
										I=1;
                                     }
										NotaDisponivel = 0;
										Vsaque-=(150*controle);
										QtdC150-=controle;
										QtdTotCed-=controle;
												printf("%d nota(s) de R$ 150,00\n",controle);
                                }
							 }

                //__________________Verificando a necessidade das notas de 50________________//

							 if((Vsaque >= 50 &&QtdC50*50>= Vsaque)||SaqueAlto){
								   controle= QtdC50;
								if(controle>0){
								if((50*controle)>Vsaque){
								   while((50*controle)>Vsaque){
										controle--;
								   }
								}
									if(SaqueAlto){
                                        if(!I){
                                            QtdTotSac +=Vsaque;
                                            QuantTotal-=Vsaque;
                                            I=1;
                                        }
									}else if(!I){
										QtdTotSac += Vsaque;
										QuantTotal-=Vsaque;
										I=1;
									}
										NotaDisponivel = 0;
										Vsaque-=(50*controle);
										QtdC50-=controle;
										QtdTotCed-=controle;

										printf("%d nota(s) de R$ 50,00\n",controle);
                                }
							 }

        //___________________Verificando a necessidade das notas de 20___________________//

							 if((Vsaque >= 20 && QtdC20*20>= Vsaque)||SaqueAlto){
								   controle= QtdC20;
								if(controle>0){
								if((20*controle)>Vsaque){
								   while((20*controle)>Vsaque){
										controle--;
								   }
								}
									if(SaqueAlto){
                                        if(!I){
                                            QtdTotSac +=Vsaque;
                                            QuantTotal-=Vsaque;
                                            I=1;
                                        }
									}else if(!I){
										QtdTotSac += Vsaque;
										QuantTotal-=Vsaque;
										I=1;
									}
									NotaDisponivel = 0;
									Vsaque-=(20*controle);
									QtdC20-=controle;
									QtdTotCed-=controle;

										printf("%d nota(s) de R$ 20,00\n",controle);
									  }
							 }

     //____________________Verificando a necessidade das notas de 10____________________//
							 if((Vsaque >= 10 &&QtdC10*10>= Vsaque)||SaqueAlto){
								   controle= QtdC10;
								if(controle>0){
                                    if((10*controle)>Vsaque){
                                        while((10*controle)>Vsaque){
                                            controle--;
                                        }
                                    }
                                if(SaqueAlto){
                                    if(!I){
                                        QtdTotSac +=Vsaque;
                                        QuantTotal-=Vsaque;
                                        I=1;
                                    }
                                }else if(!I){
                                    QtdTotSac += Vsaque;
                                    QuantTotal-=Vsaque;
                                    I=1;
                                }
										NotaDisponivel = 0;
										Vsaque-=(10*controle);
										QtdC10-=controle;
										QtdTotCed-=controle;
											printf("%d nota(s) de R$ 10,00\n",controle);
                                }
                            }
					//_______Verificando a necessidade das notas de 5__________//
							 if((Vsaque >= 5 &&QtdC5*5>= Vsaque)||SaqueAlto){
								   controle= QtdC5;
								if(controle>0){
                                    if((5*controle)>Vsaque){
                                        while((5*controle)>Vsaque){
                                            controle--;
                                        }
                                    }
                                if(SaqueAlto){
                                    if(!I){
                                        QtdTotSac +=Vsaque;
                                        QuantTotal-=Vsaque;
                                        I=1;
                                    }
                                }else if(!I){
                                        QtdTotSac += Vsaque;
                                        QuantTotal-=Vsaque;
										I=1;
                                 }
										NotaDisponivel = 0;
										Vsaque-=(5*controle);
										QtdC5-=controle;
										QtdTotCed-=controle;

										printf("%d nota(s) de R$ 5,00\n",controle);
                                }
                            }

            //________________Verificando a necessidade das notas de 2________________//
							 if((Vsaque >= 2 && QtdC2*2>= Vsaque)||SaqueAlto){
								   controle= QtdC2;
								if(controle>0){
                                    if((2*controle)>Vsaque){
                                        while((2*controle)>Vsaque){
                                            controle--;
                                        }
                                    }
                                if(SaqueAlto){
                                    if(!I){
                                        QtdTotSac +=Vsaque;
                                        QuantTotal-=Vsaque;
                                        I=1;
                                    }
                                }else if(!I){
                                    QtdTotSac += Vsaque;
                                    QuantTotal-=Vsaque;
                                    I=1;
                                  }
										NotaDisponivel = 0;
										Vsaque-=(2*controle);
										QtdC2-=controle;
										QtdTotCed-=controle;
											printf("%d nota(s) de R$ 2,00\n",controle);
										}
							 }
            //__________________Verificando a necessidade das notas de 1__________________//
							 if((Vsaque>= 1 && QtdC1*1>= Vsaque)||SaqueAlto){
								   controle= QtdC1;
								if(controle>0){
                                    if((1*controle)>Vsaque){
                                        while((1*controle)>Vsaque){
                                            controle--;
                                        }
                                    }
                                if(SaqueAlto){
                                    if(!I){
                                        QtdTotSac +=Vsaque;
                                        QuantTotal-=Vsaque;
                                        I=1;
                                    }
                                }else if(!I){
										QtdTotSac += Vsaque;
										QuantTotal-=Vsaque;
										I = 1;
                                }
										NotaDisponivel = 0;
										Vsaque-=(1*controle);
										QtdC1-=controle;
										QtdTotCed-=controle;
											printf("%d nota(s) de R$ 1,00\n",controle);
										}
							 }
							/*Se o caixa não tiver notas disposiveis para saque, informaremos o erro,
							  e retornaremos o codigo ao ponto em que é informado as notas disponiveis
							  e a digitação do CPF*/
							if(NotaDisponivel){
										printf("Desculpe! Não temos uma quantidade de nota disponivel para o valor de R$ %.2f\n",Vsaque);
										printf("Por favor digite outro \n\n");
									system("pause");
									goto ValSaq;
							 }
			/*====================================VALOR PASSADO POR EXTENSO==============================================*/
							printf("\n");
											printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
											printf("\nVALOR SACADO: R$ %.2f (",QuantiaDinheiro);
										 //=======================VALORES DE 100 MIL REAIS PARA 199 MIL=================================//
										   /*Se a variavel Resto for maior que 1, significa que o valor
											 esta acima ou é igual ao do teste imposto entao ele entrara no laço*/
											Concordancia=0;
											Resto = QuantiaDinheiro/100000;
														if(Resto>0){
															if(QuantiaDinheiro/100000==1){//Nessa parte, se o valor divido por 100 mil for igual a 1 entra ele imprime "Cem mil reais" na tela e finaliza esta parte do programa
																printf("Cem mil reais");
															}else{//Caso contrario, significa que o valor é maior que 100 mil e então ele ira continuar com os testes
																printf("Cento e ");
																Concordancia++;//Variavel que sera usada em um teste condicinal no MIL e no UM para fazer as devidas impressões na tela de acordo com a concorcia verbal
															}
															QuantiaDinheiro-=100000;//Aqui tiramos 100 Mil do valor total, caso o valor seja acima disso, os laços continuaram
														}
										 //=======================VALORES ENTRE 10 E 100 MIL REAIS=================================//
															Resto = QuantiaDinheiro/10000;//Aqui é o mesmo processo dos valor de 100 Mil, mas reajustados para valores que divididos por 10 Mil sejam maiores de 1
															if(Resto>0){
																if(QuantiaDinheiro/10000==1){//Exatamente o mesmo teste de cima mas reajustado para 10 Mil
																	printf("Dez mil reais");
																}else
																//-----------EXTENSO DE VALORES ENTRE 11 E 19 MIL REAIS-----------------//
												//__________________________________________________________________________________________//
														/*As atribuições abaixo serão repetidas novamente a frente.
														  Aqui a variavel "AuxResto" recebera a divisão do valor total
														  por 10 mil e em seguida sera somado o Ajuste nela, pois como
														  foi explicado acima,a IDE não esta dando os valores corretos
														  então o valor sera reajustado, e ainda sera passado para uma
														  variavel inteira multiplicado por dez, e que sera de vital
														  importancia em varias parte do código*/
																	AuxResto = QuantiaDinheiro/10000;
																	AuxResto += Ajuste;
																	AuxInteiro = (AuxResto*10.0);
												//___________________________________________________________________________________________//

																	if(AuxResto>=1.1&&AuxResto<2){//Teste para os valores que podem estar entre 11 e 19 mil reias
																		//Caso a quantidade seja exata
																		if(QuantiaDinheiro/AuxInteiro==1000){//Se a divisão da Quantia pelo Inteiro da divisão acima for igual a MIL significa que o valor é exato

																			if(AuxInteiro==11){printf("Onze Mil Reais");QuantiaDinheiro=0;}else//A variavel "QuantiaDinheiro",neste trecho, é zerada para que não exista problemas abaixo
																			if(AuxInteiro==12){printf("Doze Mil Reais");QuantiaDinheiro=0;}else
																			if(AuxInteiro==13){printf("Treze Mil Reais");QuantiaDinheiro=0;}else
																			if(AuxInteiro==14){printf("Quartoze Mil Reais");QuantiaDinheiro=0;}else
																			if(AuxInteiro==15){printf("Quinze Mil Reais");QuantiaDinheiro=0;}else
																			if(AuxInteiro==16){printf("Dezesseis Mil Reais");QuantiaDinheiro=0;}else
																			if(AuxInteiro==17){printf("Dezessete Mil Reais");QuantiaDinheiro=0;}else
																			if(AuxInteiro==18){printf("Dezeoito Mil Reais");QuantiaDinheiro=0;}else
																			if(AuxInteiro==19){printf("Dezenove Mil Reais");QuantiaDinheiro=0;}
																		}else{
																		//Caso não seja
																			if(AuxResto<1.2){printf("Onze Mil ");QuantiaDinheiro-=11000;Resto=0;}else//Neste trecho, tiramos o valor absoluto da "QuantiaDinheiro" e zeramos "Resto" para que não haja um somatorio errado nos teste a seguir
																			if(AuxResto<1.3){printf("Doze Mil ");QuantiaDinheiro-=12000;Resto=0;}else
																			if(AuxResto<1.4){printf("Treze Mil ");QuantiaDinheiro-=13000;Resto=0;}else
																			if(AuxResto<1.5){printf("Quartoze Mil ");QuantiaDinheiro-=14000;Resto=0;}else
																			if(AuxResto<1.6){printf("Quinze Mil ");QuantiaDinheiro-=15000;Resto=0;}else
																			if(AuxResto<1.7){printf("Dezesseis Mil ");QuantiaDinheiro-=16000;Resto=0;}else
																			if(AuxResto<1.8){printf("Dezessete Mil ");QuantiaDinheiro-=17000;Resto=0;}else
																			if(AuxResto<1.9){printf("Dezeoito Mil ");QuantiaDinheiro-=18000;Resto=0;}else
																			if(AuxResto>1.9){printf("Dezenove Mil ");QuantiaDinheiro-=19000;Resto=0;}

																			for(count=1;count<=9;count++){//O conectivo "e" não aparecera em todas as situações que algum dos testes acima de verdairo, entao ele só aparecera caso o valor apos o absoluto seja como: 19,400 ou 20,600 ou 14,700 e etc..
																				if(QuantiaDinheiro/100==count){
																					printf(" e ");
																				}
																			}
																		}
																	}

																	//__________________EXTENSO DE VALORES ACIMA OU IGUAIS A 20 MIL REAIS_________________//
																	else{
																		//--------Valores exatos-------------//
																		if(QuantiaDinheiro/AuxInteiro==1000){
																			if(AuxInteiro==20){printf("Vinte Mil Reais");}
																			if(AuxInteiro==30){printf("Trinta Mil Reais");}
																			if(AuxInteiro==40){printf("Quarenta Mil Reais");}
																			if(AuxInteiro==50){printf("Cinquenta Mil Reais");}
																			if(AuxInteiro==60){printf("Sessenta Mil Reais");}
																			if(AuxInteiro==70){printf("Setenta Mil Reais");}
																			if(AuxInteiro==80){printf("Oitenta Mil Reais");}
																			if(AuxInteiro==90){printf("Noventa Mil Reais");}
																		}
																		//-----Valores acima de 20 Mil e Abaixo de 21 Mil(por exemplo)----//
																		if(AuxResto>9.0&&AuxResto<9.1){printf("Noventa Mil ");}else
																		if(AuxResto>8.0&&AuxResto<8.1){printf("Oitenta Mil ");}else
																		if(AuxResto>7.0&&AuxResto<7.1){printf("Setenta Mil ");}else
																		if(AuxResto>6.0&&AuxResto<6.1){printf("Sessenta Mil ");}else
																		if(AuxResto>5.0&&AuxResto<5.1){printf("Cinquenta Mil ");}else
																		if(AuxResto>4.0&&AuxResto<4.1){printf("Quarenta Mil ");}else
																		if(AuxResto>3.0&&AuxResto<3.1){printf("Trinta Mil ");}else
																		if(AuxResto>2.0&&AuxResto<2.1){printf("Vinte Mil ");}else
																		if(AuxResto>1.0&&AuxResto<1.1){printf("Dez Mil ");}

																		//----------Para valores como: 99.600-------------//
																		if(AuxResto>1.1&&AuxResto<2){printf("Dez e ");}
																		if(AuxResto>2.1&&AuxResto<3){printf("Vinte e ");}
																		if(AuxResto>3.1&&AuxResto<4){printf("Trinta e ");}
																		if(AuxResto>4.1&&AuxResto<5){printf("Quarenta e ");}
																		if(AuxResto>5.1&&AuxResto<6){printf("Cinquenta e ");}
																		if(AuxResto>6.1&&AuxResto<7){printf("Sessenta e ");}
																		if(AuxResto>7.1&&AuxResto<8){printf("Setenta e ");}
																		if(AuxResto>8.1&&AuxResto<9){printf("Oitenta e ");}
																		if(AuxResto>9.1){printf("Noventa e ");}
																	}
																	Concordancia++;
																	Resto*=10000;//Essa variavel é multiplicada, nesse caso, por 10 MIL e a "QuantiaDinheiro" é subtraida por ela em seguida
																	QuantiaDinheiro-=Resto;
																		for(count=1;count<=9;count++){//Um outro teste de conectivo é feito aqui para os valores que estão entre 20 e 21 Mil ou 30 e 31 Mil(por exemplo, pois se extende até 90 mil)
																			if(QuantiaDinheiro/100==count){
																				printf(" e ");
																			}
																		}
															}
															/*A grande maioria do codigo acima se repetira abaixo, apenas em alguns pontos
															  que foram tomados outros caminhos, então sera comentado daqui para baixo
															  apenas estes pontos*/

														//======================VALORES ENTRE MIL E DEZ MIL REAIS==================//
															Resto = QuantiaDinheiro/1000;
															if(Resto>0){
																if(QuantiaDinheiro/1000==1){
																	if(Concordancia>0){printf("Um ");}
																	printf("Mil Reais");
																}else{
																	AuxResto = QuantiaDinheiro / 1000;
																	AuxResto += Ajuste;
																	AuxInteiro = (AuxResto*10.0);

														/*O valores de estão entre 1000 e 9999 terão os teste mais diversificados do resto
														  pois é mais facil usar laços de repetição com eles evitando assim varios blocos de "printf"*/
																  //------------PARTE MAIOR DO NUMERO---------------//
																		if(Concordancia>0){//Teste de concordanticia que verificara se o valor dever ser "MIL REAIS" ou "UM MIL REAIS"
																			if(Resto==1){printf("Um");}
																		}
																		if(Resto==2){printf("Dois");}//Os demais apenas serao imprimidos de acordo com seus valores
																		if(Resto==3){printf("Três");}
																		if(Resto==4){printf("Quatro");}
																		if(Resto==5){printf("Cinco");}
																		if(Resto==6){printf("Seis");}
																		if(Resto==7){printf("Sete");}
																		if(Resto==8){printf("Oito");}
																		if(Resto==9){printf("Nove");}

															/*Colocarei abaixo das variaveis dos laços exemplos de valores que podem ser assumidos*/

																		//----------Caso o valor se exato, como: 2,000 ou 3,000 reais---------------//
																			I=0;//Variavel que permite a entrada nos laços de repetições
																			for(count=2;count<10;count++){
																				if(AuxInteiro==count*10){printf(" Mil reais");I=1;}
																				//     20    ==  2  *10 --->  Nesse caso, seria imprimido "Dois Mil Reais na tela" e a variavel recebe "I" para que não seja feito mais nenhum texto com esses valores

																			}

																		//--------Caso o valor esteja entre 1,001 e 1,099 reais, por exemplo----------//
																			 if(I==0){
																				if(AuxResto>Resto&&AuxResto<Resto+0.1){printf(" Mil e ");I=1;}
																				//    1.01 >  1  &&  1.01   <    1.1  --> Seria imprimido "(Um)MIL E " na tela e os testes continuaria abaixo
																			 }

																		//--------Caso o valor seja de 1,101 ou 2,101 reias (por exemplo)-------------//
																			if(I==0){
																				if(QuantiaDinheiro/AuxInteiro!=100){//Só entrar se o numero que esta apos o mil não for divisivel por 100
																					for(count=1;count<10;count++){
																						VarCount++;
																						if((AuxResto>Resto+(VarCount/10)) && (AuxResto<Resto+((VarCount+1)/10))){printf(" Mil ");I=1;}
																						  //  2.101 >  2  +    2    /10   &&    2.101    2  +    (2   +1) /10 -->  Imprimira "Dois Mil " e os teste continuariam abaico
																					}
																				}
																			}
																		//----------Caso o valor seja 1,100 ou 1,200 ou 1,300 reais exatos(por exemplo)--------//
																			if(I==0){
																		/*Para não ocorrer erros, se o valor for acima de 1000,
																		  vamos usar a variavel I para reajustar a soma dentro do laço*/
																				I = AuxInteiro/10;//O resultado é multiplicado por 10 abaixo, se o AuxInteiro fosse 46 por acaso
																								  //a variavel "I" recebera 4, e permitira que na tela seja impresso "Três Mil e " por exemplo
																				for(count=1;count<10;count++){
																					if(AuxInteiro==(10*I)+count){printf(" Mil e ");I=1;}
																				}
																			}
																			Concordancia++;
																			Resto*=1000;
																			QuantiaDinheiro-=Resto;
																}
															}
															//======================VALORES ENTRE CEM E MIL REAIS==================//
															Resto = QuantiaDinheiro/100;
															if(Resto>0){
																	if(QuantiaDinheiro/100==1){
																		printf("Cem Reais");
																	}else{
																		AuxResto=QuantiaDinheiro/100;
																	//-----Valores exatos como 200 ou 300 reias--------//
																		if(AuxResto==2){printf("Duzentos Reais");}else
																		if(AuxResto==3){printf("Trezentos Reais");}else
																		if(AuxResto==4){printf("Quatrocentos Reais");}else
																		if(AuxResto==5){printf("Quinhetos Reais");}else
																		if(AuxResto==6){printf("Seiscentos Reais");}else
																		if(AuxResto==7){printf("Setecentos Reais");}else
																		if(AuxResto==8){printf("Oitocentos Reais");}else
																		if(AuxResto==9){printf("Novecentos Reais");}else
																	 //-----------Valores não exatos como 151 ou 203 reais--------//
																		if(Resto==1){printf("Cento e ");}else
																		if(Resto==2){printf("Duzentos e ");}else
																		if(Resto==3){printf("Trezentos e ");}else
																		if(Resto==4){printf("Quatrocentos e ");}else
																		if(Resto==5){printf("Quinhetos e ");}else
																		if(Resto==6){printf("Seiscentos e ");}else
																		if(Resto==7){printf("Setecentos e ");}else
																		if(Resto==8){printf("Oitocentos e ");}else
																		if(Resto==9){printf("Novecentos e ");}
																	}
																		Concordancia++;
																		Resto*=100;
																		QuantiaDinheiro-=Resto;
															}
															//======================VALORES DEZ A CEM REAIS==================//
															Resto = QuantiaDinheiro/10.0;
															if(Resto>0){
																		if(QuantiaDinheiro/10.0==1){
																		   printf("Dez Reais");
																		}
																		else{
																			AuxResto=QuantiaDinheiro/10.0;
																			AuxInteiro = (AuxResto*10.0)+Ajuste;
																		//----------Extenso para valores inteiros de 11 a 19 reais----------//
																			if(AuxInteiro==11){printf("Onze Reais");Resto=0;}else
																			if(AuxInteiro==12){printf("Doze Reais");Resto=0;}else
																			if(AuxInteiro==13){printf("Treze Reais");Resto=0;}else
																			if(AuxInteiro==14){printf("Quatorze Reais");Resto=0;}else
																			if(AuxInteiro==15){printf("Quinze Reais");Resto=0;}else
																			if(AuxInteiro==16){printf("Dezesseis Reais");Resto=0;}else
																			if(AuxInteiro==17){printf("Dezessete Reais");Resto=0;}else
																			if(AuxInteiro==18){printf("Dezoito Reais");Resto=0;}else
																			if(AuxInteiro==19){printf("Dezenove Reais");Resto=0;}else

																		 //------Extenso para valores exatos como 20 ou 30 ou 50 reais------//
																			if(AuxInteiro==20){printf("Vinte Reais");}else
																			if(AuxInteiro==30){printf("Trinta Reais");}else
																			if(AuxInteiro==40){printf("Quarenta Reais");}else
																			if(AuxInteiro==50){printf("Cinquenta Reais");}else
																			if(AuxInteiro==60){printf("Sessenta Reais");}else
																			if(AuxInteiro==70){printf("Setenta Reais");}else
																			if(AuxInteiro==80){printf("Oitenta Reais");}else
																			if(AuxInteiro==90){printf("Noventa Reais");}else

																		 //Caso todos os testes acima resultem em falso, os valores estarão acima de 20
																			if(Resto==2){printf("Vinte e ");}else
																			if(Resto==3){printf("Trinta e ");}else
																			if(Resto==4){printf("Quarenta e ");}else
																			if(Resto==5){printf("Cinquenta e ");}else
																			if(Resto==6){printf("Sessenta e ");}else
																			if(Resto==7){printf("Setenta e ");}else
																			if(Resto==8){printf("Oitenta e ");}else
																			if(Resto==9){printf("Noventa e ");}
																		}
																			Concordancia++;
																			Resto*=10;
																			QuantiaDinheiro-=Resto;
															}
															//======================VALORES UM A DEZ REAIS==================//
															Resto = QuantiaDinheiro/1;
																if(Resto>0){
																			if(Concordancia!=0){
																				if(Resto==1){printf("Um Reais");}
																			}else{
																				if(Resto==1){printf("Um Real");}
																			}
																			if(Resto==2){printf("Dois Reais");}
																			if(Resto==3){printf("Três Reais");}
																			if(Resto==4){printf("Quatro Reais");}
																			if(Resto==5){printf("Cinco Reais");}
																			if(Resto==6){printf("Seis Reais");}
																			if(Resto==7){printf("Sete Reais");}
																			if(Resto==8){printf("Oito Reais");}
																			if(Resto==9){printf("Nove Reais");}

																			QuantiaDinheiro-=Resto;
																}

							printf(")\n");//Apenas para fechar o parenteses aberto no printf acima
							printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
							printf("\n\n");
							system("pause");
						}
				  }
			   }
			}
/*===========================================================================================*/


/*==================================Configurações do menu do gerente===========================*/
		if(opc1==2) {
			printf("\nVocê escolheu GERENTE!\n");
			system("pause");
			do {
				system("cls");
				printf("\nMENU GERENTE");
				printf("\n\n(1) Valor total sacado");
				printf("\n(2) Valor do saldo existente");
				printf("\n(3) Quantidade de cédulas existentes");
				printf("\n(4) Abastecer o caixa eletrônico");
				printf("\n(5) Voltar ao menu principal");
				printf("\n\nDigite a opção: ");
				scanf("%d",&opc2);
				switch(opc2) {
					//QUANTIDADE DE DINHEIRO SACADO ATE O MOMENTO
					case 1: printf("\nVocê escolheu a opção %d\n",opc2);
							system("pause");
							system("clear||cls");
                                /*Como o valor do saque é um numero que tende ao infinito, vamos mostra os valores por
                                   extenso para o cliente ate 199.999.00 Reais*/
                                if(QtdTotSac>199999){
                                    printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
                                    printf("\nVALOR SACADO: R$ %.2f (",QtdTotSac);
                                    printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
                                }
								if(QtdTotSac<=199999){
								printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
											printf("\nVALOR SACADO: R$ %.2f (",QtdTotSac);
											QtdTotalExtenso = QtdTotSac;
										 //=======================VALORES DE 100 MIL REAIS PARA 199 MIL=================================//
										   /*Se a variavel Resto for maior que 1, significa que o valor
											 esta acima ou é igual ao do teste imposto entao ele entrara no laço*/
											Concordancia=0;
											Resto = QtdTotalExtenso/100000;
														if(Resto>0){
															if(QtdTotalExtenso/100000==1){//Nessa parte, se o valor divido por 100 mil for igual a 1 entra ele imprime "Cem mil reais" na tela e finaliza esta parte do programa
																printf("Cem mil reais");
															}else{//Caso contrario, significa que o valor é maior que 100 mil e então ele ira continuar com os testes
																printf("Cento e ");
																Concordancia++;//Variavel que sera usada em um teste condicinal no MIL e no UM para fazer as devidas impressões na tela de acordo com a concorcia verbal
															}
															QtdTotalExtenso-=100000;//Aqui tiramos 100 Mil do valor total, caso o valor seja acima disso, os laços continuaram
														}
										 //=======================VALORES ENTRE 10 E 100 MIL REAIS=================================//
															Resto = QtdTotalExtenso/10000;//Aqui é o mesmo processo dos valor de 100 Mil, mas reajustados para valores que divididos por 10 Mil sejam maiores de 1
															if(Resto>0){
																if(QtdTotalExtenso/10000==1){//Exatamente o mesmo teste de cima mas reajustado para 10 Mil
																	printf("Dez mil reais");
																}else
																//-----------EXTENSO DE VALORES ENTRE 11 E 19 MIL REAIS-----------------//
												//__________________________________________________________________________________________//
														/*As atribuições abaixo serão repetidas novamente a frente.
														  Aqui a variavel "AuxResto" recebera a divisão do valor total
														  por 10 mil e em seguida sera somado o Ajuste nela, pois como
														  foi explicado acima,a IDE não esta dando os valores corretos
														  então o valor sera reajustado, e ainda sera passado para uma
														  variavel inteira multiplicado por dez, e que sera de vital
														  importancia em varias parte do código*/
																	AuxResto = QtdTotalExtenso/10000;
																	AuxResto += Ajuste;
																	AuxInteiro = (AuxResto*10.0);
												//___________________________________________________________________________________________//

																	if(AuxResto>=1.1&&AuxResto<2){//Teste para os valores que podem estar entre 11 e 19 mil reias
																		//Caso a quantidade seja exata
																		if(QtdTotalExtenso/AuxInteiro==1000){//Se a divisão da Quantia pelo Inteiro da divisão acima for igual a MIL significa que o valor é exato

																			if(AuxInteiro==11){printf("Onze Mil Reais");QtdTotalExtenso=0;}else//A variavel "QuantiaDinheiro",neste trecho, é zerada para que não exista problemas abaixo
																			if(AuxInteiro==12){printf("Doze Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==13){printf("Treze Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==14){printf("Quartoze Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==15){printf("Quinze Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==16){printf("Dezesseis Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==17){printf("Dezessete Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==18){printf("Dezeoito Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==19){printf("Dezenove Mil Reais");QtdTotalExtenso=0;}
																		}else{
																		//Caso não seja
																			if(AuxResto<1.2){printf("Onze Mil ");QtdTotalExtenso-=11000;Resto=0;}else//Neste trecho, tiramos o valor absoluto da "QuantiaDinheiro" e zeramos "Resto" para que não haja um somatorio errado nos teste a seguir
																			if(AuxResto<1.3){printf("Doze Mil ");QtdTotalExtenso-=12000;Resto=0;}else
																			if(AuxResto<1.4){printf("Treze Mil ");QtdTotalExtenso-=13000;Resto=0;}else
																			if(AuxResto<1.5){printf("Quartoze Mil ");QtdTotalExtenso-=14000;Resto=0;}else
																			if(AuxResto<1.6){printf("Quinze Mil ");QtdTotalExtenso-=15000;Resto=0;}else
																			if(AuxResto<1.7){printf("Dezesseis Mil ");QtdTotalExtenso-=16000;Resto=0;}else
																			if(AuxResto<1.8){printf("Dezessete Mil ");QtdTotalExtenso-=17000;Resto=0;}else
																			if(AuxResto<1.9){printf("Dezeoito Mil ");QtdTotalExtenso-=18000;Resto=0;}else
																			if(AuxResto>1.9){printf("Dezenove Mil ");QtdTotalExtenso-=19000;Resto=0;}

																			for(count=1;count<=9;count++){//O conectivo "e" não aparecera em todas as situações que algum dos testes acima de verdairo, entao ele só aparecera caso o valor apos o absoluto seja como: 19,400 ou 20,600 ou 14,700 e etc..
																				if(QtdTotalExtenso/100==count){
																					printf(" e ");
																				}
																			}
																		}
																	}

																	//__________________EXTENSO DE VALORES ACIMA OU IGUAIS A 20 MIL REAIS_________________//
																	else{
																		//--------Valores exatos-------------//
																		if(QtdTotalExtenso/AuxInteiro==1000){
																			if(AuxInteiro==20){printf("Vinte Mil Reais");}
																			if(AuxInteiro==30){printf("Trinta Mil Reais");}
																			if(AuxInteiro==40){printf("Quarenta Mil Reais");}
																			if(AuxInteiro==50){printf("Cinquenta Mil Reais");}
																			if(AuxInteiro==60){printf("Sessenta Mil Reais");}
																			if(AuxInteiro==70){printf("Setenta Mil Reais");}
																			if(AuxInteiro==80){printf("Oitenta Mil Reais");}
																			if(AuxInteiro==90){printf("Noventa Mil Reais");}
																		}
																		//-----Valores acima de 20 Mil e Abaixo de 21 Mil(por exemplo)----//
																		if(AuxResto>9.0&&AuxResto<9.1){printf("Noventa Mil ");}else
																		if(AuxResto>8.0&&AuxResto<8.1){printf("Oitenta Mil ");}else
																		if(AuxResto>7.0&&AuxResto<7.1){printf("Setenta Mil ");}else
																		if(AuxResto>6.0&&AuxResto<6.1){printf("Sessenta Mil ");}else
																		if(AuxResto>5.0&&AuxResto<5.1){printf("Cinquenta Mil ");}else
																		if(AuxResto>4.0&&AuxResto<4.1){printf("Quarenta Mil ");}else
																		if(AuxResto>3.0&&AuxResto<3.1){printf("Trinta Mil ");}else
																		if(AuxResto>2.0&&AuxResto<2.1){printf("Vinte Mil ");}else
																		if(AuxResto>1.0&&AuxResto<1.1){printf("Dez Mil ");}

																		//----------Para valores como: 99.600-------------//
																		if(AuxResto>1.1&&AuxResto<2){printf("Dez e ");}
																		if(AuxResto>2.1&&AuxResto<3){printf("Vinte e ");}
																		if(AuxResto>3.1&&AuxResto<4){printf("Trinta e ");}
																		if(AuxResto>4.1&&AuxResto<5){printf("Quarenta e ");}
																		if(AuxResto>5.1&&AuxResto<6){printf("Cinquenta e ");}
																		if(AuxResto>6.1&&AuxResto<7){printf("Sessenta e ");}
																		if(AuxResto>7.1&&AuxResto<8){printf("Setenta e ");}
																		if(AuxResto>8.1&&AuxResto<9){printf("Oitenta e ");}
																		if(AuxResto>9.1){printf("Noventa e ");}
																	}
																	Concordancia++;
																	Resto*=10000;//Essa variavel é multiplicada, nesse caso, por 10 MIL e a "QtdTotalExtenso" é subtraida por ela em seguida
																	QtdTotalExtenso-=Resto;
																		for(count=1;count<=9;count++){//Um outro teste de conectivo é feito aqui para os valores que estão entre 20 e 21 Mil ou 30 e 31 Mil(por exemplo, pois se extende até 90 mil)
																			if(QtdTotalExtenso/100==count){
																				printf(" e ");
																			}
																		}
															}
															/*A grande maioria do codigo acima se repetira abaixo, apenas em alguns pontos
															  que foram tomados outros caminhos, então sera comentado daqui para baixo
															  apenas estes pontos*/

														//======================VALORES ENTRE MIL E DEZ MIL REAIS==================//
															Resto = QtdTotalExtenso/1000;
															if(Resto>0){
																if(QtdTotalExtenso/1000==1){
																	if(Concordancia>0){printf("Um ");}
																	printf("Mil Reais");
																}else{
																	AuxResto = QtdTotalExtenso / 1000;
																	AuxResto += Ajuste;
																	AuxInteiro = (AuxResto*10.0);

														/*O valores de estão entre 1000 e 9999 terão os teste mais diversificados do resto
														  pois é mais facil usar laços de repetição com eles evitando assim varios blocos de "printf"*/
																  //------------PARTE MAIOR DO NUMERO---------------//
																		if(Concordancia>0){//Teste de concordanticia que verificara se o valor dever ser "MIL REAIS" ou "UM MIL REAIS"
																			if(Resto==1){printf("Um");}
																		}
																		if(Resto==2){printf("Dois");}//Os demais apenas serao imprimidos de acordo com seus valores
																		if(Resto==3){printf("Três");}
																		if(Resto==4){printf("Quatro");}
																		if(Resto==5){printf("Cinco");}
																		if(Resto==6){printf("Seis");}
																		if(Resto==7){printf("Sete");}
																		if(Resto==8){printf("Oito");}
																		if(Resto==9){printf("Nove");}

															/*Colocarei abaixo das variaveis dos laços exemplos de valores que podem ser assumidos*/

																		//----------Caso o valor se exato, como: 2,000 ou 3,000 reais---------------//
																			I=0;//Variavel que permite a entrada nos laços de repetições
																			for(count=2;count<10;count++){
																				if(AuxInteiro==count*10){printf(" Mil reais");I=1;}
																				//     20    ==  2  *10 --->  Nesse caso, seria imprimido "Dois Mil Reais na tela" e a variavel recebe "I" para que não seja feito mais nenhum texto com esses valores

																			}

																		//--------Caso o valor esteja entre 1,001 e 1,099 reais, por exemplo----------//
																			 if(I==0){
																				if(AuxResto>Resto&&AuxResto<Resto+0.1){printf(" Mil e ");I=1;}
																				//    1.01 >  1  &&  1.01   <    1.1  --> Seria imprimido "(Um)MIL E " na tela e os testes continuaria abaixo
																			 }

																		//--------Caso o valor seja de 1,101 ou 2,101 reias (por exemplo)-------------//
																			if(I==0){
																				if(QtdTotalExtenso/AuxInteiro!=100){//Só entrar se o numero que esta apos o mil não for divisivel por 100
																					for(count=1;count<10;count++){
																						VarCount++;
																						if((AuxResto>Resto+(VarCount/10)) && (AuxResto<Resto+((VarCount+1)/10))){printf(" Mil ");I=1;}
																						  //  2.101 >  2  +    2    /10   &&    2.101    2  +    (2   +1) /10 -->  Imprimira "Dois Mil " e os teste continuariam abaico
																					}
																				}
																			}
																		//----------Caso o valor seja 1,100 ou 1,200 ou 1,300 reais exatos(por exemplo)--------//
																			if(I==0){
																		/*Para não ocorrer erros, se o valor for acima de 1000,
																		  vamos usar a variavel I para reajustar a soma dentro do laço*/
																				I = AuxInteiro/10;//O resultado é multiplicado por 10 abaixo, se o AuxInteiro fosse 46 por acaso
																								  //a variavel "I" recebera 4, e permitira que na tela seja impresso "Três Mil e " por exemplo
																				for(count=1;count<10;count++){
																					if(AuxInteiro==(10*I)+count){printf(" Mil e ");I=1;}
																				}
																			}
																			Concordancia++;
																			Resto*=1000;
																			QtdTotalExtenso-=Resto;
																}
															}
															//======================VALORES ENTRE CEM E MIL REAIS==================//
															Resto = QtdTotalExtenso/100;
															if(Resto>0){
																	if(QtdTotalExtenso/100==1){
																		printf("Cem Reais");
																	}else{
																		AuxResto=QtdTotalExtenso/100;
																	//-----Valores exatos como 200 ou 300 reias--------//
																		if(AuxResto==2){printf("Duzentos Reais");}else
																		if(AuxResto==3){printf("Trezentos Reais");}else
																		if(AuxResto==4){printf("Quatrocentos Reais");}else
																		if(AuxResto==5){printf("Quinhetos Reais");}else
																		if(AuxResto==6){printf("Seiscentos Reais");}else
																		if(AuxResto==7){printf("Setecentos Reais");}else
																		if(AuxResto==8){printf("Oitocentos Reais");}else
																		if(AuxResto==9){printf("Novecentos Reais");}else
																	 //-----------Valores não exatos como 151 ou 203 reais--------//
																		if(Resto==1){printf("Cento e ");}else
																		if(Resto==2){printf("Duzentos e ");}else
																		if(Resto==3){printf("Trezentos e ");}else
																		if(Resto==4){printf("Quatrocentos e ");}else
																		if(Resto==5){printf("Quinhetos e ");}else
																		if(Resto==6){printf("Seiscentos e ");}else
																		if(Resto==7){printf("Setecentos e ");}else
																		if(Resto==8){printf("Oitocentos e ");}else
																		if(Resto==9){printf("Novecentos e ");}
																	}
																		Concordancia++;
																		Resto*=100;
																		QtdTotalExtenso-=Resto;
															}
															//======================VALORES DEZ A CEM REAIS==================//
															Resto = QtdTotalExtenso/10.0;
															if(Resto>0){
																		if(QtdTotalExtenso/10.0==1){
																		   printf("Dez Reais");
																		}
																		else{
																			AuxResto=QtdTotalExtenso/10.0;
																			AuxInteiro = (AuxResto*10.0)+Ajuste;
																		//----------Extenso para valores inteiros de 11 a 19 reais----------//
																			if(AuxInteiro==11){printf("Onze Reais");Resto=0;}else
																			if(AuxInteiro==12){printf("Doze Reais");Resto=0;}else
																			if(AuxInteiro==13){printf("Treze Reais");Resto=0;}else
																			if(AuxInteiro==14){printf("Quatorze Reais");Resto=0;}else
																			if(AuxInteiro==15){printf("Quinze Reais");Resto=0;}else
																			if(AuxInteiro==16){printf("Dezesseis Reais");Resto=0;}else
																			if(AuxInteiro==17){printf("Dezessete Reais");Resto=0;}else
																			if(AuxInteiro==18){printf("Dezoito Reais");Resto=0;}else
																			if(AuxInteiro==19){printf("Dezenove Reais");Resto=0;}else

																		 //------Extenso para valores exatos como 20 ou 30 ou 50 reais------//
																			if(AuxInteiro==20){printf("Vinte Reais");}else
																			if(AuxInteiro==30){printf("Trinta Reais");}else
																			if(AuxInteiro==40){printf("Quarenta Reais");}else
																			if(AuxInteiro==50){printf("Cinquenta Reais");}else
																			if(AuxInteiro==60){printf("Sessenta Reais");}else
																			if(AuxInteiro==70){printf("Setenta Reais");}else
																			if(AuxInteiro==80){printf("Oitenta Reais");}else
																			if(AuxInteiro==90){printf("Noventa Reais");}else

																		 //Caso todos os testes acima resultem em falso, os valores estarão acima de 20
																			if(Resto==2){printf("Vinte e ");}else
																			if(Resto==3){printf("Trinta e ");}else
																			if(Resto==4){printf("Quarenta e ");}else
																			if(Resto==5){printf("Cinquenta e ");}else
																			if(Resto==6){printf("Sessenta e ");}else
																			if(Resto==7){printf("Setenta e ");}else
																			if(Resto==8){printf("Oitenta e ");}else
																			if(Resto==9){printf("Noventa e ");}
																		}
																			Concordancia++;
																			Resto*=10;
																			QtdTotalExtenso-=Resto;
															}
															//======================VALORES UM A DEZ REAIS==================//
															Resto = QtdTotalExtenso/1;
																if(Resto>0){
																			if(Concordancia!=0){
																				if(Resto==1){printf("Um Reais");}
																			}else{
																				if(Resto==1){printf("Um Real");}
																			}
																			if(Resto==2){printf("Dois Reais");}
																			if(Resto==3){printf("Três Reais");}
																			if(Resto==4){printf("Quatro Reais");}
																			if(Resto==5){printf("Cinco Reais");}
																			if(Resto==6){printf("Seis Reais");}
																			if(Resto==7){printf("Sete Reais");}
																			if(Resto==8){printf("Oito Reais");}
																			if(Resto==9){printf("Nove Reais");}

																			QtdTotalExtenso-=Resto;
																}
                                                                if(QtdTotSac==0){
																	printf(" Nenhum valor sacado até o momento");
																}

                                printf(")\n");//Apenas para fechar o parenteses aberto no printf acima
                                printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
                                printf("\n\n");
                                system("pause");
                            }
							break;
/*===========================================================================================*/


//_______________________VALOR DE SALDO EXISTENTE__________________________
					case 2: printf("\nVocê escolheu a opção %d\n",opc2);
							system("pause");
							system("clear||cls");
							///////////////////////////////////////QUANTIDADE TOTAL DE DINHEIRO NO CAIXA//////////////////////////////////////////////
							//Os codigos abaixos exercem a mesma função usada para o saque, porem com uma das variaveis readaptada nessa parte
											printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
											printf("\nVALOR TOTAL DE DINHEIRO NO CAIXA:\n R$ %.2f (",QuantTotal);
											QtdTotalExtenso = QuantTotal;

										 //=======================VALORES DE 100 MIL REAIS PARA CIMA=================================//
										   /*Se a variavel Resto for maior que 1, significa que o valor
											 esta acima ou é igual ao do teste imposto entao ele entrara no laço*/
											Resto = QtdTotalExtenso/100000;
														if(Resto>0){
															if(QtdTotalExtenso/100000==1){//Nessa parte, se o valor divido por 100 mil for igual a 1 entra ele imprime "Cem mil reais" na tela e finaliza esta parte do programa
																printf("Cem mil reais");
															}else{//Caso contrario, significa que o valor é maior que 100 mil e então ele ira continuar com os testes
																printf("Cento e ");
																Concordancia++;//Variavel que sera usada em um teste condicinal no MIL e no UM para fazer as devidas impressões na tela de acordo com a concorcia verbal
															}
															QtdTotalExtenso-=100000;//Aqui tiramos 100 Mil do valor total, caso o valor seja acima disso, os laços continuaram
														}
										 //=======================VALORES ENTRE 10 E 100 MIL REAIS=================================//
															Resto = QtdTotalExtenso/10000;//Aqui é o mesmo processo dos valor de 100 Mil, mas reajustados para valores que divididos por 10 Mil sejam maiores de 1
															if(Resto>0){
																if(QtdTotalExtenso/10000==1){//Exatamente o mesmo teste de cima mas reajustado para 10 Mil
																	printf("Dez mil reais");
																}else
																//-----------EXTENSO DE VALORES ENTRE 11 E 19 MIL REAIS-----------------//
												//__________________________________________________________________________________________//
														/*As atribuições abaixo serão repetidas novamente a frente.
														  Aqui a variavel "AuxResto" recebera a divisão do valor total
														  por 10 mil e em seguida sera somado o Ajuste nela, pois como
														  foi explicado acima,a IDE não esta dando os valores corretos
														  então o valor sera reajustado, e ainda sera passado para uma
														  variavel inteira multiplicado por dez, e que sera de vital
														  importancia em varias parte do código*/
																	AuxResto = QtdTotalExtenso/10000;
																	AuxResto += Ajuste;
																	AuxInteiro = (AuxResto*10.0);
												//___________________________________________________________________________________________//

																	if(AuxResto>=1.1&&AuxResto<2){//Teste para os valores que podem estar entre 11 e 19 mil reias
																		//Caso a quantidade seja exata
																		if(QtdTotalExtenso/AuxInteiro==1000){//Se a divisão da Quantia pelo Inteiro da divisão acima for igual a MIL significa que o valor é exato

																			if(AuxInteiro==11){printf("Onze Mil Reais");QtdTotalExtenso=0;}else//A variavel "QuantiaDinheiro",neste trecho, é zerada para que não exista problemas abaixo
																			if(AuxInteiro==12){printf("Doze Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==13){printf("Treze Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==14){printf("Quartoze Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==15){printf("Quinze Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==16){printf("Dezesseis Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==17){printf("Dezessete Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==18){printf("Dezeoito Mil Reais");QtdTotalExtenso=0;}else
																			if(AuxInteiro==19){printf("Dezenove Mil Reais");QtdTotalExtenso=0;}
																		}else{
																		//Caso não seja
																			if(AuxResto<1.2){printf("Onze Mil ");QtdTotalExtenso-=11000;Resto=0;}else//Neste trecho, tiramos o valor absoluto da "QuantiaDinheiro" e zeramos "Resto" para que não haja um somatorio errado nos teste a seguir
																			if(AuxResto<1.3){printf("Doze Mil ");QtdTotalExtenso-=12000;Resto=0;}else
																			if(AuxResto<1.4){printf("Treze Mil ");QtdTotalExtenso-=13000;Resto=0;}else
																			if(AuxResto<1.5){printf("Quartoze Mil ");QtdTotalExtenso-=14000;Resto=0;}else
																			if(AuxResto<1.6){printf("Quinze Mil ");QtdTotalExtenso-=15000;Resto=0;}else
																			if(AuxResto<1.7){printf("Dezesseis Mil ");QtdTotalExtenso-=16000;Resto=0;}else
																			if(AuxResto<1.8){printf("Dezessete Mil ");QtdTotalExtenso-=17000;Resto=0;}else
																			if(AuxResto<1.9){printf("Dezeoito Mil ");QtdTotalExtenso-=18000;Resto=0;}else
																			if(AuxResto>1.9){printf("Dezenove Mil ");QtdTotalExtenso-=19000;Resto=0;}

																			for(count=1;count<=9;count++){//O conectivo "e" não aparecera em todas as situações que algum dos testes acima de verdairo, entao ele só aparecera caso o valor apos o absoluto seja como: 19,400 ou 20,600 ou 14,700 e etc..
																				if(QtdTotalExtenso/100==count){
																					printf(" e ");
																				}
																			}
																		}
																	}

																	//__________________EXTENSO DE VALORES ACIMA OU IGUAIS A 20 MIL REAIS_________________//
																	else{
																		//--------Valores exatos-------------//
																		if(QtdTotalExtenso/AuxInteiro==1000){
																			if(AuxInteiro==20){printf("Vinte Mil Reais");}
																			if(AuxInteiro==30){printf("Trinta Mil Reais");}
																			if(AuxInteiro==40){printf("Quarenta Mil Reais");}
																			if(AuxInteiro==50){printf("Cinquenta Mil Reais");}
																			if(AuxInteiro==60){printf("Sessenta Mil Reais");}
																			if(AuxInteiro==70){printf("Setenta Mil Reais");}
																			if(AuxInteiro==80){printf("Oitenta Mil Reais");}
																			if(AuxInteiro==90){printf("Noventa Mil Reais");}
																		}
																		//-----Valores acima de 20 Mil e Abaixo de 21 Mil(por exemplo)----//
																		if(AuxResto>9.0&&AuxResto<9.1){printf("Noventa Mil ");}else
																		if(AuxResto>8.0&&AuxResto<8.1){printf("Oitenta Mil ");}else
																		if(AuxResto>7.0&&AuxResto<7.1){printf("Setenta Mil ");}else
																		if(AuxResto>6.0&&AuxResto<6.1){printf("Sessenta Mil ");}else
																		if(AuxResto>5.0&&AuxResto<5.1){printf("Cinquenta Mil ");}else
																		if(AuxResto>4.0&&AuxResto<4.1){printf("Quarenta Mil ");}else
																		if(AuxResto>3.0&&AuxResto<3.1){printf("Trinta Mil ");}else
																		if(AuxResto>2.0&&AuxResto<2.1){printf("Vinte Mil ");}else
																		if(AuxResto>1.0&&AuxResto<1.1){printf("Dez Mil ");}

																		//----------Para valores como: 99.600-------------//
																		if(AuxResto>1.1&&AuxResto<2){printf("Dez e ");}
																		if(AuxResto>2.1&&AuxResto<3){printf("Vinte e ");}
																		if(AuxResto>3.1&&AuxResto<4){printf("Trinta e ");}
																		if(AuxResto>4.1&&AuxResto<5){printf("Quarenta e ");}
																		if(AuxResto>5.1&&AuxResto<6){printf("Cinquenta e ");}
																		if(AuxResto>6.1&&AuxResto<7){printf("Sessenta e ");}
																		if(AuxResto>7.1&&AuxResto<8){printf("Setenta e ");}
																		if(AuxResto>8.1&&AuxResto<9){printf("Oitenta e ");}
																		if(AuxResto>9.1){printf("Noventa e ");}
																	}
																	Concordancia++;
																	Resto*=10000;//Essa variavel é multiplicada, nesse caso, por 10 MIL e a "QtdTotalExtenso" é subtraida por ela em seguida
																	QtdTotalExtenso-=Resto;
																		for(count=1;count<=9;count++){//Um outro teste de conectivo é feito aqui para os valores que estão entre 20 e 21 Mil ou 30 e 31 Mil(por exemplo, pois se extende até 90 mil)
																			if(QtdTotalExtenso/100==count){
																				printf(" e ");
																			}
																		}
															}
															/*A grande maioria do codigo acima se repetira abaixo, apenas em alguns pontos
															  que foram tomados outros caminhos, então sera comentado daqui para baixo
															  apenas estes pontos*/

												//======================VALORES ENTRE MIL E DEZ MIL REAIS==================//
															Resto = QtdTotalExtenso/1000;
															if(Resto>0){
																if(QtdTotalExtenso/1000==1){
																	if(Concordancia>0){printf("Um ");}
																	printf("Mil Reais");
																}else{
																	AuxResto = QtdTotalExtenso / 1000;
																	AuxResto += Ajuste;
																	AuxInteiro = (AuxResto*10.0);

														/*O valores de estão entre 1000 e 9999 terão os teste mais diversificados do resto
														  pois é mais facil usar laços de repetição com eles evitando assim varios blocos de "printf"*/
																  //------------PARTE MAIOR DO NUMERO---------------//
																		if(Concordancia>0){//Teste de concordanticia que verificara se o valor dever ser "MIL REAIS" ou "UM MIL REAIS"
																			if(Resto==1){printf("Um");}
																		}
																		if(Resto==2){printf("Dois");}//Os demais apenas serao imprimidos de acordo com seus valores
																		if(Resto==3){printf("Três");}
																		if(Resto==4){printf("Quatro");}
																		if(Resto==5){printf("Cinco");}
																		if(Resto==6){printf("Seis");}
																		if(Resto==7){printf("Sete");}
																		if(Resto==8){printf("Oito");}
																		if(Resto==9){printf("Nove");}

															/*Colocarei abaixo das variaveis dos laços exemplos de valores que podem ser assumidos*/

																		//----------Caso o valor se exato, como: 2,000 ou 3,000 reais---------------//
																			I=0;//Variavel que permite a entrada nos laços de repetições
																			for(count=2;count<10;count++){
																				if(AuxInteiro==count*10){printf(" Mil reais");I=1;}
																				//     20    ==  2  *10 --->  Nesse caso, seria imprimido "Dois Mil Reais na tela" e a variavel recebe "I" para que não seja feito mais nenhum texto com esses valores

																			}

																		//--------Caso o valor esteja entre 1,001 e 1,099 reais, por exemplo----------//
																			 if(I==0){
																				if(AuxResto>Resto&&AuxResto<Resto+0.1){printf(" Mil e ");I=1;}
																				//    1.01 >  1  &&  1.01   <    1.1  --> Seria imprimido "(Um)MIL E " na tela e os testes continuaria abaixo
																			 }

																		//--------Caso o valor seja de 1,101 ou 2,101 reias (por exemplo)-------------//
																			if(I==0){
																				if(QtdTotalExtenso/AuxInteiro!=100){//Só entrar se o numero que esta apos o mil não for divisivel por 100
																					for(count=1;count<10;count++){
																						VarCount++;
																						if((AuxResto>Resto+(VarCount/10)) && (AuxResto<Resto+((VarCount+1)/10))){printf(" Mil ");I=1;}
																						  //  2.101 >  2  +    2    /10   &&    2.101    2  +    (2   +1) /10 -->  Imprimira "Dois Mil " e os teste continuariam abaico
																					}
																				}
																			}
																		//----------Caso o valor seja 1,100 ou 1,200 ou 1,300 reais exatos(por exemplo)--------//
																			if(I==0){
																		/*Para não ocorrer erros, se o valor for acima de 1000,
																		  vamos usar a variavel I para reajustar a soma dentro do laço*/
																				I = AuxInteiro/10;//O resultado é multiplicado por 10 abaixo, se o AuxInteiro fosse 46 por acaso
																								  //a variavel "I" recebera 4, e permitira que na tela seja impresso "Três Mil e " por exemplo
																				for(count=1;count<10;count++){
																					if(AuxInteiro==(10*I)+count){printf(" Mil e ");I=1;}
																				}
																			}
																			Concordancia++;
																			Resto*=1000;
																			QtdTotalExtenso-=Resto;
																}
															}
															//======================VALORES ENTRE CEM E MIL REAIS==================//
															Resto = QtdTotalExtenso/100;
															if(Resto>0){
																	if(QtdTotalExtenso/100==1){
																		printf("Cem Reais");
																	}else{
																		AuxResto=QtdTotalExtenso/100;
																	//-----Valores exatos como 200 ou 300 reias--------//
																		if(AuxResto==2){printf("Duzentos Reais");}else
																		if(AuxResto==3){printf("Trezentos Reais");}else
																		if(AuxResto==4){printf("Quatrocentos Reais");}else
																		if(AuxResto==5){printf("Quinhetos Reais");}else
																		if(AuxResto==6){printf("Seiscentos Reais");}else
																		if(AuxResto==7){printf("Setecentos Reais");}else
																		if(AuxResto==8){printf("Oitocentos Reais");}else
																		if(AuxResto==9){printf("Novecentos Reais");}else
																	 //-----------Valores não exatos como 151 ou 203 reais--------//
																		if(Resto==1){printf("Cento e ");}else
																		if(Resto==2){printf("Duzentos e ");}else
																		if(Resto==3){printf("Trezentos e ");}else
																		if(Resto==4){printf("Quatrocentos e ");}else
																		if(Resto==5){printf("Quinhetos e ");}else
																		if(Resto==6){printf("Seiscentos e ");}else
																		if(Resto==7){printf("Setecentos e ");}else
																		if(Resto==8){printf("Oitocentos e ");}else
																		if(Resto==9){printf("Novecentos e ");}
																	}
																		Concordancia++;
																		Resto*=100;
																		QtdTotalExtenso-=Resto;
															}
															//======================VALORES DEZ A CEM REAIS==================//
															Resto = QtdTotalExtenso/10.0;
															if(Resto>0){
																		if(QtdTotalExtenso/10.0==1){
																		   printf("Dez Reais");
																		}
																		else{
																			AuxResto=QtdTotalExtenso/10.0;
																			AuxInteiro = (AuxResto*10.0)+Ajuste;
																		//----------Extenso para valores inteiros de 11 a 19 reais----------//
																			if(AuxInteiro==11){printf("Onze Reais");Resto=0;}else
																			if(AuxInteiro==12){printf("Doze Reais");Resto=0;}else
																			if(AuxInteiro==13){printf("Treze Reais");Resto=0;}else
																			if(AuxInteiro==14){printf("Quatorze Reais");Resto=0;}else
																			if(AuxInteiro==15){printf("Quinze Reais");Resto=0;}else
																			if(AuxInteiro==16){printf("Dezesseis Reais");Resto=0;}else
																			if(AuxInteiro==17){printf("Dezessete Reais");Resto=0;}else
																			if(AuxInteiro==18){printf("Dezoito Reais");Resto=0;}else
																			if(AuxInteiro==19){printf("Dezenove Reais");Resto=0;}else

																		 //------Extenso para valores exatos como 20 ou 30 ou 50 reais------//
																			if(AuxInteiro==20){printf("Vinte Reais");}else
																			if(AuxInteiro==30){printf("Trinta Reais");}else
																			if(AuxInteiro==40){printf("Quarenta Reais");}else
																			if(AuxInteiro==50){printf("Cinquenta Reais");}else
																			if(AuxInteiro==60){printf("Sessenta Reais");}else
																			if(AuxInteiro==70){printf("Setenta Reais");}else
																			if(AuxInteiro==80){printf("Oitenta Reais");}else
																			if(AuxInteiro==90){printf("Noventa Reais");}else

																		 //Caso todos os testes acima resultem em falso, os valores estarão acima de 20
																			if(Resto==2){printf("Vinte e ");}else
																			if(Resto==3){printf("Trinta e ");}else
																			if(Resto==4){printf("Quarenta e ");}else
																			if(Resto==5){printf("Cinquenta e ");}else
																			if(Resto==6){printf("Sessenta e ");}else
																			if(Resto==7){printf("Setenta e ");}else
																			if(Resto==8){printf("Oitenta e ");}else
																			if(Resto==9){printf("Noventa e ");}
																		}
																			Concordancia++;
																			Resto*=10;
																			QtdTotalExtenso-=Resto;
															}
															//======================VALORES UM A DEZ REAIS==================//
															Resto = QtdTotalExtenso/1;
																if(Resto>0){
																			if(Concordancia!=0){
																				if(Resto==1){printf("Um Reais");}
																			}else{
																				if(Resto==1){printf("Um Real");}
																			}
																			if(Resto==2){printf("Dois Reais");}
																			if(Resto==3){printf("Três Reais");}
																			if(Resto==4){printf("Quatro Reais");}
																			if(Resto==5){printf("Cinco Reais");}
																			if(Resto==6){printf("Seis Reais");}
																			if(Resto==7){printf("Sete Reais");}
																			if(Resto==8){printf("Oito Reais");}
																			if(Resto==9){printf("Nove Reais");}

																			QtdTotalExtenso-=Resto;
																}
																if(QuantTotal==0){
																	printf(" Nenhum valor existênte ");
																}

							printf(")\n");//Apenas para fechar o parenteses aberto no printf acima
							printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
							printf("\n\n");
							system("pause");
							break;
     /*===========================================================================================*/

  //___________________QUANTIDADE DE CÉDULAS EXISTENTES NO CAIXA_________________________
					case 3: printf("\nVocê escolheu a opção %d\n",opc2);
							system("pause");
							system("clear||cls");
								  printf("QUANTIDADE DE CADA CÉDULA AINDA EXISTENTE\n");
								  printf("\nR$ 500,00 --> %d cédulas\n",QtdC500);
								  printf("R$ 150,00 --> %d cédulas\n",QtdC150);
								  printf("R$ 50,00  --> %d cédulas\n",QtdC50);
								  printf("R$ 20,00  --> %d cédulas\n",QtdC20);
								  printf("R$ 10,00  --> %d cédulas\n",QtdC10);
								  printf("R$ 5,00   --> %d cédulas\n",QtdC5);
								  printf("R$ 2,00   --> %d cédulas\n",QtdC2);
								  printf("R$ 1,00   --> %d cédulas\n",QtdC1);
								  printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
											printf("\nVALOR TOTAL DE NOTAS NO CAIXA:\n %d (",QtdTotCed);

                                    //--------------------------EXTENSO------------------------//

																	QtdTotalExtenso=QtdTotCed;//Usaremos a mesma variavel que foi usada acima
																	Resto = QtdTotalExtenso/10000;//Aqui é o mesmo processo dos valor de 100 Mil, mas reajustados para valores que divididos por 10 Mil sejam maiores de 1
																	if(Resto>0){
																		if(QtdTotalExtenso/10000==1){//Exatamente o mesmo teste de cima mas reajustado para 10 Mil
																			printf("Dez mil Notas");
																		}else

																	AuxResto = QtdTotalExtenso/10000;
																	AuxResto += Ajuste;
																	AuxInteiro = (AuxResto*10.0);

																	if(AuxResto>=1.1&&AuxResto<2){//Teste para os valores que podem estar entre 11 e 19 mil Notas
																		//Caso a quantidade seja exata
																		if(QtdTotalExtenso/AuxInteiro==1000){//Se a divisão da Quantia pelo Inteiro da divisão acima for igual a MIL significa que o valor é exato

																			if(AuxInteiro==11){printf("Onze Mil Notas");QtdTotalExtenso=0;}else//A variavel "QuantiaDinheiro",neste trecho, é zerada para que não exista problemas abaixo
																			if(AuxInteiro==12){printf("Doze Mil Notas");QtdTotalExtenso=0;}else
																			if(AuxInteiro==13){printf("Treze Mil Notas");QtdTotalExtenso=0;}else
																			if(AuxInteiro==14){printf("Quartoze Mil Notas");QtdTotalExtenso=0;}else
																			if(AuxInteiro==15){printf("Quinze Mil Notas");QtdTotalExtenso=0;}else
																			if(AuxInteiro==16){printf("Dezesseis Mil Notas");QtdTotalExtenso=0;}else
																			if(AuxInteiro==17){printf("Dezessete Mil Notas");QtdTotalExtenso=0;}else
																			if(AuxInteiro==18){printf("Dezeoito Mil Notas");QtdTotalExtenso=0;}else
																			if(AuxInteiro==19){printf("Dezenove Mil Notas");QtdTotalExtenso=0;}
																		}else{
																		//Caso não seja
																			if(AuxResto<1.2){printf("Onze Mil ");QtdTotalExtenso-=11000;Resto=0;}else//Neste trecho, tiramos o valor absoluto da "QuantiaDinheiro" e zeramos "Resto" para que não haja um somatorio errado nos teste a seguir
																			if(AuxResto<1.3){printf("Doze Mil ");QtdTotalExtenso-=12000;Resto=0;}else
																			if(AuxResto<1.4){printf("Treze Mil ");QtdTotalExtenso-=13000;Resto=0;}else
																			if(AuxResto<1.5){printf("Quartoze Mil ");QtdTotalExtenso-=14000;Resto=0;}else
																			if(AuxResto<1.6){printf("Quinze Mil ");QtdTotalExtenso-=15000;Resto=0;}else
																			if(AuxResto<1.7){printf("Dezesseis Mil ");QtdTotalExtenso-=16000;Resto=0;}else
																			if(AuxResto<1.8){printf("Dezessete Mil ");QtdTotalExtenso-=17000;Resto=0;}else
																			if(AuxResto<1.9){printf("Dezeoito Mil ");QtdTotalExtenso-=18000;Resto=0;}else
																			if(AuxResto>1.9){printf("Dezenove Mil ");QtdTotalExtenso-=19000;Resto=0;}

																			for(count=1;count<=9;count++){//O conectivo "e" não aparecera em todas as situações que algum dos testes acima de verdairo, entao ele só aparecera caso o valor apos o absoluto seja como: 19,400 ou 20,600 ou 14,700 e etc..
																				if(QtdTotalExtenso/100==count){
																					printf(" e ");
																				}
																			}
																		}
																	}

																	//__________________EXTENSO DE VALORES ACIMA OU IGUAIS A 20 MIL REAIS_________________//
																	else{
																		//--------Valores exatos-------------//
																		if(QtdTotalExtenso/AuxInteiro==1000){
																			if(AuxInteiro==20){printf("Vinte Mil Notas");}
																			if(AuxInteiro==30){printf("Trinta Mil Notas");}
																			if(AuxInteiro==40){printf("Quarenta Mil Notas");}
																			if(AuxInteiro==50){printf("Cinquenta Mil Notas");}
																			if(AuxInteiro==60){printf("Sessenta Mil Notas");}
																			if(AuxInteiro==70){printf("Setenta Mil Notas");}
																			if(AuxInteiro==80){printf("Oitenta Mil Notas");}
																			if(AuxInteiro==90){printf("Noventa Mil Notas");}
																		}
																		//-----Valores acima de 20 Mil e Abaixo de 21 Mil(por exemplo)----//
																		if(AuxResto>9.0&&AuxResto<9.1){printf("Noventa Mil ");}else
																		if(AuxResto>8.0&&AuxResto<8.1){printf("Oitenta Mil ");}else
																		if(AuxResto>7.0&&AuxResto<7.1){printf("Setenta Mil ");}else
																		if(AuxResto>6.0&&AuxResto<6.1){printf("Sessenta Mil ");}else
																		if(AuxResto>5.0&&AuxResto<5.1){printf("Cinquenta Mil ");}else
																		if(AuxResto>4.0&&AuxResto<4.1){printf("Quarenta Mil ");}else
																		if(AuxResto>3.0&&AuxResto<3.1){printf("Trinta Mil ");}else
																		if(AuxResto>2.0&&AuxResto<2.1){printf("Vinte Mil ");}else
																		if(AuxResto>1.0&&AuxResto<1.1){printf("Dez Mil ");}

																		//----------Para valores como: 99.600-------------//
																		if(AuxResto>1.1&&AuxResto<2){printf("Dez e ");}
																		if(AuxResto>2.1&&AuxResto<3){printf("Vinte e ");}
																		if(AuxResto>3.1&&AuxResto<4){printf("Trinta e ");}
																		if(AuxResto>4.1&&AuxResto<5){printf("Quarenta e ");}
																		if(AuxResto>5.1&&AuxResto<6){printf("Cinquenta e ");}
																		if(AuxResto>6.1&&AuxResto<7){printf("Sessenta e ");}
																		if(AuxResto>7.1&&AuxResto<8){printf("Setenta e ");}
																		if(AuxResto>8.1&&AuxResto<9){printf("Oitenta e ");}
																		if(AuxResto>9.1){printf("Noventa e ");}
																	}
																	Concordancia++;
																	Resto*=10000;//Essa variavel é multiplicada, nesse caso, por 10 MIL e a "QtdTotalExtenso" é subtraida por ela em seguida
																	QtdTotalExtenso-=Resto;
																		for(count=1;count<=9;count++){//Um outro teste de conectivo é feito aqui para os valores que estão entre 20 e 21 Mil ou 30 e 31 Mil(por exemplo, pois se extende até 90 mil)
																			if(QtdTotalExtenso/100==count){
																				printf(" e ");
																			}
																		}
																}
															/*A grande maioria do codigo acima se repetira abaixo, apenas em alguns pontos
															  que foram tomados outros caminhos, então sera comentado daqui para baixo
															  apenas estes pontos*/

													//======================VALORES ENTRE MIL E DEZ MIL Notas==================//
															Resto = QtdTotalExtenso/1000;
															if(Resto>0){
																if(QtdTotalExtenso/1000==1){
																	if(Concordancia>0){printf("Um ");}
																	printf("Mil Notas");
																}else{
																	AuxResto = QtdTotalExtenso / 1000;
																	AuxResto += Ajuste;
																	AuxInteiro = (AuxResto*10.0);
																  //------------PARTE MAIOR DO NUMERO---------------//
																		if(Concordancia>0){//Teste de concordanticia que verificara se o valor dever ser "MIL Notas" ou "UM MIL Notas"
																			if(Resto==1){printf("Um");}
																		}
																		if(Resto==2){printf("Dois");}//Os demais apenas serao imprimidos de acordo com seus valores
																		if(Resto==3){printf("Três");}
																		if(Resto==4){printf("Quatro");}
																		if(Resto==5){printf("Cinco");}
																		if(Resto==6){printf("Seis");}
																		if(Resto==7){printf("Sete");}
																		if(Resto==8){printf("Oito");}
																		if(Resto==9){printf("Nove");}

															/*Colocarei abaixo das variaveis dos laços exemplos de valores que podem ser assumidos*/

																		//----------Caso o valor se exato, como: 2,000 ou 3,000 Notas---------------//
																			I=0;//Variavel que permite a entrada nos laços de repetições
																			for(count=2;count<10;count++){
																				if(AuxInteiro==count*10){printf(" Mil Notas");I=1;}

																			}

																		//--------Caso o valor esteja entre 1,001 e 1,099 Notas, por exemplo----------//
																			 if(I==0){
																				if(AuxResto>Resto&&AuxResto<Resto+0.1){printf(" Mil e ");I=1;}
																			 }

																		//--------Caso o valor seja de 1,101 ou 2,101 reias (por exemplo)-------------//
																			if(I==0){
																				if(QtdTotalExtenso/AuxInteiro!=100){//Só entrar se o numero que esta apos o mil não for divisivel por 100
																					for(count=1;count<10;count++){
																						VarCount++;
																						if((AuxResto>Resto+(VarCount/10)) && (AuxResto<Resto+((VarCount+1)/10))){printf(" Mil ");I=1;}
																					}
																				}
																			}
																		//----------Caso o valor seja 1,100 ou 1,200 ou 1,300 reais exatos(por exemplo)--------//
																			if(I==0){
																		/*Para não ocorrer erros, se o valor for acima de 1000,
																		  vamos usar a variavel I para reajustar a soma dentro do laço*/
																				I = AuxInteiro/10;//O resultado é multiplicado por 10 abaixo, se o AuxInteiro fosse 46 por acaso
																								  //a variavel "I" recebera 4, e permitira que na tela seja impresso "Três Mil e " por exemplo
																				for(count=1;count<10;count++){
																					if(AuxInteiro==(10*I)+count){printf(" Mil e ");I=1;}
																				}
																			}
																			Concordancia++;
																			Resto*=1000;
																			QtdTotalExtenso-=Resto;
																}
															}
															//======================VALORES ENTRE CEM E MIL NOTAS==================//
															Resto = QtdTotalExtenso/100;
															if(Resto>0){
																	if(QtdTotalExtenso/100==1){
																		printf("Cem Notas");
																	}else{
																		AuxResto=QtdTotalExtenso/100;
																	//-----Valores exatos como 200 ou 300 reias--------//
																		if(AuxResto==2){printf("Duzentas Notas");}else
																		if(AuxResto==3){printf("Trezentas Notas");}else
																		if(AuxResto==4){printf("Quatrocentas Notas");}else
																		if(AuxResto==5){printf("Quinhetas Notas");}else
																		if(AuxResto==6){printf("Seiscentas Notas");}else
																		if(AuxResto==7){printf("Setecentas Notas");}else
																		if(AuxResto==8){printf("Oitocentas Notas");}else
																		if(AuxResto==9){printf("Novecentas Notas");}else
																	 //-----------Valores não exatos como 151 ou 203 reais--------//
																		if(Resto==1){printf("Cento e ");}else
																		if(Resto==2){printf("Duzentos e ");}else
																		if(Resto==3){printf("Trezentos e ");}else
																		if(Resto==4){printf("Quatrocentos e ");}else
																		if(Resto==5){printf("Quinhetos e ");}else
																		if(Resto==6){printf("Seiscentos e ");}else
																		if(Resto==7){printf("Setecentos e ");}else
																		if(Resto==8){printf("Oitocentos e ");}else
																		if(Resto==9){printf("Novecentos e ");}
																	}
																		Concordancia++;
																		Resto*=100;
																		QtdTotalExtenso-=Resto;
															}
															//======================VALORES DEZ A CEM Notas==================//
															Resto = QtdTotalExtenso/10.0;
															if(Resto>0){
																		if(QtdTotalExtenso/10.0==1){
																		   printf("Dez Notas");
																		}
																		else{
																			AuxResto=QtdTotalExtenso/10.0;
																			AuxInteiro = (AuxResto*10.0)+Ajuste;
																		//----------Extenso para valores inteiros de 11 a 19 reais----------//
																			if(AuxInteiro==11){printf("Onze Notas");Resto=0;}else
																			if(AuxInteiro==12){printf("Doze Notas");Resto=0;}else
																			if(AuxInteiro==13){printf("Treze Notas");Resto=0;}else
																			if(AuxInteiro==14){printf("Quatorze Notas");Resto=0;}else
																			if(AuxInteiro==15){printf("Quinze Notas");Resto=0;}else
																			if(AuxInteiro==16){printf("Dezesseis Notas");Resto=0;}else
																			if(AuxInteiro==17){printf("Dezessete Notas");Resto=0;}else
																			if(AuxInteiro==18){printf("Dezoito Notas");Resto=0;}else
																			if(AuxInteiro==19){printf("Dezenove Notas");Resto=0;}else

																		 //------Extenso para valores exatos como 20 ou 30 ou 50 reais------//
																			if(AuxInteiro==20){printf("Vinte Notas");}else
																			if(AuxInteiro==30){printf("Trinta Notas");}else
																			if(AuxInteiro==40){printf("Quarenta Notas");}else
																			if(AuxInteiro==50){printf("Cinquenta Notas");}else
																			if(AuxInteiro==60){printf("Sessenta Notas");}else
																			if(AuxInteiro==70){printf("Setenta Notas");}else
																			if(AuxInteiro==80){printf("Oitenta Notas");}else
																			if(AuxInteiro==90){printf("Noventa Notas");}else

																		 //Caso todos os testes acima resultem em falso, os valores estarão acima de 20
																			if(Resto==2){printf("Vinte e ");}else
																			if(Resto==3){printf("Trinta e ");}else
																			if(Resto==4){printf("Quarenta e ");}else
																			if(Resto==5){printf("Cinquenta e ");}else
																			if(Resto==6){printf("Sessenta e ");}else
																			if(Resto==7){printf("Setenta e ");}else
																			if(Resto==8){printf("Oitenta e ");}else
																			if(Resto==9){printf("Noventa e ");}
																		}
																			Concordancia++;
																			Resto*=10;
																			QtdTotalExtenso-=Resto;
															}
															//======================VALORES UM A DEZ Notas==================//
															Resto = QtdTotalExtenso/1;
																if(Resto>0){
																			if(Concordancia!=0){
																				if(Resto==1){printf("Uma Notas");}
																			}else{
																				if(Resto==1){printf("Uma Nota");}
																			}
																			if(Resto==2){printf("Dois Notas");}
																			if(Resto==3){printf("Três Notas");}
																			if(Resto==4){printf("Quatro Notas");}
																			if(Resto==5){printf("Cinco Notas");}
																			if(Resto==6){printf("Seis Notas");}
																			if(Resto==7){printf("Sete Notas");}
																			if(Resto==8){printf("Oito Notas");}
																			if(Resto==9){printf("Nove Notas");}

																			QtdTotalExtenso-=Resto;
																}
																if(QuantTotal==0){
																	printf(" Nenhuma cédula existente ");
																}

							printf(")\n");//Apenas para fechar o parenteses aberto no printf acima
							printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
							printf("\n\n");
							system("pause");
							break;
      /*===========================================================================================*/

        //------------------------ABASTECIMENTO DO MENU-------------------------------
					case 4: printf("\nVocê escolheu a opção %d\n",opc2);
							system("pause");
							do {
								system("cls");
								printf("\nMENU ABASTECER O CAIXA ELETRÔNICO");
								printf("\n\n(500) Cédulas de 500");
								printf("\n(150) Cédulas de 150");
								printf("\n(50) Cédulas de 50");
								printf("\n(20) Cédulas de 20");
								printf("\n(10) Cédulas de 10");
								printf("\n(5) Cédulas de 5");
								printf("\n(2) Cédulas de 2");
								printf("\n(1) Cédulas de 1");
								printf("\n(0) Voltar ao menu gerente");
								printf("\n\nDigite a opção: ");
								scanf("%d",&opc3);
								switch(opc3) {
								/*Aqui seram feitas todas as verificações e atribuicões da entrada de dinheiro no caixa
								  pelo gerente do banco*/
                            /*=====================================================================================================*/

									//Verificação da quantidade de entrada de notas no valor de 500
									//E atribução   tanto na quantia total do banco, quanto na contia total da nota
									inteiro=0;
									case 500:   printf("\nVocê escolheu a opção %d\n\n",opc3);
												system("pause");
													system("clear||cls");
													printf("Quantidade de cédulas insirida: ");
													   do{//Impedindo que seja depositado uma contia de cedulas alem do permido
															scanf("%f",&C500);//"C" signica cédula
																inteiro = C500;
																if(C500<0 || C500>100){
																	printf("O maximo de cédulas de 500 que podem ser inseridas é de 100\n");
																	printf("e o minimo deve ser de ZERO\n");
																	printf("Digite novamente: ");
																}else if(C500!=inteiro){//Erro caso o gerente coloque o valor de notas como ponto flutuante
                                                                    printf("O valor de notas colocadas no caixa deve ser um numero inteiro!\n");
                                                                    printf("Digite novamente: ");
																}
													   }while(C500<0 || C500>100||C500!=inteiro);
													   //Garantindo que o gerente não irá depositar mais do que é permitido
													   if(QtdC500<100&&(QtdC500+C500)<=100){
															QtdC500+=C500;      //Somando a quantidade de notas depositas a quantidade total do banco para de seja mostrado posteriormente
															Tot500 = 500 * C500;//Multiplicação para obter o total depositado
															QuantTotal+=Tot500;//Atribuindo total depositato a quantia total do caixa
															QtdTotCed+=C500;   //Somando a quantidade de cédulas inseridas a quantidade total do caixa

													   }else{//Se o gerente insistir em tentar colocar alem do permitido apareceram mensagens de erro
															printf("Esse depósito fará com que exceda a quantia limite(100) de notas de R$ 500,00\n");
															printf("Você poderá depositar mais desta nota quando um cliente sacar uma quantia dela\n");
															system("pause");
													   }
												break;
												/*OS PROCESSOS DESCRITOS ACIMA SERAM TODOS REPETIDOS ABAIXO POREM COM SEUS RESPECTIVOS VALORES
												  REAJUSTADO, ENTAO NÃO SERA COMENTADO TODAS AS PARTES DE TODOS OS PROCESSOS ABAIXO*/
									/*=====================================================================================================*/
									/*=====================================================================================================*/
									//Verificação da quantidade de entrada de notas no valor de 150
									//E atribução   tanto na quantia total do banco, quanto na contia total da nota
									case 150:   printf("\nVocê escolheu a opção %d\n",opc3);
												system("pause");
													system("clear||cls");
													printf("Quantidade de cédulas insirida: ");
													   do{
															scanf("%f",&C150);
                                                            inteiro = C150;
																if(C150<0 || C150>200){
																	printf("O maximo de cédulas de 150 que podem ser inseridas é de 200\n");
																	printf("e o minimo deve ser de ZERO\n");
																	printf("Digite novamente: ");
																}else if(C150!=inteiro){//Erro caso o gerente coloque o valor de notas como ponto flutuante
                                                                    printf("O valor de notas colocadas no caixa deve ser um numero inteiro!\n");
                                                                    printf("Digite novamente: ");
																}
													   }while(C150<0 || C150>200||C150!=inteiro);
													   //Garantindo que o gerente não irá depositar mais do que é permitido
													   if(QtdC150<200&&(QtdC150+C150)<=200){
															QtdC150+=C150;
															Tot150 = 150 * C150;
															QuantTotal+=Tot150;
															QtdTotCed+=C150;
													   }else{
															printf("Esse depósito fará com que exceda a quantia limite(200) de notas de R$ 150,00\n");
															printf("Você poderá depositar mais desta nota quando um cliente sacar uma quantia dela\n");
															system("pause");
													   }
												break;
									/*=====================================================================================================*/
									/*=====================================================================================================*/
									//Verificação da quantidade de entrada de notas no valor de 50
									//E atribução   tanto na quantia total do banco, quanto na contia total da nota
									case 50:    printf("\nVocê escolheu a opção %d\n",opc3);
												system("pause");
													system("clear||cls");
													printf("Quantidade de cédulas insirida: ");
													   do{
															scanf("%f",&C50);
															inteiro = C50;
																if(C50<0 || C50>400){
																	printf("O maximo de cédulas de 50 que podem ser inseridas é de 400\n");
																	printf("e o minimo deve ser de ZERO\n");
																	printf("Digite novamente: ");
																}else if(C50!=inteiro){//Erro caso o gerente coloque o valor de notas como ponto flutuante
                                                                    printf("O valor de notas colocadas no caixa deve ser um numero inteiro!\n");
                                                                    printf("Digite novamente: ");
																}
													   }while(C50<0 || C50>400||C50!=inteiro);
													   //Garantindo que o gerente não irá depositar mais do que é permitido
													   if(QtdC50<400&&(QtdC50+C50)<=400){
															QtdC50+=C50;
															Tot50 = 50 * C50;
															QuantTotal+=Tot50;
															QtdTotCed+=C50;
													   }else{
															printf("Esse depósito fará com que exceda a quantia limite(400) de notas de R$ 50,00\n");
															printf("Você poderá depositar mais desta nota quando um cliente sacar uma quantia dela\n");
															system("pause");
													   }
												break;
									/*=====================================================================================================*/
									/*=====================================================================================================*/
									//Verificação da quantidade de entrada de notas no valor de 20
									//E atribução   tanto na quantia total do banco, quanto na contia total da nota
									case 20:    printf("\nVocê escolheu a opção %d\n",opc3);
												system("pause");
													system("clear||cls");
													printf("Quantidade de cédulas insirida: ");
													   do{
															scanf("%f",&C20);
															inteiro=C20;
																if(C20<0 || C20>800){
																	printf("O maximo de cédulas de 20 que podem ser inseridas é de 800\n");
																	printf("e o minimo deve ser de ZERO\n");
																	printf("Digite novamente: ");
																}else if(C20!=inteiro){//Erro caso o gerente coloque o valor de notas como ponto flutuante
                                                                    printf("O valor de notas colocadas no caixa deve ser um numero inteiro!\n");
                                                                    printf("Digite novamente: ");
																}
													   }while(C20<0 || C20>800||C20!=inteiro);
													   //Garantindo que o gerente não irá depositar mais do que é permitido
													   if(QtdC20<800&&(QtdC20+C20)<=800){
															QtdC20+=C20;
															Tot20 = 20 * C20;
															QuantTotal+=Tot20;
															QtdTotCed+=C20;
													   }else{
															printf("Esse depósito fará com que exceda a quantia limite(800) de notas de R$ 20,00\n");
															printf("Você poderá depositar mais desta nota quando um cliente sacar uma quantia dela\n");
															system("pause");
													   }
												break;
									/*=====================================================================================================*/
									/*=====================================================================================================*/
									//Verificação da quantidade de entrada de notas no valor de 10
									//E atribução   tanto na quantia total do banco, quanto na contia total da nota
									case 10:    printf("\nVocê escolheu a opção %d\n",opc3);
												system("pause");
													system("clear||cls");
													printf("Quantidade de cédulas insirida: ");
													   do{
															scanf("%f",&C10);
															inteiro = C10;
																if(C10<0 || C10>1600){
																	printf("O maximo de cédulas de 10 que podem ser inseridas é de 1600\n");
																	printf("e o minimo deve ser de ZERO\n");
																	printf("Digite novamente: ");
																}else if(C10!=inteiro){//Erro caso o gerente coloque o valor de notas como ponto flutuante
                                                                    printf("O valor de notas colocadas no caixa deve ser um numero inteiro!\n");
                                                                    printf("Digite novamente: ");
																}
													   }while(C10<0 || C500>1600||C10!=inteiro);
													   //Garantindo que o gerente não irá depositar mais do que é permitido
													   if(QtdC10<1600&&(QtdC10+C10)<=1600){
															QtdC10+=C10;
															Tot10 = 10 * C10;
															QuantTotal+=Tot10;
															QtdTotCed+=C10;
													   }else{
															printf("Esse depósito fará com que exceda a quantia limite(1600) de notas de R$ 10,00\n");
															printf("Você poderá depositar mais desta nota quando um cliente sacar uma quantia dela\n");
															system("pause");
													   }
												break;
									/*=====================================================================================================*/
									/*=====================================================================================================*/
									//Verificação da quantidade de entrada de notas no valor de 5
									//E atribução   tanto na quantia total do banco, quanto na contia total da nota
									case 5:    printf("\nVocê escolheu a opção %d\n",opc3);
												system("pause");
													system("clear||cls");
													printf("Quantidade de cédulas insirida: ");
													   do{
															scanf("%f",&C5);
															inteiro = C5;
																if(C5<0 || C5>3200){
																	printf("O maximo de cédulas de 5 que podem ser inseridas é de 3200\n");
																	printf("e o minimo deve ser de ZERO\n");
																	printf("Digite novamente: ");
																}else if(C5!=inteiro){//Erro caso o gerente coloque o valor de notas como ponto flutuante
                                                                    printf("O valor de notas colocadas no caixa deve ser um numero inteiro!\n");
                                                                    printf("Digite novamente: ");
																}
													   }while(C5<0 || C5>3200||C5!=inteiro);
													   //Garantindo que o gerente não irá depositar mais do que é permitido
													   if(QtdC5<3200&&(QtdC5+C5)<=3200){
															QtdC5+=C5;
															Tot5 = 5 * C5;
															QuantTotal+=Tot5;
															QtdTotCed+=C5;
													   }else{
															printf("Esse depósito fará com que exceda a quantia limite(3200) de notas de R$ 5,00\n");
															printf("Você poderá depositar mais desta nota quando um cliente sacar uma quantia dela\n");
															system("pause");
													   }
												break;
									/*=====================================================================================================*/
									/*=====================================================================================================*/
									//Verificação da quantidade de entrada de notas no valor de 2
									//E atribução   tanto na quantia total do banco, quanto na contia total da nota
									case 2:     printf("\nVocê escolheu a opção %d\n",opc3);
												system("pause");
													system("clear||cls");
													printf("Quantidade de cédulas insirida: ");
													   do{
															scanf("%f",&C2);
															inteiro=C2;
																if(C10<0 || C2>6400){
																	printf("O maximo de cédulas de 2 que podem ser inseridas é de 6400\n");
																	printf("e o minimo deve ser de ZERO\n");
																	printf("Digite novamente: ");
																}else if(C2!=inteiro){//Erro caso o gerente coloque o valor de notas como ponto flutuante
                                                                    printf("O valor de notas colocadas no caixa deve ser um numero inteiro!\n");
                                                                    printf("Digite novamente: ");
																}
													   }while(C2<0 || C2>6400||C2!=inteiro);
													   //Garantindo que o gerente não irá depositar mais do que é permitido
													   if(QtdC2<6400&&(QtdC2+C2)<=6400){
															QtdC2+=C2;
															Tot2 = 2 * C2;
															QuantTotal+=Tot2;
															QtdTotCed+=C2;
													   }else{
															printf("Esse depósito fará com que exceda a quantia limite(6400) de notas de R$ 2,00\n");
															printf("Você poderá depositar mais desta nota quando um cliente sacar uma quantia dela\n");
															system("pause");
													   }
												break;
									/*=====================================================================================================*/
									/*=====================================================================================================*/
									//Verificação da quantidade de entrada de notas no valor de 1
									//E atribução   tanto na quantia total do banco, quanto na contia total da nota
									case 1:     printf("\nVocê escolheu a opção %d\n",opc3);
												system("pause");
													system("clear||cls");
													printf("Quantidade de cédulas insirida: ");
													   do{
															scanf("%f",&C1);
															inteiro = C1;
																if(C1<0 || C1>12800){
																	printf("O maximo de cédulas de 1 que podem ser inseridas é de 12800\n");
																	printf("e o minimo deve ser de ZERO\n");
																	printf("Digite novamente: ");
																}else if(C1!=inteiro){//Erro caso o gerente coloque o valor de notas como ponto flutuante
                                                                    printf("O valor de notas colocadas no caixa deve ser um numero inteiro!\n");
                                                                    printf("Digite novamente: ");
																}
													   }while(C1<0 || C1>12800||C1!=inteiro);
													   //Garantindo que o gerente não irá depositar mais do que é permitido
													   if(QtdC1<12800&&(QtdC1+C1)<=12800){
															QtdC1+=C1;
															Tot1 = 1 * C1;
															QuantTotal+=Tot1;
															QtdTotCed+=C1;
													   }else{
															printf("Esse depósito fará com que exceda a quantia limite(12800) de notas de R$ 1,00\n");
															printf("Você poderá depositar mais desta nota quando um cliente sacar uma quantia dela\n");
															system("pause");
													   }
												break;
									/*=====================================================================================================*/
									case 0:     break;
									default:printf("\nOpção inválida!\n");
											system("pause");
											break;
								}
							} while(opc3!=0);
							break;
					case 5: break;
					default:printf("\nOpção inválida!\n");
							system("pause");
							break;
				}
			} while(opc2!=5);
		}
	}
} while(opc1!=3);

return 0;
}

