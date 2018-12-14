#include "container.h"
#include "sort.h"
//using namespace std;
class SelectionSort : public Sort {
	
	public:
		SelectionSort(){};
		void sort(Container* container) {
                    for (int i = 0; i < container->size() - 1; i++) {
                        int smallest = i;
                        double value = container->at(i)->evaluate();
                        for (int j = i + 1; j < container->size(); j++) {
                            if (container->at(j)->evaluate() < value) {
                                value = container->at(j)->evaluate();
                                smallest = j;
                            }
                        }
                        container->swap(i, smallest);
                    }
                }
};	
