#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H


/**
  * mutationFunc: aplica as mutacoes, quando necessario, sobre os individuos da populacao
  * recombinationFunc: utilizando algum criterio, combina os individuos da populacao, gerando outros
  * stopFunc: determina se o algoritmo deve parar ou nao
  */
void geneticAlgorithm(void *data,
                     (void)(*mutationFunc)(void *data),
                     (void)(*recombinationFunc)(void *data),
                     (void)(*stopFunc)(void *data));

#endif // GENETIC_ALGORITHM_H

