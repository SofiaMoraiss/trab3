#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph *Graph;

Graph graph_init();
//void graph_readPage(Graph g, char*path);
void graph_readIndex(Graph g, char *path);
void graph_readStopwords(Graph g, char *path);
int graph_searchStopword(Graph g, char * word);
void testa_graph(Graph g);
void graph_RankTotal(Graph g);
void graph_readGraph(Graph g, char *path);
void graph_sort_pages_by_rank(Graph g);
void graph_print_pages(Graph g);
void graph_search_pages_in_common(Graph g);
// int graph_searchStopword(Graph g, char* name);
// void graph_searchWord(Graph g, char* name);
void graph_destroy(Graph g);

#endif