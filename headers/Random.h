//		Random(a,b) returns a random integer between a and b.
//		Random(a) returns a random integer between 0 and a.

#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <cstdlib>

#define SEED srand( (unsigned)time(NULL))			//seed initialization

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

#endif
