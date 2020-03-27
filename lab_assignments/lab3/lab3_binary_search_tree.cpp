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

bool BinarySearchTree::remove(BinarySearchTree::TaskItem val ) {
	TaskItem* curr_node = root; // pointer to the current node we are evaluating
    TaskItem* parent = NULL; // parent of curr_node

    // EDGE CASES:
	// Case where tree is empty
    if (root == NULL) {
        //cout <<"TREE IS EMPTY" << endl;
        return false;
    }
    // Case where value already exist 
	else if(!exists(val)){
        return false;
    }
    // Case where tree has only one node
    else if (size == 1 && root) {
        //cout <<"TREE ONLY HAS ONE NODE. REMOVING: "<< root->priority << endl;
        delete root;
        root = NULL;
        size--;
        // cout << "SIZE: " << size << endl;
        return true;
    }
    // Case where root node only has one child
    else if (val.priority == root->priority && !(root->left) != !(root->right)) {
        //cout <<"ROOT NODE HAS ONE CHILD. REMOVING: " << curr_node->priority<< endl;
        TaskItem* temp = root;
        if (curr_node->right) {
            root = curr_node->right;
        }
        else if (curr_node->left) {
            root = curr_node->left;
        }
        delete temp;
        temp = NULL;
        size--;
        //cout << "SIZE: " << size << endl;
        return true;
    }

    // Traverse tree
    while (curr_node) {
        // Move to next node
        // Move right
        if (val.priority > curr_node->priority) {
            //cout << "MOVE RIGHT" << endl;
            parent = curr_node;
            curr_node = curr_node->right;
        }
        // Move left
        else if (val.priority < curr_node->priority) {
            //cout << "MOVE LEFT" << endl;
            parent = curr_node;
            curr_node = curr_node->left;
        }
        
        // Reached a NULL node
        if(!(curr_node)){
            break;
        }
        
        // GENERAL CASES:
        // Found node to be removed (curr_node)
        if (val.priority == curr_node->priority) {
            // Case where curr_node has no children
            if (curr_node->left==NULL && curr_node->right==NULL) {
                // cout << curr_node->priority<<" HAS NO CHILDREN" << endl;
                // cout << "PARENT: " << parent << endl;
                if (parent->left == curr_node) {
                    // cout << "REMOVING: " << parent->left->priority << endl;
                    delete parent->left;
                    parent->left = NULL;
                    curr_node = NULL; // curr_node needs to be NULL because it pointed to a dynamically allocated TaskItem that has been deallocated (delete parent->left)
                }
                else if (parent->right == curr_node) {
                    // cout << "REMOVING: " << parent->right->priority << endl;
                    delete parent->right;
                    parent->right = NULL;
                    curr_node = NULL; 
                }
                size--;
                // cout << "SIZE: " << size << endl;
                return true;
            }
            // Case where curr_node has both children
            else if(curr_node->left && curr_node->right){
                TaskItem *min = curr_node->right;
                TaskItem *min_parent = NULL;
                // cout << curr_node->priority<<" HAS BOTH CHILDREN" << endl;
                // EDGE CASE where the right tree of curr_node has no children
                    // replace curr_node with curr_node->right 
                if(min->left == NULL){
                    // cout << "REMOVING: " << curr_node->priority<<" AND REPLACING WITH "<<curr_node->right->priority << endl;
                    // cout << "CURR_NODE RIGHT: " << curr_node->right->priority<<endl;

                    curr_node->priority = curr_node->right->priority;
                    curr_node->description = curr_node->right->description;
                    if(curr_node->right->right){
                       curr_node->right = curr_node->right->right;
                    }
                    else{  
                        delete curr_node->right;
                        curr_node->right = NULL;
                    }
                    size--;
                    return true;
                }
                // GENERAL CASE
                // Find min of curr_node's right tree (i.e. far left leaf node)
                while(min->left != NULL){
                    min_parent = min;
                    min = min->left;
                }
                // cout << "REMOVING: " << curr_node->priority<<" AND REPLACING WITH "<<min->priority << endl;
                curr_node->priority = min->priority;
                curr_node->description = min->description;
                // cout << "CURR_NODE RIGHT: " << curr_node->right->priority<<endl;
                delete min_parent->left;
                min_parent->left = NULL;
                size--;
                // cout << "SIZE: " << size << endl;
                return true;
            }
            // Case where curr_node has one child
            else {
                // curr_node has a left child
                if(curr_node->left){
                    // cout << curr_node->priority<<" HAS ONE LEFT CHILD" << endl;
                    if(curr_node == parent->right){
                        // cout << "REMOVING: " << parent->right->priority<<" AND REPLACING WITH "<<curr_node->left->priority << endl;
                        parent->right = curr_node->left;
                    }
                    else if(curr_node == parent->left){
                        // cout << "REMOVING: " << parent->left->priority<<" AND REPLACING WITH "<<curr_node->left->priority << endl;
                        parent->left = curr_node->left;
                    }
                }
                // curr_node has a right child
                else if(curr_node->right){
                    // cout << curr_node->priority<<" HAS ONE RIGHT CHILD" << endl;
                    if(curr_node == parent->right){
                        // cout << "REMOVING: " << parent->right->priority<<" AND REPLACING WITH "<<curr_node->right->priority << endl;
                        parent->right = curr_node->right;
                    }
                    else if(curr_node == parent->left){
                        // cout << "REMOVING: " << parent->left->priority<<" AND REPLACING WITH "<<curr_node->right->priority << endl;
                        parent->left = curr_node->right;
                    }
                }
                delete curr_node;
                curr_node = NULL;
                size--;
                // cout << "SIZE: " << size << endl;
                return true;
            }
        }
    }

    // loop exited, node not found
    return false;
}
