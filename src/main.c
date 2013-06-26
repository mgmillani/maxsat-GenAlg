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

		t_instance inst;
		satLoadInstance(&inst,argv[i]);
		//showInstance(&inst);
		//makeGlpkData(&inst);
		//roda 10 vezes e faz a media
		unsigned int j;
		clock_t tavg = 0;
		double satisfyAverage = 0;
		double iniAvg = 0;
		for(j=0 ; j<3 ; j++)
		{
			clock_t t0 = clock();
			iniAvg += geneticAlgorithmSat(&inst,200,100,0.1);
			tavg += clock() - t0;
			satisfyAverage += satAmountSatisfied(&inst);
			//ERR("%u\t%u\n",10*(j+1),satAmountSatisfied(&inst));
		}
		satisfyAverage /= 3;
		tavg /= 3;
		iniAvg /= 3;
		//ERR("Variables: %u\n",inst.numVars);
		ERR("Clauses: %u\n",inst.numClauses);
		ERR("Result: %s\n",argv[i]);
		ERR("Initial: %lf (%lf%%)\n",iniAvg,100*iniAvg/inst.numClauses)
		ERR("Amount satisfied: %lf\n",satisfyAverage);
		ERR("Percent satisfied: %lf\n",(double)satisfyAverage/inst.numClauses);
		ERR("Delay: %lu clocks = %lf s\n",tavg,(double)(tavg)/CLOCKS_PER_SEC);
		//ERR("Clocks per sec: %ld\n",CLOCKS_PER_SEC);
		ERR("####\n####\n");
	}

	return 0;

}
