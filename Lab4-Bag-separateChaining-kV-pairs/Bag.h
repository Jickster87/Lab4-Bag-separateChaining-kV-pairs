#pragma once
//DO NOT INCLUDE BAGITERATOR
#include <utility>

//DO NOT CHANGE THIS PART
#define NULL_TVALUE -111111
#define NULL_TELEM -111111
//def key, def value, def pair = k + v
typedef int TElem;
typedef int TFreq;
typedef std::pair <TElem, TFreq> TPair;
#define NULL_TPAIR pair<TKey, TFreq>(-111111,-111111)


class BagIterator;
class Bag {
    
private:
	//Node struct DLL
    struct Node {
        TPair elemz;
        Node * next;
        Node * prev;
        Node (const TPair& e): elemz(e), next(nullptr), prev(nullptr) {};
    };
    //node struct pointer to array of pointers (heads of all separate chains for array indexes?)
    Node ** pointersTable;
    int sizeBag;
    int maxCapacity;
    float alphaLoadFactor;
    int h(int elem) const;

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
    
    void resize();
    void updateAlphaLoad();
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};
