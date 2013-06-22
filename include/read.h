#ifndef READ_H
#define READ_H

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
  * carrega um instancia do SAT a partir de um arquivo CNF
  * se a instancia passada for NULL, aloca uma nova
  */
t_instance *satLoadInstance(t_instance *,const char *fname);

/**
  * aloca uma clausula com o numero dado de literais
  */
t_clause *clauseInit(t_clause *clause,unsigned int literals);

/**
  * printa todas as clausulas da instancia
  */
void showInstance(t_instance *inst);

/**
  * printa as variaveis da clausula
  */
void showClause(t_clause *clause);

#endif // READ_H

