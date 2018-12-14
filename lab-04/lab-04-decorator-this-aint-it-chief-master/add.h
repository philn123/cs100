#include "base.h"

class Add : public Base {
	private:
		Base* operand1;
		Base* operand2;
	public:
		Add(){};
		Add(Base* op1, Base* op2) {
			operand1 = op1;
			operand2 = op2;
		}
		double evaluate() {
			return (operand1->evaluate() + operand2->evaluate());
		}

};
