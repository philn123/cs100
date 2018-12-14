#include "../header/Output_Redirect.h"
#include "../header/command.h"
#include "../header/base.h"


#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <fcntl.h>

bool singleOutputRedirect :: execute() {
    int fd, ret, status;
    pid_t pid = fork();

    //most of this is the same as input redirection
    if(pid < 0) {
        perror("Error in forking process");
        exit(1);
        return false;
    }    
    else if(!pid) {
        Command *c = (Command*)right;
        //writing to output file
        //man pages to get arguments
        fd = open(c->getFirstArgument(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR); 
        if (fd < 0) {
            perror("Open Failure");
            exit(1); //EXIT_FAILURE
            return false;
        }
        //it is one because 1 stands for stdout
        //https://www.youtube.com/watch?v=EqndHT606Tw
        ret = dup2(fd, 1);
        if (ret < 0) {
            perror("dup2");
            exit(1);
            return false;
        }
        if (close(fd) < 0) {
            perror("Close Failure");
            exit(1);
            return false;
        }
        if (!left->execute()) { //if command doesnt work
            exit(1);
            return false;
        }
        exit(0);
        return true;
    }
    else { //copying from command.cpp
        do {
            waitpid(pid, &status, 0);
        } while (WIFEXITED(status) == -1);
    }
    return (!WEXITSTATUS(status));



}

bool doubleOutputRedirect :: execute() {
    int fd, ret, status;
    pid_t pid = fork();

    //most of this is the same as input redirection
    if(pid < 0) {
        perror("Error in forking process");
        exit(1);
        return false;
    }    
    else if(!pid) {
        Command *c = (Command*)right;
        //writing to output file
        //man pages to get arguments
        //i guess it just appends?
        fd = open(c->getFirstArgument(), O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR); 
        if (fd < 0) {
            perror("Open Failure");
            exit(1); //EXIT_FAILURE
            return false;
        }
        //it is one because 1 stands for stdout
        //https://www.youtube.com/watch?v=EqndHT606Tw
        ret = dup2(fd, 1);
        if (ret < 0) {
            perror("dup2");
            exit(1);
            return false;
        }
        if (close(fd) < 0) {
            perror("Close Failure");
            exit(1);
            return false;
        }
        if (!left->execute()) { //if command doesnt work
            exit(1);
            return false;
        }
        exit(0);
        return true;
    }
    else { //copying from command.cpp
        do {
            waitpid(pid, &status, 0);
        } while (WIFEXITED(status) == -1);
    }
    return (!WEXITSTATUS(status));



}
