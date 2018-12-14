
#include "base.h"
class Op : public Base{
	

	private:
	   double operand;

	public:
	   Op(){};
	   Op(double input){
	      operand = input;
	   }
	   
	   double evaluate(){
		return operand;
	   }
	   
	    
};
