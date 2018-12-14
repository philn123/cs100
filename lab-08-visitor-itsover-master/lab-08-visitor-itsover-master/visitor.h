#pragma once
#include <string>
#include "composite.h"
#include "iterator.h"
#include <sstream>

using namespace std;

class Op;

class Visitor {
    public:
        Visitor(){};

	virtual void rootNode() = 0; //For visiting a root node (do nothing)
	virtual void sqrNode() = 0; //For visiting a square node
	virtual void multNode() = 0; //For visiting a multiple node
	virtual void subNode() = 0; //For visiting a subtraction node
	virtual void addNode() = 0; //For visiting an add node
	virtual void opNode(Op* op) = 0; //For visiting a leaf node

    	virtual void execute() = 0; //Prints all visited nodes

};


class PrintVisitor : public Visitor {
	private:
            std::string output;

	public:
	    PrintVisitor() : Visitor() {};

	    void rootNode();
	    void sqrNode();
	    void multNode();
	    void subNode();
	    void addNode();

	    void opNode(Op* op);
            //https://stackoverflow.com/questions/332111/how-do-i-convert-a-double-into-a-string-in-

    	    void execute();
};
