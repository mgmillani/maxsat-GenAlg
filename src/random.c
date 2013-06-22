#include <stdlib.h>
int randrange(int max)
{
    return ((max+1) * ((double) rand())/((double)RAND_MAX+1));
}
