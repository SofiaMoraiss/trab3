#ifndef LL_H
#define LL_H

typedef struct node *Node;
typedef struct linked_list *LinkedList;


LinkedList init_list();

void list_insert(LinkedList list, char *);

void list_iterate(LinkedList list, TST pages1, TST pages2);

void list_print(LinkedList list);

void destroy_list(LinkedList list);

#endif