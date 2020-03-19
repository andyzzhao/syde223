#include <iostream>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	delete root;
	root = NULL;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if (size == 0) {
		return BinarySearchTree::TaskItem(-1, "N/A");
	}

	TaskItem* curr_node = root;

	while (curr_node->right != NULL) {
		curr_node = curr_node->right;
	}

	return *curr_node;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if (size == 0) {
		return BinarySearchTree::TaskItem(-1, "N/A");
	}

	TaskItem* curr_node = root;

	while (curr_node->left != NULL) {
		curr_node = curr_node->left;
	}

	return *curr_node;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	if (size == 0) {
		return 0;
	}
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	return 0;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
	if (size == 0) {
		TaskItem* new_root = new TaskItem(val);
		root = new_root;
		size++;
		return true;
	} else {

		TaskItem* curr_node;
		TaskItem* prev_node;
		int val_priority = val.priority;
		curr_node = root;

		while (curr_node != NULL) {
			prev_node = curr_node;
			if (val_priority == curr_node->priority) {
				return false;
			}
			
			if (val_priority > curr_node->priority) {
				curr_node = curr_node->right;
			} else {
				curr_node = curr_node->left;
			}
		}

		curr_node = new TaskItem(val);

		if (prev_node->priority > curr_node->priority) {
			prev_node->left = curr_node;
		} else {
			prev_node->right = curr_node;
		}
		size++;
	}

    return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
	TaskItem* cur_root = root; 
	// if empty tree
	if(root == NULL){
		return false;
	}

	for(int i = 0; i < size; i++){
		// found the node to be removed 
		if(cur_root->right->priority == val.priority){
			// if the node has no children
			if(cur_root->left == NULL && cur_root->right == NULL){
				
			}
		}

		// move on to next node
		if(val.priority > cur_root->priority){
			cur_root = cur_root->right;
		}else if(val.priority < cur_root->priority){
			cur_root = cur_root->left;
		}
		// reached the leaf node
		if(cur_root == NULL){
			return false;
		}
	}
    return false;
}
