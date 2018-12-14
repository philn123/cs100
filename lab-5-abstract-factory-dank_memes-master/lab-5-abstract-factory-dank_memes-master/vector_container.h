#pragma once
#include <vector>
#include "container.h"
#include "base.h"

using namespace std;

class VectorContainer : public Container {
	
	private:
		vector<Base*> vCon;
                BaseFactory *type;	
	public:
		VectorContainer();
                VectorContainer(Sort* sort_function);
                VectorContainer(BaseFactory *flag):type(flag){};
                void add_element(Base* element);
                void print();
                void sort();
                void swap(int i, int j);
                Base* at(int i);
                int size();
};	
