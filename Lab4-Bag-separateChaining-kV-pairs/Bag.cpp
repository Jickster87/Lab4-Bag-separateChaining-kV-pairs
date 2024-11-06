#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

///ADT Bag – using a hashtable with separate chaining in which
///(unique ELEMENT, FREQUENCY)
///pairs are stored.


Bag::Bag() {
    maxCapacity = 31; //starting cap
    pointersTable = new Node * [maxCapacity];
    sizeBag = 0;
    alphaLoadFactor = 0.0f;
}

int Bag::h(TElem elem) const {
    return (abs(elem) % maxCapacity + maxCapacity) % maxCapacity; // Ensures a positive index
}

void Bag::resize() {
    int newCapacity = maxCapacity * 2;
    Node ** newTable = new Node * [newCapacity];
    //mark all nodes inside new pointer array to nullptr
    for (int i = 0; i<newCapacity; i++) {
        newTable[i] = nullptr;
    }
    for (int i = 0; i < maxCapacity; i++) {
        Node * nomad = pointersTable[i];
        while (nomad != nullptr) {
            int newInd = h(nomad->elemz.first);
            Node * nextNomad = nomad->next;
            nomad->next = newTable[newInd];
            newTable[newInd] = nomad;
            nomad = nextNomad;
        }
    }
    maxCapacity = newCapacity;
    delete [] pointersTable;
    pointersTable = newTable;
    updateAlphaLoad();
    
}

void Bag::updateAlphaLoad() {
    alphaLoadFactor = static_cast<float>(sizeBag) / maxCapacity;
}


void Bag::add(TElem elem) {
    if (alphaLoadFactor > 0.7) {
        resize();
    }

    int posLocator = h(elem);
    Node* current = pointersTable[posLocator];

    // Traverse the chain to find if the element already exists
    while (current != nullptr) {
        if (current->elemz.first == elem) {
            current->elemz.second++;  // Increment frequency if element exists
            sizeBag++;  // Update total size
            updateAlphaLoad();
            return;
        }
        current = current->next;
    }

    // Element not found, insert as a new node at the head of the chain
    TPair newElem = std::make_pair(elem, 1);  // key with initial frequency of 1
    Node* newNode = new Node(newElem);
    newNode->next = pointersTable[posLocator];
    pointersTable[posLocator] = newNode;

    sizeBag++;  // Update total size
    updateAlphaLoad();
}

///
bool Bag::remove(TElem elem) {
    int posLocator = h(elem);
    Node* current = pointersTable[posLocator];
    Node* previous = nullptr;

    // Traverse the chain to find the element
    while (current != nullptr && current->elemz.first != elem) {
        previous = current;
        current = current->next;
    }

    // Element not found
    if (current == nullptr) {
        return false;
    }

    // Decrement frequency
    current->elemz.second--;

    // If frequency is now zero, remove the node
    if (current->elemz.second == 0) {
        if (previous == nullptr) {
            // The node to remove is the first in the chain
            pointersTable[posLocator] = current->next;
        } else {
            // The node to remove is in the middle or end of the chain
            previous->next = current->next;
        }
        delete current; // Free the memory for the removed node
    }

    sizeBag--; // Decrement the size of the bag
    updateAlphaLoad(); // Update load factor
    return true;
}
///my old
//bool Bag::remove(TElem elem) {
//	
//    int posLocator = h(elem);
//    Node* current = pointersTable[posLocator];
//
//    while (current != nullptr && current->elemz.first != elem) {
//        current = current->next;
//    }
//    
//    //not found
//    if (current == nullptr) {
//          return false;
//      }
//
//    current->elemz.second--;
//    //now if elemz.second(aKa frequency is 0) remove pairNode
//    if (current->elemz.second == 0) {
//        if (current->prev == nullptr) {
//            // Removing the first node in the chain
//            pointersTable[posLocator] = current->next;
//        } else {
//            // Removing a node that is not the first
//            current->prev->next = current->next;
//        }
//        delete current; // Free the memory for the removed node
//    }
//    
//    sizeBag--; // Decrement the size of the bag
//    updateAlphaLoad(); // Update load factor
//	return true;
//}


bool Bag::search(TElem elem) const {
    int posLocator = h(elem);
    Node * nomad = pointersTable[posLocator];
    while (nomad != nullptr) {
        if (nomad->elemz.first == elem) {
            return true;
        }
        nomad = nomad->next;
    }
	return false;
}

int Bag::nrOccurrences(TElem elem) const {
    int posLocator = h(elem);
    Node* nomad = pointersTable[posLocator];
    while (nomad != nullptr) {
        if (nomad->elemz.first == elem) {
            return nomad->elemz.second;  // Return the frequency directly
        }
        nomad = nomad->next;
    }
    return 0;  // Return 0 if the element is not found
}


int Bag::size() const {
    return sizeBag;
}


bool Bag::isEmpty() const {
    return sizeBag == 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
    for (int i = 0; i < maxCapacity; i++) {
        Node * nomad = pointersTable[i];
        while (nomad != nullptr) {
            Node * terminator = nomad;
            nomad = nomad->next;
            delete terminator;
        }
    }
    delete [] pointersTable;
}
