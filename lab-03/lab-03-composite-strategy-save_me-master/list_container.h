#include <list>
#include <iostream>
#include "container.h"
#include "base.h"
#include "sort.h"
using namespace std;

class ListContainer : public Container{

	private:
		list<Base*> list_container;
	
	public:
		ListContainer(){};
                
                void set_sort_function(Sort *sort_function){
                    this->sort_function = sort_function;
                }
                
                void sort(){
                    if(sort_function != NULL){
                       this->sort_function->sort(this);
                    }
                    else{
                        cout << "EXCEPTION THROWN" << endl; //placeholder for now
                    }
                }

		void add_element(Base* element){
			list_container.push_back(element);
		}

		void print(){
			for(auto it = list_container.begin(); it != list_container.end(); it++){
				cout << (*it)->evaluate() << " ";
			}
			cout << endl;
		}
		

		
		void swap(int i, int j){
			auto it1 = list_container.begin();
			auto it2 = list_container.begin();
			int count = 0;
			for(it1; it1 != list_container.end(); it1++){
				if(count == i){
					std::advance(it2, j);
					std::swap(*it1,*it2);
				}
				count++;

			}

		

		}

		Base* at(int i){
			if(i < 0 || i >= list_container.size()){
				cout << "Out of bounds error" << endl;
			}
			else{
				int count = 0;
				for(auto it = list_container.begin(); it != list_container.end(); it++){
					if(count == i){
					    return *it;
					}
					count++;
		
				}	
			}
		}	

		int size(){
			return list_container.size();
		}
};
