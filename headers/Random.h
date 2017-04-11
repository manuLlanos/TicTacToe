//		Random(a,b) returns a random integer between a and b.
//		Random(a) returns a random integer between 0 and a.

#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <cstdlib>

#define SEED srand( (unsigned)time(NULL))			//seed initialization

unsigned Random(unsigned, unsigned );

unsigned Random(unsigned);

double RandomPorcentaje();

#endif
