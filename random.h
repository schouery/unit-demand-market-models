#ifndef RANDOM_H_
#define RANDOM_H_
#include "graph.h"

double randDouble();

double randGaussian();

int randBool();

int randInt(int max);

double gaussian_price(int market_price, double percentage);

#endif /* RANDOM_H_ */
