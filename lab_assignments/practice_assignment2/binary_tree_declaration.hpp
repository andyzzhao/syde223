#ifndef BINARY_TREE_DECLARATION_HPP
#define BINARY_TREE_DECLARATION_HPP

using namespace std;

class BinaryTreeNode {
    int value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

public:
    BinaryTreeNode();
    ~BinaryTreeNode();

    BinaryTreeNode* get_left(); 
    BinaryTreeNode* get_right();

    int get_value();


};
#endif