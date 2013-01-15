#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct {
  int bidders, items, edges;
  int *dbidder, *ditem;
  int **b_adj, **i_adj;
  int *bweight;
  double **adj;
  int *Nb;
} Graph;

typedef Graph * graph;

graph graph_new(int bidders, int items);
void graph_add_edge(graph g, int bidder, int item, double value);
void graph_print(graph g);
void graph_save(graph g, char *filename);
void randNb(graph g, int min, int max);

#endif /* GRAPH_H_ */