#include "binary_tree_declaration.hpp"

BinaryTreeNode::BinaryTreeNode() {};

BinaryTreeNode::BinaryTreeNode(int new_value) {
    value = new_value;
};

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

void BinaryTreeNode::set_left(BinaryTreeNode* target) {
    left = target;
}

void BinaryTreeNode::set_right(BinaryTreeNode* target) {
    right = target;
}
