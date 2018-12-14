#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "base.h"
class Connector: public Base {

	protected:
		Base* left;
		Base* right;
    public:
        Connector(Base* x, Base* y) {
            left = x;
            right = y;
        }
        ~Connector(){
            delete left;
            delete right;
        }

        virtual bool execute() = 0;

        int precedence(){
            return 2;
        }

        void setLeft(Base *left) {
            this->left = left;
        }

        void setRight(Base *right) {
            this->right = right;
        }
		
};

#endif
