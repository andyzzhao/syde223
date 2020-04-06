// Jeffrey Ng (20762964)
// Andy Zhao (20785698)

#include <iostream>
#include <string>
#include "binary_tree_declaration.hpp"

using namespace std;

void find_and_print_sum_of_nodes (BinaryTreeNode * T, int desired_sum, int cur_sum, string buffer) {

    //exit if T is NULL
    if (!T) return;

    // update the ongoing sum with the current value for T
    int new_sum = cur_sum + T->get_value();

    // update the current path string
    string new_buffer = buffer + " " + to_string(T->get_value());

    // cout << "Test: " << new_buffer << endl;

    // if the desired sum is found, print the corresponding path
    if (new_sum == desired_sum) 
        cout << new_buffer << endl;

    // TODO: continue down the left subtree
    find_and_print_sum_of_nodes (T->get_left(), desired_sum, new_sum, new_buffer);

    // TODO: continue down the right subtree
    find_and_print_sum_of_nodes (T->get_right(), desired_sum, new_sum, new_buffer);

    // TODO: restart from the left subtree if buffer=""
    if (buffer=="") {
        find_and_print_sum_of_nodes (T->get_left(), desired_sum, 0, "");
    }

    // TODO: restart from the right subtree if buffer=""
    if (buffer=="") {
        find_and_print_sum_of_nodes (T->get_right(), desired_sum, 0, "");
    }
}

int find_max_sum_of_nodes (BinaryTreeNode* T, int &temp_max_sum) {
    // exit if T is NULL
    if (!T) return 0;

    // derive the maximum sum for the left subtree
    int left_sum = find_max_sum_of_nodes(T->get_left(), temp_max_sum);

    // derive the maximum sum for the right subtree
    int right_sum = find_max_sum_of_nodes(T->get_right(), temp_max_sum);

    int max1, max2;
    
    // TODO: compare T->value, left_sum + T->value, and right_sum + T->value; store as max1
    max1 = max(max(T->get_value(), left_sum + T->get_value()), T->get_value() + right_sum);
    
    // TODO: compare max1, left_sum + right_sum + T->value; store as max2
    max2 = max(max1, left_sum + right_sum + T->get_value());

    // TODO: update temp_max_sum with the new max
    if (max2 > temp_max_sum)
        temp_max_sum = max2;

    // TODO: return max1
    return max1;
}

int find_max_sum_of_nodes(BinaryTreeNode *T) {
    int temp_max_sum = INT_MIN;

    find_max_sum_of_nodes(T, temp_max_sum);

    return temp_max_sum;
}

class TreeAlgorithmTests{
public:
    // PURPOSE: test find_and_print_sum_of_nodes
    void test1a(){
        // Declare all nodes
        BinaryTreeNode* node1 = new BinaryTreeNode(5);
        BinaryTreeNode* node2 = new BinaryTreeNode(3);
        BinaryTreeNode* node3 = new BinaryTreeNode(1);
        BinaryTreeNode* node4 = new BinaryTreeNode(-1);
        BinaryTreeNode* node5 = new BinaryTreeNode(8);
        BinaryTreeNode* node6 = new BinaryTreeNode(18);
        BinaryTreeNode* node7 = new BinaryTreeNode(6);
        BinaryTreeNode* node8 = new BinaryTreeNode(11);

        // Set connections between nodes
        node1->set_left(node2);
        node1->set_right(node3);
        node2->set_left(node4);
        node2->set_right(node5);
        node3->set_right(node8);
        node4->set_left(node6);
        node5->set_left(node7);

        find_and_print_sum_of_nodes(node1, 11, 0, "");
        return;
    }
    // PURPOSE: test find_and_print_sum_of_nodes
    void test1b(){
        // Declare all nodes
        BinaryTreeNode* node1 = new BinaryTreeNode(1);
        BinaryTreeNode* node2 = new BinaryTreeNode(3);
        BinaryTreeNode* node3 = new BinaryTreeNode(1);
        BinaryTreeNode* node4 = new BinaryTreeNode(7);
        BinaryTreeNode* node5 = new BinaryTreeNode(8);
        BinaryTreeNode* node6 = new BinaryTreeNode(-1);
        BinaryTreeNode* node7 = new BinaryTreeNode(6);
        BinaryTreeNode* node8 = new BinaryTreeNode(4);

        // Set connections between nodes
        node1->set_left(node2);
        node1->set_right(node3);
        node2->set_left(node4);
        node2->set_right(node5);
        node3->set_right(node8);
        node4->set_left(node6);
        node5->set_left(node7);

        find_and_print_sum_of_nodes(node1, 6, 0, "");
        return;
    }
    // PURPOSE: test find_and_print_sum_of_nodes
    void test1c(){
        // Declare all nodes
        BinaryTreeNode* node1 = new BinaryTreeNode(-3);
        BinaryTreeNode* node2 = new BinaryTreeNode(8);
        BinaryTreeNode* node3 = new BinaryTreeNode(1);
        BinaryTreeNode* node4 = new BinaryTreeNode(4);
        BinaryTreeNode* node5 = new BinaryTreeNode(2);
        BinaryTreeNode* node6 = new BinaryTreeNode(3);
        BinaryTreeNode* node7 = new BinaryTreeNode(7);
        BinaryTreeNode* node8 = new BinaryTreeNode(-1);
        BinaryTreeNode* node9 = new BinaryTreeNode(-5);

        // Set connections between nodes
        node1->set_left(node2);
        node1->set_right(node3);

        node3->set_right(node5);
        node3->set_left(node4);

        node5->set_left(node6);
        node5->set_right(node7);

        node6->set_left(node8);

        node7->set_right(node9);

        // Call functions
        find_and_print_sum_of_nodes(node1, 5, 0, "");
        return;
    }

    // PURPOSE: test find_max_sum_of_nodes
    void test2a(){
        int globalMax = INT_MIN;

        // Declare all nodes
        BinaryTreeNode* node5 = new BinaryTreeNode(-5);
        BinaryTreeNode* node3 = new BinaryTreeNode(3);
        BinaryTreeNode* node10 = new BinaryTreeNode(10);
        BinaryTreeNode* node2 = new BinaryTreeNode(2);
        BinaryTreeNode* node7 = new BinaryTreeNode(7);
        BinaryTreeNode* node1 = new BinaryTreeNode(-1);
        BinaryTreeNode* node8 = new BinaryTreeNode(8);
        
        // Set connections between nodes
        node5->set_right(node10);
        node5->set_left(node3);

        node3->set_left(node2);
        node3->set_right(node7);

        node10->set_right(node8);
        node10->set_left(node1);
        
        find_max_sum_of_nodes(node5, globalMax);
        cout << globalMax << endl;
        return;
    }
    void test2b(){
        int globalMax = INT_MIN;
        // Declare all nodes
        BinaryTreeNode* node8 = new BinaryTreeNode(8);
        BinaryTreeNode* node5 = new BinaryTreeNode(-5);
        BinaryTreeNode* node20 = new BinaryTreeNode(20);
        BinaryTreeNode* node40 = new BinaryTreeNode(40);
        BinaryTreeNode* node50 = new BinaryTreeNode(-50);

        node8->set_left(node5);
        node8->set_right(node50);

        node5->set_left(node20);
        node5->set_right(node40);
        
        find_max_sum_of_nodes(node8, globalMax);
        cout << globalMax << endl;
        return;
    }
    void test2c(){
        int globalMax = INT_MIN;
        // Declare all nodes
        BinaryTreeNode* node20 = new BinaryTreeNode(20);
        BinaryTreeNode* node10 = new BinaryTreeNode(-10);
        BinaryTreeNode* node5 = new BinaryTreeNode(-5);
        
        node20->set_right(node10);
        node20->set_right(node5);

        find_max_sum_of_nodes(node20, globalMax);
        cout << globalMax << endl;

        return;
    }
};

int main() {

    TreeAlgorithmTests tree_tests; 
    // find_and_print_sum_of_nodes tests
    cout << "TEST 1A RESULTS" << endl;
    cout << "EXPECTED: (3,8) (11)" << endl;
    cout << "ACTUAL: " << endl;
    tree_tests.test1a();
    cout << endl;

    cout << "TEST 1B RESULTS" << endl;
    cout << "EXPECTED: (1,1,4) (7,-1) (6)" << endl;
    cout << "ACTUAL: " << endl;
    tree_tests.test1b();
    cout << endl;

    cout << "TEST 1C RESULTS" << endl;
    cout << "EXPECTED: (-3,8) (1,4) (2,3) (1,2,3,-1) (1,2,7,-5)" << endl;
    cout << "ACTUAL: " << endl;
    tree_tests.test1c();
    cout << endl;

    // find_max_sum_of_nodes test
    cout << "TEST 2A RESULTS" << endl;
    cout << "EXPECTED: 24 " << endl;
    cout << "ACTUAL: ";
    tree_tests.test2a();
    cout << endl;

    cout << "TEST 2B RESULTS" << endl;
    cout << "EXPECTED: 55" << endl;
    cout << "ACTUAL: ";
    tree_tests.test2b();
    cout << endl;

    cout << "TEST 2C RESULTS" << endl;
    cout << "EXPECTED: 20" << endl;
    cout << "ACTUAL: ";
    tree_tests.test2c();

    return 0;
}