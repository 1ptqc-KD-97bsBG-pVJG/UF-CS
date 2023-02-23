#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>
#include <vector>
using namespace std;


template <typename T>
class LinkedList {

  public:
    class Node {
      public:
        T data;
        Node *next;
        Node *prev;
        // not sure about this line
       Node(const T& d = T{}, Node* n = nullptr, Node* p = nullptr) : data{ d }, next{ n }, prev{ p } {}
    };
  Node *head;
  Node *tail;
  int nodeCount;


    // Default constructor. How many nodes in an empty list? (Answer: 0) What is head pointing to? What is tail pointing to? (Answer: nullptr) Initialize your variables! 
    LinkedList() {
    head = tail = nullptr;
    nodeCount = 0;
    };

    LinkedList(const LinkedList<T>& list) {
      head = tail = nullptr;
      nodeCount = 0;
      Node* temp = list.head;
      while (temp != nullptr) {
        AddTail(temp->data);
        temp = temp->next;
      }
    };

    // The usual. Clean up your mess. (Delete all the nodes created by the list.)
    ~LinkedList() {
      Node *temp = head;
      while (temp != nullptr) {
        Node *temp2 = temp;
        temp = temp->next;
        delete temp2;
      }
      head = tail = nullptr;
      nodeCount = 0;
    };

    void AddHead(const T& data) {
        Node *newNode = new Node(data);
        newNode->next = newNode->prev = nullptr;
        // check if list is empty
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        nodeCount++;   
    };


    // Create a new Node at the end of the list to store the passed in parameter.
    void AddTail(const T& data) {
      Node *newNode = new Node(data);
      newNode->next = newNode->prev = nullptr;
      // check if list is empty
      if (head == nullptr) {
        head = tail = newNode;
      } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
      }
      nodeCount++;
    };

    // Given an array of values, insert a node for each of those at the beginning list, maintaining the original order. 
    void AddNodesHead(const T* data, unsigned int count) {
      for (unsigned int i = count - 1; i > 0; i--) {
        AddHead(data[i]);
      }
      if (count > 0) {
          AddHead(data[0]);
      }
    };

    // Ditto, except adding to the end of the list.
    void AddNodesTail(const T* data, unsigned int count) {
      for (unsigned int i = 0; i < count; i++) {
        AddTail(data[i]);
      }
    };

    // How many things are stored in this list? 
    unsigned int NodeCount() const {
      return nodeCount;
    };

    // Iterator through all of the nodes and print out their values, one a time. 
    void PrintForward() const {
      Node *temp = head;
      while (temp != nullptr) {
        cout << temp->data << endl;
        temp = temp->next;
      }
    };

    // Print out the values in reverse order.
    void PrintReverse() const {
      Node *temp = tail;
      while (temp != nullptr) {
        cout << temp->data << endl;
        temp = temp->prev;
      }
    };

// Instructions
  // In this part you will implement various functions to access parts of the container:

  // Getting the head and tail nodes:

  // Head()
  // Tail()
  // Getting a specific node based on an index--allowing this container to be used as though it were an array**

  // GetNode()
  // operator[]()
  // Finding the FIRST node based on a value

  // Find()
  // Finding ALL nodes based on a value

  // FindAll
  // You will also implement the other two members of the Big Three

  // The copy constructor
  // The copy assignment operator

// accessors
  Node* Head() {
    return head;
  };

  const Node* Head() const {
    return head;
  };

  Node* Tail() {
    return tail;
  };

  const Node* Tail() const {
    return tail;
  };

  // Given an index, return a pointer to the node at that index. Throws an exception of type out_of_range if the index is out of range. Const and non-const versions. 
  Node* GetNode(unsigned int index) {
    if (index >= nodeCount) {
      throw out_of_range("");
    }
    Node *temp = head;
    for (unsigned int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp;
  };

  const Node* GetNode(unsigned int index) const{
    if (index >= nodeCount) {
      throw out_of_range("");
    }
    Node *temp = head;
    for (unsigned int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp;
  };

  // Find the first node with a data value matching the passed in parameter, returning a pointer to that node. Returns nullptr if no matching node found.  
  Node* Find(const T& data) {
    Node *temp = head;
    while (temp != nullptr) {
      if (temp->data == data) {
        return temp;
      }
      temp = temp->next;
    }
    return nullptr;
  };

// Operators
  // Overloaded subscript operator. Takes an index, and returns data from the index-th node. Throws an out_of_range exception for an invalid index. Const and non-const versions. 
  const T& operator[](unsigned int index) const {
    if (index >= nodeCount) {
      throw out_of_range("");
    }
    Node *temp = head;
    for (unsigned int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  };

};
#endif