#ifndef GRAPH_H 
#define GRAPH_H 

typedef struct graph graph;

//------------- functions --------------------//
struct graph* createGraph();
int insertVertex(struct graph*, int);
void insertEdge(struct graph*, int, int, int);

void emptyMemory(struct graph*);
void printGraph(struct graph*);

#endif
