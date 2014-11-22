#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct vertex{
	int element;
	int visited;
	int cost;
	struct edge* edgeList;
};

struct edge{
	int weight;
	int accsses;
	struct edge* prox;
};

struct graph{
	struct vertex* vertexList;
	int numVertex;
};


//------------------------- Operations about the graph -------------------------//
struct graph* createGraph(int nVertices){
	struct graph* ptGraph;
	ptGraph = (struct graph*)calloc(1,sizeof(struct graph));
	ptGraph->vertexList = (struct vertex*)calloc(nVertices,sizeof(struct vertex));
	ptGraph->numVertex = nVertices;
	return ptGraph;
}

void emptyMemory(struct graph* ptGraph){
	int i;
	struct edge *tmp, *aux;

	for(i=0; i < ptGraph->numVertex; i++){
		tmp = (ptGraph->vertexList)[i].edgeList;
		while(tmp){
			aux = tmp;
			tmp = tmp->prox;
			free(aux);
		}
	}
	free(ptGraph->vertexList);
	free(ptGraph);
}

//------------------------- Operations about the vertexs -------------------------//
int insertVertex(struct graph* ptGraph, int elem){
	(ptGraph->vertexList)[elem].element = elem;
	(ptGraph->vertexList)[elem].cost = 99999;
	return elem;
}

//------------------------- operations about the edges -------------------------//
void insertEdge(struct graph* ptGraph, int destVertex, int origVertex, int weight){
	struct edge* new;

	new = (struct edge*)calloc(1,sizeof(struct edge));
	(*new).accsses = destVertex;
	new->weight = weight;
	new->prox = (ptGraph->vertexList)[origVertex].edgeList;
	(ptGraph->vertexList)[origVertex].edgeList = new;

	// undirected graph 
	new=(struct edge*)calloc(1,sizeof(struct edge));
	(*new).accsses = origVertex;
	new->weight = weight;
	new->prox = (ptGraph->vertexList)[destVertex].edgeList;
	(ptGraph->vertexList)[destVertex].edgeList = new;
}


//------------------------- Debug -------------------------//
void printGraph(struct graph* ptGraph){
	int i;
	struct edge* tmp;

	for(i=0; i<ptGraph->numVertex; i++){
		tmp = (ptGraph->vertexList)[i].edgeList;
		printf("vertex: %d",(ptGraph->vertexList)[i].element);
		printf("  -->");
		while(tmp){
			printf(" %d",tmp->accsses);
			tmp = tmp->prox;
		}

		printf("\nvisited: %d",(ptGraph->vertexList)[i].visited);
		printf("\ncost: %d",(ptGraph->vertexList)[i].cost);
		printf("\n\n");
	}
}
