#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "graph.h"
#include "random.h"
using namespace std;

int bidders = -1, items = -1, vmin = -1, vmax = -1, degree = -1, mult = 10;
double radius;
char *filename;

double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void usage(char *argv){
  cout << argv << " [-n bidders_and_items | -b bidders -i items] " <<
                  "-h max_value [-r radius | -d degree] -m multiplier filename" << endl;
  cout << "-n bidders_and_items: The number of bidders and the number of items are both equal to bidders_and_items." << endl;
  cout << "-b bidders: Sets the number of bidders." << endl;
  cout << "-i items: Sets the number of items." << endl;
  cout << "-h max_value: Defines the maximum multiplier for a bidder." << endl;
  cout << "-r radius: Defines the radius for the neighbourhod of a bidder." << endl;
  cout << "-d degree: Expected degree" << endl;
  cout << "-m multiplier: Multlipies the value by multipler before rounding to integer. Used so the value are sufficiently diferent." << endl;
  cout << "\t Default: 10" << endl;
  cout << "filename: The filename for the file to be saved." << endl;
}

int setup(int argc, char **argv) {
  int c; 
  opterr = 0; 
  while ((c = getopt (argc, argv, "n:b:i:l:h:r:d:m:")) != -1) {
    switch (c) {
      case 'n':
        bidders = atoi(optarg);
        items = atoi(optarg);
      case 'b':
        bidders = atoi(optarg);
        break;
      case 'i':
        items = atoi(optarg);
        break;
      case 'h':
        vmax = atof(optarg);
        break;
      case 'r':
      	radius = atof(optarg);
      	break;
      case 'd':
        degree = atoi(optarg);
        break;
      case 'm':
        mult = atoi(optarg);
        break;
      case '?':
        if (optopt == 'b' || optopt == 'i' || optopt == 'h' || optopt == 'n' || optopt == 'm')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        return -1;
      default:
        return -1;
    }
  }
  for (int index = optind; index < argc; index++)
    filename = argv[index];
  if(!filename)
    return -1;
  if(bidders <= 0 || items <= 0 || vmax <= 1 || (degree <= 0 && radius <= 0) || mult <= 0)
    return -1;
  return 1;
}

int main(int argc, char **argv) {
  double pi = atan(1)*4;
	double *bidderx, *biddery, *itemx, *itemy;
	double *multiplier;
	srand(time(0));
	if (setup(argc, argv) < 0) {
    	usage(argv[0]);
    	exit(0);
  }
  if(degree > 1) {
    radius = sqrt(degree / (items * pi));
  }
  graph g = graph_new(bidders, items);
  bidderx = (double *)malloc(bidders * sizeof(double));
  biddery = (double *)malloc(bidders * sizeof(double));
	itemx = (double *)malloc(items * sizeof(double));
	itemy = (double *)malloc(items * sizeof(double));
	multiplier = (double *)malloc(bidders * sizeof(double));
	for (int i = 0; i < bidders; i++) {
		bidderx[i] = randDouble();
		biddery[i] = randDouble();
		multiplier[i] = randDouble()*vmax;
	}
	for (int j = 0; j < items; j++) {
		itemx[j] = randDouble();
		itemy[j] = randDouble();
	}
	for(int i = 0; i < bidders; i++) {
    	for(int j = 0; j < items; j++) {
    		double d = dist(bidderx[i], biddery[i], itemx[j], itemy[j]);
      		if(d <= radius) {
      			double value = 1.0 + (multiplier[i] * mult) / d;
      			graph_add_edge(g, i, j, value);
      		}
    	}
  	}	
 	graph_save(g, filename); 	
	return 0;
}