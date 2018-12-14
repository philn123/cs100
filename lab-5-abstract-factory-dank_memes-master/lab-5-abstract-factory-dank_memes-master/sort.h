#pragma once
class Container;

class Sort {
	public:
        /* Constructors */
		Sort(){};

        /* Pure Virtual Functions */
		virtual void sort(Container* container) = 0;
};
