#include <bits/stdc++.h>
#include "red_black_tree.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "red_black_tree.h"

using namespace std;

struct basic_test : public testing::Test{
    tree tree1;

    void SetUp() {
        tree1.root = nullptr;
        insert_node(&tree1, 15);
        insert_node(&tree1, 5);
        insert_node(&tree1, 1);
        insert_node(&tree1, 40);
        insert_node(&tree1, 12);
        insert_node(&tree1, 23);
        insert_node(&tree1, 9);
        insert_node(&tree1, 13);
        insert_node(&tree1, 10);
    }
};

struct complex_tree : public testing::Test {
    tree tree2;

    void SetUp() {
        tree2.root = nullptr;
        insert_node(&tree2, 40);
        insert_node(&tree2, 50);
        insert_node(&tree2, 60);
        insert_node(&tree2, 70);
        insert_node(&tree2, 80);
        insert_node(&tree2, 90);
        insert_node(&tree2, 30);
        insert_node(&tree2, 45);
        insert_node(&tree2, 20);
        insert_node(&tree2, 15);
        insert_node(&tree2, 16);
        insert_node(&tree2, 17);
        insert_node(&tree2, 18);
        insert_node(&tree2, 33);



    }

};
TEST(cases, line_right_uncle){
    tree tree1;
    tree1.root = nullptr;
    insert_node(&tree1, 15);
    insert_node(&tree1, 5);
    insert_node(&tree1, 1);

    ASSERT_EQ(tree1.root->value, 5);
    ASSERT_EQ(tree1.root->left_child->value, 1);
    ASSERT_EQ(tree1.root->right_child->value, 15);


    //colors
    ASSERT_EQ(tree1.root->color, 2);
    ASSERT_EQ(tree1.root->left_child->color, 1);
    ASSERT_EQ(tree1.root->right_child->color, 1);
    cout << "line_right_uncle: PASSED" << endl;
}


// case 2 is black(triangle), case 3 black(line)
TEST_F(basic_test, case_2_3_values){
    cout << "Testing case 3 and 2 rotation around root" << endl;
    cout <<"............................................" << endl;

    ASSERT_EQ(tree1.root->left_child->value, 5);
    ASSERT_EQ(tree1.root->right_child->value, 15);

    ASSERT_EQ(tree1.root->right_child->right_child->value, 40);
    ASSERT_EQ(tree1.root->right_child->left_child->value, 13);

    ASSERT_EQ(tree1.root->left_child->left_child->value, 1);
    ASSERT_EQ(tree1.root->left_child->right_child->value, 9);

}

TEST_F(basic_test, case_2_3_color){
    cout << "Testing colors" << endl;
    cout <<"............................................" << endl;

    ASSERT_EQ(tree1.root->color, 2);
    ASSERT_EQ(tree1.root->left_child->color, 1);
    ASSERT_EQ(tree1.root->right_child->color, 1);

    ASSERT_EQ(tree1.root->right_child->right_child->color, 2);
    ASSERT_EQ(tree1.root->right_child->left_child->color, 2);

    ASSERT_EQ(tree1.root->left_child->left_child->color, 2);
    ASSERT_EQ(tree1.root->left_child->right_child->color, 2);

}

TEST_F(basic_test, case_2_3_null){
    cout << "Testing null values" << endl;
    cout <<"............................................" << endl;

    ASSERT_EQ(tree1.root->parent, nullptr);


    ASSERT_EQ(tree1.root->right_child->right_child->color, 2);

    ASSERT_EQ(tree1.root->right_child->left_child->right_child, nullptr);
    ASSERT_EQ(tree1.root->right_child->left_child->left_child, nullptr);

    ASSERT_EQ(tree1.root->left_child->right_child->right_child->left_child, nullptr);
    ASSERT_EQ(tree1.root->left_child->right_child->right_child->right_child, nullptr);

}

TEST_F(complex_tree, testing_values){
    cout << "Testing values in complex tree" << endl;
    cout <<"............................................" << endl;

    ASSERT_EQ(tree2.root->value, 50);
    ASSERT_EQ(tree2.root->right_child->value, 70);
    ASSERT_EQ(tree2.root->right_child->right_child->value, 80);
    ASSERT_EQ(tree2.root->right_child->right_child->right_child->value, 90);

    ASSERT_EQ(tree2.root->left_child->value, 20);
    ASSERT_EQ(tree2.root->left_child->left_child->value, 16);
    ASSERT_EQ(tree2.root->left_child->left_child->left_child->value, 15);
    ASSERT_EQ(tree2.root->left_child->right_child->value, 40);

    ASSERT_EQ(tree2.root->left_child->right_child->right_child->value, 45);
    ASSERT_EQ(tree2.root->left_child->right_child->left_child->value, 30);
    ASSERT_EQ(tree2.root->left_child->right_child->left_child->right_child->value, 33);

}

int run_tests(int argc,char **argv){

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}