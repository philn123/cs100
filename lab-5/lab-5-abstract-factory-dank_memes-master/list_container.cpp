#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include "list_container.h"
#include "basePrint.h"
#include "binary_print.h"
#include "scientific_print.h"
#include "double_print.h"
using namespace std;

ListContainer::ListContainer(){
}

void ListContainer::sort(){
    if(sort_function != NULL){
        this->sort_function->sort(this);
    }
    else{
        cout << "EXCEPTION THROWN" << endl; //placeholder for now
    }

}
void ListContainer::add_element(Base* element){
    list_container.push_back(element);
}

void ListContainer::print(){
    BasePrint *b;
    for(auto it = list_container.begin(); it != list_container.end(); it++){
      //  cout << (*it)->evaluate() << " ";
        b = type->generatePrint(((*it)->evaluate()));
        b->print();
    }
    cout << endl;

}

void ListContainer::swap(int i, int j){

            auto it1 = list_container.begin();
            auto it2 = list_container.begin();
            int count = 0;
            for(it1; it1 != list_container.end(); it1++){
                if(count == i){
                    advance(it2, j);
                    std::swap(*it1,*it2); //need std:: to differentiate i guess
                }
                count++;

            }

}

Base* ListContainer::at(int i){

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
int ListContainer::size(){
    return list_container.size();
}



