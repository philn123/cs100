#include "sort.h"
#include "base.h"
#include "add.h"
#include "multiply.h"
#include "container.h"
#include "list_container.h"
#include "Op.h"
#include "gtest/gtest.h"
#include "bubble_sort.h"
#include <iostream>
using namespace std;

TEST(EchoTest, TestingBubbleSort){
    ListContainer *list = new ListContainer();
    Op *op8 = new Op(8);
    Op *op1 = new Op(1);
    Op *op4 = new Op(4);
    Mult *op32 = new Mult(op8, op4);
    list->add_element(op4);
    list->add_element(op1);
    list->add_element(op8);
    list->add_element(op32);
    
    cout << "Before Sort: ";
    list->print();
    cout << endl;

    list->set_sort_function(new BubbleSort());
    list->sort();
    list->print();
}



int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
