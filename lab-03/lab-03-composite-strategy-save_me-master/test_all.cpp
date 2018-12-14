nclude "gtest/gtest.h"
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
#include "sort.h"
#include "container.h"
#include <vector>
using namespace std;

TEST (OpTest, Operation) {
        Op* op1 = new Op(3);
        EXPECT_EQ(3, op1->evaluate());
}
TEST (OpTest, OperationAlpha) {
        Op* op1 = new Op('a');
        EXPECT_EQ('a', op1->evaluate());
}
TEST(OpTest, Add) {
        Op* op1 = new Op(3.0);
        Op* op2 = new Op(7);
        Add* sum1 = new Add(op1, op2);
        EXPECT_EQ(10, sum1->evaluate());
}

TEST(OpTest, AddAlpha) {
        Op* op1 = new Op('a');
        Op* op2 = new Op('b');
        Add* sum1 = new Add(op1, op2);
        EXPECT_EQ(195, sum1->evaluate());
}
TEST (OpTest, Subtract) {
        Op* op1 = new Op(6.0);
        Op* op2 = new Op(10);
        Sub* difference = new Sub(op1, op2);
        EXPECT_EQ(-4, difference->evaluate());
}

TEST (OpTest, SubtractAlpha) {
        Op* op1 = new Op('b');
        Op* op2 = new Op('a');
        Sub* difference = new Sub(op1, op2);
        EXPECT_EQ(1, difference->evaluate());
}

TEST (OpTest, Divide) {
        Op* op1 = new Op(4.5);
        Op* op2 = new Op(5);
        Div* quotient = new Div(op1, op2);
        EXPECT_EQ(0.9, quotient->evaluate());
}

TEST (OpTest, Multiply) {
        Op* op1 = new Op(6);
        Op* op2 = new Op(9);
        Mult* product = new Mult(op1, op2);
        EXPECT_EQ(54, product->evaluate());
}

TEST(OpTest, Square) {
        Op* op1 = new Op(8);
        Sqr* product = new Sqr(op1);
        EXPECT_EQ(64, product->evaluate());
}

TEST(OpTest, Vector) {
        Op* op1 = new Op(5); Op* op2 = new Op(3);
        Add* sum1 = new Add(op1, op2);
        Sqr* product = new Sqr(op1);
        VectorContainer* container = new VectorContainer();
        container->add_element(sum1);
        container->add_element(product);
        container->print();
        container->swap(0, 1);
        container->print();
        EXPECT_EQ(8, container->at(1)->evaluate());
}

TEST(OpTest, List) {
        Op* op1 = new Op(5); Op* op2 = new Op(3);
        Add* sum1 = new Add(op1, op2);
        Sqr* product = new Sqr(op1);
        ListContainer* container = new ListContainer();
        container->add_element(sum1);
        container->add_element(product);
        container->print();
        container->swap(0, 1);
        container->print();
        EXPECT_EQ(8, container->at(1)->evaluate());
}

TEST(OpTest, SelectionSort) {
        Op* op1 = new Op(1); Op* op2 = new Op(2); Op* op3 = new Op(3);
        Add* sum1 = new Add(op1, op2);
        Sub* difference = new Sub(op3, op1);
        Mult* product = new Mult(op2, op3);
        Div* quotient = new Div(op3, op1);
        VectorContainer* container = new VectorContainer();
        container->add_element(sum1);
        container->add_element(difference);
        container->add_element(product);
        container->add_element(quotient);
        container->print();
        SelectionSort* selection = new SelectionSort();
        container->set_sort_function(selection);
        container->sort();
        container->print();
        EXPECT_EQ(1, container->at(0));
        EXPECT_EQ(3, container->at(1));
        EXPECT_EQ(3, container->at(2));
        EXPECT_EQ(6, container->at(3));
}

TEST(OpTest, BubbleSort) {
        Op* op1 = new Op(1); Op* op2 = new Op(2); Op* op3 = new Op(3);
        Add* sum1 = new Add(op1, op2);
        Sub* difference = new Sub(op3, op1);
        Mult* product = new Mult(op2, op3);
        Div* quotient = new Div(op3, op1);
        ListContainer* container = new ListContainer();
        container->add_element(sum1);
        container->add_element(difference);
        container->add_element(product);
        container->add_element(quotient);
        container->print();
        BubbleSort* bubble = new BubbleSort();
        container->set_sort_function(bubble);
        container->sort();
        container->print();
        EXPECT_EQ(6, container->at(0));
        EXPECT_EQ(3, container->at(1));
        EXPECT_EQ(3, container->at(2));
        EXPECT_EQ(1, container->at(3));
}

TEST(OpTest, SelectionBubbleSelection) {
        Op* op1 = new Op(2); Op* op2 = new Op(3); Op* op3 = new Op(4);
        Add* sum1 = new Add(op1, op2);
        Sub* difference = new Sub(op3, op1);
        Mult* product = new Mult(op2, op3);
        Div* quotient = new Div(op3, op1);
        VectorContainer* container = new VectorContainer();
        container->add_element(sum1);
        container->add_element(difference);
        container->add_element(product);
        container->add_element(quotient);
        SelectionSort* selection = new SelectionSort();
        container->set_sort_function(selection);
        container->sort();
        container->print();
        BubbleSort* bubble = new BubbleSort();
        container->set_sort_function(bubble);
        container->sort();
        container->print();
        container->set_sort_function(selection);
        container->sort();
        container->print();
        EXPECT_EQ(2, container->at(0));
        EXPECT_EQ(2, container->at(1));
        EXPECT_EQ(5, container->at(2));
        EXPECT_EQ(12, container->at(3));
}


int main(int argc, char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

