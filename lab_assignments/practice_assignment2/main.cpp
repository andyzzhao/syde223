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
    max2 = (max1, left_sum + right_sum + T->get_value());

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


int main() {
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

    // Call functions
    // find_and_print_sum_of_nodes(node1, 11, 0, "");
    int globalMax = INT_MIN;
    find_max_sum_of_nodes(node1, globalMax);
    cout << globalMax << endl;
}