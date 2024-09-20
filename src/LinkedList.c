#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/TST.h"
#include "../include/Graph.h"
#include "../include/LinkedList.h"

struct node {
    char *str;
    struct node *next;
    struct node *prev;
};

struct linked_list {
    Node head;
    Node tail;
};

LinkedList init_list() {
    LinkedList list = (LinkedList) malloc(sizeof(struct linked_list));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_insert(LinkedList list, char *s) {
    Node new_node = (Node) malloc(sizeof(struct node));
    if (new_node == NULL) return;

    new_node->str = strdup(s);
    if (new_node->str == NULL) {
        free(new_node);
        return;
    }
    new_node->next = list->head;
    new_node->prev = NULL;

    if (list->head != NULL) {
        list->head->prev = new_node;
    } 
    else {
        list->tail = new_node;
    }

    list->head = new_node;
}

void list_print_forward(LinkedList list) {
    Node current = list_get_head(list);
    while (current != NULL) {
        printf("%s ", list_get_str(current));
        current = list_get_next(current);
    }
}


void list_print_reverse(LinkedList list) {
    Node current = list_get_tail(list);
    while (current != NULL) {
        printf("%s\n", list_get_str(current));
        current = list_get_prev(current);
    }
}


char *list_get_str(Node node) {
    if (node == NULL) {
        return NULL;
    }
    return node->str;
}

Node list_get_next(Node node) {
    if (node == NULL) {
        return NULL;
    }
    return node->next;
}

Node list_get_prev(Node node) {
    if (node == NULL) {
        return NULL;
    }
    return node->prev;
}

Node list_get_head(LinkedList list) {
    if (list == NULL) {
        return NULL;
    }
    return list->head;
}

Node list_get_tail(LinkedList list) {
    if (list == NULL) {
        return NULL;
    }
    return list->tail;
}

// void list_iterate(LinkedList list, TST pages1, TST pages2) {
//     printf("\npages: ");
//     Node current = list->head;
//     int *val1 = NULL;
//     int *val2 =NULL;
//     while (current != NULL) {
//         val1 = TST_search(pages1, current->str);
//         if (val1){
//             // printf("pages1: %d\n", *val1);
//             if (*val1>=0){
//                 val2 = TST_search(pages2, current->str);
//                 if (val2){
//                     // printf("pages2: %d\n", *val2);
//                     if (*val2>=0){
//                         printf("%s ", current->str );
//                     }
//                 }
//             }
//         }

//         current = current->next;
//     }
//     printf("\n");
// }

void destroy_list(LinkedList list) {
    Node current = list->head;
    Node next;
    while (current != NULL) {
        next = current->next;
        free(current->str);
        free(current);
        current = next;
    }
    free(list);
}

