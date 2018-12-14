#include <iostream>
#include "base.h"
#include "Op.h"
#include "add.h"

using namespace std;

int main() {
	double num1;
	double num2;

	cin >> num1 >> num2;

	Op* op1 = new Op(num1);
	Op* op2 = new Op(num2);

	Add test = Add(op1, op2);

	cout << test.evaluate() << endl;

	return 0;
}
