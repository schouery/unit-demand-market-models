#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "graph.h"
#include "random.h"
#define STAR 2
using namespace std;

int bidders = -1, items = -1, ncharac = -1, nprefs = -1, vmin = -1, vmax = -1, deviation = 1, min_group_size = 1, max_group_size = 1;
char *filename;
double percentage = 0.1;

void rand_charac(int *charac, int ncharac) {
  for(int i = 0; i < ncharac; i++)
    charac[i] = randBool();
}

void rand_profile(int *profile, int ncharac, int nprefs) {
  int p = 0;
  while(p < nprefs) {
    int i = randInt(ncharac-1);
    if(profile[i] != STAR) {
      profile[i] = STAR;
      p++;
    }
  }
  for(int i = 0; i < ncharac; i++) {
    if(profile[i] != STAR) {
      profile[i] = randBool();
    }
  }  
}

bool match(int *charac, int *profile, int ncharac) {
  for(int i = 0; i < ncharac; i++) {
    if(profile[i] != STAR && charac[i] != profile[i]) {
      return false;
    }
  }
  return true;
}

void usage(char *argv){
  cout << argv << " [-n bidders_and_items | -b bidders -i items] -c number_of_characteristics -p number_of preferences" <<
                  "-l min_value -h max_value [-d deviation] [-g min_group_size -G max_group_size] filename" << endl;
  cout << "-n bidders_and_items: The number of bidders and the number of items are both equal to bidders_and_items." << endl;
  cout << "-b bidders: Sets the number of bidders." << endl;
  cout << "-i items: Sets the number of items." << endl;
  cout << "-c number_of_characteristics: Defines the number of characteristics that an item has." << endl;
  cout << "-p number_of_preferences: Defines the number of preferences of a bidder." << endl;
  cout << "-l min_value: Defines the minium market price of an item." << endl; 
  cout << "-h min_value: Defines the maximum market price of an item." << endl;
  cout << "-d deviation: The percentage of deviation. For exemple, if the mean price is (randomly) chosen as 10 and deviation is 0.2, then the standard deviation used is 2." << endl;
  cout << "\t Default: 0.1." << endl;
  cout << "-g min_group_size: The minimum size of bidders group." << endl;
  cout << "\t Default: 1." << endl;
  cout << "-G max_group_size: The maximum size of bidders group." << endl;
  cout << "\t Default: 1." << endl;
  cout << "filename: The filename for the file to be saved." << endl;
}

int setup(int argc, char **argv) {
  int c; 
  opterr = 0; 
  while ((c = getopt (argc, argv, "n:b:i:c:p:l:h:d:g:G:")) != -1) {
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
      case 'c':
        ncharac = atoi(optarg);
        break;
      case 'p':
        nprefs = atoi(optarg);
        break;
      case 'l':
        vmin = atoi(optarg);
        break;
      case 'h':
        vmax = atoi(optarg);
        break;
      case 'd':
        percentage = atof(optarg);
        break;
      case 'g':
        min_group_size = atoi(optarg);
        break;
      case 'G':
        max_group_size = atoi(optarg);
        break;
      case '?':
        if (optopt == 'b' || optopt == 'i' || optopt == 'c' || optopt == 'p' || optopt == 'l' ||
            optopt == 'h' || optopt == 'd')
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

  if(bidders <= 0 || items <= 0 || ncharac <= 0 || nprefs <= 0 || vmin <= 0 || vmax <= 0 || vmin > vmax || percentage <= 0 || percentage >= 1)
    return -1;
  return 1;
}

int main(int argc, char *argv[]) {
  srand(time(0));
  if (setup(argc, argv) < 0) {
    usage(argv[0]);
    exit(0);
  }
  graph g = graph_new(bidders, items);
  randNb(g, min_group_size, max_group_size + 1); 
  int **charac;
  charac = (int **)malloc(items * sizeof(int *));
  for(int j = 0; j < items; j++) {
    charac[j] = (int *)malloc(ncharac * sizeof(int));
    rand_charac(charac[j], ncharac);
  }
  int **profiles;
  profiles = (int **)malloc(bidders * sizeof(int *));
  for(int i = 0; i < bidders; i++) {
    profiles[i] = (int *)calloc(ncharac, sizeof(int));
    rand_profile(profiles[i], ncharac, nprefs);
  }
  int *market_price = (int *)malloc(items * sizeof(int));
  for(int j = 0; j < items; j++) {
    market_price[j] = randInt(vmax - vmin) + vmin;
  }
  for(int i = 0; i < bidders; i++) {
    for(int j = 0; j < items; j++) {
      if(match(charac[j], profiles[i], ncharac))
        graph_add_edge(g, i, j, 1.0 + gaussian_price(market_price[j], percentage));
    }
  }
  graph_save(g, filename);
  return 0;
}