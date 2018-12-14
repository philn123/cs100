#include "base.h"

class Div : public Base{

	private:
	   Base *operator_1;
	   Base *operator_2;


	public:
	   Div(){};
	   Div(Base *input_1,Base *input_2){
	      operator_1 = input_1;
	      operator_2 = input_2;
	   }

	   double evaluate(){
	      return (operator_1->evaluate()/operator_2->evaluate());
	   }


};
