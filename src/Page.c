#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/TST.h"
#include "../include/Page.h"

#define ALPHA 0.85

struct page {
    int n_out;
    int n_in;
    long double rank;
    long double lastRank;
    char * name;
    char** outs;
    char** ins;
};

Page init_page(int n_out, char * name, long double rank) {
    Page p = (Page)malloc(sizeof(struct page));

    p->n_out = 0;
    p->rank = rank;
    p->lastRank = rank;

    p->name = strdup(name);
    p->outs = (char**)malloc(n_out * sizeof(char*));
    p->ins = NULL;
    p->n_in = 0;

    return p;
}

int page_compare_by_rank(const void *a, const void *b) {
    Page pageA = *(Page *)a;
    Page pageB = *(Page *)b;

    if (pageA->rank > pageB->rank) {
        return -1;
    } else if (pageA->rank < pageB->rank) {
        return 1;
    } else {
        return strcmp(pageA->name, pageB->name);
    }
}

void page_addLinkIn(Page p, char *token) {
    p->ins = (char**)realloc(p->ins, (p->n_in + 1) * sizeof(char*));
    p->ins[p->n_in] = strdup(token);
    p->n_in++;
}

void page_rank(Page p, TST pages, int n){

    // printf("\nentrei na pag %s com ranks : %Lf   e   %Lf \n", p->name, p->lastRank, p->rank);

    Page aux=NULL;

    long double rank = ((1.0 - ALPHA)/ n);
    if (abs(p->n_out)==0){
        rank += ALPHA*p->lastRank;
        // printf(" extra: %Lf\n", rank);
    }
    for (int j=0; j<p->n_in; j++){
        aux = (Page)TST_search(pages, p->ins[j]);
        // printf("%s tem %d outs\n", p->ins[j], aux->n_out);
        // exit(1);
        if (aux){
            rank += (ALPHA*(aux->lastRank/aux->n_out));
            // printf("\n rank += %f *(%Lf  /  %d) = %Lf\n",ALPHA, aux->lastRank, aux->n_out, ALPHA*(aux->lastRank/fabs(aux->n_out)));
        }
    }

    p->lastRank=p->rank;
    p->rank=rank;
    // printf("\n sai do page com ranks : %Lf   e   %Lf \n", p->lastRank, p->rank);
}

long double page_getRank(Page p) {

    if (p){
       return p->rank;
    }
    return -1.00;
}

long double page_getLastRank(Page p) {

    if (p){
       return p->lastRank;
    }
    return -1.00;
}

char * page_getLinkIn(Page p, int i) {

    if (p){
       return p->ins[i];
    }
    return NULL;
}

char * page_getLinkOut(Page p, int i) {

    if (p){
       return p->outs[i];
    }
    return NULL;
}

char * page_getName(Page p) {

    if (p){
       return p->name;
    }
    return NULL;
}

int page_getNOut(Page p) {

    if (p){
       return p->n_out;
    }
    return -1.00;
}

int page_getNIn(Page p) {

    if (p){
       return p->n_in;
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
    free(page->name);

    if (page->ins) {
        for (int i = 0; i<page->n_in; i++) {
            free(page->ins[i]);
        }
        free(page->ins);
    }

    free(page);
}

