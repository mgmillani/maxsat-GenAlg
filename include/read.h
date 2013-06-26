#ifndef READ_H
#define READ_H

#include "sat.h"

/**
  * carrega um instancia do SAT a partir de um arquivo CNF
  * se a instancia passada for NULL, aloca uma nova
  */
t_instance *satLoadInstance(t_instance *,const char *fname);

/**
  * aloca uma clausula com o numero dado de literais
  */
t_clause *clauseInit(t_clause *clause,unsigned int literals);

void makeGlpkData(t_instance *inst);

/**
  * printa todas as clausulas da instancia
  */
void showInstance(t_instance *inst);

/**
  * printa as variaveis da clausula
  */
void showClause(t_clause *clause);

#endif // READ_H

