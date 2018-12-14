
//#include "gtest/gtest.h"
#include <iostream>
#include "base.h"
#include "Op.h"
#include "add.h"
#include "sub.h"
#include "sqr.h"
#include "divide.h"
#include "multiply.h"
#include "vector_container.h"
#include "list_container.h"
#include "selection_sort.h"
#include "bubble_sort.h"
#include "container.h"
#include "ceiling.h"
#include "absolute_value.h"
#include "floor.h"
#include "DoubleFactory.h"
#include "BaseFactory.h"
#include "ScientificFactory.h"
#include "BinaryFactory.h"
using namespace std;

int main(int argc, char *argv[]){

    char *type = argv[argc-1];
    BaseFactory *b;

    if(*type == 'd'){
        b = new DoubleFactory();
    }
    else if(*type == 'b'){
        b = new BinaryFactory();
    }
    else
        b = new ScientificFactory();

    Op* op7 = new Op(7);
    Op* op4 = new Op(4);
    Op* op3 = new Op(3);
    Op* op2 = new Op(2);
    Mult* A = new Mult(op7, op4);
    Add* B = new Add(op3, A);
    Sub* C = new Sub(B, op2);
    Sqr* D = new Sqr(C);

    VectorContainer* container = new VectorContainer(b);
    container->add_element(A);
    container->add_element(B);
    container->add_element(C);
    container->add_element(D);

    cout << "Container Before Sort: " << endl;
    container->print();

    cout << "Container After Sort: " << endl;
    container->set_sort_function(new SelectionSort());
    container->sort();
    container->print();
    
    return 0;
}
