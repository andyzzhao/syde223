#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
	    
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))		
	    return true;
	}
	
	// TODO: Implement all of the test cases below
	
	// PURPOSE: select() and search() work properly
	bool test3() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_front(DronesManager::DroneRecord(200));
		manager1.insert_front(DronesManager::DroneRecord(300));

		manager2.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_front(DronesManager::DroneRecord(200));
		manager2.insert_front(DronesManager::DroneRecord(300));

		ASSERT_TRUE(manager1.select(0) == manager2.select(0));
		ASSERT_TRUE(manager1.select(1) == manager2.select(1));
		ASSERT_TRUE(manager1.select(2) == manager2.select(2));
		ASSERT_FALSE(manager1.select(0) == manager2.select(2));

		ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(300)) == 0);
		ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(200)) == 1);
		ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(100)) == 2);

	    return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));

		ASSERT_TRUE(manager1.remove_front());
		ASSERT_TRUE(manager2.remove_back());

		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 0)
		ASSERT_TRUE(manager1.first == NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first == NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == NULL)		

	    return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
		DronesManager manager1;
		manager1.insert_front(DronesManager::DroneRecord(1000));
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_front(DronesManager::DroneRecord(200));
		manager1.insert_front(DronesManager::DroneRecord(300));
		
		ASSERT_TRUE(manager1.replace(2, DronesManager::DroneRecord(500)));
		ASSERT_TRUE(manager1.replace(1, DronesManager::DroneRecord(700)));
		ASSERT_TRUE(manager1.replace(0, DronesManager::DroneRecord(900)));
		ASSERT_TRUE(manager1.replace(3, DronesManager::DroneRecord(800)));

		ASSERT_FALSE(manager1.replace(4, DronesManager::DroneRecord(900))); // invalid
		
		ASSERT_TRUE(manager1.search(900) == 0);
		ASSERT_TRUE(manager1.search(700) == 1);
		ASSERT_TRUE(manager1.search(500) == 2);
		ASSERT_TRUE(manager1.search(800) == 3);
		
		ASSERT_TRUE(manager1.reverse_list());

		ASSERT_TRUE(manager1.search(900) == 3);
		ASSERT_TRUE(manager1.search(700) == 2);
		ASSERT_TRUE(manager1.search(500) == 1);
		ASSERT_TRUE(manager1.search(800) == 0);

		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL);

	    return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
		DronesManager manager1;
		manager1.insert_front(DronesManager::DroneRecord(1000));
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_front(DronesManager::DroneRecord(200));
		manager1.insert_front(DronesManager::DroneRecord(300));
		
		ASSERT_TRUE(manager1.search(300) == 0);
		ASSERT_TRUE(manager1.search(200) == 1);
		ASSERT_TRUE(manager1.search(100) == 2);
		ASSERT_TRUE(manager1.search(1000) == 3);
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL);

	    return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
		DronesManager manager1;
		manager1.insert_front(DronesManager::DroneRecord(1000));
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_front(DronesManager::DroneRecord(200));
		manager1.insert_front(DronesManager::DroneRecord(300));

		manager1.insert(DronesManager::DroneRecord(0), 2);
		manager1.insert(DronesManager::DroneRecord(10), 0);
		manager1.insert(DronesManager::DroneRecord(20), 6);

		ASSERT_TRUE(manager1.search(10) == 0);
		ASSERT_TRUE(manager1.search(300) == 1);
		ASSERT_TRUE(manager1.search(200) == 2);
		ASSERT_TRUE(manager1.search(0) == 3);
		ASSERT_TRUE(manager1.search(100) == 4);
		ASSERT_TRUE(manager1.search(1000) == 5);
		ASSERT_TRUE(manager1.search(20) == 6);
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL);
	    return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
		DronesManager manager1;
		// add elemetns
		manager1.insert_back(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager::DroneRecord(200));
		manager1.insert_back(DronesManager::DroneRecord(300));

		// remove elements
		ASSERT_TRUE(manager1.remove_back());
		ASSERT_TRUE(manager1.remove_back());
		ASSERT_TRUE(manager1.remove_back());

		// invalid removal
		ASSERT_TRUE(!manager1.remove_back());

		// check if list is empty
		ASSERT_TRUE(manager1.get_size() == 0);
		ASSERT_TRUE(manager1.empty() == true);
		ASSERT_TRUE(manager1.first == NULL);
		ASSERT_TRUE(manager1.last == NULL);

		manager1.insert_back(DronesManager::DroneRecord(400));
		manager1.insert_back(DronesManager::DroneRecord(500));

		ASSERT_TRUE(manager1.get_size() == 2);
		ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(400));
		ASSERT_TRUE(manager1.select(1) == DronesManager::DroneRecord(500));	
		
	    return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		DronesManager manager1;
		manager1.insert(DronesManager::DroneRecord(100), 0);
		manager1.insert(DronesManager::DroneRecord(200), 1);
		manager1.insert(DronesManager::DroneRecord(300), 2);
		manager1.insert(DronesManager::DroneRecord(0), 2);
		manager1.insert(DronesManager::DroneRecord(10), 0);
	
		ASSERT_FALSE(manager1.insert(DronesManager::DroneRecord(20), 6)); // invalid
		ASSERT_FALSE(manager1.insert(DronesManager::DroneRecord(30), 10)); // invalid
		ASSERT_FALSE(manager1.insert(DronesManager::DroneRecord(400), -2)); // invalid

		ASSERT_TRUE(manager1.get_size() == 5);

		manager1.remove(0);
		manager1.remove(3);
		manager1.remove(1);

		ASSERT_TRUE(manager1.get_size() == 2);
		
		ASSERT_TRUE(manager1.search(100) == 0);
		ASSERT_TRUE(manager1.search(0) == 1);

		ASSERT_TRUE(manager1.first != NULL);
		ASSERT_TRUE(manager1.last != NULL);

		return true;
	}    
	    	
	// PURPOSE: inserts into an unsorted list, then sort the list
	bool test10() {
		DronesManagerSorted manager1;
		manager1.insert_back(DronesManager::DroneRecord(200));
		manager1.insert_back(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager::DroneRecord(300));	
		manager1.insert_back(DronesManager::DroneRecord(150));	
		manager1.insert_back(DronesManager::DroneRecord(250));	
		ASSERT_TRUE(manager1.get_size() == 5);

		manager1.sort_asc();
		ASSERT_TRUE(manager1.is_sorted_asc());
		ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager1.select(1) == DronesManager::DroneRecord(150));	
		ASSERT_TRUE(manager1.select(2) == DronesManager::DroneRecord(200));
		ASSERT_TRUE(manager1.select(3) == DronesManager::DroneRecord(250));	
		ASSERT_TRUE(manager1.select(4) == DronesManager::DroneRecord(300));

		manager1.sort_desc();
		ASSERT_TRUE(manager1.is_sorted_desc());
		ASSERT_TRUE(manager1.select(4) == DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager1.select(3) == DronesManager::DroneRecord(150));	
		ASSERT_TRUE(manager1.select(2) == DronesManager::DroneRecord(200));
		ASSERT_TRUE(manager1.select(1) == DronesManager::DroneRecord(250));	
		ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(300));
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL);

		return true;
	}  
	
	// PURPOSE: insert and remove into sorted manager in ascending order
	bool test11() {
		DronesManagerSorted manager1;
		manager1.insert_back(DronesManager::DroneRecord(200));
		manager1.insert_back(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager::DroneRecord(300));	
		manager1.insert_back(DronesManager::DroneRecord(500));	
		manager1.insert_back(DronesManager::DroneRecord(600));
		ASSERT_TRUE(manager1.get_size() == 5);	
		ASSERT_FALSE(manager1.insert_sorted_asc(DronesManager::DroneRecord(350))); // invalid
		
		manager1.sort_asc(); // [100,200,300,500,600]
		// check if sorted
		ASSERT_TRUE(manager1.is_sorted_asc()); 

		// insert at the end
		ASSERT_TRUE(manager1.insert_sorted_asc(DronesManager::DroneRecord(700)));
		ASSERT_TRUE(manager1.select(5) == DronesManager::DroneRecord(700));

		// insert between between two elements
		ASSERT_TRUE(manager1.insert_sorted_asc(DronesManager::DroneRecord(400)));
		ASSERT_TRUE(manager1.select(3) == DronesManager::DroneRecord(400)); 

		// insert at front
		ASSERT_TRUE(manager1.insert_sorted_asc(DronesManager::DroneRecord(50)));
		ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(50)); 

		ASSERT_TRUE(manager1.get_size() == 8);	
		ASSERT_TRUE(manager1.is_sorted_asc()); 

		ASSERT_TRUE(manager1.remove(7)); // remove from end
		ASSERT_TRUE(manager1.remove(0)); // remove from front
		ASSERT_TRUE(manager1.remove(2)); // remove from middle
		ASSERT_FALSE(manager1.remove(5)) // invalid
		ASSERT_TRUE(manager1.get_size() == 5);	
		ASSERT_TRUE(manager1.is_sorted_asc());

		return true;
	}
	
	// PURPOSE: insert and remove into sorted manager in descending order
	bool test12() {
		DronesManagerSorted manager1;
		manager1.insert_back(DronesManager::DroneRecord(200));
		manager1.insert_back(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager::DroneRecord(300));	
		manager1.insert_back(DronesManager::DroneRecord(500));	
		manager1.insert_back(DronesManager::DroneRecord(600));
		ASSERT_TRUE(manager1.get_size() == 5);	
		ASSERT_FALSE(manager1.insert_sorted_desc(DronesManager::DroneRecord(350))); // invalid
		
		manager1.sort_desc(); // [600,500,300,200,100]
		// check if sorted
		ASSERT_TRUE(manager1.is_sorted_desc()); 

		// insert at the end
		ASSERT_TRUE(manager1.insert_sorted_desc(DronesManager::DroneRecord(50)));
		ASSERT_TRUE(manager1.select(5) == DronesManager::DroneRecord(50));

		// insert between between two elements
		ASSERT_TRUE(manager1.insert_sorted_desc(DronesManager::DroneRecord(400)));
		ASSERT_TRUE(manager1.select(2) == DronesManager::DroneRecord(400)); 

		// insert at front
		ASSERT_TRUE(manager1.insert_sorted_desc(DronesManager::DroneRecord(700)));
		ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(700)); 

		ASSERT_TRUE(manager1.get_size() == 8);	
		ASSERT_TRUE(manager1.is_sorted_desc()); 

		ASSERT_TRUE(manager1.remove(7)); // remove from end
		ASSERT_TRUE(manager1.remove(0)); // remove from front
		ASSERT_TRUE(manager1.remove(2)); // remove from middle
		ASSERT_FALSE(manager1.remove(5)) // invalid
		ASSERT_TRUE(manager1.get_size() == 5);	
		ASSERT_TRUE(manager1.is_sorted_desc());

		return true;
	}

};

#endif