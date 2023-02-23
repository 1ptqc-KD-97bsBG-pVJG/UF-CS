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

    // Create a new Node at the front of the list to store the passed in parameter.
    void AddHead(const T& data) {
      Node *newNode = new Node(data);
      newNode->next = newNode->prev = nullptr;
      // check if list is empty
      if (head == nullptr) {
        head = tail = newNode;
      } else {
        newNode->next = head;
        newNode->prev = newNode;
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
      for (unsigned int i = 0; i < count; i++) {
        AddHead(data[i]);
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
};
#endif