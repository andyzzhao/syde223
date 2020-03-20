#include <iostream>
#include <stack>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	size = 0;
	root = NULL;
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
	return get_node_depth(root);
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	if (root == NULL) {
		return;
	}

	stack <TaskItem*> s;
	s.push(root);

	while (s.empty() == false) {
		TaskItem* curr_node = s.top();
		cout << "Priority: " << curr_node->priority << endl;
		cout << "Description: " << curr_node->description << endl;
		cout << endl;
		s.pop();

		if (curr_node->right) {
			s.push(curr_node->right);
		}
		
		if (curr_node->left) {
			s.push(curr_node->left);
		}
	}
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	if (size == 0) {
		return false;
	}

	TaskItem* curr_node = root;

	while (curr_node != NULL) {
		if (*curr_node == val) {
			return true;
		}
		
		if (curr_node->priority < val.priority) {
			curr_node = curr_node->right;
		} else {
			curr_node = curr_node->left;
		}
	}

	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return &root;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	if (n == NULL) {
		return 0;
	} else if (n->left == NULL && n->right == NULL) {
		return 1;
	} else {
		int left = get_node_depth(n->left);
		int right = get_node_depth(n->right);
		if (left > right) {
			return 1 + left;
		} else {
			return 1 + right;
		}
	}
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
	TaskItem* right_node = root->right; 
	TaskItem* left_node = root->left; 
	bool found = false;
	// if empty tree
	if(root == NULL){
		return false;
	}

	while(!found){
		if(val == *cur_root){
			delete cur_root;
			cur_root = NULL;
			root = NULL;
			size--;
			return true;
		}
		// found the node to be removed to the right
		if(*right_node == val){
			// If right_node is a leaf node
			if(right_node->right==NULL && right_node->left==NULL){
				delete right_node;
				right_node = NULL;
				cur_root->right = NULL;
				size--;
				return true;
			}// If right_node has one child
			else if(right_node->right==NULL || right_node->left==NULL){
				if(right_node->right==NULL){
					cur_root->right = right_node->left;
					delete right_node;
					size--;
					return true;
				}else if(right_node->left==NULL){
					cur_root->right = right_node->right;
					delete right_node;
					right_node = NULL;
					size--;
					return true;
				}
			}// If right_node has two children 
			else if(right_node->right && right_node->left){
				// find min in right tree 
				TaskItem* min_node = right_node->right;
				TaskItem* before_min_node = right_node->right;
				while (min_node->left->left != NULL) {
					before_min_node = min_node->left;
					min_node = min_node->left->left;
				}
				before_min_node->left = NULL;
				min_node->right = right_node->right;
				min_node->left = right_node->left;
				cur_root->right = min_node;
				delete right_node;
				right_node = NULL;
				size--;
				return true;
			}
			
		}
		// found the node to be removed to the left
		else if(*left_node == val){
			// If left_node is a leaf node
			if(left_node->right==NULL && left_node->left==NULL){
				delete left_node;
				left_node = NULL;
				cur_root->right = NULL;
				size--;
				return true;
			}// If left_node has one child
			else if(left_node->right==NULL || left_node->left==NULL){
				if(left_node->right==NULL){
					cur_root->right = left_node->left;
					delete left_node;
					left_node = NULL;
					size--;
					return true;
				}else if(left_node->left==NULL){
					cur_root->right = left_node->right;
					delete left_node;
					size--;
					return true;
				}
			}// If left_node has two children 
			else if(left_node->right && left_node->left){
				// find min in right tree 
				TaskItem* min_node = left_node->right;
				TaskItem* before_min_node = left_node->right;
				while (min_node->left->left != NULL) {
					before_min_node = min_node->left;
					min_node = min_node->left->left;
				}
				before_min_node->left = NULL;
				min_node->right = left_node->right;
				min_node->left = left_node->left;
				cur_root->right = min_node;
				delete left_node;
				left_node = NULL;
				size--;
				return true;
			}
		}

		// move on to next node
		if(val.priority > cur_root->priority){
			cur_root = cur_root->right;
		}else if(val.priority < cur_root->priority){
			cur_root = cur_root->left;
		}
		right_node = cur_root->right;
		left_node = cur_root->left;

		if(right_node==NULL && left_node==NULL && cur_root->priority!=val.priority){
			break;
		}
	}
    return false;
}
