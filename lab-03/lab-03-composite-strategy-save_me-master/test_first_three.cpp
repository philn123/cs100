#include <iostream>
#include "base.h"
#include "divide.h"
#include "multiply.h"
#include "gtest/gtest.h"
#include "Op.h"
#include "add.h"
#include "sqr.h"
#include "sub.h"
using namespace std;
/*
TEST(EchoTest, TestOperandDifferent){
    double test_value = 8;
    EXPECT_EQ(5, test_value);
}
*/
TEST(EchoTest, TestCorrectOperand){
    double test_value = 56;
    EXPECT_EQ(56, test_value);
}
TEST(EchoTest, TestMultiply){
    Op *one = new Op(5);
    Op *two = new Op(6);
    Mult *x = new Mult(one, two);
    EXPECT_EQ(30, x->evaluate());
}
/*
TEST(EchoTest, Test_Fail_Multiply){
   Op *first = new Op(50);
   Op *second = new Op(10);
   Mult *z = new Mult(first, second);
   EXPECT_NE(500, z->evaluate());
}
*/
TEST(EchoTest, TestingDivide){
    Op *num = new Op(10);
    Op *denom = new Op(5);
    Div *d = new Div(num, denom);
    EXPECT_EQ(2, d->evaluate());
}
TEST(EchoTest, TestingNotEqualDivide){
    Op *num1 = new Op(100);
    Op *num2 = new Op(20);
    Div *dividend = new Div(num1, num2);
    EXPECT_NE(2, dividend->evaluate());
}
TEST(EchoTest, TestingChildren){
    Op *op8 = new Op(8);
    Op *op5 = new Op(5);
    Op *op2 = new Op(2);
    Mult *x = new Mult(op8, op5);
    Mult *y = new Mult(x, op2);
    Op *op10 = new Op(10);
    Sub *z = new Sub(op10, y);
    EXPECT_NE(0, z->evaluate());

}
TEST(EchoTest, TestDivide){
    Op *op4 = new Op(4);
    Op *op1 = new Op(1.5);
    Mult *x = new Mult(op4, op1);
    Div *y = new Div(x, op4);
    ASSERT_DOUBLE_EQ(1.5, y->evaluate());
}    






int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
