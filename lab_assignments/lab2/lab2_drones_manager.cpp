#include "lab2_drones_manager.hpp"
#include <iostream>
// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
	DroneRecord* null_node = new DroneRecord;
	first = null_node;
	last = null_node;
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
		DroneRecord* node_ptr = first;

		for (int i = 0; i < get_size(); i++) {
			if (i == index) {
				return *node_ptr;
			}
			node_ptr = node_ptr->next;
		}
	}
	return DroneRecord();
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
			cout << "Drone Record No: " << i;
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
	DroneRecord *node_ptr = new DroneRecord(value);

	if(get_size() > index){
		DroneRecord* node_ptr = first;

		for(int i = 0; i < get_size(); i++){
			node_ptr = node_ptr->next;
			
			if (i == index) {
				node_ptr->next
				*node_ptr = value;
			}
		}
	}
	
	return false;
}

bool DronesManager::insert_front(DroneRecord value) {
	DroneRecord *node_ptr = new DroneRecord(value);
	value.prev = NULL;
	value.next = first;
	first->prev = node_ptr;
	first = node_ptr;
	size++;

	if (size == 1) {
		last = node_ptr;
	}

	return false;
}

bool DronesManager::insert_back(DroneRecord value) {
	DroneRecord *node_ptr = new DroneRecord(value);
	value.prev = last;
	value.next = NULL;
	last->prev = node_ptr;
	last = node_ptr;
	size++;

	if (size == 1) {
		first = node_ptr;
	}

	return false;
}

bool DronesManager::remove(unsigned int index) {
	DroneRecord *curr_ptr = first;
	DroneRecord *prev_ptr = first;
	DroneRecord *next_ptr = first;

	if (size < index) {
		return false;
	}

	for (int i = 0; i < index; i++) {
		curr_ptr = curr_ptr->next;
	}

	for (int i = 0; i < index - 1; i++) {
		prev_ptr = prev_ptr->next;
	}

	for (int i = 0; i < index + 1; i++) {
		next_ptr = next_ptr->next;
	}

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
	DroneRecord* node_ptr = first;

	if (node_ptr = NULL) {
		return false;
	}

	first = first->next;
	first->prev = NULL;

	node_ptr->next = NULL;
	delete node_ptr;
	node_ptr = NULL;

	size--;

	return true;
}

bool DronesManager::remove_back() {
	DroneRecord* node_ptr = last;

	if (node_ptr = NULL) {
		return false;
	}

	last = last->prev;
	last->next = NULL;

	node_ptr->prev = NULL;
	delete node_ptr;
	node_ptr = NULL;

	size--;

	return false;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	return false;
}

bool DronesManager::reverse_list() {
	return false;
}

bool DronesManagerSorted::is_sorted_asc() const {
	return false;
}

bool DronesManagerSorted::is_sorted_desc() const {
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
	return false;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
	return false;
}

void DronesManagerSorted::sort_asc() {
}
    
void DronesManagerSorted::sort_desc() {
}
