#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph *Graph;

Graph graph_init();
//void graph_readPage(Graph g, char*path);
void graph_readIndex(Graph g, char *path);
void graph_readStopwords(Graph g, char *path);
int graph_searchStopword(Graph g, char * word);
void testa_graph(Graph g);
void graph_readGraph(Graph g, char *path);
// int graph_searchStopword(Graph g, char* name);
// void graph_searchWord(Graph g, char* name);
void graph_destroy(Graph g);

#endif