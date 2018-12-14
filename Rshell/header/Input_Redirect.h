#ifndef _INPUT_REDIRECT_H_
#define _INPUT_REDIRECT_H_
#include "Connector.h"
#include <cstddef>
class InputRedirect : public Connector {

    public:
		InputRedirect() : Connector(NULL, NULL) {};
		InputRedirect(Base *left, Base *right) : Connector(left, right) {};
		bool execute();


};


#endif
