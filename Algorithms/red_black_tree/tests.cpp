#include <bits/stdc++.h>

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "tests.h"


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

    //void TearDown() { delete_tree(tree1.root);}
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

struct complex_tree_first_half : public testing::Test {
    tree tree3;

    void SetUp() {
        tree3.root = nullptr;
        insert_node(&tree3, 40);
        insert_node(&tree3, 50);
        insert_node(&tree3, 60);
        insert_node(&tree3, 70);
        insert_node(&tree3, 80);
        insert_node(&tree3, 90);
        insert_node(&tree3, 30);
        insert_node(&tree3, 45);
        insert_node(&tree3, 20);
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

    delete_tree(tree1.root);
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

    delete_tree(tree1.root);
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

    delete_tree(tree1.root);

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

    delete_tree(tree1.root);
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

    delete_tree(tree2.root);
}

TEST_F(complex_tree_first_half, beginning_right_part_tree){
    cout << "Testing values in beginning_right_part_tree" << endl;
    cout <<"............................................" << endl;

    ASSERT_EQ(tree3.root->value, 50);
    ASSERT_EQ(tree3.root->right_child->value, 70);
    ASSERT_EQ(tree3.root->right_child->right_child->value, 80);
    ASSERT_EQ(tree3.root->right_child->left_child->value, 60);

    ASSERT_EQ(tree3.root->color, 2);
    ASSERT_EQ(tree3.root->right_child->color, 1);
    ASSERT_EQ(tree3.root->right_child->right_child->color, 2);
    ASSERT_EQ(tree3.root->right_child->left_child->color, 2);

    delete_tree(tree3.root);
}

TEST_F(complex_tree_first_half, beginning_left_part_tree){
    cout << "Testing values in beginning_left_part_tree" << endl;
    cout <<"............................................" << endl;

    ASSERT_EQ(tree3.root->value, 50);
    ASSERT_EQ(tree3.root->left_child->value, 40);
    ASSERT_EQ(tree3.root->left_child->left_child->value, 30);
    ASSERT_EQ(tree3.root->left_child->right_child->value, 45);
    ASSERT_EQ(tree3.root->left_child->left_child->left_child->value, 20);


    ASSERT_EQ(tree3.root->value, 50);
    ASSERT_EQ(tree3.root->left_child->color, 1);
    ASSERT_EQ(tree3.root->left_child->left_child->color, 2);
    ASSERT_EQ(tree3.root->left_child->right_child->color, 2);
    ASSERT_EQ(tree3.root->left_child->left_child->left_child->color, 1);

    delete_tree(tree3.root);
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////////////deletion/////////////////////////////////////////////////

TEST_F(basic_test, deletion_basic_values1){
    cout << "Testing basic deletion values1" << endl;
    cout <<"............................................" << endl;

    main_deletion_switcher( &tree1, 9);

    ASSERT_EQ(tree1.root->left_child->value, 5);
    ASSERT_EQ(tree1.root->left_child->right_child->value, 10);
    ASSERT_EQ(tree1.root->left_child->right_child->left_child, nullptr);
    ASSERT_EQ(tree1.root->left_child->right_child->right_child, nullptr);

    delete_tree(tree1.root);
}

TEST_F(basic_test, deletion_basic_case4_right_double_black){
    cout << "Testing deletion case 4 right double black" << endl;
    cout <<"............................................" << endl;
    main_deletion_switcher( &tree1, 9);
    main_deletion_switcher( &tree1, 10);

    ASSERT_EQ(tree1.root->left_child->value, 5);
    ASSERT_EQ(tree1.root->left_child->left_child->value, 1);

    ASSERT_EQ(tree1.root->left_child->right_child, nullptr);
    ASSERT_EQ(tree1.root->left_child->left_child->left_child, nullptr);
    ASSERT_EQ(tree1.root->left_child->left_child->right_child, nullptr);
    // colors
    ASSERT_EQ(tree1.root->left_child->color, 2);
    ASSERT_EQ(tree1.root->left_child->left_child->color, 1);

    delete_tree(tree1.root);
}

TEST_F(basic_test, deletion_case5_case6){
    cout << "Testing deletion case5_case6" << endl;
    cout <<"............................................" << endl;
    main_deletion_switcher( &tree1, 9);
    main_deletion_switcher( &tree1, 10);
    main_deletion_switcher( &tree1, 13);

    ASSERT_EQ(tree1.root->right_child->value, 23);
    ASSERT_EQ(tree1.root->right_child->left_child->value, 15);
    ASSERT_EQ(tree1.root->right_child->right_child->value, 40);

    ASSERT_EQ(tree1.root->right_child->right_child->parent->value, 23);

    delete_tree(tree1.root);
}

TEST_F(basic_test, deletion_case4_right){
    cout << "Testing deletion case4_right" << endl;
    cout <<"............................................" << endl;
    main_deletion_switcher( &tree1, 9);
    main_deletion_switcher( &tree1, 10);
    main_deletion_switcher( &tree1, 13);
    main_deletion_switcher( &tree1, 40);

    ASSERT_EQ(tree1.root->right_child->value, 23);
    ASSERT_EQ(tree1.root->right_child->left_child->value, 15);
    ASSERT_EQ(tree1.root->right_child->right_child, nullptr);

    delete_tree(tree1.root);
}


TEST_F(basic_test, deletion_whole_tree){
    cout << "Testing deletion_whole_tree" << endl;
    cout <<"............................................" << endl;
    main_deletion_switcher( &tree1, 9);
    main_deletion_switcher( &tree1, 10);
    main_deletion_switcher( &tree1, 13);
    main_deletion_switcher( &tree1, 40);
    main_deletion_switcher( &tree1, 12);
    main_deletion_switcher( &tree1, 5);
    main_deletion_switcher( &tree1, 1);
    main_deletion_switcher( &tree1, 23);
    main_deletion_switcher( &tree1, 15);

    ASSERT_EQ(tree1.root, nullptr);

}


TEST_F(complex_tree, deletion_case_6_left_double_black){
    cout << "Testing deletion case_6_left_double_black" << endl;
    cout <<"............................................" << endl;

    main_deletion_switcher(&tree2, 15);
    ASSERT_EQ(tree2.root->left_child->value, 20);
    ASSERT_EQ(tree2.root->left_child->left_child->value, 17);

    ASSERT_EQ(tree2.root->left_child->left_child->right_child->value, 18);
    ASSERT_EQ(tree2.root->left_child->left_child->left_child->value, 16);

    ASSERT_EQ(tree2.root->left_child->left_child->right_child->left_child, nullptr);
    ASSERT_EQ(tree2.root->left_child->left_child->right_child->right_child, nullptr);

    ASSERT_EQ(tree2.root->left_child->left_child->left_child->left_child, nullptr);
    ASSERT_EQ(tree2.root->left_child->left_child->left_child->right_child, nullptr);

    delete_tree(tree2.root);
}



TEST_F(complex_tree, deletion_case_4_left_double_black){
    cout << "Testing deletion case_4_left_double_black" << endl;
    cout <<"............................................" << endl;

    main_deletion_switcher(&tree2, 15);
    main_deletion_switcher(&tree2, 16);
    ASSERT_EQ(tree2.root->left_child->value, 20);
    ASSERT_EQ(tree2.root->left_child->left_child->value, 17);

    ASSERT_EQ(tree2.root->left_child->left_child->right_child->value, 18);
    ASSERT_EQ(tree2.root->left_child->left_child->left_child, nullptr);
    // colors
    ASSERT_EQ(tree2.root->left_child->left_child->right_child->color, 1);
    ASSERT_EQ(tree2.root->left_child->left_child->color, 2);

    delete_tree(tree2.root);
}

TEST_F(complex_tree, deletion_case_6_right_double_black){
    cout << "Testing deletion case_6_right_double_black" << endl;
    cout <<"............................................" << endl;

    main_deletion_switcher(&tree2, 15);
    main_deletion_switcher(&tree2, 16);
    main_deletion_switcher(&tree2, 45);
    //print_rb_tree("", tree2.root, false);
    ASSERT_EQ(tree2.root->left_child->value, 20);
    ASSERT_EQ(tree2.root->left_child->left_child->value, 17);

    ASSERT_EQ(tree2.root->left_child->right_child->value, 33);
    ASSERT_EQ(tree2.root->left_child->right_child->right_child->value, 40);
    ASSERT_EQ(tree2.root->left_child->right_child->left_child->value, 30);

    ASSERT_EQ(tree2.root->left_child->right_child->right_child->right_child, nullptr);
    ASSERT_EQ(tree2.root->left_child->right_child->left_child->left_child, nullptr);
    ASSERT_EQ(tree2.root->left_child->right_child->left_child->right_child, nullptr);

    ASSERT_EQ(tree2.root->left_child->right_child->left_child->color, 2);
    ASSERT_EQ(tree2.root->left_child->right_child->color, 1);
    ASSERT_EQ(tree2.root->left_child->right_child->right_child->color, 2);

    delete_tree(tree2.root);
}

TEST_F(complex_tree, deletion_case_5_right_double_black_case_6){
    cout << "Testing deletion case_5_right_double_black_case_6" << endl;
    cout <<"............................................" << endl;

    main_deletion_switcher(&tree2, 15);
    main_deletion_switcher(&tree2, 16);
    main_deletion_switcher(&tree2, 45);
    main_deletion_switcher(&tree2, 30);
    main_deletion_switcher(&tree2, 40);
    main_deletion_switcher(&tree2, 33);

    ASSERT_EQ(tree2.root->left_child->value, 18);
    ASSERT_EQ(tree2.root->left_child->left_child->value, 17);
    ASSERT_EQ(tree2.root->left_child->right_child->value, 20);

    ASSERT_EQ(tree2.root->left_child->color, 2);
    ASSERT_EQ(tree2.root->left_child->left_child->color, 2);
    ASSERT_EQ(tree2.root->left_child->right_child->color, 2);

    delete_tree(tree2.root);
}


TEST_F(complex_tree, deletion_case_3_left_double_3_case_root){
    cout << "Testing deletion case_3_left_double and next 3 case root" << endl;
    cout <<"............................................" << endl;

    main_deletion_switcher(&tree2, 15);
    main_deletion_switcher(&tree2, 16);
    main_deletion_switcher(&tree2, 45);
    main_deletion_switcher(&tree2, 30);
    main_deletion_switcher(&tree2, 40);
    main_deletion_switcher(&tree2, 33);
    main_deletion_switcher(&tree2, 17);
    //print_rb_tree("", tree2.root, false);
    ASSERT_EQ(tree2.root->left_child->value, 18);
    ASSERT_EQ(tree2.root->left_child->right_child->value, 20);
    ASSERT_EQ(tree2.root->value, 50);
    ASSERT_EQ(tree2.root->right_child->value, 70);

    ASSERT_EQ(tree2.root->left_child->left_child, nullptr);

    //colors
    ASSERT_EQ(tree2.root->left_child->color, 2);
    ASSERT_EQ(tree2.root->left_child->right_child->color, 1);
    ASSERT_EQ(tree2.root->color, 2);
    ASSERT_EQ(tree2.root->right_child->color, 1);

    delete_tree(tree2.root);
}

TEST_F(complex_tree, deletion_case_2_left_double_case4){
    cout << "Testing deletion case_2_left_double  folowing case 4" << endl;
    cout <<"............................................" << endl;

    main_deletion_switcher(&tree2, 15);
    main_deletion_switcher(&tree2, 16);
    main_deletion_switcher(&tree2, 45);
    main_deletion_switcher(&tree2, 30);
    main_deletion_switcher(&tree2, 40);
    main_deletion_switcher(&tree2, 33);
    main_deletion_switcher(&tree2, 17);
    main_deletion_switcher(&tree2, 20);
    main_deletion_switcher(&tree2, 18);


    ASSERT_EQ(tree2.root->value, 70);
    ASSERT_EQ(tree2.root->left_child->value, 50);
    ASSERT_EQ(tree2.root->left_child->right_child->value, 60);

    ASSERT_EQ(tree2.root->right_child->value, 80);
    ASSERT_EQ(tree2.root->right_child->right_child->value, 90);

    ASSERT_EQ(tree2.root->color, 2);
    ASSERT_EQ(tree2.root->left_child->color, 2);
    ASSERT_EQ(tree2.root->left_child->right_child->color, 1);

    ASSERT_EQ(tree2.root->right_child->color, 2);
    ASSERT_EQ(tree2.root->right_child->right_child->color, 1);

    delete_tree(tree2.root);
}


int run_tests(int argc,char **argv){

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}