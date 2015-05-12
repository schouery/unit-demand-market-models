#include <unistd.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "random.h"
#include <vector>
using namespace std;

int bidders = -1, items = -1, vmin = 512, vmax = 1023;
char *filename;

void usage(char *argv){
  cout << argv << " [-n bidders_and_items | -b bidders -i items]"
              << " -l min_value -h max_value" << endl;
  cout << "-l min_value: Defines the minium market price of an item." << endl; 
  cout << "\t Default: 512" << endl;
  cout << "-h min_value: Defines the maximum market price of an item." << endl;
  cout << "\t Default: 1023" << endl;
  cout << "filename: The filename for the file to be saved." << endl;
}

int setup(int argc, char **argv) {
  int c; 
  opterr = 0; 
  while ((c = getopt (argc, argv, "n:b:i:l:h:")) != -1) {
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
      case 'l':
        vmin = atoi(optarg);
        break;
      case 'h':
        vmax = atoi(optarg);
        break;
      case '?':
        if (optopt == 'n' || optopt == 'b' || optopt == 'i' || optopt == 'l' || optopt == 'h')
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
  if(bidders <= 0 || items <= 0)
    return -1;
  return 1;
}

int main(int argc, char *argv[]) {
  srand(time(0));
  if (setup(argc, argv) < 0) {
    usage(argv[0]);
    exit(0);
  }
  vector<vector<int> > matrix(bidders, vector<int>(items));
  for (int i = 0; i < bidders; ++i) {
    for (int j = 0; j < items; ++j) {
      matrix[i][j] = vmin + randInt(vmax-vmin + 1);
    }
  }
  ofstream file;
  file.open(filename);
  file << bidders << " " << items << " " << bidders*items << endl;
  for(int i = 0; i < bidders; i++) {
    for(int j = 0; j < items; j++) {
      file << i << " " << j << " " << matrix[i][j] << endl;
    }
  }
  file.close();
  return 0;
}
