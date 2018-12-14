#include <string>
#include <sstream>
#include "visitor.h"
#include "composite.h"
#include <iostream>


using namespace std;

void PrintVisitor :: rootNode () {}

void PrintVisitor :: sqrNode() {
    output += "^2 ";
}

void PrintVisitor :: multNode() {
    output += "* ";
}

void PrintVisitor :: subNode() {
    output += "- ";
}

void PrintVisitor :: addNode() {
    output += "+ ";
}

void PrintVisitor :: opNode(Op *op) {
    ostringstream ss;
    ss << op->evaluate();
    output = output + ss.str() + " ";
}

void PrintVisitor :: execute() {
    cout << output << endl;
}
