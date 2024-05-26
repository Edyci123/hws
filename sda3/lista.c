/* BIC CODRUT EDUARD - 312CB */
#include "lista.h"
#include <stdlib.h>

TNode initListNode(float value) {
    TNode newNode = (TNode) malloc(sizeof(Node));
    newNode->info = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertList(TLista list, float value) {
    TNode newNode = initListNode(value);
    if (list->start == NULL) {
        list->start = list->end = newNode;
        return;
    }
    newNode->prev = list->end;
    list->end->next = newNode;
    list->end = list->end->next;
}

void insertListStart(TLista list, float value) {
    TNode newNode = initListNode(value);
    if (list->start == NULL) {
        list->start = list->end = newNode;
        return;
    }
    list->start->prev = newNode;
    newNode->next = list->start;
    list->start = newNode;
}

TLista copyList(TLista list) {
    TLista newList = malloc(sizeof(Lista));
    if (list == NULL) {
        return newList;
    }
    TNode current = list->start;
    while (current) {
        insertList(newList, current->info);
        current = current->next;
    }
    return newList;
}

void freeList(TLista list) {
    // TNode current = list->start;
    // TNode nextNode;
    // while (current != NULL) {
    //     nextNode = current->next;
    //     free(current);
    //     current = nextNode;
    // }
    list->start = NULL;
    // list->end = NULL;
}