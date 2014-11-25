#ifndef GRAPH_H 
#define GRAPH_H 

typedef struct graph graph;
typedef struct edge edge;
typedef struct vertex vertex;
typedef struct path path;

//------------- functions --------------------//
struct graph* createGraph();
int getGraphSize(struct graph*);
int insertVertex(struct graph*, int);
void insertEdge(struct graph*, int, int, int);

struct path* createPath(int);
void startingPath(struct path*, int);

void addPath(struct path*, int);
void shiftPath(struct path*, int, int, int);
void removePath(struct path*, int, int);

int edgeWeight(struct edge*, int);
int totalPathWeight(struct graph*, struct path*);
void tsp_backtracking(struct graph*, struct path*, struct path*, int* );

void emptyMemoryGraph(struct graph*);
void emptyMemoryPath(struct path*);

#endif
