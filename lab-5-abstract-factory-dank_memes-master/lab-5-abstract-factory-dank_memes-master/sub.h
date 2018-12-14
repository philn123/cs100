#include "base.h"

class Sub : public Base {
	private:
		Base* operand1;
		Base* operand2;
	public:
		Sub(){};
		Sub(Base* op1, Base* op2) {
			operand1 = op1;
			operand2 = op2;
		}
		double evaluate() {
			return	(operand1->evaluate() - operand2->evaluate());
		}

};
