#include "lab2_drones_manager.hpp"

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
	for (int i = 0; i < get_size(); i++) {
		if (i == index) {
			
		}
	}

	return DroneRecord();
}

unsigned int DronesManager::search(DroneRecord value) const {
	return 0;
}

void DronesManager::print() const {
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
