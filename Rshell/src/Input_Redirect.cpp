#include "../header/base.h"
#include "../header/Input_Redirect.h"
#include "../header/command.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <fcntl.h>

bool InputRedirect::execute() {
    //https://www.youtube.com/watch?v=fL-zXw_oLbw 
    //main source, had to change quite a few things
    //tried checking close just in case
    int fd;
    int ret;
    pid_t pid = fork();
    int status;

    if(pid < 0) {
        perror("Error in forking process");
        exit(1);
        return false;
    }    
    else if(!pid) {
        //had to convert to command type or it would not work
        Command *c = (Command*)right;
        fd = open(c->getFirstArgument(), O_RDONLY); //using read only
        if (fd < 0) {
            perror("Open Failure");
            exit(1); //EXIT_FAILURE
            return false;
        }
        //not sure why it has to be zero
        ret = dup2(fd, 0);
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
