#include <stdlib.h>
#include <string.h>

#include "geneticAlgorithm.h"
#include "range.h"
#include "random.h"
#include "sat.h"

#include "debug.h"

/**
  * avaliationFunc :
  * mutationFunc: aplica as mutacoes, quando necessario, sobre um individuo
  * recombinationFunc: utilizando algum criterio, combina dois individuos da populacao, gerando outros
  * stopFunc: determina se o algoritmo deve parar ou nao. Retorna true se sim, falso caso contrario
  */
  /*
void geneticAlgorithm(void *data, void *population, unsigned int memberSize,
                     (double)(*avaliationFunc)(void *data)
                     (void)(*mutationFunc)(void *data,void *individual),
                     (void)(*recombinationFunc)(void *data,void *father, void *mother, void *child),
                     (void)(*stopFunc)(void *data))
{

	while(!stopFunc(data))
	{
		recombinationFunc(data);
		mutationFunc(data);
	}

}
*/
/**
  * implementacao de um algoritmo genetico para solucao do problema do max-sat
  * atribui a melhor solucao encontrada a inst->var
  */
void geneticAlgorithmSat(t_instance *inst, unsigned int popSize, unsigned int maxIterations, double mutationChance)
{

	unsigned int i;
	double best = 0;
	unsigned char *origVar = inst->var;
	int mutationLimit = RAND_MAX*mutationChance;
	//gera uma populacao inicial aleatoria
	t_individual pop0[popSize];
	//buffer auxiliar para facilitar as operacoes
	t_individual pop1[popSize];
	t_individual *pop = pop0;
	t_individual *buf = pop1;

	double accFitness[popSize];
	for(i=0 ; i < popSize ; i++)
	{
		pop0[i].var = malloc(inst->numVars*sizeof(*pop0[i].var));
		pop1[i].var = malloc(inst->numVars*sizeof(*pop1[i].var));
		unsigned int j;
		for(j=0 ; j < inst->numVars; j++)
		{
			pop0[i].var[j] = rand() & 1;
		}
		inst->var = pop0[i].var;
		pop0[i].fitness = satPercentSatisfied(inst);
		if(pop0[i].fitness > best)
		{
			best = pop0[i].fitness;
			memcpy(origVar,pop0[i].var,sizeof(*origVar)*inst->numVars);
		}
	}

	for(i=0 ; i<maxIterations ; i++)
	{
		//ordena a populacao
		qsort(pop,popSize,sizeof(*pop),compareIndividuals);
		//faz o crossover, gerando uma nova populacao de mesmo tamanho
		//primeiro, gera a aptidao acumulada para fazer uma selecao enviesada
		unsigned int j;
		accFitness[0] = pop[0].fitness;
		for(j=1 ; j<popSize ; j++)
			accFitness[j] = pop[j].fitness + accFitness[j-1];

		//gera uma nova populacao de mesmo tamanho
		for(j=0 ; j<popSize ; j++)
		{
			//escolhe um pai aleatoriamente mas com base na aptidao acumulada
			unsigned int father = rangeSearch(accFitness,rand()%((unsigned int)accFitness[popSize-1]),popSize-1);
			unsigned int mother = rangeSearch(accFitness,rand()%((unsigned int)accFitness[popSize-1]),popSize-1);
			satCrossover(pop+father,pop+mother,buf+j,inst->numVars);
			//aplica uma mutacao
			if(rand() > mutationLimit)
			{
				satMutation(buf+j,inst->numVars);
			}
			//calcula a aptidao do novo membro
			inst->var = buf[j].var;
			buf[j].fitness = satPercentSatisfied(inst);
		}
		//troca o buffer com a populacao
		t_individual *aux;
		aux = pop;
		pop = buf;
		buf = aux;
	}

	//libera a memoria

	for(i=0 ; i<popSize ; i++)
	{
		free(pop0[i].var);
		free(pop1[i].var);
	}


	inst->var = origVar;
}

void satCrossover(t_individual *father, t_individual *mother, t_individual *child,unsigned int numVars)
{
	unsigned int i,j;
	for(i=0,j=numVars/2 ; i<numVars/2 ; i++,j++)
	{
		child->var[i] = father->var[i];
		child->var[j] = mother->var[j];
	}
	//se for um numero impar de variaveis
	if((numVars&1) == 1)
	{
		child->var[numVars-1] = mother->var[numVars-1];
	}
}

void satMutation(t_individual *individual,unsigned int numVars)
{
	//troca uma variavel aleatoria
	unsigned int index = rand()%numVars;
	individual->var[index] ^= 1;
}

int compareIndividuals(const void *a, const void *b)
{
	const t_individual *c = a;
	const t_individual *d = b;

	return c->fitness - d->fitness;
}

