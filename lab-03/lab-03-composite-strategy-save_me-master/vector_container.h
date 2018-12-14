#include <vector>
#include <iostream>
#include "container.h"
#include "base.h"


using namespace std;

class VectorContainer : public Container {
	
	private:
		vector<Base*> vCon;
	
	public:
		VectorContainer(){};

 
		void add_element(Base* element) {
			vCon.push_back(element);
		}

		void print() {
			for (int i = 0; i < vCon.size(); i++) {
				cout << vCon.at(i)->evaluate() << " ";
			}
			cout << "\n";		
                }
                void set_sort_function(Sort *sort_function){
                    this->sort_function = sort_function;
    
                }

		void sort() {
                    if(sort_function != NULL){
                        this->sort_function->sort(this);
                    }
                    else{
                       cout << "EXCEPTION SORT IS NULL" << endl;
                    }
		}

		void swap(int i, int j){
			Base* temp = vCon.at(i);
			vCon.at(i) = vCon.at(j);
			vCon.at(j) = temp;
		}
		Base* at(int i) {
			return vCon.at(i);
		}
		int size() {
			return vCon.size();
		}

};	
