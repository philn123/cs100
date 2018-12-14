#include "../header/base.h"
#include "../header/Pipe.h"
#include "../header/command.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <fcntl.h>

bool Pipe :: execute() {
    //https://www.youtube.com/watch?v=uHH7nHkgZ4w
    int fds[2];
    int status;
    pid_t pid, pid2;


    int ret = pipe(fds);
    if(ret < 0) { //error
        perror("Pipe Error");
        exit(1);
        return false;
    }
    pid = fork();
    if(pid < 0) {
        perror("Error in forking process");
        exit(1);
        return false;
    }
    //https://stackoverflow.com/questions/37895274/c-in-unix-fork-waitpid-and-pipes
    //using pipe is only visible to the concerned processes, tried inherited pipe
    //tried using one fork already, it did not fully run gtests, so we had to fork twice

    if(pid == 0) { //returns 0 which means success
        pid2 = fork();

        if(pid2 < 0) {
            perror("Error fork");
            exit(1);
            return false;
        }
        else if(pid2  == 0) {

            if(dup2(fds[1], 1) < 0) {
                perror("dup2");
                exit(1);
                return false;
            } 
            if(close(fds[0]) < 0) { //we close the read side
                perror("Close Failure");
                exit(1);
                return false;
            }
            if(!left->execute()) {
                exit(1);
                return false;
            }
            exit(0);
        }
        else {
            if(dup2(fds[0], 0) < 0) {
                perror("dup2");
                exit(1);
                return false;
            } 
            if(close(fds[1]) < 0) { //closing the output side
                perror("Close Failure");
                exit(1);
                return false;
            }
            if(!right->execute()) {
                exit(1);
                return false;
            }
            exit(0);

        }
    }

        
    //close pipe at the end
    if (close(fds[0]) < 0 ) {
        perror("Close Failure");
        exit(1);
        return false;
    }
    if (close(fds[1]) < 0 ) {
        perror("Close Failure");
        exit(1);
        return false;
    }

    //we have to wait at the end or zombie children
    do {
        waitpid(pid, &status, 0);
    } while (WIFEXITED(status) == -1);

    return !WEXITSTATUS(status);
}
