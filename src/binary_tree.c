#include "binary_tree.h"

struct Node{
    void *key;
    void *value;
    struct Node *left;
    struct Node *right;
};

struct BinaryTree{
    // int size;
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};

KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *kvp = (KeyValPair*) malloc( sizeof(KeyValPair) );

    kvp->key = key;
    kvp->value = val;

    return kvp;
}

void key_val_pair_destroy(KeyValPair *kvp){
    free(kvp);
}

Node *node_construct(void *key, void *value, Node *left, Node *right){
    Node *node = (Node*) malloc( sizeof(Node) );

    node->key = key;
    node->value = value;
    node->left = left;
    node->right = right;

    return node;
}

void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){

    key_destroy_fn(node->key);
    val_destroy_fn(node->value);
    
    if( node->left )
        node_destroy(node->left, key_destroy_fn, val_destroy_fn);
    if( node->right )
        node_destroy(node->right, key_destroy_fn, val_destroy_fn);
   
    free(node);
}

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){

    BinaryTree *bt = (BinaryTree*) malloc( sizeof(BinaryTree) );
    // bt->size = 0;
    bt->root = NULL;
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;

    return bt;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){
    bt->root = add_recursive(bt->root, key, value);
    // free(value);
    // free(key);
}

Node *add_recursive(Node *node, data_type key, data_type val){

    if( !node )
        return node_construct(key, val, NULL, NULL);
    
    if( strcmp(key, node->key) < 0 )
        node->left = add_recursive(node->left, key, val);
    else
        node->right = add_recursive(node->right, key, val);

    return node;
}

int binary_tree_empty(BinaryTree *bt){
    return !bt->root;
}

void binary_tree_remove(BinaryTree *bt, void *key);




void *binary_tree_get(BinaryTree *bt, void *key){
    Node *node = get_recursive(bt->root, key);

    if( !node )
        return NULL;
    
    return node->value;
}

Node *get_recursive(Node *node, data_type key){

    if( !node )
        return NULL;

    int cmp = strcmp(key, node->key);

    if( !cmp )
        return node;
    else if( cmp < 0 )
        node = get_recursive(node->left, key);
    else if( cmp > 0 )
        node = get_recursive(node->right, key);
    

    return node;
}

void binary_tree_destroy(BinaryTree *bt){
    node_destroy(bt->root, bt->key_destroy_fn, bt->val_destroy_fn);
    free(bt);
}