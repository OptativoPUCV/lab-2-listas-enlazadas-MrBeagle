#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * list = (List *)malloc(sizeof(List));
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
    return list; 
}

void * firstList(List * list) {
    if (list->head != NULL){
        list->current = list->head;
        return list->current->data;
    }
    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL) {
        if (list->current->next != NULL) {
            list->current = list->current->next;
            return list->current->data;
        }
        return NULL;
    }
    return NULL;
}

void * lastList(List * list) {
    if (list->tail != NULL){
        list->current = list->tail;
        return list->current->data;
    }
    return NULL;
}

void * prevList(List * list) {
    if (list->current != NULL){
        if (list->current == list->head) {
            return NULL; 
        }
        if (list->current->prev != NULL) {
            list->current = list->current->prev;
        }
        return list->current->data;
    }
    return NULL;
}

void pushFront(List * list, void * data) {
    Node * newNode = createNode(data);
    newNode->next = list->head;
    if (list->head != NULL){
        list->head->prev = newNode;
    } else {
        list->tail = newNode;
    }
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node * newNode = createNode(data);
    if (list->current == NULL){
        return;
    }
    newNode->next = list->current->next;
    newNode->prev = list->current;
    if (list->current->next != NULL){
        list->current->next->prev = newNode;
    } else {
        list->tail = newNode;
    }
    list->current->next = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current == NULL){
        return NULL;
    }
    Node * aux = list->current;
    void * data = aux->data;
    if (list->current->prev != NULL) {
        list->current->prev->next = list->current->next;
    } else {
        list->head = list->current->next;
    }
    if (list->current->next != NULL) {
        list->current->next->prev = list->current->prev;
    } else {
        list->tail = list->current->prev;
    }
    if (list->current->next != NULL) {
        list->current = list->current->next;
    } else {
        list->current = list->current->prev;
    }
    free(aux);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}