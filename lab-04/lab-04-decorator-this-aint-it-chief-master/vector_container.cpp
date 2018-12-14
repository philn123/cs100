#include <vector>
#include <iostream>
#include "vector_container.h"
#include "base.h"

using namespace std;

VectorContainer::VectorContainer(){
}

void VectorContainer::add_element(Base* element){
    vCon.push_back(element);
}

void VectorContainer::print(){
    for(int i = 0; i < vCon.size(); i++){
        cout << vCon.at(i)->evaluate() << " ";
    }
    cout << "\n";
}
void VectorContainer::sort(){
    if(sort_function != NULL){
        this->sort_function->sort(this);
    }
    else{
        cout << "EXCEPTION SORT IS NULL" << endl;
    }

}
void VectorContainer::swap(int i, int j){

    Base* temp = vCon.at(i);
    vCon.at(i) = vCon.at(j);
    vCon.at(j) = temp;

}

Base* VectorContainer::at(int i){
    return vCon.at(i);
}

int VectorContainer::size(){
    return vCon.size();
}

