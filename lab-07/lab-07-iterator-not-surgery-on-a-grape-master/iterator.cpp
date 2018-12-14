#include <iostream>
#include "iterator.h"
#include "composite.h"
using namespace std;

//------OPERATOR_ITERATOR---
OperatorIterator::OperatorIterator(Base* ptr) : Iterator(ptr) {};

void OperatorIterator :: first() {
    current_ptr = self_ptr->get_left();
}

void OperatorIterator :: next() {
    if (current_ptr == self_ptr->get_left()) 
        current_ptr = self_ptr->get_right();
    else
        current_ptr = NULL;
}

bool OperatorIterator :: is_done() { 
    if (current_ptr)
        return false;
    
    return true;
}

Base* OperatorIterator :: current() {
    return current_ptr;
}


//-----UNARY_ITERATOR----
UnaryIterator :: UnaryIterator(Base* ptr) : Iterator(ptr) {};

void UnaryIterator :: first() { 
    current_ptr = self_ptr->get_left();
}

void UnaryIterator :: next() {
    current_ptr = NULL;
}

bool UnaryIterator :: is_done() {
    if(current_ptr)
        return false;
    
    return true;
}

Base* UnaryIterator :: current() {
    return current_ptr;
}

//

//--------NULL_ITERATOR------
NullIterator :: NullIterator(Base *ptr) : Iterator(ptr) {};

void NullIterator :: first() {
    return;
}
void NullIterator :: next() {
    return;
}
bool NullIterator :: is_done() {
    return true;
}
Base* NullIterator :: current() {
    return NULL;
}

//

//---------PREORDER_ITERATOR----

PreorderIterator :: PreorderIterator(Base* ptr) : Iterator(ptr) {};

void PreorderIterator::first() {
    // Empty the stack (just in case we had something leftover from another run)
    // Create an iterator for the Base* that we built the iterator for
    // Initialize that iterator and push it onto the stack

    while(!iterators.empty()) {
        iterators.pop();
    }
    Iterator *it = self_ptr->create_iterator();

    if(it) {
        it->first();
        iterators.push(it);
    }

}
void PreorderIterator::next() {
    // Create an iterator for the item on the top of the stack
    // Initialize the iterator and push it onto the stack
    // As long as the top iterator on the stack is_done(), pop it off the stack and then advance whatever iterator is now on top of the stack

    if(!iterators.empty()) {
        Iterator *it = iterators.top()->current()->create_iterator();
        it->first();
        iterators.push(it);
    
    //put the emoty first so it doesnt seg fault at the end
        while(!iterators.empty() && iterators.top()->is_done()) {
            iterators.pop();
        
            if(!iterators.empty())
                iterators.top()->next();

        }
    }

}

bool PreorderIterator::is_done() {
    // Return true if there are no more elements on the stack to iterate
    if(iterators.empty()) 
        return true;

    return false;
}

Base* PreorderIterator::current() {
    // Return the current for the top iterator in the stack
    if(!iterators.empty())
        return iterators.top()->current();

    return NULL;
}
