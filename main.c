#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int opcao();
//, int t, int *dia, int *mes, int *ano, int data_atual
void cadastroEvento(char **nome, int *qtd_pessoas,int t);
void exibir_eventos(char **nome,int *qtd, int t);
int dataAtual();
int extrairNumero(char *valor);
int inverteData(char *num1);

int main(int argc, char *argv[]) 
{
	int sair = 0, t_e = 0;
	int *qtd_pessoas;
	char **nome_evento;
	char **nome_pessoas;
	int data;
	//vari�veis de data
	int *dia, *mes, *ano;
	dia = (int *)malloc(t_e * sizeof(int));
	mes = (int *)malloc(t_e * sizeof(int));
	ano = (int *)malloc(t_e * sizeof(int));
	//---------------------------------------------------
	//---Aloca��o das vari�veis principais---
	qtd_pessoas = (int *)malloc(t_e * sizeof(int));
    nome_pessoas = (char**)malloc(t_e * sizeof(char*));
    nome_evento = (char**)malloc(t_e * sizeof(char *));
    //---------------------------------------------------
	data = dataAtual();
	printf("%d\n",data);
	do
	{
		sair = opcao();
		//--Cadastrar eventos
		if(sair == 1)
		{
			cadastroEvento(nome_evento,qtd_pessoas,t_e);
			t_e++;
			nome_evento = (char**) realloc(nome_evento, (t_e+1)*sizeof(char*));
            qtd_pessoas = (int*) realloc(qtd_pessoas,(t_e+1)*sizeof(int));
		}
		//--Exibir eventos cadastrados
		else if(sair == 3)
		{
			exibir_eventos(nome_evento,qtd_pessoas,t_e);
		}
	}while(sair!=4);
	
	return 0;
}

//---Fun��o para cadastro de eventos
void cadastroEvento(char **nome, int *qtd_pessoas, int t)
{
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
}

//---Fun��o para exibir tela inicial de op��es---
int opcao()
{
    int escolha;
    printf("Escolha uma opcao:\n");
    printf("1 - cadastrar evento;\n");
    printf("2 - Participar de um evento;\n");
    printf("3 - Exibir eventos cadastrados;\n");
    printf("4 - sair;\n");
    scanf("%d",&escolha);
    getchar();
    return escolha;
}

//---Exibir eventos cadastrados---
void exibir_eventos(char **nome,int *qtd, int t)
{
	int i;
	for(i=0;i<t;i++)
	{
		printf("------------------------------------------\n");
		printf("Evento - %d: %s\n",i+1,nome[i]);
		printf("Quantidade de pessoas: %d\n",qtd[i]);
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
	printf("Data: %s\n",data_hoje);
	data_num = extrairNumero(data_hoje);
	sprintf(data_char,"%d",data_num);
	
	return inverteData(data_char);
}

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
	num /= 10;
}

int inverteData(char *num1)
{
	int j, r=0;
	char num2[20];
	
	//sprintf(num1,"%d",data);
	
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
	
	return extrairNumero(num2);
}


