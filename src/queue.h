#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "types.h"
#include "vector.h"

typedef struct Queue Queue;

// cria uma queue
Queue *queue_construct();

// insere um item na queue 
void queue_push(Queue *queue, data_type value);

// remove o elemento mais antigo da pilha e o retorna
data_type queue_pop(Queue *queue);

// retorna 1 se a queue está vazia e 0 caso contrário
bool queue_empty(Queue *queue);

// libera o espaco alocado para a queue
void queue_destroy(Queue *queue);

// void print_size(Queue *q);

#endif