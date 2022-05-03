#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int opcao();
void cadastroEvento(char **nome, int *qtd_pessoas,int t, int *dia, int *mes, int *ano, int data_atual);
void exibir_eventos(char **nome,int *qtd, int t, int *dia, int *mes, int *ano);
int dataAtual();
int extrairNumero(char *valor);
int inverteData(char *num1);
void cadastroPessoas(char ***nome, char **nome_evento, int *idade, int t);

int main02(int argc, char *argv[]) 
{
	int sair = 0, t_e = 0, t_p=0;
	int *qtd_pessoas;
	char **nome_evento;
	char ***nome_pessoas;
	int *idade;
	int data;
	//variáveis de data
	int *dia, *mes, *ano, *data_evento;
	dia = (int *)malloc(t_e * sizeof(int));
	mes = (int *)malloc(t_e * sizeof(int));
	ano = (int *)malloc(t_e * sizeof(int));
	//---------------------------------------------------
	//---Alocação das variáveis principais---
	qtd_pessoas = (int *)malloc(t_e * sizeof(int));
    nome_pessoas = (char***)malloc(t_e * sizeof(char**));
    nome_evento = (char**)malloc(t_e * sizeof(char *));
    idade = (int *)malloc(t_e * sizeof(int));
    //---------------------------------------------------
	data = dataAtual();
	printf("%d\n",data);
	do
	{
		sair = opcao();
		//--Cadastrar eventos
		switch(sair)
		{
			case 1:
				cadastroEvento(nome_evento,qtd_pessoas,t_e,dia,mes,ano,data);
				t_e++;
				nome_evento = (char**) realloc(nome_evento, (t_e+1)*sizeof(char*));
          	 	qtd_pessoas = (int*) realloc(qtd_pessoas,(t_e+1)*sizeof(int));
          	    dia = (int*) realloc(dia,(t_e+1)*sizeof(int));
            	mes = (int*) realloc(mes,(t_e+1)*sizeof(int));
            	ano = (int*) realloc(ano,(t_e+1)*sizeof(int));
            	break;
           //--Cadastrar pessoas nos eventos
		    case 2:
            	printf("Opcao indisponivel!\n");
            	break;
            case 3:
            	exibir_eventos(nome_evento,qtd_pessoas,t_e,dia,mes,ano);
            	break;
            case 4:
				break;	
			default:
				printf("\nOpcao invalida!!!\n");
		}
		
	}while(sair!=4);
	
	return 0;
}
//--- [0] - Função para exibir tela inicial de opções---
int opcao()
{
    int escolha;
    printf("Escolha uma opcao:\n");
    printf("1 - cadastrar evento sdfsdf;\n");
    printf("2 - Participar de um evento;\n");
    printf("3 - Exibir eventos cadastrados;\n");
    printf("4 - sair;\n");
    scanf("%d",&escolha);
    getchar();
    return escolha;
}

//---[1] - Função para cadastro de eventos
void cadastroEvento(char **nome, int *qtd_pessoas,int t, int *dia, int *mes, int *ano, int data_atual)
{
	int data, dia_, mes_, ano_;
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
	getchar();
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
	getchar();
}

//--- [3] - Exibir eventos cadastrados---
void exibir_eventos(char **nome,int *qtd, int t, int *dia, int *mes, int *ano)
{
	int i;
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
	
	return extrairNumero(num2);
}


