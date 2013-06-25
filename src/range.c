#include "range.h"

/**
  * dada a faixa acumulada e um valor, determina em qual faixa esse valor pertence
  */
unsigned int rangeSearch(double *vector, double value,unsigned int size)
{
	unsigned int pos = size*(value/vector[size-1]);
	if(pos >= size)
		return size-1;
	else
		return pos;
}
