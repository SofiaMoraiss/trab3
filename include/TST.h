#ifndef TST_H
#define TST_H

#include <stddef.h>  // Para usar size_t

typedef struct node * TST;
typedef struct string * String;

typedef void (*destroy_value_fn)(void *);

typedef void (*substitutes_value_fn)(void *, void *);

TST create_node(char c);

TST TST_insert(TST t, const char* key, void *val, substitutes_value_fn subs_value);

void* TST_search(TST t, const char* key);
void destroy_TST(TST t, destroy_value_fn destroy_value);

#endif