In the case gtest not installed:

https://github.com/google/googletest

for compiling via terminal:
https://gist.github.com/Cartexius/4c437c084d6e388288201aadf9c8cdd5


if using Clion and some problem occurred:
https://stackoverflow.com/questions/33638433/setup-google-test-in-clion

https://www.youtube.com/watch?v=M067vFQG7ZA

Tests are testing logic of insertion and deletion of red black tree.
They do not test memory leaks. If test fails, resources wont be properly free().

Node is always replace with inorder successor

////////////////////////////////////////////////////////////////
Insertion has 3 case all cases have mirror images
for visual explanation https://www.youtube.com/watch?v=5IBxA-bZZH8&t=143s
1. node is red node->parent is red, uncle is red
2. (triangle)node is red node->parent is red, uncle is black, grand_parent is black
grand_parent = node->parent->parent
node value < node->parent->value, grand_parent->value >= node->parent->value,
grand_parent->left_child->value < grand_parent->value

3.  (line) node is red, node->parent is red, uncle is black
grand_parent = node->parent->parent
node->value >= node->parent->value >= grand_parent->value < grand_parent->left_child->value


///////////////////////////////////////////////////////////////////////
Deletion has basic cases
if is leaf and red => just delete
if node(about to delete) is black left child is nullptr and right child is red and leaf
 swap values node->value = right->child->value and delete right child

if node(about to delete) is black and left child is red and leaf and right child is nullptr
same as above

end base cases
/////////
6 case for visualisation 19 min and 58 sec.

https://www.youtube.com/watch?v=CTvfzU_uNKE

case 1,4,6 are terminal and most easy cases do them first

