#pragma once
typedef struct stack
{
    /* data */
    struct stack *next;
    void* item;
}Stack;



/// @brief 
/// @param  Stack
/// @param  Value generic
void stack_append(Stack**, void*);
void stack_delete_top(Stack**);
