#include <bits/stdc++.h>
#include "red_black_tree.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "red_black_tree.h"

using namespace std;

struct basic_test : public testing::Test{
    tree tree_basic;

    void SetUp() {
        tree_basic.root = nullptr;
        insert_node(&tree_basic, 10);
        insert_node(&tree_basic, 20);
        insert_node(&tree_basic, 5);
    }

};

TEST_F(basic_test, values1){

    ASSERT_EQ(tree_basic.root->left_child->value, 5);
    ASSERT_EQ(tree_basic.root->right_child->value, 20);
}

int run_tests(int argc,char **argv){

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}