#include "scientific_print.h"
#include "binary_print.h"
#include "gtest/gtest.h"
#include "double_print.h"
#include "DoubleFactory.h"
#include "BaseFactory.h"
#include "ScientificFactory.h"
#include "BinaryFactory.h"
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
#include "sort.h"
#include "container.h"
#include <vector>
#include <iostream>

using namespace std;
TEST(EchoTest, ScientificPrintTest){
    double value = 4.5;
    BasePrint *b = new ScientificPrint(value);
    testing::internal::CaptureStdout();
    b->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("4.500000e+00", output);

  //  cout << endl;

    double value2 = -2.4;
    BasePrint *b2 = new ScientificPrint(value2);
    testing::internal::CaptureStdout();
    b2->print();
    std::string output2 = testing::internal::GetCapturedStdout();
    //b2->print();
    EXPECT_EQ("-2.400000e+00", output2);
}
TEST(EchoTest, BinaryPrintTest){

    int value = 4;
    BasePrint *b = new BinaryPrint(value);
    testing::internal::CaptureStdout();
    b->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("00000100", output);

    double value2 = 2.4;
    
    BasePrint *b2 = new BinaryPrint(value2);
    testing::internal::CaptureStdout();
    b2->print();
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ("00000010", output2);
}
TEST(EchoTest, DoubleTest){

    double value = 4.5;
    DoublePrint *d = new DoublePrint(value);
    testing::internal::CaptureStdout();
    d->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("4.5", output);


}
TEST(EchoTest, DoubleFactoryTest){
    double value = 15.5;
    BaseFactory *doub = new DoubleFactory();
    BasePrint *b = doub->generatePrint(value);

    testing::internal::CaptureStdout();
    b->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("15.5", output);

}
TEST(EchoTest, ScientificFactoryTest){
    double value = 12.5;
    BaseFactory *science = new ScientificFactory();
    BasePrint *b = science->generatePrint(value);
    testing::internal::CaptureStdout();
    b->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1.250000e+01", output);
}
TEST(EchoTest, BinaryFactoryTest){
    double value = 2;
    BaseFactory *bin = new BinaryFactory();
    BasePrint *b = bin->generatePrint(value);
    testing::internal::CaptureStdout();
    b->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("00000010",output); 
}
TEST(EchoTest, ListContainerFactoryTest){
    BaseFactory *b = new BinaryFactory();
    ListContainer *l = new ListContainer(b);
    Op *op4 = new Op(4.2);
    l->add_element(op4);

    testing::internal::CaptureStdout();
    l->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("00000100\n",output); 

    Op *op5 = new Op(5);
    l->add_element(op5);
    l->print();

}
TEST(EchoTest, VectorContainerFactoryTest){
    BaseFactory *b = new ScientificFactory();
    VectorContainer *v = new VectorContainer(b);
    Op *op12 = new Op(12.2);
    v->add_element(op12);
    testing::internal::CaptureStdout();
    v->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1.220000e+01\n",output); 


    Op *op5 = new Op(5);
    v->add_element(op5);
    v->print();
}



int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
