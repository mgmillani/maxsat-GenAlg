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

#endif // SAT_H

