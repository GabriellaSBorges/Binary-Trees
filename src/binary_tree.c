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

void key_val_pair_destroy(KeyValPair *kvp){
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

    change_nodes_from_tree(bt, node);

    bt->key_destroy_fn(node->key);
    bt->val_destroy_fn(node->value);
    free(node);
}

void change_nodes_from_tree(BinaryTree *bt, Node *node){

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

KeyValPair *binary_tree_pop_min(BinaryTree *bt){
    Node *node = bt->root;

    while( node->left )
        node = node->left;
    KeyValPair *pair =  key_val_pair_construct( node->key, node->value );

    change_nodes_from_tree(bt, node);
    free(node);

    return pair;
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt){
   Node *node = bt->root;

    while( node->right )
        node = node->right;
    KeyValPair *pair =  key_val_pair_construct( node->key, node->value );

    change_nodes_from_tree(bt, node);
    free(node);

    return pair;
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

Vector *binary_tree_inorder_traversal(BinaryTree *bt){
    Stack *stack =  stack_construct();
    Vector *vector = vector_construct();
    Node *node = bt->root;

    stack_push(stack, node);
    node = node->left;

    while( !stack_empty(stack) || node ){
        while( node ){
            stack_push(stack, node);
            node = node->left;
        }

        if( stack_empty(stack) ){
            break;

        } else {
            node = stack_pop(stack);

            KeyValPair *pair = key_val_pair_construct(node->key, node->value);
            vector_push_back(vector, pair);

            node = node->right;
        }     
    }

    stack_destroy(stack);
    return vector;
}

Vector *binary_tree_preorder_traversal(BinaryTree *bt){
    Stack *stack =  stack_construct();
    Vector *vector = vector_construct();
    Node *node = bt->root;

    stack_push(stack, node);

    while( !stack_empty(stack) && node ){
        node = stack_pop(stack);

        KeyValPair *pair = key_val_pair_construct(node->key, node->value);
        vector_push_back(vector, pair);

        if( node->right )
            stack_push(stack, node->right);
        if( node->left )
            stack_push(stack, node->left);
    }

    stack_destroy(stack);
    return vector;
}

Vector *binary_tree_postorder_traversal(BinaryTree *bt){
    Stack *stack_1 =  stack_construct();
    Stack *stack_2 =  stack_construct();

    Vector *vector = vector_construct();
    Node *node = bt->root;

    stack_push(stack_1, node);

    while( !stack_empty(stack_1) ){
        node = stack_pop(stack_1);

        if( node->left )
            stack_push(stack_1, node->left);
        if( node->right )
            stack_push(stack_1, node->right);
        
        stack_push(stack_2, node);
    }

    while( !stack_empty(stack_2) ){
        node = stack_pop(stack_2);

        KeyValPair *pair = key_val_pair_construct(node->key, node->value);
        vector_push_back(vector, pair);
    }

    stack_destroy(stack_1);
    stack_destroy(stack_2);
    return vector;
}

Vector *binary_tree_levelorder_traversal(BinaryTree *bt){
    Queue *queue = queue_construct();

    Vector *vector = vector_construct();
    Node *node = bt->root;
    queue_push(queue, node);

    while( !queue_empty(queue) ){
        node = queue_pop(queue);

        if( node->left )
            queue_push(queue, node->left);
        if( node->right )
            queue_push(queue, node->right);

        KeyValPair *pair = key_val_pair_construct(node->key, node->value);
        vector_push_back(vector, pair);
    }

    queue_destroy(queue);
    return vector;
}

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt){
    Vector *vector = vector_construct();
    inorder(vector, bt->root);

    return vector;
}

void inorder(Vector *vector, Node *node){

    if( !node )
        return;
    
    inorder(vector, node->left);

    KeyValPair *pair = key_val_pair_construct(node->key, node->value);
    vector_push_back(vector, pair);

    inorder(vector, node->right);
}

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt){
    Vector *vector = vector_construct();
    preorder(vector, bt->root);

    return vector;
}

void preorder(Vector *vector, Node *node){
    if( !node )
        return;
        
    KeyValPair *pair = key_val_pair_construct(node->key, node->value);
    vector_push_back(vector, pair);
    
    preorder(vector, node->left);
    preorder(vector, node->right);
}

Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);

void postorder(Vector *vector, Node *node);
