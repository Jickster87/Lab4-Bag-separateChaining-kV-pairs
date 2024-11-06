#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
    int currentPos;
    Bag::Node * currentNode;
    int currentFrequency;

	BagIterator(const Bag& c);
public:
	void first();
    void move();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
