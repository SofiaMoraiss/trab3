#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/TST.h"

#define MAX_LENGHT 1000

struct node {
    void *val;
    char c;
    TST l, m, r;
};


TST create_node(char c) {
    TST node = (TST)malloc(sizeof(struct node));
    node->c = c;
    node->l = node->m = node->r = NULL;
    node->val = NULL;
    return node;
}

TST rec_insert(TST t, const char* key, void *val, int d, substitutes_value_fn subs_value ) {
    unsigned char c = key[d];
    if (t == NULL) {
        t = create_node(c);
    }

    if (c < t->c) {
        t->l = rec_insert(t->l, key, val, d, subs_value);
    } else if (c > t->c) {
        t->r = rec_insert(t->r, key, val, d, subs_value);
    } else if (d < strlen((char*)key) - 1) {
        t->m = rec_insert(t->m, key, val, d + 1, subs_value);
    } else {
        if (t->val != NULL) {
            subs_value(t->val, val);
        }
        else {
            t->val = val;
        }
    }
    return t;
}

TST TST_insert(TST t, const char* key, void *val, substitutes_value_fn subs_value) {
    return rec_insert(t, key, val, 0, subs_value);
}

TST rec_search(TST t, const char* key, int d) {
    if (t == NULL) {
        return NULL;
    }

    unsigned char c = key[d];

    if (c < t->c) {
        return rec_search(t->l, key, d);
    } else if (c > t->c) {
        return rec_search(t->r, key, d);
    } else if (d < strlen((char*)key) - 1) {
        return rec_search(t->m, key, d + 1);
    } else {
        return t;
    }
}

void* TST_search(TST t, const char* key) {
    t = rec_search(t, key, 0);
    if (t == NULL || t->val == NULL) {
        return NULL;
    } else {
        return t->val;
    }
}

char *TST_getSingleWord(TST tree) {
    if (!tree) {
        return NULL;
    }

    TST node = tree;
    char buffer[MAX_LENGHT];
    int index = 0;

    while (node) {
        buffer[index++] = node->c;
        if (node->val != NULL) {
            buffer[index] = '\0';
            return strdup(buffer);
        }
        node = node->m;
    }

    return NULL;
}


void TST_destroy(TST t, destroy_value_fn destroy_value) {
    if (t == NULL) {
        return;
    }

    TST_destroy(t->l, destroy_value);
    TST_destroy(t->m, destroy_value);
    TST_destroy(t->r, destroy_value);

    if (t->val != NULL && destroy_value != NULL) {
        destroy_value(t->val);
    }

    free(t);
}

