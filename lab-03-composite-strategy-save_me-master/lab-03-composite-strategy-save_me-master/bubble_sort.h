#include "container.h"
#include "sort.h"
#include "base.h"
#include <cstdlib>
class BubbleSort : public Sort{

    public:
        
        BubbleSort(){};
        void sort(Container *container){
            int s = container->size();
            bool swapped;
            for(int i = 0; i < s ; i++){
                swapped = false;
                for(int j = 0; j < s-i-1; j++){
                    if(container->at(j)->evaluate() < container->at(j+1)->evaluate()){
                        container->swap(j, j+1);              
                        swapped = true;  
                    }
                }
                if(!swapped)
                    break;
            }      

        }

};
