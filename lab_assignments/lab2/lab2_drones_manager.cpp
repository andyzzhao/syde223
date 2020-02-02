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
			if (node_ptr->next == NULL) {
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
	return false;
}

bool DronesManager::insert_front(DroneRecord value) {
	

	return false;
}

bool DronesManager::insert_back(DroneRecord value) {
	return false;
}

bool DronesManager::remove(unsigned int index) {
	return false;
}

bool DronesManager::remove_front() {
	return false;
}

bool DronesManager::remove_back() {
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
