#include <list>
#include <iostream>
#include "container.h"
#include "base.h"
using namespace std;

class ListContainer : public Container{

	private:
		list<Base*> list_container;
	
	public:
		ListContainer();
                
                void sort();

		void add_element(Base* element);

		void print();
		
		void swap(int i, int j);

		Base* at(int i);	

		int size();
};
