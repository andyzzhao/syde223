#include "lab3_priority_queue.hpp"

#include <iostream>
using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	capacity = n_capacity; 
	size = 0;
	heap = new TaskItem*[n_capacity + 1];
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
	delete heap; 
	heap = NULL;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	if (size == 0) {
		return true;
	}
	return false;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	if (size == capacity) {
		return true;
	}
	return false;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	if (size > 0) {
		int i = 1;
		TaskItem* temp = heap[1];
		while (i <= size) {
			cout << "Priority: " << temp->priority << endl;
			cout << "Description: " << temp->description << endl; 
			i++;
		}
	}
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	if (heap[1]) {
		return *heap[1];
	} else {
		return TaskItem(-1, "NULL");
	}
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
	if (size == capacity) {
		return false;
	}

	if (size == 0) {
		heap[1] = new TaskItem(val);
	} else {
		int i = size + 1;
		heap[i] = new TaskItem(val);
		while (i > 1 && heap[i/2]->priority < heap[i]->priority) {
			TaskItem* temp = heap[i]; // swap values
			heap[i] = heap[i/2];
			heap[i/2] = temp;
			i /= 2;
		}
	}

	size++;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	if(size > 0){
		if(size == 1){
			heap[1] = NULL;
			size--;
			return true;
		}
		// replace root with end leaf 
		TaskItem* end = heap[size];
		heap[1] = end; 
		heap[size] = NULL; 
		
		// replace root with largest child node and repeat down the tree
		int i = 1; // i - root node
		while (i < size) {
			if (heap[2*i] && heap[2*i+1]) {
				if (heap[2*i]->priority > heap[i]->priority && heap[2*i]->priority > heap[2*i+1]->priority){
					TaskItem* temp = heap[i];
					heap[i] = heap[2*i];
					heap[2*i] = temp;
				} else if (heap[2*i+1]->priority > heap[i]->priority) {
					TaskItem* temp = heap[i];
					heap[i] = heap[2*i+1];
					heap[2*i+1] = temp;
				} else {
					break;
				}
			} else if (heap[2*i]) {
				if (heap[2*i]->priority > heap[i]->priority) {
					TaskItem* temp = heap[i];
					heap[i] = heap[2*i];
					heap[2*i] = temp;
				} else {
					break;
				}
			} else if (heap[2*i+1]) {
				if (heap[2*i+1]->priority > heap[i]->priority) {
					TaskItem* temp = heap[i];
					heap[i] = heap[2*i+1];
					heap[2*i+1] = temp;
				} else {
					break;
				}
			}
			i *= 2;
		}
		size--;
		return true;
	}
	
	return false;
}
