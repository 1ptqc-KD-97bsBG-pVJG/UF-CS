// Ways to add information to the container

// AddHead()
// AddTail()
// AddNodesHead()
// AddNodesTail()
// A way to get some information about the container

// NodeCount()
// Ways to see the data in the container

// PrintForward()
// PrintReverse()
// And some essentials for any class

// Default constructor
// Destructor (other members of the Big Three will come later)
// This project will use the memory leak detection functionality contained in leaker.h and leaker.cpp from the previous assignment. Be sure to delete all of the container's nodes in the destructor!

#include <iostream>

class Node {
  public:
    int data;
    Node* next;
    Node(int data = 0, Node* next = nullptr) {
        this->data = data;
        this->next = next;
    }
};

class LinkedList {
  private:
    Node* head;
    Node* tail;
    int nodeCount;

  public:
    // default constructor
    LinkedList() {

    }

    // destructor
    ~LinkedList() {

    }

    // AddHead
    AddHead() {

    }

    // AddTail
    AddTail() {

    }
};