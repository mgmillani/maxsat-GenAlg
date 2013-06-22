#include <stdlib.h>

#include "geneticAlgorithm.h"
#include "random.h"

#include "sat.h"

/**
  * avaliationFunc :
  * mutationFunc: aplica as mutacoes, quando necessario, sobre um individuo
  * recombinationFunc: utilizando algum criterio, combina dois individuos da populacao, gerando outros
  * stopFunc: determina se o algoritmo deve parar ou nao. Retorna true se sim, falso caso contrario
  */
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

void geneticAlgorithmSat(t_instance *inst, unsigned int popSize, unsigned int maxIterations, double mutationChance)
{

	unsigned int i;
	unsigned int mutationLimit = RAND_MAX*mutationChance;
	//gera uma populacao inicial aleatoria
	t_individual pop0[popSize];
	//buffer auxiliar para facilitar as operacoes
	t_individual pop1[popSize];
	t_individual *pop = pop0;
	t_individual *buf = pop1;
	double accFitness[popSize];
	for(i=0 ; i < popSize ; i++)
	{
		pop0[i].var = malloc(popSize*sizeof(*pop0[i].var));
		unsigned int j;
		for(j=0 ; j < inst->numVars)
		{
			pop0[i].var[j] = rand() & 1;
			pop0[i].fitness = satPercentSatisfied(pop0[1].var,inst);
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
			unsigned int father = randrange(accFitness[j]);
			unsigned int mother = randrange(accFitness[j]);
			satCrossover(pop+father,pop+mother,pop+j);
			//aplica uma mutacao
			if(rand() > mutationLimit)
			{
				satMutation(pop+j);
			}
		}
	}
}
