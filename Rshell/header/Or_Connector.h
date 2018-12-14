#ifndef OR_CONNECTOR_H
#define OR_CONNECTOR_H
#include "Connector.h"
#include <cstddef> //NULL
using namespace std;
class Or_Connector : public Connector{
    public:
	Or_Connector() : Connector(NULL, NULL){};
        Or_Connector(Base* x, Base* y): Connector(x,y){};
        bool execute();
        
};

#endif
