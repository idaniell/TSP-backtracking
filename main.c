#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "graph.h"

struct graph* buildGraph(){
	FILE* file;
	char* token;
	graph* ptGraph;
	int edge;
	int vertex1;
	int vertex2;

	if(!(file=fopen("./input","r"))){
		printf("file error");
		exit(1);
	}

	token = readFile(&file);//number of vertex
	ptGraph =  createGraph(atoi(token));
	free(token);

	token = readFile(&file);//number of edges
	free(token);

	while(token = readFile(&file)){
		vertex1 = atoi(token);
		free(token);

		token = readFile(&file);
		vertex2 = atoi(token);
		free(token);

		token = readFile(&file);
		edge = atoi(token);
		free(token);

		insertEdge(ptGraph, insertVertex(ptGraph, vertex2), insertVertex(ptGraph, vertex1), edge);
	}

	close(file);
	return ptGraph;
}

int main(int argc, char** argv){
	graph* ptGraph = buildGraph();

	printGraph(ptGraph);
	emptyMemory(ptGraph);
	return 0;
}
