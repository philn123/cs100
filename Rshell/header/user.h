#ifndef _user_h
#define _user_h

#include "base.h"

#include <string>
#include <vector>
#include <list>
class User{

    private:
        std::string prompt_sign;
    
    public:
        User();

        void start();
        
        std::list<std::string> parse(std::string&);

		
	Base* createTree(std::list<std::string>&);
	
    //creates a single command and returns it for expression
        Base* createCommand(std::vector<std::string>&);
        
        char* convertString(const std::string);
        
    private: //helper functions

        bool isConnector(std::string&);
        bool evenParentheses(const std::list<std::string>&);

};




#endif
