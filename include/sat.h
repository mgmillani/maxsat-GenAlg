#ifndef SAT_H
#define SAT_H

typedef struct s_clause
{
	unsigned int *var; //tera size posicoes
	unsigned char *signal; //var xor signal = literal
	unsigned int size;

}t_clause;

typedef struct s_instance
{
	unsigned char *var;  //tera numvars posicoes
	unsigned int numVars; //numero de variaveis do problema
	t_clause *clause;
	unsigned int numClauses;

}t_instance;

/**
  * determina a porcentagem de clausulas satisfeitas
  */
double satPercentSatisfied(t_instance *inst);

/**
  * determina o numero de clausulas satisfeitas
  */
unsigned int satAmountSatisfied(t_instance *inst);

void satPrintVars(t_instance *inst);

#endif // SAT_H

