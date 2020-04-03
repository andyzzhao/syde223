#include "binary_tree_declaration.hpp"

BinaryTreeNode::BinaryTreeNode() {};

BinaryTreeNode::~BinaryTreeNode() {};

BinaryTreeNode* BinaryTreeNode::get_left() {
    return left;
}

BinaryTreeNode* BinaryTreeNode::get_right() {
    return right;
}

int BinaryTreeNode::get_value() {
    return value;
}

