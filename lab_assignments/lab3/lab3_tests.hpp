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
		std::string expected_tree_level_order = "10";

		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(10, "A new node")));
		ASSERT_TRUE(bst.size == 1 && bst.get_size() == 1);

		std::string tree_level_order = level_order(bst.root);
		ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)

		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(10, "A new node")));

		return true;
	}

	// PURPOSE: Tests insert, remove, and size on linear list formation with three elements
	bool test3() {
		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(10, "A new node")));
		ASSERT_TRUE(bst.size == 1 && bst.get_size() == 1);
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(18, "A new node")));
		ASSERT_TRUE(bst.size == 2 && bst.get_size() == 2);
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(17, "A new node")));
		ASSERT_TRUE(bst.size == 3 && bst.get_size() == 3);

		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(10, "A new node")));
		ASSERT_TRUE(bst.size == 2 && bst.get_size() == 2);
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(18, "A new node")));
		ASSERT_TRUE(bst.size == 1 && bst.get_size() == 1);
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(17, "A new node")));
		ASSERT_TRUE(bst.size == 0 && bst.get_size() == 0);

		return true;
	}

	// PURPOSE: Tests removal of a node with one child
	bool test4() {
		BinarySearchTree bst;		
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(10, "A new node")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(12, "A new node")));
		ASSERT_TRUE(bst.size == 2 && bst.get_size() == 2);
		
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(10, "A new node")));
		ASSERT_TRUE(bst.size == 1 && bst.get_size() == 1);

		return true;
	}

	// PURPOSE: Tests insert of multiple elements and remove till nothing remains
	bool test5() {		
		BinarySearchTree bst;	
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(5, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(2, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(12, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(-4, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(3, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(9, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(21, "yeet")));
		
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(12, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(-4, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(3, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(5, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(2, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(9, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(21, "yeet")));
		
		ASSERT_TRUE(bst.get_size() == 0);
		
		return true;
	}
		
	// PURPOSE: Tests removal of root node when both children of root have two children
	bool test6() {
		BinarySearchTree bst;	
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(2, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(12, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(-4, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(3, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(9, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(21, "yeet")));

		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(2, "yeet")));
		return true;
	}

	// PURPOSE: Tests depth with many inserts and some removes
	bool test7() {
		BinarySearchTree bst;
		BinarySearchTree::TaskItem new_node1 = BinarySearchTree::TaskItem(5, "yeet");
		BinarySearchTree::TaskItem* new_node1_ptr = &new_node1;
		
		BinarySearchTree::TaskItem new_node2 = BinarySearchTree::TaskItem(-4, "yeet");
		BinarySearchTree::TaskItem* new_node2_ptr = &new_node2;
	
		BinarySearchTree::TaskItem new_node3 = BinarySearchTree::TaskItem(3, "yeet");
		BinarySearchTree::TaskItem* new_node3_ptr = &new_node3;
		
		BinarySearchTree::TaskItem new_node4 = BinarySearchTree::TaskItem(2, "yeet");
		BinarySearchTree::TaskItem* new_node4_ptr = &new_node4;
		
		BinarySearchTree::TaskItem new_node5 = BinarySearchTree::TaskItem(19, "yeet");
		BinarySearchTree::TaskItem* new_node5_ptr = &new_node5;

		ASSERT_TRUE(bst.insert(new_node1));
		ASSERT_TRUE(bst.insert(new_node4));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(12, "yeet")));
		ASSERT_TRUE(bst.insert(new_node2));
		ASSERT_TRUE(bst.insert(new_node3));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(9, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(21, "yeet")));
		ASSERT_TRUE(bst.insert(new_node5));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(25, "yeet")));

		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(12, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(21, "yeet")));

		ASSERT_TRUE(bst.get_node_depth(new_node1_ptr) == 1);
		ASSERT_TRUE(bst.get_node_depth(new_node2_ptr) == bst.get_node_depth(new_node3_ptr));
		ASSERT_TRUE(bst.get_node_depth(new_node4_ptr) == bst.get_node_depth(new_node5_ptr));
		
		return true;
	}

	// PURPOSE: Tests lots of inserts and removes
	bool test8() {
		cout << endl;
		cout << endl;
		cout << "TEST 8 STARTS HERE" << endl;
		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(20, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(11, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(3, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(-3, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(32, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(0, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(-21, "yeet")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(200, "yeet")));

		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(20, "yeet")));
		//bst.print();
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(11, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(3, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(-3, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(32, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(0, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(-21, "yeet")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(200, "yeet" )));

		ASSERT_TRUE(bst.get_size() == 0);

		return true;
	}
};
#endif