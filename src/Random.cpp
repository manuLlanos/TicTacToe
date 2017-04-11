
#include "../headers/Random.h"

unsigned Random(unsigned m, unsigned M)
{
	return m + rand()%(M-m);
}

unsigned Random(unsigned M)
{
	return Random(0,M);
}

double RandomPorcentaje()				// return a percetage [0;1) with 4 precission digits
{
	return (double )Random(10000)/10000;
}
