#include <iostream>
#include "gtest/gtest.h"
#include "basePrint.h"
#include "double_print.h"

TEST(BranchTest, DoublePrint) {
	DoublePrint* test = new DoublePrint(4.0);
	test->print();	
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
