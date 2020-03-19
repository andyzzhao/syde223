#ifndef LAB3_TESTS_HPP
#define LAB3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include <algorithm>
#include <sstream>
#include <queue>

#include "lab3_priority_queue.hpp"
#include "lab3_binary_search_tree.hpp"

class PriorityQueueTest {
public:
	// PURPOSE: Tests if the new queue is valid
	bool test1() {
		PriorityQueue q(5);
		ASSERT_TRUE( q.empty() );
		ASSERT_TRUE( !q.full() );
		ASSERT_TRUE( q.get_size() == 0 );
		return true;
	}

	// PURPOSE: Tests enqueue of one item and then dequeue of that item
	bool test2() {
		PriorityQueue q(5);
		ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(7, "Test")) );
		ASSERT_TRUE( q.dequeue() );

		ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(-4, "Test Again")) );
		ASSERT_TRUE( q.dequeue());

		return true;
	}

	// PURPOSE: Tests enqueue too many
	bool test3() {
		PriorityQueue q(2);
		ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(7, "Test")) );
		ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(2, "Test2")) );
		ASSERT_FALSE( q.enqueue(PriorityQueue::TaskItem(3, "Test3")) );
		return true;
	}
  
	// PURPOSE: Tests enqueue too many then dequeue too many
	bool test4() {
		PriorityQueue q(2);
		ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(3, "Test")) );
		ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(9, "Test")) );
		ASSERT_FALSE( q.enqueue(PriorityQueue::TaskItem(-1, "Test")) );
		
		ASSERT_TRUE( q.dequeue() );
		ASSERT_TRUE( q.dequeue() );
		ASSERT_FALSE( q.dequeue() );
		
		return true;
	}
};

class BinarySearchTreeTest {
public:
	bool insert_nodes(BinarySearchTree &tree, int *in, int nin) {
		for(int i = 0; i < nin; i++) {
			ASSERT_TRUE(tree.insert(BinarySearchTree::TaskItem(in[i],"Test Task")));
		}
		return true;
	}

	// PURPOSE: Traverse the tree using breadth-first traversal
	// Output is as follows: "val1 val2 ... valN"
	std::string level_order(BinarySearchTree::TaskItem* root) {
		if (!root) {
      		return "";
    	}    

		std::stringstream ss;
		std::queue<BinarySearchTree::TaskItem*> node_queue;
		node_queue.push(root);
		while (!node_queue.empty()) {
			BinarySearchTree::TaskItem* cur_node = node_queue.front();
			node_queue.pop();
			ss << cur_node->priority << " ";
			if (cur_node->left) {
				node_queue.push(cur_node->left);
			}
			if (cur_node->right) {
				node_queue.push(cur_node->right);
			}
		}
    
		std::string level_order_str = ss.str();

		return level_order_str.substr(0, level_order_str.size() - 1);
	}

	// PURPOSE: Tests if the new tree is valid
	bool test1() {
		std::string expected_tree_level_order = "";
    
		BinarySearchTree bst;
		ASSERT_TRUE(bst.root == NULL);
		ASSERT_TRUE(bst.size == 0 && bst.get_size() == 0);
    
		// compare the tree's representation to the expected tree
		std::string tree_level_order = level_order(bst.root);
		ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
		return true;
	}

	// PURPOSE: Tests a tree with one node
	bool test2() {
		return false;
	}

	// PURPOSE: Tests insert, remove, and size on linear list formation with three elements
	bool test3() {
		return false;
	}

	// PURPOSE: Tests removal of a node with one child
	bool test4() {
		return false;
	}

	// PURPOSE: Tests insert of multiple elements and remove till nothing remains
	bool test5() {
		return false;
	}
 
	// PURPOSE: Tests removal of root node when both children of root have two children
	bool test6() {
		return false;
	}

	// PURPOSE: Tests depth with many inserts and some removes
	bool test7() {
		return false;
	}

	// PURPOSE: Tests lots of inserts and removes
	bool test8() {
		return false;
	}
};
#endif
