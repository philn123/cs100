#include "base.h"

class Sqr : public Base {
	private:
		Base* operand1;
	public:
		Sqr(){};
		Sqr(Base* op1) {
			operand1 = op1;
		}
		double evaluate() {
			return (operand1->evaluate() * operand1->evaluate());
		}
};
