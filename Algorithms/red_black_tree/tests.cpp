#include <bits/stdc++.h>
#include "red_black_tree.h"


using namespace std;

struct flags{
    bool ok;
};
// test when 3 nodes
void test1(tree* rb_tree) {
    cout << "test1: " << endl;
    if (rb_tree->root->parent == NULL) {
        cout << "Root parent is NULL: OK" << endl;
    } else {
        cout << "Root parent is NULL: Mistake!" << endl;
    }

    if (rb_tree->root->color == 2) {
        cout << "Root parent color: OK" << endl;
    } else {
        cout << "Root parent color: Mistake!" << endl;
    }

    if (rb_tree->root->value > rb_tree->root->left_child->value) {
        cout << "Root Left Child value: OK" << endl;
    } else {
        cout << "Root Left Child value: Mistake!" << endl;
    }

    if (rb_tree->root->value <= rb_tree->root->right_child->value) {
        cout << "Root Right Child value: OK" << endl;
    } else {
        cout << "Root Right Child value: Mistake!" << endl;
    }


    if(rb_tree->root->left_child->color == 1 && rb_tree->root->right_child->color == 1){
        cout << "Root Right and Left Children color: OK" << endl;
    }
    else{
        cout << "Root Right and Left Children color: Mistake!" << endl;
    }

}

void test_whole_tree(tree *rb_tree, rb_node *node){
    if(node == NULL){
        return;
    }

    //dfs
    if(node->left_child != NULL){
        test_whole_tree(rb_tree, node->left_child);
    }
    if(node->right_child != NULL){
        test_whole_tree(rb_tree, node->right_child);
    }

    if(rb_tree->root->parent == NULL){
        cout<< "Root OK" << endl;
    }
    else{
        cout<< "Root Mistake!" << endl;
    }

    if(node->left_child != NULL){
        if(node->left_child->value < node->value){
            cout << "left value Ok" << endl;
        }
        else{
            cout << node->value << " Left value " << node->left_child->value << " Mistake!" << endl;
        }
    }
    if(node->right_child != NULL){
        if( node->right_child->value >= node->value){
            cout << "Right value Ok" << endl;
        }
        else{
            cout << node->value << " Right value " << node->right_child->value << " Mistake!" << endl;
        }
    }
}

void test_colors(rb_node *node){
    bool ok = true;
    if(node == NULL){
        return;
    }

    //dfs
    if(node->left_child != NULL){
        test_colors(node->left_child);
    }
    if(node->right_child != NULL){
        test_colors(node->right_child);
    }

    if(node->parent == NULL){
        if(node->color == 2){
            cout << "Root color Ok" << endl;
        }
        else{
            cout <<  "Root color: Mistake!" << endl;
        }
    }

    if(node->color == 1){ // red node must have black siblings
        if(node->left_child != NULL && node->left_child->color != 2){
            ok = false;
            cout << node->value << " Has wrong color!" << endl;
        }
        if(node->right_child != NULL &&node->right_child->color != 2){
            ok = false;
            cout << node->value << " Has wrong color!" << endl;
        }
    }

    if(ok){
        cout << "Tree has colors ok" << endl;
    }
    else{
        cout << "Tree colors Mistake!" << endl;
    }
}