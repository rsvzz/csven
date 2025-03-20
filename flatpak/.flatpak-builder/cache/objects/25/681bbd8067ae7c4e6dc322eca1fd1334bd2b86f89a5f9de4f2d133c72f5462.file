#include "../../inc/stack.h"
#include <stdlib.h>
#include <stdio.h>

void stack_append(Stack **base, void *inf)
{

    Stack *aux = malloc(sizeof(Stack));
    aux->item = inf;
    if (*base == NULL)
    {
        aux->next = NULL;
        //*base = malloc(sizeof(Stack));
        *base = aux;
    }
    else
    {
        aux->next = *base;
        *base = aux;
    }
}

void stack_delete_top(Stack **base)
{
    Stack *aux = *base;
    *base = aux->next;
    free(aux);
    aux = NULL;
}