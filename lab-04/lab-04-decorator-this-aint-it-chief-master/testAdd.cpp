#include "gtest/gtest.h"
#include <iostream>
#include "base.h"
#include "Op.h"
#include "add.h"
#include "sub.h"
#include "sqr.h"
#include "vector_container.h"

TEST(OpTest, Add) {
	Op* op1 = new Op(3);
	Op* op2 = new Op(7);
	Add* sum1 = new Add(op1, op2);
	EXPECT_EQ(10, sum1->evaluate());
}

TEST (OpTest, Subtract) {
	Op* op1 = new Op(6);
	Op* op2 = new Op(10);
	Sub* difference = new Sub(op1, op2);
	EXPECT_EQ(-4, difference->evaluate());
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

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
