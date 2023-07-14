#include "queue.h"
struct Queue{
    Vector *vector;
};


Queue *queue_construct(){
    Queue *q = (Queue*) malloc( sizeof(Queue) );
    q->vector = vector_construct();
    return q;
}

void queue_push(Queue *queue, data_type data){
    vector_push_back(queue->vector, data);
}

bool queue_empty(Queue *queue){
    return vector_size(queue->vector) == 0;
}

void *queue_pop(Queue *queue){
    return vector_pop_front(queue->vector);
}

void queue_destroy(Queue *queue){
    vector_destroy(queue->vector);
    free(queue);
}

// void print_size(Queue *q){
//     // printf("SIZE %d\n", deque_size(q->vector));
// }