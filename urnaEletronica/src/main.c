
#include <asf.h>
#include "stdint.h"
#include "multitarefas.h"

/*
 * Prototipos das tarefas
 */
void printOptions(void);
void readVote(void);
void encrypt(void);
void printResults(void);


/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_3			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_4			(TAM_MINIMO_PILHA + 24)


/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_3[TAM_PILHA_3];
uint32_t PILHA_TAREFA_4[TAM_PILHA_4];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	system_init();
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(printOptions, "printOptions", PILHA_TAREFA_1, TAM_PILHA_1, 1);
	
	CriaTarefa(readVote, "readVote", PILHA_TAREFA_2, TAM_PILHA_2, 2);

	CriaTarefa(encrypt, "encrypt", PILHA_TAREFA_3, TAM_PILHA_3, 3);
	
	CriaTarefa(readVote, "printResults", PILHA_TAREFA_4, TAM_PILHA_4, 4);
	
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}

/* Tarefas de exemplo que usam funcoes para suspender/continuar as tarefas */

void printOptions(void)
{
	
}

void readVote(void)
{
	
}

void encrypt(void)
{
	
}


void printResults(void)
{

}