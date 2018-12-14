#ifndef BASE_H_
#define BASE_H_

class Base {

	public:
		virtual bool execute() = 0;
        virtual int precedence() = 0;
};

#endif
