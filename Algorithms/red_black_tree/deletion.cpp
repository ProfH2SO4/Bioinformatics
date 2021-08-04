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
    if(node == nullptr){
        return nullptr;
    }
    rb_node* temp = node;
    while(temp->left_child != nullptr){
        temp = temp->left_child;
    }
    return temp;

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

void left_rotation(rb_node* node, rb_node* node_parent, rb_node* node_right_child){
       if(is_left_child(node_parent->parent->value, node_parent->value)){
           node_parent->parent->left_child = node_right_child;
       }
       else{
           node_parent->parent->right_child = node_right_child;
       }

       node_right_child->parent = node_parent->parent;
       if(node_right_child->left_child != nullptr){
           node_right_child->left_child->parent = node_parent;
       }

       node_parent->right_child = node_right_child->left_child;

       node_right_child->left_child = node_parent;
       node_parent->parent = node_right_child;

}

void right_rotation(rb_node* node, rb_node* node_parent, rb_node* node_left_child){
    if(is_left_child(node_parent->parent->value, node_parent->value)){
        node_parent->parent->left_child = node_left_child;
    }
    else{
        node_parent->parent->right_child = node_left_child;
    }

    node_left_child->parent = node_parent->parent;
    if(node_left_child->right_child != nullptr){
        node_left_child->right_child->parent = node_parent;
    }

    node_parent->left_child = node_left_child->right_child;

    node_left_child->right_child = node_parent;
    node_parent->parent = node_left_child;
}

void delete_case_fourth(rb_node* x, rb_node* w, bool side) { // if true then x is on right side
    w->color = x->parent->color;
    x->parent->color = 2; // x parent black
    if(side){ //x on right side
        w->left_child->color = 2;
        right_rotation(x->parent->parent, x->parent, w);
    }
    else{ // x on left side
        w->right_child->color = 2;
        left_rotation(x->parent->parent, x->parent, w);
    }
}

void recolor(rb_node* node_to_delete, rb_node* node_to_replace){
    if(node_to_delete->color == 1 && node_to_replace->color == 2){
        node_to_replace->color = 1;
    }
}

void fix_case_three(rb_node* replacement, rb_node* r_parent, rb_node* r_p_o_child, bool side){
        r_p_o_child->color = 1;

}

// s => replacement parent other child, side true => replacement as right child
void fix_case_four(rb_node* replacement, rb_node* r_parent, rb_node* s, bool side){

    r_parent->color = 1;
    s->color = 2;

    if(replacement->left_child == nullptr && replacement->right_child == nullptr){
        if(!side){ // replacement on left
            r_parent->left_child = nullptr;
        }
        else
        {
            r_parent->right_child = nullptr;
        }
    }

    if(replacement->right_child != nullptr){
        if(!side){ // replacement on left
            r_parent->left_child = replacement->right_child;
        }
        else
        {
            r_parent->right_child = replacement->right_child;
        }
        replacement->right_child->parent = r_parent;
    }

    free(replacement);
}

void fix_case_five(rb_node* replacement, rb_node* r_parent, rb_node* s, bool side){
    s->color = 1;
    if(!side){
        s->left_child->color = 2;
        right_rotation(s->left_child, s, s->right_child);
    }
    else{
        s->right_child->color = 2;
        //left_rotation(s->right_child, s, s->left_child);
        left_rotation(s->left_child, s, s->right_child);

    }
}

void fix_case_six(rb_node* replacement, rb_node* r_parent, rb_node* s, bool side){
    s->color = r_parent->color;
    r_parent->color = 2;
    if(!side){
        s->right_child->color = 2;
        left_rotation(replacement, r_parent, s);
        r_parent->left_child = nullptr;

    }
    else{
        s->left_child->color = 2;
        right_rotation(replacement, r_parent, s);
        r_parent->right_child = nullptr;
    }
    free(replacement);
}


bool is_third_case(rb_node* replacement, rb_node* r_parent, rb_node* r_p_o_child, bool side){
    if(!side){
        if(replacement->color == 2 && r_parent->color == 2 && r_p_o_child->color == 2
        && (r_p_o_child->left_child == nullptr || r_p_o_child->left_child->color == 2)
        && (r_p_o_child->right_child == nullptr || r_p_o_child->right_child->color == 2)){
            return true;
        }
    }
    return false;
}

bool is_fourth_case(rb_node* replacement, rb_node* r_parent, rb_node* s, bool side){
    if(replacement->color == 2 && replacement->parent->color == 1) {
        rb_node* x = nullptr;
        rb_node* y = nullptr;
        if(!side) {
            x = s->left_child;
            y = s->right_child;
        }
        else{
            x = s->right_child;
            y = s->left_child;
        }
        if (s->color == 2 && (x == nullptr || x->color == 2)
            && (y == nullptr) || (y->color == 2)) {
            return true;
        }
    }
    return false;
}

//if side false replacement on left
bool is_five_case(rb_node* replacement, rb_node* r_parent, rb_node* s, bool side){
    rb_node* x = nullptr;
    rb_node* y = nullptr;
    if(!side) {
        x = s->left_child;
        y = s->right_child;
    }
    else{
            x = s->right_child;
            y = s->left_child;
        }
    if (replacement->color == 2 && replacement->parent->color == 2 && s != nullptr
        && s->color == 2 && x != nullptr && x->color == 1
        && (y == nullptr || y->color == 2)) {
        return true;
    }
    return false;
}

void main_deletion_switcher(tree* rb_tree, int value_to_find) {
    rb_node *node_to_replace = find_node(rb_tree->root, value_to_find);
    if (node_to_replace == nullptr) {
        cout << " Value not in tree!" << endl;
        return;
    }
    rb_node* replacement = NULL;
    replacement = find_smallest_node(node_to_replace->right_child); // find replacement
    // node to replace is leaf
    if(replacement == nullptr) { replacement = node_to_replace;}
    node_to_replace->value = replacement->value;

    if(replacement->left_child == NULL && replacement->right_child == NULL){
        if(replacement->color == 1){ // if red leaf just delete it
            if(is_left_child(replacement->parent->value, replacement->value)){
                replacement->parent->left_child = nullptr;
            }
            else{
                replacement->parent->right_child = nullptr;
            }
            free(replacement);
            return;
        }
        //if is root
        if(replacement->parent == nullptr){ rb_tree->root = nullptr; free(replacement); return;}
    }
    // right child is red and has both null siblings
    if(replacement->right_child != nullptr && replacement->right_child->color == 1 &&
    replacement->right_child->left_child == nullptr && replacement->right_child->right_child == nullptr){

        replacement->value = replacement->right_child->value;
        free(replacement->right_child);
        replacement->right_child = nullptr;
        return;
    }
    rb_node* r_parent = replacement->parent;


    // replacement is on left side if false
    bool r_left = is_left_child(replacement->parent->value, replacement->value);
    while(true) {
        rb_node *y = nullptr;
        rb_node *s = nullptr;
        if (r_left) {
            y = r_parent->right_child->right_child;
            s = r_parent->right_child;
        } else {
            y = r_parent->left_child->left_child;
            s = r_parent->left_child;
        }
        // 3 case
        if (is_third_case(replacement, replacement->parent, s, !r_left)) {
            fix_case_three(replacement, replacement->parent, s, !r_left);
            if (replacement->parent->parent == nullptr) { // if replacement->parent is root then end;
                return;
            }
        }
        // case 4
        if(is_fourth_case(replacement, replacement->parent,s, false)){
            fix_case_four(replacement, replacement->parent, s, false);
            return;
        }

        // 5 case
        if (is_five_case(replacement, replacement->parent, s, !r_left)) {
            fix_case_five(replacement, replacement->parent, s, !r_left);
        }
        // 6 case
        if (replacement->color == 2 && s != nullptr && s->color == 2 &&
            y != nullptr && y->color == 1) {
            fix_case_six(replacement, r_parent, s, !r_left);
            return;

        }
    }
}