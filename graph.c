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
	struct edge* next;
};

struct graph{
	struct vertex* vertexList;
	int numVertex;
};

struct path{
	int element;
	int lengthPath;
	struct path* next;
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
			tmp = tmp->next;
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

//--------------------------- Operations about the edges ----------------------------//
void insertEdge(struct graph* ptGraph, int destVertex, int origVertex, int weight){
	struct edge* new;

	new = (struct edge*)calloc(1,sizeof(struct edge));
	(*new).accsses = destVertex;
	new->weight = weight;
	new->next = (ptGraph->vertexList)[origVertex].edgeList;
	(ptGraph->vertexList)[origVertex].edgeList = new;

	// undirected graph 
	new=(struct edge*)calloc(1,sizeof(struct edge));
	(*new).accsses = origVertex;
	new->weight = weight;
	new->next = (ptGraph->vertexList)[destVertex].edgeList;
	(ptGraph->vertexList)[destVertex].edgeList = new;
}

//----------------------------- Operations about the TSP ----------------------------//

int edgeWeight(struct edge* ptEdge, int vertex){
	struct edge* tmp = ptEdge;

	while(tmp->element != vertex){
		tmp = tmp->next;
	}

	return tmp->weight;
}

int pathLength(struct graph* ptGraph, struct path* ptPath){
	int i, sum = 0;

	for(i=1 ; i<ptPath->lengthPath; i++){
		sum += edgeWeight((ptGraph->vertexList)[i-1].edgeList, i);
	}

	return sum;
}

int pathContains(struct path* ptPath, int vertex){
	int i;
	struct path* tmp = ptPath;

	for(i=0; i<tmp->lengthPath; i++){
		if(tmp->element == vertex){
			return 1;
		}
	}
	
	return 0;
}

void addPath(struct path** ptPath, int vertex){
	struct path* new;

	new=(struct path*)calloc(1,sizeof(struct path));
	new->element = vertex;
	(new->lengthPath)++;
	new->next = *ptPath;
	*ptPath = new;
}

void removePath(struct path** ptPath, int vertex){
	struct path* ptFree = *ptPath;
	
	if((*ptPath)->element == vertex){
		*ptPath = (*ptPath)->next;
	}
	else{
		struct path* ptBefore = *ptPath;

		while(ptFree->element != vertex){
			ptBefore = ptFree;
			ptFree = ptFree->next;
		}
	}

	ptBefore->next = ptFree->next;
	free(ptFree);
}

void tsp_backtracking(struct graph* ptGraph, struct path* ptPath, int bestLength){
	
	//if the path is longe than best (so far), quit!
	if(pathLength(ptGraph, ptPath) > bestLength){
		return;
	}

	//if the path is complete, quit!
	else if(completePath(ptGraph, ptPath) && pathLength(ptGraph, ptPath) <= bestLength){
		bestPath = copyArray(ptPath);
		bestLength = pathLength(ptGraph, bestPath);
		return;
	}

	//path doesn t contain a vertex, add it
	else{
		int i;
		
		for(i=0; i< ptGraph->numVertex; i++){
			if(!pathContains(i)){
				addPath(&ptPath, i);
				tsp_backtracking(ptGraph, ptPath, bestLength);
				removePath(&ptPath, i); 
			}
		}
	}
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
			tmp = tmp->next;
		}

		printf("\nvisited: %d",(ptGraph->vertexList)[i].visited);
		printf("\ncost: %d",(ptGraph->vertexList)[i].cost);
		printf("\n\n");
	}
}
