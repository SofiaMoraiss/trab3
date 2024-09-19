#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "../include/Graph.h"
#include "../include/TST.h"
#include "../include/LinkedList.h"
#include "../include/Page.h"

#define MAX_PATH_LENGTH 1024

struct graph {
    int n_pages; // number of pages
    LinkedList pages_names;
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

    g->pages_names=init_list();
    g->words=NULL;
    g->stopwords=NULL;
    g->pages=NULL;
    
    return g;
}

void* graph_searchWord(Graph g, char * word){ // lembrar que val 0 é valido
    TST val = (TST)TST_search(g->words, word);

    if (val != NULL) {
        return val;
    } else {
        return NULL;
    }
    
}

void graph_print_pagesInCommon(Graph g, char* w1, char* w2){

    TST pages1= (TST)graph_searchWord(g, w1);
    TST pages2= (TST)graph_searchWord(g, w2);

    list_iterate(g->pages_names, pages1, pages2);

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
    char file_path[MAX_PATH_LENGTH];
    snprintf(file_path, sizeof(file_path), "%sstopwords.txt", path);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Couldn't open %s\n", file_path);
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
        //printf("%s  ", Linha);
        graph_addStopword(g, Linha);
    }
    printf("\n");

    free(Linha);
    fclose(file);
}

// void subs_TST_TST(void *old, void *new) {
//     TST old_tree = (TST)old;
//     TST new_tree = (TST)new;

//     if (old_tree == NULL) {
//         old_tree = new_tree;
//     } else if (new_tree != NULL) {
//         old_tree = TST_insert(old_tree, new_tree, subs_TST);
//     }
// }

void destroy_int_value(void *val) {
    if (val!=NULL){
        free(val);
        val = NULL;
    }
}


void subs_TST_int1(void *old, void *new) {

    TST old_tree = (TST)old;
    
    char *new_key = TST_getSingleWord(new);

    int *val = (int *)malloc(sizeof(int));
    *val = 1;

    old_tree = TST_insert(old_tree, (const char *)new_key, val, subs_int);

    free(new_key);
    TST_destroy(new, destroy_int_value);
}




void to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

void graph_addWord(Graph g, char *word, char *page) {
    to_lowercase(word);

    // int already = graph_searchWord(g, word);

    // if (already >= 0) {
    //     return;
    // }

    int is_stop = graph_searchStopword(g, word);

    if (is_stop >= 0) {
        return;
    }

    printf("%s ", word);

    TST val = NULL;

    int *val1 = (int *)malloc(sizeof(int));
    *val1 = 1;
    val = TST_insert(val, page, val1, subs_int);

    g->words = TST_insert(g->words, (const char *)word, val, subs_TST_int1);

    g->n_words++;
}


void graph_readPage(Graph g, char *path, char *name) {
    char file_path[MAX_PATH_LENGTH];
    snprintf(file_path, sizeof(file_path), "%spages/%s", path, name);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Couldn't open %s\n", file_path);
        return;
    }

    g->n_pages++;

    char *Linha = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&Linha, &len, file)) != -1) {
        if (Linha[read - 1] == '\n') {
            Linha[read - 1] = '\0';
        }

        char *token = strtok(Linha, " ");
        while (token != NULL) {
            // printf(" %s\n", token);
            graph_addWord(g, token, name);
            token = strtok(NULL, " ");
        }
        
    }
    printf("\n");

    free(Linha);
    fclose(file);
}

void graph_readIndex(Graph g, char *path) {
    char file_path[MAX_PATH_LENGTH];
    snprintf(file_path, sizeof(file_path), "%sindex.txt", path);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Couldn't open %s\n", file_path);
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
        list_insert(g->pages_names, Linha);
        graph_readPage(g, path, Linha);
    }
    printf("\n");

    free(Linha);
    //graph_print_pagesInCommon( g, "abacate", "ruim");
    fclose(file);
}

void graph_readGraph(Graph g, char *path) {
    char file_path[MAX_PATH_LENGTH];
    snprintf(file_path, sizeof(file_path), "%sgraph.txt", path);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Couldn't open %s\n", file_path);
        return;
    }

    char *Linha = NULL;
    size_t len = 0;
    ssize_t read;

    // printf("\nReading: %s:\n", file_path);

    int i=0;

    while ((read = getline(&Linha, &len, file)) != -1) {
        if (Linha[read - 1] == '\n') {
            Linha[read - 1] = '\0';
        }
        i = 0;

        Page page = NULL;
        char *name;
        char *token = strtok(Linha, " ");

        while (token != NULL) {
            if (i == 0) {
                name = strdup(token);
            } else if (i == 1) {
                page = init_page(atoi(token), (1.0 / g->n_pages));
            } else {
                page_addLinkOut(page, token);
            }
            token = strtok(NULL, " ");
            i++;
        }
        g->pages = TST_insert(g->pages, name, page, subs_int);

        printf("%s : %lf, ",name, page_getRank(page));

        free(name);
    }

    printf("\n");

    free(Linha);
    fclose(file);
}

void testa_graph(Graph g){
    printf("\n-----------------------\n");
    Page test = (Page)TST_search(g->pages, "zztxt");

    if (test){
        printf("%lf ----\n", page_getRank(test));
    }

}



void destroy_TST_int(void *val) {
    TST_destroy((TST)val, destroy_int_value);
}

void destroy_TST_TST_int(void *val) {
    TST_destroy((TST)val, destroy_TST_int);
}

void destroy_TST_page(void *val) {
    if (val!=NULL){
        destroy_page(val);
        val = NULL;
    }
}

void graph_destroy(Graph g) {
    TST_destroy(g->pages, destroy_TST_page);
    TST_destroy(g->stopwords, destroy_int_value);
    TST_destroy(g->words, destroy_TST_int);
    destroy_list(g->pages_names);
    free(g);
}