#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../include/Graph.h"
#include "../include/TST.h"

struct graph {
    int n_pages; // number of pages
    TST pages;   // TST for storing pages' names

    int n_stopwords; // number of stopwords
    TST stopwords;   // TST for storing stopwords

    int n_words; // number of words
    TST words;   // TST for storing words
};

Graph graph_init() {
    Graph g = (Graph)calloc(1, sizeof(struct graph));
    g->n_pages = 0;
    g->n_stopwords = 0;
    g->n_words = 0;

    g->stopwords=NULL;
    
    return g;
}

int graph_searchStopword(Graph g, char * word){ // lembrar que val 0 é valido
    int* val = (int*)TST_search(g->stopwords, word);

    if (val != NULL) {
        return *val;
    } else {
        return -1;
    }
    
}

void subs_int(void *old, void *new) {

}

void graph_addStopword(Graph g, char * word){
    int *val = (int *)malloc(sizeof(int));
    *val = g->n_stopwords;
    
    g->stopwords = TST_insert(g->stopwords, (const char *)word, val, subs_int);

    g->n_stopwords++;

}

void graph_readStopwords(Graph g, char *path) {
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%sstopwords.txt", path);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Couldn't open stopwords.txt\n");
        graph_destroy(g);
        exit(1);
    }

    char *Linha = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&Linha, &len, file)) != -1) {
        if (Linha[read - 1] == '\n') {
            Linha[read - 1] = '\0';
        }
        printf("%s  ", Linha);
        graph_addStopword(g, Linha);
    }
    printf("\n");

    free(Linha);
    graph_searchStopword(g, "sofia");
    fclose(file);
}

void destroy_int_value(void *val) {
    if (val!=NULL){
        free(val);
        val = NULL;
    }
}

void destroy_TST_value(void *val) {
    destroy_TST((TST)val, destroy_int_value);
}

void graph_destroy(Graph g) {
    // destroy_TST(g->pages);
    destroy_TST(g->stopwords, destroy_int_value);
    // destroy_TST(g->words);
    free(g);
}