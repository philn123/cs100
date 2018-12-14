#ifndef COMMAND_H_
#define COMMAND_H_

#include "base.h"
#include <vector>

class Command : public Base {

	private:
	    std::vector<char*> arguments; //char * because execvp takes in char* and &vector[0] = char**

	public:	
	    Command(std::vector<char *>);
	    ~Command();
	    bool execute();
	    int precedence();
		char* getFirstArgument();

        //helper
        private:
            bool test();




};

#endif
