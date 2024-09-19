#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/TST.h"
#include "../include/Page.h"


struct page {
    int n_out;
    int n_in;
    double rank;
    char** outs;
    char** ins;
};

Page init_page(int n_out, double rank) {
    Page p = (Page)malloc(sizeof(struct page));

    p->n_out = 0;
    p->rank = rank;

    p->outs = (char**)malloc(n_out * sizeof(char*));
    p->ins = NULL;
    p->n_in = 0;

    return p;
}

void page_addLinkIn(Page p, char *token) {
    p->ins = (char**)realloc(p->ins, (p->n_in + 1) * sizeof(char*));
    p->ins[p->n_in] = strdup(token);
    p->n_in++;
}

double page_getRank(Page p) {

    if (p){
       return p->rank;
    }
    return -1.00;
}

void page_addLinkOut(Page p, char *token) {
    p->outs = (char**)realloc(p->outs, (p->n_out + 1) * sizeof(char*));
    p->outs[p->n_out] = strdup(token);
    p->n_out++;
}


void destroy_page(void *p) {
    if (!p) return;
    
    Page page = (Page )p;

    for (int i = 0; i < page->n_out; i++) {
        free(page->outs[i]);
    }

    free(page->outs);

    if (page->ins) {
        for (int i = 0; page->ins[i] != NULL; i++) {
            free(page->ins[i]);
        }
        free(page->ins);
    }

    free(page);
}

