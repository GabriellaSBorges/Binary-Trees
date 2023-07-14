
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

// typedef struct Node
// {
//     void *key;
//     void *value;
//     struct Node *left;
//     struct Node *right;
// } Node;

// typedef struct
// {
//     Node *root;
//     CmpFn cmp_fn;
//     KeyDestroyFn key_destroy_fn;
//     ValDestroyFn val_destroy_fn;
// } BinaryTree;

KeyValPair *key_val_pair_construct(void *key, void *val);
void key_val_pair_destroy(KeyValPair *kvp);
// void *pair_return_key(KeyValPair *kvp);
// void *pair_return_val(KeyValPair *kvp);

Node *node_construct(void *key, void *value, Node *left, Node *right, Node *parent);
void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn);

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn);
void binary_tree_add(BinaryTree *bt, void *key, void *value);
Node *add_recursive(BinaryTree *bt, Node *node, Node *parent, data_type key, data_type val);

int binary_tree_empty(BinaryTree *bt);
void binary_tree_remove(BinaryTree *bt, void *key);
void change_nodes_from_tree(BinaryTree *bt, Node *old);
void transplant(BinaryTree *bt, Node *old, Node *new);

KeyValPair *binary_tree_min(BinaryTree *bt);
KeyValPair *binary_tree_max(BinaryTree *bt);
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);

void *binary_tree_get(BinaryTree *bt, void *key);
Node *get_recursive(CmpFn cmp_fn, Node *node, data_type key);

void binary_tree_destroy(BinaryTree *bt);

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
void inorder(Vector *vector, Node *node);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
void preorder(Vector *vector, Node *node);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);
void postorder(Vector *vector, Node *node);

#endif