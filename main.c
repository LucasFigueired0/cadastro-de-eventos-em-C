#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <windows.h>

void cls(void)
{
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
     GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
 
    FillConsoleOutputCharacter(hConsole, TEXT(' '),
                   dwConSize, coordScreen, &cCharsWritten);
 
    GetConsoleScreenBufferInfo(hConsole, &csbi);
 
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
                               dwConSize, coordScreen, &cCharsWritten);
   
    SetConsoleCursorPosition(hConsole, coordScreen);
}

int opcao();
void cadastroEvento(char **nome, int *qtd_pessoas,int t, int *dia, int *mes, int *ano, int data_atual);
void exibir_eventos(char **nome,int *qtd, int t, int *dia, int *mes, int *ano);
int dataAtual();
int extrairNumero(char *valor);
int inverteData(char *num1);
int escolhaEvento(char **evento, int tE);
int cadastroPessoas(char **nome, char **nome_evento, int *idade, int t, int tP,int *id);
void participantes(char **nome, char **evento, int tP, int tE, int *id);

int main(int argc, char *argv[]) 
{
	int sair = 0, t_e = 0, t_p=0;
	int *qtd_pessoas;
	char **nome_evento;
	char **nome_pessoas;
	int *idade;
	int data;
	int aux=0;
	//-------------------
	int *id_evento;
	id_evento = (int *)malloc(t_p * sizeof(int));
	//------------------
	//Alocação das variáveis de data
	int *dia, *mes, *ano, *data_evento;
	dia = (int *)malloc(t_e * sizeof(int));
	mes = (int *)malloc(t_e * sizeof(int));
	ano = (int *)malloc(t_e * sizeof(int));
	//---------------------------------------------------
	//---Alocação das variáveis principais---
	qtd_pessoas = (int *)malloc(t_e * sizeof(int));
    nome_pessoas = (char**)malloc(t_e * sizeof(char*));
    nome_evento = (char**)malloc(t_e * sizeof(char *));
    idade = (int *)malloc(t_e * sizeof(int));
    //---------------------------------------------------
	
	data = dataAtual();
	//printf("%s\n",data);
	do
	{
		sair = opcao();
		switch(sair)
		{
			//--1 - Cadastrar eventos
			case 1:
				
				cadastroEvento(nome_evento,qtd_pessoas,t_e,dia,mes,ano,data);
				t_e++;
				nome_evento = (char**) realloc(nome_evento, (t_e+1)*sizeof(char*));
          	 	qtd_pessoas = (int*) realloc(qtd_pessoas,(t_e+1)*sizeof(int));
          	    dia = (int*) realloc(dia,(t_e+1)*sizeof(int));
            	mes = (int*) realloc(mes,(t_e+1)*sizeof(int));
            	ano = (int*) realloc(ano,(t_e+1)*sizeof(int));
            	break;
           //--2 - Cadastrar pessoas nos eventos
		    case 2:
            	aux = cadastroPessoas(nome_pessoas, nome_evento, idade, t_e, t_p, id_evento);
            	if(aux <= 0)
            	{
            		break;
				}
				else
				{
					t_p++;
            		nome_pessoas = (char**) realloc(nome_pessoas,(t_p+1)*sizeof(char*));
            		idade = (int*) realloc(idade,(t_p+1)*sizeof(int));
            		id_evento = (int*)realloc(id_evento,(t_p+1)*sizeof(int));
				}
            	break;
           //--3 - Exibir eventos cadastrados
            case 3:
            	exibir_eventos(nome_evento,qtd_pessoas,t_e,dia,mes,ano);
            	break;
            //--4 - Participantes
			case 4:
				participantes(nome_pessoas, nome_evento, t_p, t_e, id_evento);
				break;
           //--5 - Sair
            case 5:
				break;	
			default:
				printf("\nOpcao invalida!!!\n");
		}
		
	}while(sair!=5);
	
	
	
	return 0;
}
//--- [0] - Função para exibir tela inicial de opções---
int opcao()
{
    //cls();
	int escolha;
    printf("========================================\n");
	printf("Escolha uma opcao:\n");
    printf("1 - cadastrar evento;\n");
    printf("2 - Participar de um evento;\n");
    printf("3 - Exibir eventos cadastrados;\n");
    printf("4 - Exibir lista de participantes\n");
    printf("5 - sair\n");
    printf("========================================\n");
    scanf("%d",&escolha);
    getchar();
    return escolha;
}

//---[1] - Função para cadastro de eventos
void cadastroEvento(char **nome, int *qtd_pessoas,int t, int *dia, int *mes, int *ano, int data_atual)
{
	cls();
	int data, dia_, mes_, ano_, n=1;
	char nome01[80];
	int qtd=0;
	//--Entrada do nome do evento--
	printf("Digite o nome do evento: ");
	fgets(nome01,80,stdin);
	strtok(nome01,"\n");
	nome[t] = (char*) malloc(50*sizeof(char));
	strcpy(nome[t],nome01);
	
	//--Entrada da quantidade de pessoas--
	printf("Quantidade de pessoas: ");
	scanf("%d",&qtd);
	qtd_pessoas[t] = qtd;
	//getchar();
	
	//Entrada dos valores de data
	while(data_atual >= data)
	{
		printf("Data do evento:\n");
		printf("Dia: ");
		scanf("%d",&dia_);
		printf("Mes: ");
		scanf("%d",&mes_);
		printf("Ano: ");
		scanf("%d",&ano_);
		data = (ano_*100 + mes_) * 100+dia_;
		if(data_atual >= data)
		{
			printf("\nData invalida!\n");
		}
		else
		{
			break;
		}
	}
	dia[t] = dia_;
	mes[t] = mes_;
	ano[t] = ano_;
	
	printf("------------------------------------------\n");
	printf("------EVENTO CADASTRADO COM SUCESSO!------\n");
	printf("------------------------------------------\n");
	printf("\nDigite 0 para voltar ao menu anterior -> ");
	while(n!=0) scanf("%d",&n);
	//getchar();
}

//[2] - Função para cadastrar pessoas nos eventos
int cadastroPessoas(char **nome, char **nome_evento, int *idade, int t, int tP, int *id)
{
	cls();
	int opcao=-1, aux = 0,i,j;
	char auxNome[50];
	
	if(t<=0)
	{
		printf("\nNenhum evento disponivel!\n");
		aux = 0;
	}
	else
	{
		//Trecho para inserir o id do evento
		do
		{
			opcao == 0;
			printf("---Escolha o numero do evento--\n");
			for(i=0;i<t;i++)
			{
				printf("%d - %s\n",i+1,nome_evento[i]);
			}
			scanf("%d",&opcao);
			if(opcao<=0 || opcao > t)
			{
				printf("\nAlternativa invalida!!!\n");
			}
			else
			{
				opcao -= 1;
				aux += 1;
				break;
			}
		}while(opcao<=0 || opcao > t);
		getchar();
		//Trecho para inserir o nome
		printf("Digite seu nome: ");
		fgets(auxNome,50,stdin);
		strtok(auxNome,"\n");
	
		nome[tP] = (char*)malloc(50*sizeof(char));
		strcpy(nome[tP],auxNome);
		id[tP] = opcao;
	
		printf("------------------------------------------\n");
		printf("------CADASTRO EFETUADO COM SUCESSO!------\n");
		printf("------------------------------------------\n");
	
	}
	
	int n = 1;
	printf("\nDigite 0 para voltar ao menu anterior -> ");
	while(n!=0) scanf("%d",&n);
	return aux;
}

//--- [3] - Exibir eventos cadastrados---
void exibir_eventos(char **nome,int *qtd, int t, int *dia, int *mes, int *ano)
{
	cls();
	int i;
	if(t<=0)
	{
		printf("\nNenhum evento disponivel!\n");
	}
	else
	{
		for(i=0;i<t;i++)
		{
			printf("------------------------------------------\n");
			printf("Evento - %d: %s\n",i+1,nome[i]);
			printf("Quantidade de pessoas: %d\n",qtd[i]);
			if(dia[i] < 10 && mes[i] < 10)
			{
				printf("Data do evento 0%d/0%d/%d\n",dia[i],mes[i],ano[i]);
			}
			else if(dia[i] < 10 && mes[i]>=10)
			{
				printf("Data do evento 0%d/%d/%d\n",dia[i],mes[i],ano[i]);
			}
			else if(dia[i] > 10 && mes[i]<=10)
			{
				printf("Data do evento %d/0%d/%d\n",dia[i],mes[i],ano[i]);
			}
			else
			{
				printf("Data do evento %d/%d/%d\n",dia[i],mes[i],ano[i]);	
			}
		
			if(t==1)
			{
				printf("------------------------------------------\n");
			}
		}
		if(t>1)
		{
			printf("------------------------------------------\n");
		}
	}
	
	int n=1;
	printf("Digite 0 para voltar ao menu anterior -> ");
	while(n!=0) scanf("%d",&n);
}

//[4] - Função para filtrar participantes
void participantes(char **nome, char **evento, int tP, int t, int *id)
{
	
	int opcao;
	int aux=0;
	int i=0,j=0;
	int n = 1;
	
	
	if(t <= 0)
	{
		printf("\nNenhum evento disponivel!\n");
	}
	else
	{
		do
		{
			cls();
			printf("1 - Filtrar por evento\n2 - Listar todos os participantes\n3 - Sair\n");
			scanf("%d",&opcao);
			if(opcao == 1)
			{
				printf("---Escolha o um evento--\n");
				
				i=0;
				while(i<t)
				{
					printf("%d - %s\n",i+1,evento[i]);
					i++;
				}
				
				scanf("%d",&aux);
				while(aux<=0 || aux > t) 
				{
					printf("\nOpcao invalida, tente outra!\n");
					scanf("%d",&aux);
				}
				aux -= 1;
				printf("\n");
				printf("---%s\n---\n",evento[aux]);
				j=0;
				for(i=0;i<tP;i++)
				{
					if(id[i] == aux)
					{
						j++;
						printf("%d - %s\n",j, nome[i]);
					}
				}
				printf("\n");
				printf("\nDigite 0 para voltar -> ");
				while(n!=0) scanf("%d",&n);
				//cls();
			}
			else if(opcao == 2)
			{
				for(i=0;i<tP;i++)	
				{
					//cls();
					aux = 0;
					aux = id[i];
					printf("------------------------------\n");
					printf("%d - %s\n",i+1,nome[i]);
					printf("Evento: %s\n",evento[aux]);
					printf("Id do evento: %d\n",aux);
					printf("------------------------------\n");
				}
				printf("\nDigite 0 para voltar -> ");
				while(n!=0) scanf("%d",&n);
			}
			else if(opcao == 3)
			{
				printf("\nDigite 0 para voltar ao menu anterior -> ");
				while(n!=0) scanf("%d",&n);
				break;
			}	
			else
			{
				printf("\nOpcao invalida!!!\n");
			}			
		}while(opcao!=3);	
	}
	
	printf("\nDigite 0 para voltar ao menu anterior -> ");
	while(n!=0) scanf("%d",&n);
}

//Fução para exibir a hora atual
int dataAtual()
{
	int data_num;
	int data_num_invert;
	char data_char[20];
	
	time_t data_hora_segundos;
	struct tm *timeinfo;
	time(&data_hora_segundos);
	timeinfo = localtime(&data_hora_segundos);
	char data_hoje[80];
	strftime(data_hoje,80,"%d/%m/%Y",timeinfo);
	strtok(data_hoje,"\n");
	
	//printf("Data: %s\n",data_hoje);
	
	data_num = extrairNumero(data_hoje);
	sprintf(data_char,"%d",data_num);
	
	return inverteData(data_char);
}

//Função para obter os caracteres numericos da função dataAtual
int extrairNumero(char *valor)
{
	int num = 0;
	int i;
	
	for(i=0; valor[i] != '\0';i++)
	{
		if(isdigit(valor[i]))
		{
			num += (int)(valor[i])-'0';
			num *=10;
		}
	}
	
	return num /= 10;
}

int inverteData(char *num1)
{
	int j, r=0;
	char num2[20];
	
	for(j=0;j<8;j++)
	{
		if(j==0)
		{
			num2[j] = num1[4];
		}
		else if(j==1)
		{
			num2[j] = num1[5];
		}
		else if(j==2)
		{
			num2[j] = num1[6];
		}
		else if(j==3)
		{
			num2[j] = num1[7];
		}
		else if(j==4)
		{
			num2[j] = num1[2];
		}
		else if(j==5)
		{
			num2[j] = num1[3];
		}
		else if(j==6)
		{
			num2[j] = num1[0];
		}
		else if(j==7)
		{
			num2[j] = num1[1];
		}
	}
	
	//printf("%s\n", num2);
	return extrairNumero(num2);
}







