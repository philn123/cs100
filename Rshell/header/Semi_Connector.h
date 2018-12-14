#ifndef SEMI_CONNECTOR_H
#define SEMI_CONNECTOR_H
#include "Connector.h"
#include <cstddef> //NULL
using namespace std;
class Semi_Connector : public Connector{
    public:
	Semi_Connector() : Connector(NULL, NULL){};
        Semi_Connector(Base* x, Base* y): Connector(x,y){};
        bool execute();
        
};

#endif
