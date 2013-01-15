#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "random.h"
#include "graph.h"

double randDouble() {
	return ((double) rand()) / RAND_MAX;
}

double randGaussian() {
	static int haveNumber = 0;
	static double next;
	double v1, v2, s, multiplier;
	if (haveNumber) {
		haveNumber = 0;
		return next;
	} else {
		do { 
			v1 = 2 * randDouble() - 1;
			v2 = 2 * randDouble() - 1;
			s = v1 * v1 + v2 * v2;
		} while (s >= 1 || s == 0);
	  multiplier = sqrt(-2 * log(s)/s);
		next = v2 * multiplier;
		haveNumber = 1;
		return v1 * multiplier;
	}
}

int randBool() {
  if(randDouble() <= 0.5)
    return 0;
  else
    return 1;
}

int randInt(int max) {
  return randDouble()*max;
}

double gaussian_price(int market_price, double percentage) {
  double standard_deviation = percentage*market_price;
  double p = randGaussian()*standard_deviation + market_price;
  return (p >= 1) ? p : 1;
}
