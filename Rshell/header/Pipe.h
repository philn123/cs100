#ifndef _PIPE_H_
#define _PIPE_H_

#include "Connector.h"
#include "command.h"
#include <cstddef>

class Pipe : public Connector {
    public:
        Pipe() : Connector(NULL, NULL){};
        Pipe(Base *left, Base *right) : Connector(left, right) {};
        bool execute();

};


#endif
