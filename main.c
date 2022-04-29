#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int opcao();
//, int t, int *dia, int *mes, int *ano, int data_atual
void cadastroEvento(char **nome, int *qtd_pessoas,int t);
void exibir_eventos(char **nome,int *qtd, int t);
void dataAtual();

int main(int argc, char *argv[]) 
{
	int sair = 0, t_e = 0;
	int *qtd_pessoas;
	char **nome_evento;
	char **nome_pessoas;
	
	//variáveis de data
	int *dia, *mes, *ano;
	dia = (int *)malloc(t_e * sizeof(int));
	mes = (int *)malloc(t_e * sizeof(int));
	ano = (int *)malloc(t_e * sizeof(int));
	
	//---Alocação das variáveis principais---
	qtd_pessoas = (int *)malloc(t_e * sizeof(int));
    
    nome_pessoas = (char**)malloc(t_e * sizeof(char*));
    
    nome_evento = (char**)malloc(t_e * sizeof(char *));
	dataAtual();
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
	
	/*
	int i;
	for(i=0;i<t_e;i++)
	{
		printf("Evento - %d: %s\n",i+1,nome_evento[i]);
		printf("Quantidade de pessoas: %d\n",qtd_pessoas[i]);
	}*/
	return 0;
}

//---Função para cadastro de eventos
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

//---Função para exibir tela inicial de opções---
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

void dataAtual()
{
	time_t data_hora_segundos;
	struct tm *timeinfo;
	time(&data_hora_segundos);
	timeinfo = localtime(&data_hora_segundos);
	char data_hoje[80];
	strftime(data_hoje,80,"%d/%m/%Y",timeinfo);
	strtok(data_hoje,"\n");
	printf("Data: %s\n",data_hoje);
}


