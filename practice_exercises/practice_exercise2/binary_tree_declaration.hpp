#ifndef BINARY_TREE_DECLARATION_HPP
#define BINARY_TREE_DECLARATION_HPP

class BinaryTreeNode {
    int value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

public:
    BinaryTreeNode();
    BinaryTreeNode(int new_value);
    ~BinaryTreeNode();

    BinaryTreeNode* get_left(); 
    BinaryTreeNode* get_right();

    void set_left(BinaryTreeNode* target); 
    void set_right(BinaryTreeNode* target);

    int get_value();
    friend void delete_tree(BinaryTreeNode* node);

};
#endif