
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

void print_rb_tree(const std::string& prefix, const rb_node* node, bool isLeft);
void init_node(rb_node *node, int value);
rb_node* find_node_to_connect(tree* rb_tree, int value);
void fix(tree* rb_tree, rb_node *node);
void insert_node(tree* rb_tree, int value);


#endif //UNTITLED_RED_BLACK_TREE_H
