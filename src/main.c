#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/TST.h"
#include "../include/Graph.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <directory path>\n", argv[0]);
        return 1;
    }

    Graph g = graph_init();
    
    graph_readStopwords(g, argv[1]);

    graph_destroy(g);

    return 0;
}