#include "stack.h"

struct Stack{
    Vector *vector;
};

Stack *stack_construct(){
    Stack *s = (Stack*) malloc( sizeof(Stack) );
    s->vector = vector_construct();
    return s;
}

void stack_push(Stack *stack, void *data){
    vector_push_back(stack->vector, data);
}

bool stack_empty(Stack *stack){
    return vector_size(stack->vector) == 0;
}

void *stack_pop(Stack *stack){
    return vector_pop_back(stack->vector);
}

void stack_destroy(Stack *stack){
    vector_destroy(stack->vector);
    free(stack);
}