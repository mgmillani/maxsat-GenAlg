#include <stdio.h>

#include "sat.h"

/**
  * determina a porcentagem de clausulas satisfeitas
  */
double satPercentSatisfied(t_instance *inst)
{
	return 100.0*(double)satAmountSatisfied(inst)/inst->numClauses;
}

void satPrintVars(t_instance *inst)
{
	unsigned int i;
	for(i=0 ; i<inst->numVars ; i++)
	{
		printf("X%u = %u\n",i,(unsigned int)inst->var[i]);
	}
}

unsigned int satAmountSatisfied(t_instance *inst)
{
	//para cada clausula
	unsigned int i;
	unsigned int satisfied = 0;
	for(i=0 ; i<inst->numClauses ; i++)
	{
		//para cada variavel
		unsigned int j;
		unsigned int sum = 0;
		t_clause *c = inst->clause+i;
		for(j=0 ; j<c->size ; j++)
		{
			//calcula o valor verdade da varivel dentro da clausula
			sum += inst->var[c->var[j]] ^ c->signal[j];
		}
		if(sum!=0)
			satisfied++;
	}

	return satisfied;
}
