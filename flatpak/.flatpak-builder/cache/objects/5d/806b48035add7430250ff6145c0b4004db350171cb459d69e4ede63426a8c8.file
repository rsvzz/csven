#include "../../inc/queue.h"
#include <stdlib.h>
#include <stdio.h>
void queue_append(Queue** list, void* item){
    Queue *aux = malloc(sizeof(Queue));
    aux->item = item;
    aux->next = NULL;
    if(*list == NULL){
        //*list = malloc(sizeof(Queue));
        *list = aux;
        (*list)->end = aux;
    }
    else{
        (*list)->end->next = aux;
        (*list)->end = aux;
    }
}

void queue_remove(Queue** list){
    Queue *aux = *list;
    *list = aux->next;
    free(aux);
    aux = NULL;
}