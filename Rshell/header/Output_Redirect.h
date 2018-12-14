#ifndef _OUTPUT_REDIRECT_H_
#define _OUTPUT_REDIRECT_H_
#include "command.h"
#include "Connector.h"
#include <cstddef>
class singleOutputRedirect : public Connector {

    public:
        singleOutputRedirect() : Connector(NULL,NULL){};
        singleOutputRedirect(Base *left, Base *right) : Connector(left, right) {};
        bool execute();


};

class doubleOutputRedirect : public Connector {
    public:
        doubleOutputRedirect() : Connector(NULL,NULL){};
        doubleOutputRedirect(Base *left, Base *right) : Connector(left, right) {};
        bool execute();

};


#endif
