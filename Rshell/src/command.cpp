#include "../header/command.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstring> //strcmp
#include <errno.h> //errno global var
Command::Command(std::vector<char *> args) {
    arguments = args;
    arguments.push_back(NULL); //lets execvp know when to terminate argument list
}

Command::~Command(){
    std::vector<char*>::iterator it;
    
    for(it = arguments.begin(); it != arguments.end(); it++) {
        delete (*it);
        *it = 0;
    }
    arguments.clear();

}

char* Command::getFirstArgument() {
	return arguments.at(0);
}

bool Command :: execute() {
    //checking for exit command
    char* s = (char*)"exit";
    if (!strcmp(arguments.at(0), s)) { //strcmp returns 0 if equal
        exit(0);
    }
    
    //this handles replacing the brackets for test command
    //it works because of parsing by spaces, so this is valid
    if(!strcmp(arguments.at(0),(char*)"[")) {
        
        //we have to do minus 1 because of null character at the end       
        for(int i = 0; i < arguments.size()-1; i++) {
            
            if(!strcmp(arguments.at(i), (char*)"]")) {
                arguments.erase(arguments.begin() + i);
                arguments.at(0) = (char*)"test";
                break;
            }

        }
    }

    int status; //used as pointer for information
                // for terminating process to be stored.

    pid_t pid;
    pid = fork();	/*  Negative Pid = child creation failed
                            Positive Pid = return to parent,
				value contains new ID of child process
			    Zero Pid = returned to new child process
                     */

    if (pid < 0) { 
	perror("Error fork");
        exit(1);
	return false;
    }
    else if (pid == 0) { //child process

        //have to put in here or program core dumps
        char *t = (char*)"test";
        if(!strcmp(arguments.at(0),t)) {
            return test();
        }
	if (execvp(arguments.at(0), &arguments.at(0)) == -1) {
		perror("Error in running command");
		exit(1); //EXIT_FAILURE 
		return false;
	}
		
    }
    else {  //parent process

        //watching for if child changes
        do {
            waitpid(pid, &status, 0);
        } while (WIFEXITED(status) == -1);
    }

    return !WEXITSTATUS(status); //it needs ! so it returns false so connector 
                                // doesnt run command its not suppose to

}

bool Command :: test() {

    //its saying if theres nothing other than the word test
    //because last index is NULL
    if(!arguments.at(1)) {
	std::cout << "(False)" << std::endl;
	exit(1);
        return false;
    }

    //https://stackoverflow.com/questions/12927216/system-call-return-values-and-errno
    //used this as a resource to learn what setting errno means
    //we have to use perror because it is syscall
    //perror translates errno message to print
    struct stat buf;
    if(!strcmp(arguments.at(1), (char*)"-e")) {
        
        int return_value = stat(arguments.at(2), &buf);
        
        if(!return_value) { //on success, stat returns 0
            std::cout << "(True)" << std::endl;    
        }
        else {
            //ENOENT-Man Pages, means file/path doesnt exist
            if (errno == ENOENT)
                std::cout << "(False)" << std::endl;

            else //this means stat failed because there was no path inputed
                perror("Status Error");

            //hopefully this fixes the exit problem
            exit(1); //EXIT_FAILURE
            return false;
        }      
    }
    //https://stackoverflow.com/questions/40163270/what-is-s-isreg-and-what-does-it-do
    else if(!strcmp(arguments.at(1), (char*)"-f")) {
	int return_value = stat(arguments.at(2), &buf);

	if(return_value == -1) {
            if (errno == ENOENT)
                 std::cout << "(False)" << std::endl;
            else
                 perror("Status Error");

            exit(1); //EXIT_FAILURE
            return false;
        }
        if (S_ISREG(buf.st_mode)) {
            std::cout << "(True)" << std::endl;
        }
        //this means not regular file
        else {
            std::cout << "(False)" << std::endl;
            exit(1);
            return false;
        }

    }
    else if (!strcmp(arguments.at(1), (char*)"-d")) {
        int return_value = stat(arguments.at(2), &buf);
        
        if(return_value == -1) {

            if (errno == ENOENT)
                std::cout << "(False)" << std::endl;
            else
                perror("Status Error");

            exit(1); //EXIT_FAILURE
            return false;
        }

        if (S_ISDIR(buf.st_mode)) {
            std::cout << "(True)" << std::endl;
        }
        //this means not directory
        else {
            std::cout << "(False)" << std::endl;
            exit(1);
            return false;
        }
    }
    else { //same code as -e flag, copy and paste

        //if user enters test test, or test - e  
        if(arguments.size() > 3) {
            std::cout << "Error: Invalid Syntax" << std::endl;
            exit(1);
            return false;            
        }
        else {
            int return_value = stat(arguments.at(1), &buf);
        
            if(!return_value) { //on success, stat returns 0
                std::cout << "(True)" << std::endl;    
            }
            else {
                if (errno == ENOENT)
                    std::cout << "(False)" << std::endl;
                else
                    perror("Status Error");

                exit(1); //EXIT_FAILURE
                return false;
            }     

        } 

    }


    
    exit(0); //exit success if it is gonna return true
    return true;

}

int Command::precedence() {
	return 1;
}
