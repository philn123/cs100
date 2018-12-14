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



    Op *op8 = new Op(8.8);
    Op *opN2 = new Op(-2.2);
    Op *op5 = new Op(5.5);
    Mult *x = new Mult(opN2, op5);
    Add *a = new Add(x, op8);

    cout << "(8.8 - 2.2 + 5.5) = " <<  a->evaluate() << endl;
    Ceiling *c = new Ceiling(a);
    cout << "ceil(8.8 -2.2 + 5.5) = " << c->evaluate() << endl;
    Absolute *abs = new Absolute(c);
    cout << "abs(ceil(-3.3)) = " << abs->evaluate() << endl; 
    VectorContainer *v = new VectorContainer(b);
    v->add_element(op8);
    v->add_element(opN2);
    v->add_element(op5);
    v->add_element(x);
    v->add_element(a);
    v->add_element(abs);
    v->add_element(c);
    cout << "Numbers added to container: ";
    v->print();
    cout << endl;
    cout << "Sorted from least to greatest: ";
    v->set_sort_function(new SelectionSort());
    v->sort();
    v->print();
    cout << endl;

    cout << "Sorted from greatest to least: ";
    v->set_sort_function(new BubbleSort());
    v->sort();
    v->print();
    cout << endl;
    
    Floor *f = new Floor(v->at(v->size()-1));
    Absolute *abs2 = new Absolute(f);
    cout << "Turn last number into whole number using floor and absolute value: " << abs2->evaluate() << endl;
    cout << "Swap last two values: " << endl;
    v->swap(0, v->size()-1);
    v->print();    
    cout << "Take first and last values, divide them and give back the absolute value: " << endl;
    Div *d = new Div(v->at(0), v->at(v->size()-1));
    Absolute *absd = new Absolute(d);
    cout << absd->evaluate() << endl;


    


    return 0;
}      
