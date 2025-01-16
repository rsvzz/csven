#pragma once
typedef struct queue
{
    void* item;
    struct queue* next;
    struct queue* end;
}Queue;

/// @brief Add list
/// @param  Queue & lista
/// @param  Item add lista
void queue_append(Queue**, void*);
/// @brief Remove list queue
/// @param  Queue list
void queue_remove(Queue**);
