#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include "sat.h"

typedef struct s_individual
{
	unsigned char *var;
	double fitness;
}t_individual;

/**
  * mutationFunc: aplica as mutacoes, quando necessario, sobre os individuos da populacao
  * recombinationFunc: utilizando algum criterio, combina os individuos da populacao, gerando outros
  * stopFunc: determina se o algoritmo deve parar ou nao
  */
/*
void geneticAlgorithm(void *data,
                     (void)(*mutationFunc)(void *data),
                     (void)(*recombinationFunc)(void *data),
                     (void)(*stopFunc)(void *data));
*/
/**
  * implementacao de um algoritmo genetico para solucao do problema do max-sat
  */
unsigned int geneticAlgorithmSat(t_instance *inst,
                         unsigned int popSize,
                         unsigned int maxIterations,
                         double mutationChance);

void satCrossover(t_individual *father, t_individual *mother, t_individual *child,unsigned int numVars);

void satMutation(t_individual *individual,int mutationLimit,unsigned int numVars);

int compareIndividuals(const void *a, const void *b);

#endif // GENETIC_ALGORITHM_H

