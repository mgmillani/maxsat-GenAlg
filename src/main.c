#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "read.h"
#include "geneticAlgorithm.h"
#include "sat.h"

#include "debug.h"

int main(int argc, char *argv[])
{
	srand(time(NULL));

	int i;
	for(i=1 ; i<argc ; i++)
	{
		clock_t t0= clock();
		t_instance inst;
		satLoadInstance(&inst,argv[i]);
		geneticAlgorithmSat(&inst,300,300,0.1);
		ERR("Variables: %u\n",inst.numVars);
		ERR("Clauses: %u\n",inst.numClauses);
		ERR("Result: %s\n",argv[i]);
		ERR("Amount satisfied: %u\n",satAmountSatisfied(&inst));
		ERR("Percent satisfied: %lf\n",satPercentSatisfied(&inst));
		ERR("Delay: %lu clocks = %lf s\n",clock() - t0,(double)(clock() - t0)/CLOCKS_PER_SEC);
		ERR("Clocks per sec: %ld\n",CLOCKS_PER_SEC);
		ERR("####\n####\n");
	}

	return 0;

}
