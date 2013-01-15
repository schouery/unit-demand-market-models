#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "graph.h"
#include "random.h"
using namespace std;

int bidders = -1, items = -1, qmax = -1, max_edges = -1, min_group_size = 1, max_group_size = 1; 
double percentage = 0.1;
char *filename;

void usage(char *argv){
  cout << "usage: " << argv << " [-n bidders_and_items | -b bidders -i items] -e edges " <<
                  "-q max_quality [-d percentage_of_deviation] [-g min_group_size -G max_group_size] filename" << endl;
  cout << "-n bidders_and_items: The number of bidders and the number of items are both equal to bidders_and_items." << endl;
  cout << "-b bidders: Sets the number of bidders." << endl;
  cout << "-i items: Sets the number of items." << endl;
  cout << "-e edges: Number of edges of the graph." << endl;
  cout << "-q max_quality: Defines the maximum quality of an item." << endl;
  cout << "-d percentage_of_deviation: The percentage of deviation. For exemple, if the mean price is (randomly) chosen as 10 and deviation is 0.2, then the standard deviation used is 2." << endl;
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
  while ((c = getopt (argc, argv, "n:b:i:e:q:d:g:G:")) != -1) {
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
      case 'e':
        max_edges = atoi(optarg);
        break;
      case 'q':
        qmax = atoi(optarg);
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
        if (optopt == 'b' || optopt == 'i' || optopt == 'e' || optopt == 'q' || optopt == 'd')
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
  if(bidders <= 0 || items <= 0 || max_edges <= 0 || max_edges > bidders*items || qmax <= 0 || percentage <= 0 || percentage >= 1)
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
  for(int edges = 0; edges < max_edges; edges++)
  {
    bool found = false;
    while(!found) {
      int b = randInt(g->bidders);
      double q = randDouble();
      for(int i = 0; i < g->items && q > 0; i++) {
        double weight =  (double) (g->ditem[i] + 1) / (edges + g->items);
        if(q <= weight && !g->adj[b][i]) {
          graph_add_edge(g, b, i, 1);
          found = true;
        }            
        q -= weight;
      }
    }
  }
  for(int i = 0; i < g->bidders; i++) {
    for(int k = 0; k <= g->dbidder[i]; k++) {
      int j = g->b_adj[i][k];
      double quality = randDouble() * qmax;
      g->adj[i][j] = 1.0 + gaussian_price(quality / g->dbidder[i], percentage);    
    }
  }
  graph_save(g, filename);
  return 0;
}