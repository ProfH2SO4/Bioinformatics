
#ifndef UNTITLED_RED_BLACK_TREE_H
#define UNTITLED_RED_BLACK_TREE_H


typedef struct rb_node{
    rb_node *parent;
    rb_node *left_child;
    rb_node *right_child;
    int color;
    int value;
} rb_node;

typedef struct tree{
    rb_node *root;
} tree;

rb_node* find_node(tree* rb_tree, int value);
void fix(tree* rb_tree, rb_node *node);
void insert_node(tree* rb_tree, int value);


#endif //UNTITLED_RED_BLACK_TREE_H
