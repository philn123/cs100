#pragma once
#include "basePrint.h"
#include <iostream>

class DoublePrint : public BasePrint{

	private:
		double value;

	public:
		DoublePrint();
		DoublePrint(double val) {
			value = val;
		}

		void print() {
			std::cout << value;
		}

};
