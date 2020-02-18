#include "lab2_drones_manager.hpp"
#include <iostream>
// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
	first = NULL;
	last = NULL;
	size = 0;
}

DronesManager::~DronesManager() {
	first = nullptr;
	last = nullptr;
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	if (lhs.batteryType == rhs.batteryType && lhs.description == rhs.description && lhs.droneID == rhs.droneID 
		&& lhs.droneType == rhs.droneType && lhs.manufacturer == rhs.manufacturer && lhs.range == rhs.range 
		&& lhs.yearBought == rhs.yearBought) {
		return true;
	}
	return false;
}

unsigned int DronesManager::get_size() const {
	if (size) {
		return size;
	}
	return 0;
}

bool DronesManager::empty() const {
	if (size <= 0) {
		return true;
	}
	return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (get_size() > 0) {
		if (index > get_size() - 1) {
			return *last;
		}

		DroneRecord* node_ptr = first;

		for (int i = 0; i < get_size(); i++) {
			if (i == index) {
				return *node_ptr;
			}
			node_ptr = node_ptr->next;
		}
	}
	return DroneRecord(0);
}

unsigned int DronesManager::search(DroneRecord value) const {
	if (get_size() > 0) {
		DroneRecord* node_ptr = first;

		for (int i = 0; i < get_size(); i++) {
			if (*node_ptr == value) {
				return i;
			}
			if (node_ptr->next == NULL) {
				return i;
			}
			node_ptr = node_ptr->next;
		}
	}

	return 0;
}

void DronesManager::print() const {
	if (get_size() > 0) {
		DroneRecord* node_ptr = first;
		for (int i = 0; i < get_size(); i++) {
			cout << endl;
			cout << "Drone Record No: " << i << endl;
			cout << "Description: " << node_ptr->description << endl;
			cout << "Manufacturer: " << node_ptr->manufacturer << endl;
			cout << "Battery Type: " << node_ptr->batteryType << endl;
			cout << "Drone Type: " << node_ptr->droneType << endl;
			cout << "Drone ID: " << node_ptr->droneID << endl;
			cout << "Range: " << node_ptr->range << endl;
			cout << "Year Bought: " << node_ptr->yearBought << endl;
			node_ptr = node_ptr->next;
		}
	}
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	DroneRecord* node_ptr = new DroneRecord(value);

	if (index == 0) {
		return insert_front(value);
	}
	if (index == get_size()) {
		return insert_back(value);
	}

	// normal case: 
	if (get_size() >= index){
		DroneRecord* curr_ptr = first;

		for (int i = 0; i < get_size(); i++){
			if (i == index) {
				DroneRecord* prev_ptr = curr_ptr->prev;

				curr_ptr->prev = node_ptr;  
				prev_ptr->next = node_ptr;

				node_ptr->next = curr_ptr;
				node_ptr->prev = prev_ptr;
				size++; 
				return true;
			}
			curr_ptr = curr_ptr->next;
		}
	}

	// index does not exist, return false
	return false;
}

bool DronesManager::insert_front(DroneRecord value) {
	DroneRecord *node_ptr = new DroneRecord(value);
	DroneRecord *next_ptr = first;
	if (size == 0) {
		first = node_ptr;
		last = node_ptr;
		node_ptr->prev = NULL;
		node_ptr->next = NULL;
		size++;
		return true;
	}
	
	node_ptr->prev = NULL;
	node_ptr->next = next_ptr;
	next_ptr->prev = node_ptr;
	first = node_ptr;
	size++;

	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	DroneRecord *node_ptr = new DroneRecord(value);
	if (size == 0) {
		first = node_ptr;
		last = node_ptr;
		node_ptr->prev = NULL;
		node_ptr->next = NULL;
		size++;
		return true;
	}

	node_ptr->prev = last;
	node_ptr->next = NULL;
	last->next = node_ptr;
	last = node_ptr;
	size++;

	return true;
}

bool DronesManager::remove(unsigned int index) {
	DroneRecord *curr_ptr = first;
	DroneRecord *prev_ptr = first;
	DroneRecord *next_ptr = first;

	if (size < index || index < 0) {
		return false;
	}

	if (index == 0) {
		return remove_front();
	}

	if (index == size - 1) {
		return remove_back();
	}

	for (int i = 0; i < index; i++) {
		curr_ptr = curr_ptr->next;
	}
	prev_ptr = curr_ptr->prev;
	next_ptr = curr_ptr->next;

	prev_ptr->next = next_ptr;
	next_ptr->prev = prev_ptr;

	curr_ptr->next = NULL;
	curr_ptr->prev = NULL;

	delete curr_ptr;
	curr_ptr = NULL;
	size--;

	return true;
}

bool DronesManager::remove_front() {
	if (first == NULL) {
		return false;
	}
	if (first->next == NULL) {
		first = NULL;
		last = NULL;
		size--;
		return true;
	}

	DroneRecord* node_ptr = first;
	DroneRecord* next_ptr = node_ptr->next;

	first->next = NULL;
	next_ptr->prev = NULL;

	first = next_ptr;

	delete node_ptr;
	node_ptr = NULL;

	size--;

	return true;
}

bool DronesManager::remove_back() {
	if (last == NULL) {
		return false;
	}

	if (last->prev == NULL) {
		first = NULL;
		last = NULL;
		size--;
		return true;
	}

	DroneRecord* node_ptr = last;
	DroneRecord* prev_ptr = node_ptr->prev;

	prev_ptr->next = NULL;
	node_ptr->prev = NULL;

	last = prev_ptr;
	
	delete node_ptr;
	node_ptr = NULL;

	size--;

	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	DroneRecord* new_node_ptr = new DroneRecord(value);
	DroneRecord* replace_node_ptr = first;

	if (first == NULL) {
		return false;
	}
	
	if (index >= size) {
		return false;
	}

	// Get to replace value
	for (int i = 0; i < index; i++) {
		replace_node_ptr = replace_node_ptr->next;
		if (replace_node_ptr == NULL) {
			return false;
		}
	} 

	// Set pointers to point to new value
	DroneRecord* prev_ptr = replace_node_ptr->prev;
	DroneRecord* next_ptr = replace_node_ptr->next;
	if (prev_ptr != NULL) {
		prev_ptr->next = new_node_ptr;
	}
	if (next_ptr != NULL) {
		next_ptr->prev = new_node_ptr;
	}

	new_node_ptr->prev = prev_ptr;
	new_node_ptr->next = next_ptr;
	
	// set replaced node pointers to null
	replace_node_ptr->next = NULL;
	replace_node_ptr->prev = NULL;

	if (replace_node_ptr == first) {
		first = new_node_ptr;
	}
	if (replace_node_ptr == last) {
		last = new_node_ptr;
	}

	return true;
}

bool DronesManager::reverse_list() {
	if (size <= 1) {
		return false;
	}

	if (first == NULL || last == NULL) {
		return false;
	}

	DroneRecord* curr_ptr = first;
	DroneRecord* next_ptr = curr_ptr->next;

	for (int i = 0; i < size; i++) {
		if (curr_ptr != NULL) {
			curr_ptr->next = curr_ptr->prev;
		} else {
			curr_ptr->next = NULL;
		}

		if (next_ptr != NULL) {
			curr_ptr->prev = next_ptr;
		} else {
			curr_ptr->prev = NULL;
		}

		curr_ptr = next_ptr;
		if (next_ptr != NULL) {
			next_ptr = next_ptr->next;
		}
	}

	// switch first and last
	DroneRecord* tmp_first = first;
	first = last;
	last = tmp_first;

	return true;
}

bool DronesManagerSorted::is_sorted_asc() const {
	DroneRecord* curr_ptr = first;
	int prev_value = 0;

	for (int i = 0; i < size; i++) {
		if (curr_ptr->droneID < prev_value) {
			return false;
		}
		prev_value = curr_ptr->droneID;
		curr_ptr = curr_ptr->next;
	}

	return true;
}

bool DronesManagerSorted::is_sorted_desc() const {
	DroneRecord* curr_ptr = first;
	int prev_value = first->droneID;

	for (int i = 0; i < size; i++) {
		if (curr_ptr->droneID > prev_value) {
			return false;
		}
		prev_value = curr_ptr->droneID;
		curr_ptr = curr_ptr->next;
	}

	return true;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
	DroneRecord* new_node = new DroneRecord(val);

	if (size <= 0) {
		first = new_node;
		last = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
		return true;
	}

	if (!is_sorted_asc()) {
		return false;
	}

	if (new_node->droneID < first->droneID) {
		return insert_front(val);
	}

	DroneRecord* curr_node = first;
	DroneRecord* prev_node = NULL;

	if (curr_node == NULL) {
		return insert_front(val);
	}
	
	for (int i = 0; i < size; i++) {

		if (new_node->droneID < curr_node->droneID) {
			prev_node->next = new_node;
			curr_node->prev = new_node;
			new_node->next = curr_node;
			new_node->prev = prev_node;

			size++;
			return true;
		}

		curr_node = curr_node->next;
		if (prev_node == NULL) {
			prev_node = first;
		} else {
			prev_node = prev_node->next;
		}

		if (curr_node == NULL) {
			return insert_back(val);
		}
	}

	return false;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
	DroneRecord* new_node = new DroneRecord(val);

	if (size <= 0) {
		first = new_node;
		last = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
		return true;
	}

	if (!is_sorted_desc()) {
		return false;
	}

	if (new_node->droneID > first->droneID) {
		return insert_front(val);
	}

	DroneRecord* curr_node = first;
	DroneRecord* prev_node = NULL;

	if (curr_node == NULL) {
		return insert_front(val);
	}
	
	
	for (int i = 0; i < size; i++) {

		if (new_node->droneID > curr_node->droneID) {
			prev_node->next = new_node;
			curr_node->prev = new_node;
			new_node->next = curr_node;
			new_node->prev = prev_node;

			size++;
			return true;
		}

		curr_node = curr_node->next;
		if (prev_node == NULL) {
			prev_node = first;
		} else {
			prev_node = prev_node->next;
		}

		if (curr_node == NULL) {
			return insert_back(val);
		}
	}

	return false;
}

void DronesManagerSorted::sort_asc() {
	int swapped; 
    DroneRecord* cur_ptr; 
    DroneRecord* last_ptr = NULL; 
   
	// Check for empty list
    if (first == NULL) {
        return; 
	}

    do{ 
        swapped = 0; 
        cur_ptr = first; 
   
        while (cur_ptr->next != last_ptr){ 
            if (cur_ptr->droneID > cur_ptr->next->droneID){  
                swap(cur_ptr->droneID, cur_ptr->next->droneID); 
                swapped = 1; 
            }
            cur_ptr = cur_ptr->next; 
        } 
        last_ptr = cur_ptr; 
    } 
    while (swapped); 
}
    
void DronesManagerSorted::sort_desc() {
	int swapped; 
    DroneRecord* cur_ptr; 
    DroneRecord* last_ptr = NULL; 
   
	// Check for empty list
    if (first == NULL) {
        return; 
	}

    do{ 
        swapped = 0; 
        cur_ptr = first; 
   
        while (cur_ptr->next != last_ptr){ 
            if (cur_ptr->droneID < cur_ptr->next->droneID) {  
                swap(cur_ptr->droneID, cur_ptr->next->droneID); 
                swapped = 1; 
            }
            cur_ptr = cur_ptr->next; 
        } 
        last_ptr = cur_ptr; 
    } 
    while (swapped); 
}
