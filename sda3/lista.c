#include "lista.h"
#include <stdlib.h>

TNode initListNode(int value) {
    TNode newNode = (TNode) malloc(sizeof(Node));
    newNode->info = value;
    newNode->next = NULL;
    return newNode;
}

void insertList(TLista list, int value) {
    TNode newNode = initListNode(value);
    if (list->start == NULL) {
        list->start = list->end = newNode;
        return;
    }
    list->end->next = newNode;
    list->end = list->end->next;
}


void freeList(TLista list) {
    TNode current = list->start;
    TNode nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    list->start = NULL;
    list->end = NULL;
}