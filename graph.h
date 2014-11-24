#ifndef GRAPH_H 
#define GRAPH_H 

typedef struct graph graph;

//------------- functions --------------------//
struct graph* createGraph();
int insertVertex(struct graph*, int);
void insertEdge(struct graph*, int, int, int);

void addPath(struct path**, int);
void removePath(struct path**, int);

int edgeWeight(struct edge*, int);
int pathLength(struct graph*, struct path*);
void tsp_backtracking(struct graph*, struct path*, int);

void emptyMemory(struct graph*);
void printGraph(struct graph*);

#endif
