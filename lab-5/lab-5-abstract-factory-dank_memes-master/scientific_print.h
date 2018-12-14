#ifndef _SCIENTIFICPRINT_H_
#define _SCIENTIFICPRINT_H_
#include <iostream>
#include "basePrint.h"
using namespace std;

class ScientificPrint : public BasePrint{
	private:
	    double value;

	public:
	    ScientificPrint(){};
	    ScientificPrint(double val):value(val){};
	
	    void print(){
		ios_base::fmtflags f( cout.flags() );
	        cout << scientific << value;
		cout.flags( f );
                //https://stackoverflow.com/questions/2273330/restore-the-state-of-stdcout-after-manipulating-it
	    }
};

#endif
