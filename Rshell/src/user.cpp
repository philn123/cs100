#include "../header/user.h"
#include "../header/And_Connector.h"
#include "../header/Or_Connector.h"
#include "../header/Semi_Connector.h"
#include "../header/base.h"
#include "../header/command.h"
#include "../header/Parentheses.h"
#include "../header/Input_Redirect.h"
#include "../header/Output_Redirect.h"
#include "../header/Pipe.h"

#include <limits.h> //used to get username
#include <unistd.h> //and hostmachine
#include <string>
#include <stack> //used to convert to postfix
#include <vector>
#include <iostream>
#include <algorithm> //std::find
#include <cstring> //STRTOK
#include <stdexcept> //to catch segfaults
#include <list> //we're using a list because queue seg faults on hammer

using std::string;
using std::vector;
using std::stack;
using std::list;

User :: User():prompt_sign("$ "){};

void User :: start(){
    string user_command;
    Base *executable_command;
    list<string> parsed_command;

    //getting host and user
    char host_machine[HOST_NAME_MAX];
    char user_name[LOGIN_NAME_MAX];
    gethostname(host_machine, HOST_NAME_MAX);
    getlogin_r(user_name, LOGIN_NAME_MAX);

    std::cout << user_name << "@" << host_machine << prompt_sign;

    //keeps asking for input till exit
    while(std::getline(std::cin, user_command)){
        
        parsed_command = parse(user_command);
        
        //if user enters space or enter key, it'll skip
        if (!parsed_command.empty()) {

            executable_command = createTree(parsed_command);

            //this is to make sure that it does not segfault when 
            //createTree returns NULL
            
	    if (executable_command) {    
		executable_command->execute();
	    }

            delete executable_command; 

        }       

        std::cout << user_name << "@" << host_machine << prompt_sign;
    }



}
//this stays the same as last time
//we just return a list instead of a vector
list<string> User :: parse(string &user_command){
    list<string> commands;

    //finding comment and removing it and everything after it
    size_t index = user_command.find("#");

    if (index != string::npos) {  //if we did find the comment, truncate string
        user_command = user_command.substr(0, index);
    }

	//adding space before and after every single parenthesis

	//adds space before
	for (int i = 0; i < user_command.size(); i++) {
		if (user_command.at(i) == '(') {
		    user_command.insert(i++, " ");
		}
		if (user_command.at(i) == ')') {
		    user_command.insert(i++, " ");
		}
	}
	
	//adds space after
	for (int i = 0; i < user_command.size(); i++) {
                //we use x so we do not get out of range
                int x = i;
		if (user_command.at(x) == '(') {
		    x++;	
                    user_command.insert(x++, " ");
		}
                else if (user_command.at(x) == ')') {
		    x++;
		    user_command.insert(x++, " ");
		}
	}
    
    //dealing with semicolon connected to string    
    //inserts a space before every semicolon to parse
    for(int i = 0; i < user_command.size(); i++) {
        if (user_command.at(i) == ';') {
            user_command.insert(i++, " ");
        }       
    }


    //cppreference strtok
    //converting string into char* for tokenizing
    //and parsing by spaces
    char *cmd = (char*)user_command.c_str();
    char *token = strtok(cmd, " ");

    //adding parsed strings to vector to return
    while (token != NULL) {
        commands.push_back(token);
        token = std::strtok(NULL, " ");
    }   
    return commands;

}

Base* User::createTree(list<string> &parsed_command) {
        //checks for uneven parenthesis before creating any objects
        if(!evenParentheses(parsed_command))
            return NULL;

	vector<Base*> command_tree;

	//this section creates a vector of base*
	//easier to work on abstractly since we just have to think of
	//as a single object instead of a bunch of strings
	while (!parsed_command.empty()) {	
            vector<string> command; //to hold the strings before connectors

            //adding strings up to a connector or end of parsed input
            
            while(!isConnector(parsed_command.front()) && !parsed_command.empty()) {
                command.push_back(parsed_command.front());
                parsed_command.pop_front();
            }

            if (!command.empty()) {

                //we build the commands first before doing anything
                //idea from Fangsheng
                // so previous way did not work
                // when pointer was passed around, char* got messed up
                // so i manually converted it to a char*

                Base *temp = createCommand(command);
                command_tree.push_back(temp);

                command.clear(); //just to make sure it deallocates everyting
            }
            else if (parsed_command.front() == ";") {
                Connector *connect = new Semi_Connector(NULL,NULL);
                command_tree.push_back(connect);
                parsed_command.pop_front();

            }
            else if (parsed_command.front() == "&&") {
                Connector *connect = new And_Connector(NULL,NULL);
                command_tree.push_back(connect);
                parsed_command.pop_front();

            }
            else if (parsed_command.front() == "||") {
                Connector *connect = new Or_Connector(NULL,NULL);
                command_tree.push_back(connect);
                parsed_command.pop_front();
            }
            else if (parsed_command.front() == "(") {
                Base *paren = new openParentheses();
                command_tree.push_back(paren);
                parsed_command.pop_front();
            } 
            else if (parsed_command.front() == ")") {
                Base *paren = new closedParentheses();
                command_tree.push_back(paren);
                parsed_command.pop_front();
            }
            else if (parsed_command.front() == "<") {
                Base *paren = new InputRedirect();
                command_tree.push_back(paren);
                parsed_command.pop_front();
            }
            else if (parsed_command.front() == ">") {
                Base *paren = new singleOutputRedirect();
                command_tree.push_back(paren);
                parsed_command.pop_front();
            }
            else if (parsed_command.front() == ">>") {
                Base *paren = new doubleOutputRedirect();
                command_tree.push_back(paren);
                parsed_command.pop_front();
            }
            else if (parsed_command.front() == "|") {
                Base *paren = new Pipe();
                command_tree.push_back(paren);
                parsed_command.pop_front();
            }
	}


	//http://www.cs.man.ac.uk/~pjj/cs212/fix.html
	//https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
	//link is to converting expression to postfix notation
	//changing design because it will be easier to deal with parenthesis

	//our infix expression is in vector called command_tree
	stack<Base*> connector_stack;
	vector<Base*> output;

	for (int i = 0; i < command_tree.size(); i++) {
		if (command_tree.at(i)->precedence() == 1) { //command
		    output.push_back(command_tree.at(i));
		}
		else if (command_tree.at(i)->precedence() == 2) { //connector
		    if (connector_stack.empty()) {
		        connector_stack.push(command_tree.at(i));
		    }
		    else {
	    	        if(connector_stack.top()->precedence() == 4) {
                            connector_stack.push(command_tree.at(i));
                        }
                        else {
                            output.push_back(connector_stack.top());
			    connector_stack.pop();
		            connector_stack.push(command_tree.at(i));
                        }
		    }

		}
                else if(command_tree.at(i)->precedence() == 4) { //open parenthesis
                    connector_stack.push(command_tree.at(i));
                }
                else if (command_tree.at(i)->precedence() == 3) { //closed paren
                    if (connector_stack.top()->precedence() == 4 && output.empty()) {
                        std::cout << "Error: No valid commands inside parentheses" << std::endl;
                        return NULL;
                    }

                    while(connector_stack.top()->precedence() != 4) {
                        output.push_back(connector_stack.top());
                        connector_stack.pop();
                    }
                    connector_stack.pop(); //pop first paren
                }

	}
        
        //pop all remainding connectors off the stack and onto
        //postfix output vector
	while (!connector_stack.empty()) {
	    output.push_back(connector_stack.top());
	    connector_stack.pop();
	}

	/*
         * Resources for Evaluating PostFix:
         * https://www.geeksforgeeks.org/stack-set-4-evaluation-postfix-expression/
         * now we have to evaluate the postfix notation by building the tree
        */

        //we keep this NULL for safety
        Base *tree = NULL;
        stack<Base *> command_stack;

	//output vector now has postfix notation
	for(int i = 0; i < output.size(); i++) {
	    if (output.at(i)->precedence() == 1) { //command
		command_stack.push(output.at(i));
	    }
	    else if(output.at(i)->precedence() == 2){ //connector
		Base *left_cmd = NULL;
		Base *right_cmd = NULL;
                                
		if (!command_stack.empty()) {
		    right_cmd = command_stack.top();
                }
                else {
                    //dont want to pop an empty stack
                    std::cout << "Error: Not enough arguments for connector" << std::endl;
                    return NULL;
                }
                command_stack.pop(); //1-can seg fault

		if (!command_stack.empty()) {
	            left_cmd = command_stack.top();
                }
                else {
                    //dont want to pop an empty stack, this means there
                    //is a single missing argument
                    std::cout << "Error: Not enough arguments for connector" << std::endl;
                    return NULL;
                }

		command_stack.pop(); //2-can seg fault
                    
                //Cast it because output is a base* not connector
		Connector *connect2 = (Connector*)(output.at(i));

		//checking if left, right is NULL
                //this is an emergency check just in case something got by
                //do not want to seg fault
		if (!left_cmd || !right_cmd) {
                    std::cout << "Not enough commands" << std::endl;
		}
		connect2->setLeft(left_cmd);
		connect2->setRight(right_cmd);
		command_stack.push(connect2);


	    }
	}
        //same idea as previous code, top of stack = end of vector
    tree = command_stack.top();

    //this will return the correct pointer or NULL
    return tree;
}

//this only creates a single command
Base* User::createCommand(vector<string> &command) {

    vector<char *> v;

    
    for(int i = 0; i < command.size(); i++){
        v.push_back(convertString(command.at(i)));
    } 
    

    return (new Command(v));
}

//we have to manually convert it or char* does not work
//will try the other way later
char* User :: convertString(const string scmd){
    char *c = new char[scmd.size()+1];
    std::copy(scmd.begin(), scmd.end(), c);
    c[scmd.size()] = '\0';
    return c;

}


bool User :: isConnector(string &command) {

    std::vector<string> connectors;
    connectors.push_back("&&");
    connectors.push_back("||");
    connectors.push_back(";");
    connectors.push_back(")");
    connectors.push_back("(");
    connectors.push_back("<");
    connectors.push_back(">>");
    connectors.push_back(">");
    connectors.push_back("|");
    //for (auto it = connectors.begin(); it != connectors.end(); it++) {
    for(auto it : connectors) {  
        if(command == it)
            return true;

    }

    return false;


}

bool User :: evenParentheses(const list<string> &parsed_command) {
    int count = 0;
    
    for(auto it = parsed_command.begin(); it != parsed_command.end(); it++) {
        if(*it == "(")
            count++;
        if(*it == ")")
            count--;
    }
    
    if(count == 0)
        return true;
    else {
        std::cout << "Error: Uneven Parentheses" << std::endl;
        return false;
    }
}



