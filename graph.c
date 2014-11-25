#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct vertex{
	int element;
	struct edge* edgeList;
};

struct edge{
	int weight;
	int access;
	struct edge* next;
};

struct graph{
	struct vertex* vertexList;
	int numVertex;
};


struct path{
	int* elements;
	int usedLength;
};

//------------------------- Operations about the graph -------------------------//
struct graph* createGraph(int nVertices){
	struct graph* ptGraph;
	ptGraph = (struct graph*)calloc(1,sizeof(struct graph));
	ptGraph->vertexList = (struct vertex*)calloc(nVertices,sizeof(struct vertex));
	ptGraph->numVertex = nVertices;
	return ptGraph;
}

void emptyMemoryGraph(struct graph* ptGraph){
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

int getGraphSize(struct graph* ptGraph){
	return ptGraph->numVertex;
}

//-------------------------- Operations about the vertex ----------------------------//
int insertVertex(struct graph* ptGraph, int elem){
	(ptGraph->vertexList)[elem].element = elem;
	return elem;
}

//--------------------------- Operations about the edges ----------------------------//
void insertEdge(struct graph* ptGraph, int destVertex, int origVertex, int weight){
	struct edge* new;

	new = (struct edge*)calloc(1,sizeof(struct edge));
	(*new).access = destVertex;
	new->weight = weight;
	new->next = (ptGraph->vertexList)[origVertex].edgeList;
	(ptGraph->vertexList)[origVertex].edgeList = new;

	// undirected graph 
	new=(struct edge*)calloc(1,sizeof(struct edge));
	(*new).access = origVertex;
	new->weight = weight;
	new->next = (ptGraph->vertexList)[destVertex].edgeList;
	(ptGraph->vertexList)[destVertex].edgeList = new;
}

//----------------------------- Operations about the path ---------------------------//

struct path* createPath(int size){
	int i;
	struct path* ptPath;
	
	ptPath= (struct path*)calloc(1,sizeof(struct path));
	ptPath->elements = (int*)calloc(size,sizeof(int));
	ptPath->usedLength = 0;
	
	for(i=0; i<size; i++){
		(ptPath->elements)[i] = -1;
	}
	return ptPath;
}

void startingPath(struct path* ptPath, int vertex){
	(ptPath->elements)[0] = vertex;
	(ptPath->usedLength)++;
}

void printPath(struct path* ptPath){
	int i;

	for(i=ptPath->usedLength-1; i > -1; i--){
		printf("%d ", (ptPath->elements)[i]);
	}
	printf("\n");
}

void emptyMemoryPath(struct path* ptPath){
	free(ptPath->elements);
	free(ptPath);
}
//----------------------------- Operations about the TSP ----------------------------//

int edgeWeight(struct edge* ptEdge, int vertex){
	struct edge* tmp = ptEdge;

	while(tmp->access != vertex){
		tmp = tmp->next;
	}
	return tmp->weight;
}

int totalPathWeight(struct graph* ptGraph, struct path* ptPath){
	int i, sum = 0;

	for(i=1 ; i < ptPath->usedLength; i++){
		sum += edgeWeight((ptGraph->vertexList)[(ptPath->elements)[i-1]].edgeList, (ptPath->elements)[i]); //Weight vertex source to destination vertex 
	}
	return sum;
}

int pathContains(struct path* ptPath, int vertex){
	int i;

	for(i=0; i<ptPath->usedLength; i++){
		if((ptPath->elements)[i] == vertex){
			return 1;
		}
	}
	return 0;
}

int completePath(struct graph* ptGraph, struct path* ptPath){
	return ptGraph->numVertex == ptPath->usedLength;
}

void addPath(struct path* ptPath, int vertex){
	(ptPath->elements)[ptPath->usedLength] = vertex;
	(ptPath->usedLength)++;
}

void shiftPath(struct path* ptPath, int initial, int usedLength, int pathLength){
	if(initial == pathLength-1){
		(ptPath->elements)[initial] = -1;
	}
	else{
		int i;
		for(i=initial; i<usedLength; i++){
			(ptPath->elements)[i] = (ptPath->elements)[i+1];	
		}
	}
}

void removePath(struct path* ptPath, int vertex, int pathLength){
	int i;

	for(i=0; i<ptPath->usedLength; i++){
		if((ptPath->elements)[i] == vertex){
			shiftPath(ptPath, i, ptPath->usedLength, pathLength);
		}
	}
	(ptPath->usedLength)--;
}

void copyArray(struct path* ptBestPath, struct path* ptPath){
	int i;

	for(i=0; i<ptPath->usedLength; i++){
		(ptBestPath->elements)[i] = (ptPath->elements)[i];
	}
	ptBestPath->usedLength = ptPath->usedLength;
}

void tsp_backtracking(struct graph* ptGraph, struct path* ptPath, struct path* ptBestPath, int* bestLength){
	
	//if the path is longe than best (so far), quit!
	if(totalPathWeight(ptGraph, ptPath) > *bestLength){
		return;
	}

	//if the path is complete, quit!
	else if(completePath(ptGraph, ptPath) && totalPathWeight(ptGraph, ptPath) <= *bestLength){ 
		copyArray(ptBestPath, ptPath);
		*bestLength = totalPathWeight(ptGraph, ptBestPath);
		return;
	}

	//path doesn t contain a vertex, add it
	else{
		int i;
		struct edge* ptEdge = (ptGraph->vertexList)[(ptPath->elements)[ptPath->usedLength-1]].edgeList; //The vertex always to analyze will be the last

		for( ; ptEdge != NULL; ptEdge = ptEdge->next){
			if(!pathContains(ptPath, ptEdge->access)){
				addPath(ptPath, ptEdge->access);
				tsp_backtracking(ptGraph, ptPath, ptBestPath, bestLength);
				removePath(ptPath, ptEdge->access , ptGraph->numVertex); 
			}
		}
	}
}
