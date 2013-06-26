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
		unsigned int k;

		satisfyAverage = 0;
		unsigned int step = 5;
		unsigned int repeat = 10;
		for(j=1 ; j<2 ; j++)
		{
			unsigned int k;
			satisfyAverage = 0;
			//for(k=0 ; k<repeat ; k++)
			//{
				clock_t t0 = clock();
				iniAvg += geneticAlgorithmSat(&inst,100,60,0.1);
				tavg += clock() - t0;
				satisfyAverage += satAmountSatisfied(&inst);
			//}
			//ERR("%u\t%lf\n",step*j,satisfyAverage/repeat);
		}

		ERR("Result: %s\n",argv[i]);
		ERR("Initial: %lf (%lf%%)\n",iniAvg,100*iniAvg/inst.numClauses)
		ERR("Amount satisfied: %lf\n",satisfyAverage);
		ERR("Percent satisfied: %lf\n",(double)satisfyAverage/inst.numClauses);
		ERR("Delay: %lu clocks = %lf s\n",tavg,(double)(tavg)/CLOCKS_PER_SEC);
		ERR("####\n####\n");
	}

	return 0;

}
