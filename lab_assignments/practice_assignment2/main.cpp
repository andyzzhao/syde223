// Jeffrey Ng (20762964)
// Andy Zhao (20785698)

#include <iostream>
#include <binary_tree_declaration.hpp>

using namespace std;

void find_and_print_sum_of_nodes (BinaryTreeNode * T, int desired_sum, int cur_sum, string buffer) {

    //exit if T is NULL
    if (!T) return;

    // update the ongoing sum with the current value for T
    int new_sum = cur_sum + T->get_value();

    // update the current path string
    string new_buffer = buffer + " " + int2ascii(T->get_value());

    // if the desired sum is found, print the corresponding path
    if (new_sum == desired_sum) 
        cout << new_buffer << endl;

    // TODO: continue down the left subtree

    // TODO: continue down the right subtree

    // TODO: restart from the left subtree if buffer=""

    // TODO: restart from the right subtree if buffer=""
}

int find_max_sum_of_nodes (BinaryTreeNode* T, int &temp_max_sum) {
    // exit if T is NULL
    if (!T) return 0;

    // derive the maximum sum for the left subtree
    int left_sum = find_max_sum_of_nodes(T->get_left(), temp_max_sum);

    // derive the maximum sum for the right subtree
    int right_sum = find_max_sum_of_nodes(T->get_right(), temp_max_sum);

    // TODO: compare T->value, left_sum + T->value, and right_sum + T->value; store as max1
    
    // TODO: compare max1, left_sum + right_sum + T->value; store as max2

    // TODO: update temp_max_sum with the new max

    // TODO: return max1
}

int find_max_sum_of_nodes(BinaryTreeNode *T) {
    int temp_max_sum = INT_MIN;

    find_max_sum_of_nodes(T, temp_max_sum);

    return temp_max_sum;
}


int main() {

}