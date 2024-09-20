#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/TST.h"
#include "../include/Graph.h"
#include <unistd.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <directory path>\n", argv[0]);
        return 1;
    }

    Graph g = graph_init();
    
    graph_readStopwords(g, argv[1]);

    graph_readIndex(g, argv[1]);

    graph_readGraph(g, argv[1]);


    graph_RankTotal(g);

    graph_sort_pages_by_rank(g);

    //graph_print_pages(g);

    graph_search_pages_in_common(g);

    graph_destroy(g);

    return 0;
}