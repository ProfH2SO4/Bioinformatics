#include <bits/stdc++.h>
#include "deletion.h"


using namespace std;
// clean whole tree
void delete_tree(rb_node *root){
    if(root->left_child!= nullptr) delete_tree(root->left_child);
    if(root->right_child!= nullptr) delete_tree(root->right_child);
    free(root);
}

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


void left_rotation(tree* rb_tree, rb_node* node, rb_node* node_parent, rb_node* node_right_child){
    if(node_parent->parent != nullptr) {
        if (is_left_child(node_parent->parent->value, node_parent->value)) {
            node_parent->parent->left_child = node_right_child;
        } else {
            node_parent->parent->right_child = node_right_child;
        }
    }
    else{
        rb_tree->root = node_right_child;
    }

    node_right_child->parent = node_parent->parent;
    if(node_right_child->left_child != nullptr){
       node_right_child->left_child->parent = node_parent;
    }

    node_parent->right_child = node_right_child->left_child;

    node_right_child->left_child = node_parent;
    node_parent->parent = node_right_child;

}

void right_rotation(tree* rb_tree, rb_node* node_left_child,
                    rb_node* node_parent, rb_node* node_right_child){

    if(node_parent->parent != nullptr) { // if not root
        if (is_left_child(node_parent->parent->value, node_parent->value)) {
            node_parent->parent->left_child = node_left_child;
        } else {
            node_parent->parent->right_child = node_left_child;
        }
    }
    else{
        rb_tree->root = node_left_child;
        //node_right_child->parent = nullptr;
    }

    node_left_child->parent = node_parent->parent;
    if (node_left_child->right_child != nullptr) {
        node_left_child->right_child->parent = node_parent;
    }

    node_parent->left_child = node_left_child->right_child;

    node_left_child->right_child = node_parent;

    node_parent->parent = node_left_child;
}


void recolor(rb_node* node_to_delete, rb_node* node_to_replace){
    if(node_to_delete->color == 1 && node_to_replace->color == 2){
        node_to_replace->color = 1;
    }
}

void fix_case_two(tree* rb_tree, rb_node* double_black, rb_node* r_parent, rb_node* s, bool side){
    s->color = 2;
    r_parent->color = 1;
    if(!side){
        left_rotation(rb_tree, double_black, r_parent, s);
        if(double_black->left_child == nullptr && double_black->right_child == nullptr){
            r_parent->left_child = nullptr;
        }
    }
    else{
        right_rotation(rb_tree, s, r_parent, double_black);
        if(double_black->left_child == nullptr && double_black->right_child == nullptr){
            r_parent->right_child = nullptr;
        }
    }

}

void fix_case_three(rb_node* double_black, rb_node* r_parent, rb_node* s, bool side){
    s->color = 1;
    if(double_black->left_child == nullptr && double_black->right_child == nullptr) {
        // connect parent
        if (!side) {
            r_parent->left_child = double_black->right_child;
        } else {
            r_parent->right_child = double_black->right_child;
        }
    }
}

// s => double_black parent other child, side true => double_black as right child
void fix_case_four(rb_node* double_black, rb_node* r_parent, rb_node* s, bool side){

    r_parent->color = 2;
    s->color = 1;

    if(double_black->left_child == nullptr && double_black->right_child == nullptr){
        if(!side){ // double_black on left
            r_parent->left_child = nullptr;
        }
        else
        {
            r_parent->right_child = nullptr;
        }
    }

    if(double_black->right_child != nullptr){
        if(!side){ // double_black on left
            r_parent->left_child = double_black->right_child;
        }
        else
        {
            r_parent->right_child = double_black->right_child;
        }
        double_black->right_child->parent = r_parent;
    }
}

void fix_case_five(tree* rb_tree, rb_node* replacement, rb_node* r_parent, rb_node* s, bool side){
    s->color = 1;
    if(!side){
        s->left_child->color = 2;
        right_rotation(rb_tree, s->left_child, s, s->right_child);
    }
    else{
        s->right_child->color = 2;
        left_rotation(rb_tree, s->left_child, s, s->right_child);

    }
}

void fix_case_six(tree* rb_tree, rb_node* double_black, rb_node* r_parent, rb_node* s, bool side){
    int temp = s->color;
    s->color = r_parent->color;
    r_parent->color = temp;
    if(!side){
        s->right_child->color = 2;
        left_rotation(rb_tree, double_black, r_parent, s);
        // if no children point to null
        if(double_black->left_child == nullptr && double_black->right_child == nullptr){
            r_parent->left_child = nullptr;
        }
    }
    else{
        s->left_child->color = 2;
        right_rotation(rb_tree, s, r_parent, double_black);
        if(double_black->left_child == nullptr && double_black->right_child == nullptr){
            r_parent->right_child = nullptr;
        }
    }
}
// initialize s children
pair<rb_node*, rb_node*> initialize_x_y(rb_node* s, bool side){
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

    return make_pair(x, y);

}
//if side false double black on left
bool is_second_case(rb_node* double_black, rb_node* r_parent, rb_node* s, bool side){
    //s on right side then x = left child, y = right child
    //mirror image x = right child, y = left child
    pair<rb_node*, rb_node*> s_child = initialize_x_y(s, side);

    if(double_black->color == 2 && r_parent->color == 2 && s->color == 1
       && s_child.first->color == 2 && s_child.second->color == 2){
        return true;
    }
    return false;
}

bool is_third_case(rb_node* double_black, rb_node* r_parent, rb_node* s, bool side){
    pair<rb_node*, rb_node*> s_child = initialize_x_y(s, side);

    if(double_black->color == 2 && r_parent->color == 2 && s->color == 2
       && (s_child.first == nullptr || s_child.first->color == 2)
       && (s_child.second == nullptr || s_child.second->color == 2)){
        return true;
    }

    return false;
}

bool is_fourth_case(rb_node* replacement, rb_node* r_parent, rb_node* s, bool side){
    if(replacement->color == 2 && replacement->parent->color == 1) {
        pair<rb_node*, rb_node*> s_child = initialize_x_y(s, side);
        if (s->color == 2 && (s_child.first == nullptr || s_child.first->color == 2)
            && (s_child.second == nullptr || s_child.second->color == 2)) {
            return true;
        }
    }
    return false;
}

//if side false double black on left
bool is_five_case(rb_node* replacement, rb_node* r_parent, rb_node* s, bool side){
    pair<rb_node*, rb_node*> s_child = initialize_x_y(s, side);
    if (replacement->color == 2 && s != nullptr
        && s->color == 2 && s_child.first != nullptr && s_child.first->color == 1
        && (s_child.second == nullptr || s_child.second->color == 2)) {
        return true;
    }
    return false;
}

void main_deletion_switcher(tree* rb_tree, int value_to_find) {
    if(rb_tree->root == nullptr){
        cout << "Tree is empty" << endl;
        return;
    }
    rb_node *node_to_replace = find_node(rb_tree->root, value_to_find);
    if (node_to_replace == nullptr) {
        cout << " Value not in tree!" << endl;
        return;
    }
    rb_node* in_ord_suc = find_smallest_node(node_to_replace->right_child); // find in_ord_suc
    // node to replace  has no post order successor
    if(in_ord_suc == nullptr) { in_ord_suc = node_to_replace;}
    node_to_replace->value = in_ord_suc->value;

    if(in_ord_suc->left_child == nullptr && in_ord_suc->right_child == nullptr){
        if(in_ord_suc->color == 1){ // if red leaf just delete it
            if(is_left_child(in_ord_suc->parent->value, in_ord_suc->value)){
                in_ord_suc->parent->left_child = nullptr;
            }
            else{
                in_ord_suc->parent->right_child = nullptr;
            }
            free(in_ord_suc);
            return;
        }
        //if is root
        if(in_ord_suc->parent == nullptr){ rb_tree->root = nullptr; free(in_ord_suc); return;}
    }
    // right child is red and has both null siblings
    if(in_ord_suc->right_child != nullptr && in_ord_suc->right_child->color == 1 &&
       in_ord_suc->right_child->left_child == nullptr && in_ord_suc->right_child->right_child == nullptr){

        in_ord_suc->value = in_ord_suc->right_child->value;
        free(in_ord_suc->right_child);
        in_ord_suc->right_child = nullptr;
        return;
    }
    // node_to_replace left child is red and left child has both children null
    else if(node_to_replace->right_child == nullptr
    && node_to_replace->left_child != nullptr
    && node_to_replace->left_child->color == 1
    && node_to_replace->left_child->left_child == nullptr
    && node_to_replace->left_child->right_child == nullptr){
        node_to_replace->value = node_to_replace->left_child->value;
        free(node_to_replace->left_child);
        node_to_replace->left_child = nullptr;
        return;
    }

    rb_node* double_black = in_ord_suc;

    for(auto i =0; i<3;++i) {
        rb_node* r_parent = double_black->parent;
        rb_node *y = nullptr;
        rb_node *s = nullptr;
        // false: double_black is on right side, true: left side
        bool r_left = is_left_child(double_black->parent->value, double_black->value);
        if (r_left) {
            y = r_parent->right_child->right_child;
            s = r_parent->right_child;
        } else {
            y = r_parent->left_child->left_child;
            s = r_parent->left_child;
        }
        // 2 case
        if(is_second_case(double_black, double_black->parent, s, !r_left)){
            fix_case_two(rb_tree, double_black, double_black->parent, s, !r_left);
            continue;
        }
        // 3 case
        if (is_third_case(double_black, double_black->parent, s, !r_left)) {
            fix_case_three(double_black, double_black->parent, s, !r_left);
            double_black = double_black->parent;
            if (double_black->parent == nullptr) { // if in_ord_suc->parent is root then end;
                free(in_ord_suc);
                return;
            }
        }
        // 4 case
        if(is_fourth_case(double_black, double_black->parent,s, !r_left)){
            fix_case_four(double_black, double_black->parent, s, !r_left);
            free(in_ord_suc);
            return;
        }
        // 5 case
        if (is_five_case(double_black, double_black->parent, s, !r_left)) {
            fix_case_five(rb_tree, double_black, double_black->parent, s, !r_left);
        }
        // 6 case
        if (double_black->color == 2 && s != nullptr && s->color == 2
        && y != nullptr && y->color == 1) {
            fix_case_six(rb_tree ,double_black, r_parent, s, !r_left);
            free(in_ord_suc);
            return;

        }
    }
}