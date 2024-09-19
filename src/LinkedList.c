#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/TST.h"
#include "../include/Graph.h"
#include "../include/LinkedList.h"

struct node {
    char *str;
    Node next;
};

struct linked_list {
    Node head;
};

LinkedList init_list() {
    LinkedList list = (LinkedList ) malloc(sizeof(struct linked_list));
    list->head = NULL;
    return list;
}

void list_insert(LinkedList list, char *s) {
    Node new_node = (Node ) malloc(sizeof(struct node));
    new_node->str = strdup(s);
    new_node->next = list->head;
    list->head = new_node;
}

void list_print(LinkedList list) {
    Node current = list->head;
    while (current != NULL) {
        printf("%s\n", current->str);
        current = current->next;
    }
}

void list_iterate(LinkedList list, TST pages1, TST pages2) {
    printf("\npages: ");
    Node current = list->head;
    int *val1 = NULL;
    int *val2 =NULL;
    while (current != NULL) {
        val1 = TST_search(pages1, current->str);
        if (val1){
            // printf("pages1: %d\n", *val1);
            if (*val1>=0){
                val2 = TST_search(pages2, current->str);
                if (val2){
                    // printf("pages2: %d\n", *val2);
                    if (*val2>=0){
                        printf("%s ", current->str );
                    }
                }
            }
        }

        current = current->next;
    }
    printf("\n");
}

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
