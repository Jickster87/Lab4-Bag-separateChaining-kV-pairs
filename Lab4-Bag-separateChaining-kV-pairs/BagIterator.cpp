#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

void BagIterator::move(){
    while (currentPos < bag.maxCapacity && bag.pointersTable[currentPos] == nullptr) {
        currentPos++;
    }
    if (currentPos<bag.maxCapacity) {
        currentNode = bag.pointersTable[currentPos];
        currentFrequency = 0;
    } else {currentNode = nullptr;}
}

BagIterator::BagIterator(const Bag& c): bag(c)
{
    currentPos = 0;
    currentFrequency = 0;
    currentNode = nullptr;
    
    //skip as long as lower than maxcap and is no Node in index
    move();
}

void BagIterator::first() {
    currentPos = 0;
    currentNode = nullptr;
    currentFrequency = 0;
    move();
  
}


void BagIterator::next() {
    if (!valid()) {
        throw  exception();
    }
    if (currentFrequency < currentNode->elemz.second - 1) {
        currentFrequency++;
    } else {
        // Move to the next node in the chain
        currentNode = currentNode->next;
        currentFrequency = 0;

        if (currentNode == nullptr) {
            // Move to the next non-empty position in the table
            currentPos++;
            move();
        }
    }
    
}


bool BagIterator::valid() const {
    return currentPos < bag.maxCapacity && currentNode != nullptr;
}



TElem BagIterator::getCurrent() const
{
    if (!valid()) {
        throw exception();
    }
    return currentNode->elemz.first;
}
