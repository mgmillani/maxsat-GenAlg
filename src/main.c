#include <stdio.h>
#include <stdlib.h>

#include "read.h"

#include "debug.h"

int main(int argc, char *argv[])
{
	int i;
	for(i=1 ; i<argc ; i++)
	{
		t_instance inst;
		satLoadInstance(&inst,argv[i]);
		ERR("Num Vars: %u\n",inst.numVars);
		//showInstance(&inst);
		makeGlpkData(&inst);
		ERR("***********\n");
	}

	return 0;

}
