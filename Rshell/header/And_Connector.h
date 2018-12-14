#ifndef AND_CONNECTOR_H
#define AND_CONNECTOR_H
#include "Connector.h"
#include <cstddef> //NULL
using namespace std;
class And_Connector : public Connector{
    public:
    	And_Connector() : Connector(NULL, NULL){};
        And_Connector(Base* x, Base* y): Connector(x,y){};
        bool execute();
        
};

#endif
