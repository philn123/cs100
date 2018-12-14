#pragma once
class BasePrint {
	private:
		/* Value to Print */
		double value;

	public:
		/* Constructors */
		BasePrint(){};
		BasePrint(double value){};
		
		/* Pure Virtual Print Function */
		virtual void print() = 0;
};


