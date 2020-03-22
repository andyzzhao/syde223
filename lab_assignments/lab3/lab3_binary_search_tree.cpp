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
	bool found = false;
	TaskItem* temp_node;;
	TaskItem* curr_node = root;
	TaskItem* prev_node = NULL;

	// If tree is empty
	if(root==NULL){
		return false;
	}

	// If tree only has one node
	if(*root==val && root->right==NULL && root->left==NULL){
		delete root;
		root = NULL;
		size--;
		return true;
	}
	// if tree is only three nodes
	if(*root==val && root->right && root->left){
		TaskItem* left_node = root->left;
		TaskItem* right_node = root->right;
		delete root;
		root = right_node;

		size--;
		return true;
	}

	while(!found){
		if(*curr_node == val){
			// Found node to be removed
			if(curr_node->right==NULL && curr_node->left==NULL) {
				// Case 1: leaf node
				if(prev_node->priority > curr_node->priority){
					// curr_node is a left node
					delete prev_node->left;
					prev_node->left = NULL;
				}
				else if(prev_node->priority < curr_node->priority){
					// curr_node is a right node
					delete prev_node->right;
					prev_node->right = NULL;
				}
				size--;
				return true;
			}
			else if(curr_node->right!=NULL && curr_node->left!=NULL){
				// Case 2: Node has two children
				// Find min node in right tree
				TaskItem* right_min_node = curr_node->right;
				TaskItem* prev_right_min_node = curr_node;
				while(right_min_node->left != NULL){
					prev_right_min_node = prev_right_min_node->left;
					right_min_node = right_min_node->left;
				}
				if(prev_node->priority > curr_node->priority){
					// curr_node is a left node
					delete prev_node->left;
					prev_node->left = right_min_node;
				}
				else if(prev_node->priority < curr_node->priority){
					// curr_node is a right node
					delete prev_node->right;
					prev_node->right = right_min_node;
				}
				delete prev_right_min_node->left;
				prev_right_min_node->left = NULL;
				size--;
				return true;

			}
			else if(curr_node->right!=NULL || curr_node->left!=NULL){
				// Case 3: Node has only one child
				if(prev_node->priority > curr_node->priority){
					// curr_node is a left node
					delete prev_node->left;
					if(curr_node->right){
						// curr_node has a right child
						prev_node->left = curr_node->right;
					}
					else if(curr_node->left){
						// curr_node has a left child
						prev_node->left = curr_node->left;
					}
					size--;
					return true;
				}
				else if(prev_node->priority < curr_node->priority){
					// curr_node is a right node
					delete prev_node->right;
					if(curr_node->right){
						// curr_node has a right child
						prev_node->right = curr_node->right;
					}
					else if(curr_node->left){
						// curr_node has a left child
						prev_node->right = curr_node->left;
					}
					size--;
					return true;
				}
			}
		}

		cout << "MOVE TO NEXT NODE" << endl;
		// move on to next node
		prev_node = curr_node;
		if(val.priority > curr_node->priority){
			cout << "MOVE RIGHT" << endl;
			curr_node = curr_node->right;
		}else if(val.priority < curr_node->priority){
			cout << "MOVE LEFT" << endl;
			curr_node = curr_node->left;
		} // reached a leaf node
		else if(!(val == *curr_node) && curr_node->right==NULL && curr_node->left==NULL){
			break;
		}
	}
    return false;
}
