#ifndef LL_H
#define LL_H

typedef struct node *Node;
typedef struct linked_list *LinkedList;


LinkedList init_list();
void list_insert(LinkedList list, char *);
void list_iterate(LinkedList list, TST pages1, TST pages2);
void list_print(LinkedList list);
char *list_get_str(Node node);
Node list_get_next(Node node);
Node list_get_head(LinkedList list);
Node list_get_tail(LinkedList list);
Node list_get_prev(Node node);
void list_print_forward(LinkedList list);
void list_print_reverse(LinkedList list);
void destroy_list(LinkedList list);

#endif