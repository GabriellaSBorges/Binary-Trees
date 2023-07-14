#include "binary_tree.h"

struct Node{
    void *key;
    void *value;
    Node *left;
    Node *right;
    Node *parent;
};

struct BinaryTree{
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

void key_val_pair_destroy(KeyValPair *kvp, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    free(kvp);
}

Node *node_construct(void *key, void *value, Node *left, Node *right, Node *parent){
    Node *node = (Node*) malloc( sizeof(Node) );

    node->key = key;
    node->value = value;
    node->left = left;
    node->right = right;
    node->parent = parent;

    return node;
}

void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){

    if( node ){
        key_destroy_fn(node->key);
        val_destroy_fn(node->value);
        
        if( node->left )
            node_destroy(node->left, key_destroy_fn, val_destroy_fn);
        if( node->right )
            node_destroy(node->right, key_destroy_fn, val_destroy_fn);
    }
    

   
    free(node);
}

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){

    BinaryTree *bt = (BinaryTree*) malloc( sizeof(BinaryTree) );
    bt->root = NULL;
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;

    return bt;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){
    bt->root = add_recursive(bt, bt->root, NULL, key, value);
}

Node *add_recursive(BinaryTree *bt, Node *node, Node *parent, data_type key, data_type val){
    
    if( !node )
        return node_construct(key, val, NULL, NULL, parent);

    parent = node;
    int cmp = bt->cmp_fn(key, node->key);

    if( cmp < 0 )
        node->left = add_recursive(bt, node->left, parent, key, val);
    else if( cmp > 0 )
        node->right = add_recursive(bt, node->right, parent, key, val);
    else{
        bt->key_destroy_fn(key);
        bt->val_destroy_fn(node->value);
        node->value = val;
    }
        
    return node;
}

int binary_tree_empty(BinaryTree *bt){
    return !bt->root;
}

void binary_tree_remove(BinaryTree *bt, void *key){
    Node *node = get_recursive(bt->cmp_fn, bt->root, key);

    if( !node->left )
        transplant(bt, node, node->right);
    else if( !node->right )
        transplant(bt, node, node->left);

    else{
        Node *new = node->right;

        if( new->parent == node ){
            transplant(bt, node, new);
            new->left = node->left;
            new->left->parent = new;

        } else {
            transplant(bt, new, new->right);
            new->right = node->right;
            new->right->parent = new;
        }
    }

    bt->key_destroy_fn(node->key);
    bt->val_destroy_fn(node->value);
    free(node);
}

void transplant(BinaryTree *bt, Node *old, Node *new){

    if( !old->parent )
        bt->root = new;
    else if( old == old->parent->left )
        old->parent->left = new;
    else 
        old->parent->right = new;
    
    if( new )
        new->parent = old->parent;
}

KeyValPair *binary_tree_min(BinaryTree *bt){
    Node *node = bt->root;

    while( node->left )
        node = node->left;
    
    return key_val_pair_construct( node->key, node->value );
}

KeyValPair *binary_tree_max(BinaryTree *bt){
    Node *node = bt->root;

    while( node->right )
        node = node->right;
    
    return key_val_pair_construct( node->key, node->value );
}

void *binary_tree_get(BinaryTree *bt, void *key){
    Node *node = get_recursive(bt->cmp_fn, bt->root, key);

    if( !node )
        return NULL;
    
    return node->value;
}

Node *get_recursive(CmpFn cmp_fn, Node *node, data_type key){

    if( !node )
        return NULL;

    int cmp = cmp_fn(key, node->key);

    if( !cmp )
        return node;
    else if( cmp < 0 )
        node = get_recursive(cmp_fn, node->left, key);
    else if( cmp > 0 )
        node = get_recursive(cmp_fn, node->right, key);
    

    return node;
}

void binary_tree_destroy(BinaryTree *bt){
    node_destroy(bt->root, bt->key_destroy_fn, bt->val_destroy_fn);
    free(bt);
}