#ifndef PARENTHESES_H_
#define PARENTHESES_H_

#include "base.h"

class openParentheses : public Base {
public:
	openParentheses() {};
	bool execute() {};
	int precedence() {
		return 4;
	}
		
};

class closedParentheses : public Base {
public:
	closedParentheses() {};
	bool execute() {};
	int precedence() {
		return 3;
	}

};
#endif
