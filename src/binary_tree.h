
#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "stack.h"
#include "queue.h"

typedef struct Node Node;
typedef struct BinaryTree BinaryTree;

typedef int (*CmpFn)(void *, void *);
typedef void (*KeyDestroyFn)(void *);
typedef void (*ValDestroyFn)(void *);

typedef struct{
    void *key;
    void *value;
} KeyValPair;

// constroi e destroi um ponteiro para struct KeyValPair
KeyValPair *key_val_pair_construct(void *key, void *val);
void key_val_pair_destroy(KeyValPair *kvp);

// constroi e destroi um node
Node *node_construct(void *key, void *value, Node *left, Node *right, Node *parent);
void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn);

// constroi um ponteiro para struct BinaryTree
BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn);

// adiciona um nó à árvore, com auxilio de uma funcao recursiva que percorre a arvore e adiciona o novo nó
void binary_tree_add(BinaryTree *bt, void *key, void *value);
Node *add_recursive(BinaryTree *bt, Node *node, Node *parent, data_type key, data_type val);

// retorna 1 se a arvore estiver vazia e 0 caso contrario
int binary_tree_empty(BinaryTree *bt);

// remove um nó da árvore
void binary_tree_remove(BinaryTree *bt, void *key);

// verifica a posicao do nó a ser retirado para trocar as subarvores, a partir da funcao "transplant"
void change_nodes_from_tree(BinaryTree *bt, Node *old);

// retorna o menor nó a partir do nó dado como parametro
Node *tree_minimum(Node *node);

// troca uma subarvore por outra, a fim de retirar um nó
void transplant(BinaryTree *bt, Node *old, Node *new);

// retorna o valor do nó minimo ou maximo da arvore
KeyValPair *binary_tree_min(BinaryTree *bt);
KeyValPair *binary_tree_max(BinaryTree *bt);

// retorna o valor do nó minimo ou maximo da arvore e o remove
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);

// retorna o valor de um nó, com auxilio de uma funcao recursiva que percorre a arvore a fim de achar o no procurado
void *binary_tree_get(BinaryTree *bt, void *key);
Node *get_recursive(CmpFn cmp_fn, Node *node, data_type key);

// libera a memoria armazenada para um ponteiro de struct BinaryTree
void binary_tree_destroy(BinaryTree *bt);

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

// funcoes iterativas de percurso em arvore binaria 
Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

// funcoes recursivas de percurso em arvores binarias
Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
void inorder(Vector *vector, Node *node);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
void preorder(Vector *vector, Node *node);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);
void postorder(Vector *vector, Node *node);

#endif