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


// Code Structure As shown above, the Linked List class itself stores very little data: Pointers to the first and last nodes, 
// and a count. In some implementations, you might only have a pointer to the first node, and that’s it. In 
// addition to those data members, your Linked List class must conform to the following interface: 
 
 
 
// COP3503 Programming Fundamentals 2 
 
  
  
  
// Function Reference 
// Behaviors 
// PrintForward Iterator through all of the nodes and print out their values, one a time. 
// PrintReverse Exactly the same as PrintForward, except completely the opposite. 
// PrintForwardRecursive This function takes in a pointer to a Node—a starting node. From that node, 
// recursively visit each node that follows, in forward order, and print their values. 
// This function MUST be implemented using recursion, or tests using it will be 
// worth no points. Check your textbook for a reference on recursion. 
// PrintReverseRecursive Same deal as PrintForwardRecursive, but in reverse. 
// Accessors 
// NodeCount How many things are stored in this list? 
 
// COP3503 Programming Fundamentals 2 
// FindAll Find all nodes which match the passed in parameter value, and store a pointer to 
// that node in the passed in vector. Use of a parameter like this (passing a 
// something in by reference, and storing data for later use) is called an output 
// parameter. 
// Find Find the first node with a data value matching the passed in parameter, 
// returning a pointer to that node. Returns nullptr if no matching node found.  
// GetNode Given an index, return a pointer to the node at that index. Throws an exception 
// of type out_of_range if the index is out of range. Const and non-const versions. 
// Head Returns the head pointer. Const and non-const versions. 
// Tail Returns the tail pointer. Const and non-const versions. 
// Insertion Operations 
// AddHead Create a new Node at the front of the list to store the passed in parameter. 
// AddTail Create a new Node at the end of the list to store the passed in parameter. 
// AddNodesHead Given an array of values, insert a node for each of those at the beginning 
// list, maintaining the original order. 
// of the 
// AddNodesTail Ditto, except adding to the end of the list. 
// InsertAfter Given a pointer to a node, 
// the indicated node. 
// create a new node to store the passed in value, after 
// InsertBefore Ditto, except insert the new node before the indicated node. 
// InsertAt Inserts a new Node to store the first parameter, at the index-th location. So if 
// you specified 3 as the index, the new Node should have 3 Nodes before it. 
// Throws an out_of_range exception if given an invalid index. 
// Removal Operations 
// RemoveHead Deletes the first Node in the list. Returns whether or not the Node was removed. 
// RemoveTail Deletes the last Node, returning whether or not the operation was successful. 
// Remove Remove ALL Nodes containing values matching that of the passed-in 
// Returns how many instances were removed. 
// parameter. 
// RemoveAt Deletes the index-th Node from the list, returning whether or not the operation 
// was successful. 
// Clear Deletes all Nodes. Don’t forget the node count—how 
// after you deleted all of them? 
// many nodes do you have 
// Operators 
// operator[] Overloaded subscript operator. Takes an index, and returns data from the index-
// th node. Throws an out_of_range exception for an invalid index. Const and non-
// const versions. 
// operator= Assignment operator. After listA = listB, listA == listB is true. Can 
// of your existing functions to make write this one? (Hint: Yes you 
// you utilize any 
// can.) 
// operator== Overloaded equality operator. Given listA and listB, is listA equal to listB? What 
// would make one Linked List equal to another? If each of its nodes were equal to 
// the corresponding node of the other. (Similar to comparing two arrays, just with 
// non-contiguous data). 
// Construction / Destruction 
// LinkedList() Default constructor. How many nodes in an empty list? (Answer: 0) What is head 
// pointing to? What is tail pointing to? (Answer: nullptr) Initialize your variables! 
// Copy Constructor Sets “this” to a copy of the passed in LinkedList. For example, if the other list has 
// 10 nodes, with values of 1-10? “this” should have a copy of that same data. 
// ~LinkedList() The usual. Clean up your mess. (Delete all the nodes created by the list.)

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

template <typename T>
class LinkedList {
  private:
    Node* head;
    Node* tail;
    Node* curr;
    int nodeCount;

  public:
    // Default constructor. How many nodes in an empty list? (Answer: 0) What is head pointing to? What is tail pointing to? (Answer: nullptr) Initialize your variables! 
    LinkedList() {
    head = tail = curr = nullptr;
    nodeCount = 0;
    }

    // The usual. Clean up your mess. (Delete all the nodes created by the list.)
    ~LinkedList() {
      Node* temp = head;
      while (temp != nullptr) {
        Node* next = temp -> next;
        delete temp;
        temp = next;
      }
    }

    // Create a new Node at the front of the list to store the passed in parameter.
    void AddHead(const T& data) {
      Node* newNode = new Node(data);
      // check if list is empty
      if (head == nullptr) {
        head = tail = newNode;
      } else {
        newNode -> next = head;
        head = newNode;
      }
      nodeCount++;   
    }

    // Create a new Node at the end of the list to store the passed in parameter.
    void AddTail(const T& data) {
      Node* newNode = new Node(data);
      // check if list is empty
      if (head == nullptr) {
        head = tail = newNode;
      } else {
        tail -> next = newNode;
        tail = newNode;
      }
      nodeCount++;
    }
};