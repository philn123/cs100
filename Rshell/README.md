# Assignment 4: RSHELL

## Introduction
**RShell** is a program developed in C++ with standard libraries from the C++11 standard that emulates the Bash shell. It has some similiar functionality to bash with being able to execute single commands, executing commands with comments, and chaining commands together with connector operators (`&&`, `||`, `;`); where these commands are located in `/bin/` . We achieved this by utilizing a composite pattern to design our shell, where the connector class is the composite and the command class is the leaf. Additionally, by utilizing parentheses, we can change the precedence of our commands and Rshell will run them in the order dictated by the parentheses. It also implements the test command, where it can determine whether a file or directory exists. The latest revision now supports I/O redirection with single input redirect '<', single and double output redirect '>' and '>>'. Alongside pipe '|' which allows us to chain outputs of commands into inputs of other commands.

## Instructions 

Clone it from git repo:

```console
git clone https://github.com/cs100/assignment-1-you_would_not_believe_your_eyes.git
```

CD into assignment folder:
```console
cd assignment-1-you_would_not_believe_your_eyes/
```

Checkout the HW4 Tag:
```console
git checkout tags/hw4
```

Initialize Google Test:
```console
git submodule init
git submodule update
```

Run CMake:

```console
cmake3 .
```

Compile:

```console
make
```

There will be two executables in the root directory `rshell` and `test`:

```console
./rshell 
./test
```

## Overview of Design Document Updates and Changes

- Updated UML diagram for assignment 4 with new connectors and functions
- Update Class Description to include I/O redirection classes
- Updated our roadblocks section 
- Updated Coding Strategy


## Bugs and Complications

- `help` command returns permission denied
- Rshell does not implement quotations. Echo "#" will not print out the #
- `cd` command does not run in **Rshell**
- `echo hello &&` does not request for an input after the `&&` connector, it returns an error
- `&&` and `||` do not work if the user enters a single one like `&`
- typing three or more connectors like `;;;` will not work with the program, this applies to the other connectors.
- typing `;` will output an error message
- typing `echo;;` will output an error message
- if the user enters () with nothing inside, it will output own error message
- entering test alone will return false and now will print out (False)
- these new commands will not work with spaces
- on Phillip's hammer server, the pipe command does not work due to unavailable resources
- pinging a server will not work on hammer, such as ping google, program will just wait
- entering a single redirection connector with one argument will display an error
- Rshell does not support stderr redirection
- exit commands will not exit the program when used as argument with redirection operators, such as exit < Makefile, or exit > new.txt
- gtest has commands that create new files, but they also delete the files afterwards so you will not see them

 
## Contributors

Phillip Nguyen

Fangsheng Chao
