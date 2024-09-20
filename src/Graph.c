#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

#include "../include/Graph.h"
#include "../include/TST.h"
#include "../include/LinkedList.h"
#include "../include/Page.h"

#define MAX_PATH_LENGTH 1024
#define E_CONST 0.000001

struct graph {
    int n_pages; // number of pages
    int n_pages_allocated;
    Page * pages_list;
    TST pages;   // TST for storing pages' names

    int n_stopwords; // number of stopwords
    TST stopwords;   // TST for storing stopwords

    int n_words; // number of words
    TST words;   // TST for storing words
};

Graph graph_init() {
    Graph g = (Graph)calloc(1, sizeof(struct graph));
    g->n_pages = 0;
    g->n_pages_allocated = 0;
    g->n_stopwords = 0;
    g->n_words = 0;

    g->pages_list=NULL;
    g->words=NULL;
    g->stopwords=NULL;
    g->pages=NULL;
    
    return g;
}

void graph_addPage(Graph g, Page page) {
    if (!g || !page) return;

    g->pages_list[g->n_pages_allocated] = page;

    g->n_pages_allocated++;

}

void graph_sort_pages_by_rank(Graph g) {
    qsort(g->pages_list, g->n_pages, sizeof(Page), page_compare_by_rank);
}

void graph_print_pages(Graph g) {
    for (int i = 0; i < g->n_pages; i++) {
        printf("Page %d: %s\n", i + 1, page_getName(g->pages_list[i]));
    }
}


void* graph_searchWord(Graph g, char * word){ // lembrar que val 0 é valido
    TST val = (TST)TST_search(g->words, word);

    if (val != NULL) {
        return val;
    } else {
        return NULL;
    }
    
}
void to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

void graph_print_pagesInCommon(Graph g, LinkedList words) {
    TST pages1 = NULL;
    int *val1 = NULL;
    char *page_name = NULL;
    LinkedList prs = init_list();
    if (prs == NULL) {
        return;
    }
    printf("search:");

    list_print_forward(words);

    printf("\npages:");

    for (int i = 0; i < g->n_pages; i++) {
        page_name = strdup(page_getName(g->pages_list[i]));
        if (page_name == NULL) {
            continue;
        }
        

        Node current_node = list_get_head(words);
        int found_all = 1;
        
        while (current_node != NULL) {
            char *word = list_get_str(current_node);
            if (word == NULL) {
                found_all = 0;
                break;
            }

            pages1 = (TST)TST_search(g->words, word);
            if (pages1 == NULL) {
                found_all = 0;
                break;
            }

            val1 = (int *)TST_search(pages1, page_name);
            
            if (!val1) {
                found_all = 0;
                break;
            }
            current_node = list_get_next(current_node);
        }

        if (found_all) {
            long double pr = page_getRank(g->pages_list[i]);
            int needed = snprintf(NULL, 0, "%Lf", pr);
            char *pr_str = (char *)malloc(needed + 1);
            if (pr_str == NULL) {
                free(page_name);
                continue;
            }
            snprintf(pr_str, needed + 1, "%Lf", pr);
            list_insert(prs, pr_str);
            printf("%s ", page_name);
            free(pr_str);
        }
        
        free(page_name);
    }

    printf("\n");

    printf("pr:");

    Node current_node = list_get_tail(prs);

    while (current_node != NULL) {
        char *rank = list_get_str(current_node);
        if (rank != NULL) {
            printf("%s ", rank);
        }
        current_node = list_get_prev(current_node);
    }

    printf("\n");

    destroy_list(prs);
}

void graph_search_pages_in_common(Graph g) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
        LinkedList words = init_list();
        if (words == NULL) {
            fprintf(stderr, "Failed to initialize words list\n");
            free(line);
            continue;
        }

        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        char *token = strtok(line, " ");
        while (token != NULL) {
            to_lowercase(token);
            list_insert(words, token);
            token = strtok(NULL, " ");
        }

        graph_print_pagesInCommon(g, words);
        destroy_list(words);
    }

    free(line);
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
    // printf("\n");

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





void graph_addWord(Graph g, char *word, char *page) {
    to_lowercase(word);

    int is_stop = graph_searchStopword(g, word);

    if (is_stop >= 0) {
        return;
    }

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

    char *Linha = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&Linha, &len, file)) != -1) {
        if (Linha[read - 1] == '\n') {
            Linha[read - 1] = '\0';
        }

        char *token = strtok(Linha, " ");
        while (token != NULL) {
            graph_addWord(g, token, name);
            token = strtok(NULL, " ");
        }
        
    }

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
        graph_readPage(g, path, Linha);
        g->n_pages++;
    }

    g->pages_list = calloc(g->n_pages, sizeof(Page));
    if (!g->pages_list) {
        perror("Failed to allocate memory for page vector");
        return;
    }

    free(Linha);
    fclose(file);
}

void graph_setIns(Graph g) {
    Page p = NULL;
    char* name = NULL;

    for (int i = 0; i < g->n_pages; i++) {
        for (int j = 0; j < page_getNOut(g->pages_list[i]); j++) {
            name = strdup(page_getLinkOut(g->pages_list[i], j));
            // printf("%d o link out: %s\n",i, name );
            p = (Page)TST_search(g->pages, name);
            if (p) {
                page_addLinkIn(p, page_getName(g->pages_list[i]));
                // printf("%s tem %s como in\n", page_getName(g->pages_list[i]), name);
            }
            free(name);
        }
    }
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
                page = init_page(atoi(token), name,(1.0 / g->n_pages));
            } else {
                page_addLinkOut(page, token);
            }
            token = strtok(NULL, " ");
            i++;
        }
        g->pages = TST_insert(g->pages, name, page, subs_int);

        graph_addPage(g, page);
        // long double x = page_getRank(g->pages_list[g->n_pages_allocated-1]);

        free(name);
    }

    graph_setIns(g);

    free(Linha);
    fclose(file);
}

void testa_graph(Graph g){
    printf("\n-----------------------\n");
    Page test = (Page)TST_search(g->pages, "e.txt");

    if (test){
        // printf("\nRank: %Lf ----\n", page_getRank(test));
    }

}

long double graph_calc_E(Page * pages, int n){

    long double res=0.0;
    for (int i = 0; i < n; i++){
        res+=fabs(page_getRank(pages[i])-page_getLastRank(pages[i]));
        //printf(" +abs( %Lf - %Lf )= %Lf\n", page_getRank(pages[i]), page_getLastRank(pages[i]), res);
    }
    // printf("\nE  antes = %Lf\n", res);
    res*=(1.0/n);
    // printf("E = %Lf\nE_CONST = %f", res, E_CONST);

    return res;
}

void graph_RankTotal(Graph g){

    int k=1;

    do { // loop das iterações k
        // printf("\n-------------- iteração  k= '%d'\n", k);
        for (int i = 0; i < g->n_pages; i++){
            // printf("\n pag id='%d':\n", i);
            page_rank(g->pages_list[i], g->pages, g->n_pages);  // loop i
        }
        // printf("\n");
        k++;
    } while ((graph_calc_E(g->pages_list, g->n_pages) >= E_CONST));
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
    if (!g) return;

    TST_destroy(g->pages, destroy_TST_page);
    TST_destroy(g->stopwords, destroy_int_value);
    TST_destroy(g->words, destroy_TST_int);

    // for (int i = 0; i < g->n_pages; i++) {
    //     destroy_page(g->pages_list[i]);
    // }
    free(g->pages_list);
    free(g);
}
