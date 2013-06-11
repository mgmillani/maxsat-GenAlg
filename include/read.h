#ifndef READ_H
#define READ_H

typedef struct s_instance
{

	unsigned char *var;  //tera numvars posicoes
	unsigned int numVars; //numero de variaveis do problema
	t_clause *clause;
	unsigned int numClauses;

}t_instance;

#endif // READ_H

