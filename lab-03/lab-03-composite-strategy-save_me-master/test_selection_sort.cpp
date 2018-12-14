#include "base.h"
#include "add.h"
#include "multiply.h"
#include "container.h"
#include "Op.h"
#include "gtest/gtest.h"
#include "selection_sort.h"
#include "vector_container.h"
#include <vector>
using namespace std;


TEST(EchoTest, Sorting){
    Op* op1 = new Op(1);
    Op* op5 = new Op(5);
    Op* op2 = new Op(2);
    Op* op3 = new Op(3);
    Mult *x = new Mult(op5, op3);
    Mult *y = new Mult(op2, op3);

    VectorContainer *vec = new VectorContainer();
    vec->add_element(op1);
    vec->add_element(x);
    vec->add_element(y);
    vec->add_element(op3);
    vec->add_element(op2);
    vec->add_element(op5);
    vec->print();
    vec->set_sort_function(new SelectionSort());
    vec->sort();
    vec->print();
}
TEST(EchoTest, Swapping){
    
    Op* op1 = new Op(1);
    Op* op5 = new Op(5);
    Op* op2 = new Op(2);
    Op* op3 = new Op(3);
    Mult *x = new Mult(op5, op3);
    Mult *y = new Mult(op2, op3);

    VectorContainer *vec = new VectorContainer();
    vec->add_element(op1);
    vec->add_element(x);
    vec->add_element(y);
    vec->add_element(op3);
    vec->add_element(op2);
    vec->add_element(op5);
    vec->print();
    vec->swap(0,1);
    vec->print();
    vec->swap(1,5);
    vec->print();
    vec->swap(5,3);
    vec->print();
    vec->swap(2,4);
    vec->print();
}
     
int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
