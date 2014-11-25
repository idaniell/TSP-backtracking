#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "graph.h"

struct graph* buildGraph(char* input){
	FILE* file;
	char* token;
	graph* ptGraph;
	int edge;
	int vertex1;
	int vertex2;

	if(!(file=fopen(input, "r"))){
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

void isTherePath(struct path* ptBestPath, int bestLength, int maxLength){
	if(bestLength < 999999 && bestLength <= maxLength){
		printPath(ptBestPath);
	}
	else{
		printf("impossivel\n");
	}
}

int main(int argc, char** argv){
	int maxLength, bestLength = 999999;
	char input[15] = "./";

	if(argc == 3){
		strcpy(input,argv[1]);
		maxLength = atoi(argv[2]);

	}
	else{
		printf("./a.out <input> <maxWeight\n");
		exit(1);
	}
	
	graph* ptGraph = buildGraph(input);
	path* ptPath = createPath(getGraphSize(ptGraph));
	path* ptBestPath = createPath(getGraphSize(ptGraph));

	startingPath(ptPath, 0);
	tsp_backtracking(ptGraph, ptPath, ptBestPath, &bestLength);
	isTherePath(ptBestPath, bestLength, maxLength);

	emptyMemoryGraph(ptGraph);
	emptyMemoryPath(ptPath);
	emptyMemoryPath(ptBestPath);
	return 0;
}
