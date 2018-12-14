#include <iostream>
#include "base.h"
#include "container.h"
#include "gtest/gtest.h"
#include <list>
#include "Op.h"
#include "divide.h"
#include "multiply.h"
#include "add.h"
#include "list_container.h"

using namespace std;

TEST(EchoTest, AddElement){
	ListContainer *l = new ListContainer();
	Op *op8 = new Op(8);
	l->add_element(op8);
	l->print();
	Op *op5 = new Op(5);
	l->add_element(op5);
	Mult *x = new Mult(op5, op8);
	l->add_element(x);
	l->print();
	EXPECT_EQ(8, l->at(0)->evaluate());
	
}



TEST(EchoTest, AtIndex){
	ListContainer *test = new ListContainer();
	Op *op5 = new Op(5);
	Op *op10 = new Op(10);
	Div *x = new Div(op10, op5);
	test->add_element(x);
	test->print();
	EXPECT_EQ(2, test->at(0)->evaluate());
        test->at(2);
}
TEST(EchoTest, Size){
    ListContainer *test2 = new ListContainer();
    Op *op1 = new Op(1);
    Op *op2 = new Op(2);
    Op *op4 = new Op(4);
    Op *op5 = new Op(5);
    Op *op10 = new Op(10);
    test2->add_element(op1);
    test2->add_element(op2);
    test2->add_element(op4);
    test2->add_element(op5);
    test2->add_element(op10);
    EXPECT_EQ(5, test2->size());
    test2->print();
}
TEST(EchoTest, SWAP){
    ListContainer *test2 = new ListContainer();
    Op *op1 = new Op(1);
    Op *op2 = new Op(2);
    Op *op3 = new Op(3);
    Op *op4 = new Op(4);
    test2->add_element(op1);
    test2->add_element(op2);
    test2->add_element(op3);
    test2->add_element(op4);
    test2->swap(1,2);
    EXPECT_EQ(3, test2->at(1)->evaluate());
    test2->print();
    test2->swap(0,1);
    test2->print();
    test2->swap(0,3);
    test2->print();
    test2->swap(3,1);
    test2->print();
    
}
int main(int argc, char **argv){
	    ::testing::InitGoogleTest(&argc, argv);
	    return RUN_ALL_TESTS();
}
