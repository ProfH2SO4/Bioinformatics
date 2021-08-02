#include <bits/stdc++.h>
#include "deletion.h"


using namespace std;

rb_node* find_node(rb_node* root, int value_to_find){
    rb_node *temp = root;
    bool found = false;

    while(temp != nullptr){
        if(temp->value == value_to_find){
            found = true;
            break;
        }
        if( temp->value > value_to_find){
            temp = temp->left_child;
        }
        else{
            temp = temp->right_child;
        }
    }

    if(!found){ // if not found in tree
        return nullptr;
    }
    return temp;

}

rb_node* find_smallest_node(rb_node* node){
    rb_node* temp = node;
    while(temp->left_child != nullptr){
        temp = temp->left_child;
    }
    return temp;

}


void delete_leaf(rb_node* node_to_delete){

    if(node_to_delete->color == 1){
        if(node_to_delete->left_child == nullptr && node_to_delete->right_child == nullptr){
            if(node_to_delete->value >= node_to_delete->parent->value){
                node_to_delete->parent->right_child= nullptr;
            }
            else{
                node_to_delete->parent->left_child = nullptr;
            }
            free(node_to_delete);
        }
    }
}

bool is_left_child(int parent_value, int child_value){
    return child_value < parent_value; // true if left child
}

bool is_root(rb_node root){
    return root.parent == nullptr; // true if root
}

void delete_case_two(rb_node* node_to_fix){
    node_to_fix->left_child->color = 1;
    if(node_to_fix->color == 1) { node_to_fix->color = 2; return; }

}

void left_rotation(rb_node* node_parent, rb_node* node, rb_node* node_right_child){
       if(is_left_child(node_parent->value, node->value)){
           node->parent->right_child = node_right_child;
       }
       else{
           node->right_child->left_child = node_right_child;
       }

       node->right_child->parent = node->parent;
       node->right_child->left_child = node->right_child;

       node_right_child->left_child = node;
       node->parent =  node_right_child;
}

void right_rotation(rb_node* node_parent, rb_node* node, rb_node* node_left_child){
    if(is_left_child(node_parent->value, node->value)){
        node->parent->right_child = node_left_child;
    }
    else{
        node->right_child->left_child = node_left_child;
    }

    node->left_child->parent = node->parent;
    node->left_child->right_child = node->left_child;

    node_left_child->right_child = node;
    node->parent =  node_left_child;
}

void delete_case_fourth(rb_node* x, rb_node* w, bool side) { // if true then x is on right side
    w->color = x->parent->color;
    x->parent->color = 2; // x parent black
    if(side){ //x on right side
        w->left_child->color = 2;
        left_rotation(x->parent->parent, x->parent, w);
    }
    else{ // x on left side
        w->right_child->color = 2;
        right_rotation(x->parent->parent, x->parent, w);
    }
}

void delete_one_null(rb_node* node_to_delete){
    rb_node* temp = nullptr;
    rb_node* x = nullptr;
    if(node_to_delete->right_child != nullptr){
        if(node_to_delete->right_child->left_child == nullptr){
            temp = node_to_delete->right_child;
        }
        else{
            temp = find_smallest_node(node_to_delete->right_child);
            temp->parent->left_child = temp->right_child;
            if(temp->right_child != nullptr){
                temp->right_child->parent = temp->parent;
            }
        }
        x = temp->right_child;
        if(node_to_delete->left_child != nullptr){ // check if one null child
            temp->left_child = node_to_delete->left_child;
            temp->left_child->parent = temp->left_child;
        }
        temp->parent = node_to_delete->parent;
    }

    if(!is_root(*node_to_delete) && is_left_child(node_to_delete->parent->value, node_to_delete->value)){
        node_to_delete->parent->left_child = temp;
    }
    else if(!is_root(*node_to_delete) && !is_left_child(node_to_delete->parent->value, node_to_delete->value)){
        node_to_delete->parent->right_child = temp;
    }

    // recolor
    if(node_to_delete->color == 1){
        temp->color = 1;
    }

    if(node_to_delete->color == 2 && temp->color == 1){
        temp->color = 2;
    }

    if(temp->color == 1 && temp->right_child->color == 1){
        temp->right_child->color = 2;
    }
    free(node_to_delete);

    //second case
    if(temp != nullptr && temp->right_child != nullptr && temp->left_child != nullptr){
        if(temp->right_child->color == 2 && temp->left_child->color == 2 &&
        (temp->left_child->left_child  == nullptr|| temp->left_child->left_child->color == 2) &&
        (temp->left_child->right_child  == nullptr|| temp->right_child->right_child->color == 2)){
            delete_case_two(temp);
        }
    }

    //third or fourth case
    rb_node* w = NULL;
    if(is_left_child(x->parent->value, x->value)){ // x is left child
        w = x->parent->right_child;
        if(x->color == 2  && x->parent->right_child->color == 2 // fourth case
        && w->right_child != nullptr && w->right_child->color == 1){
            delete_case_fourth(x, w, false);
        }
    }
    else{
        w = x->parent->left_child;
        if(x->color == 2  && x->parent->left_child->color == 2 // fourth case
           && w->left_child != nullptr && w->left_child->color == 1){
            delete_case_fourth(x, w,true);
        }
    }
}




void main_deletion_switcher(tree* rb_tree, int value_to_find){
    rb_node* node_to_delete = find_node(rb_tree->root, value_to_find);
    if(node_to_delete == nullptr){
        cout << " Value not in tree!" << endl;
        return;
    }
    // both children NULL
    if(node_to_delete->right_child == nullptr && node_to_delete->left_child == nullptr){
        delete_leaf(node_to_delete);
    }
    else if(node_to_delete->right_child == nullptr || node_to_delete->left_child == nullptr){
        delete_one_null(node_to_delete);
    }
    delete_one_null(node_to_delete);
}