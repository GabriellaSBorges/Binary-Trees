#ifndef _STACK_H_
#define _STACK_H_

#include "types.h"
#include "vector.h"

typedef struct Stack Stack;

// cria uma stack
Stack *stack_construct();

// insere um item na stack
void stack_push(Stack *stack, void *data);

// retorna 1 se a queue está vazia e 0 caso contrário
bool stack_empty(Stack *stack);

// remove o elemento mais novo da pilha e o retorna
void *stack_pop(Stack *stack);

// libera o espaco alocado para a stack
void stack_destroy(Stack *stack);

#endif