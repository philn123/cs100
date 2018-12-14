#pragma once

class BasePrint;

class BaseFactory {
public:
	/* Constructor */
	BaseFactory() {};

	/* Pure Virtual Generate Function */
        virtual	BasePrint* generatePrint(double value) = 0;
};
