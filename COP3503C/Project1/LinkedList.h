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

    // Given an array of values, insert a node for each of those at the beginning list, maintaining the original order. 
    void AddNodesHead(const T& data, int count) {
      for (int i = count - 1; i >= 0; i--) {
        AddHead(data[i]);
      }
    }

    // Ditto, except adding to the end of the list.
    void AddNodesTail(const T& data, int count) {
      for (int i = 0; i < count; i++) {
        AddTail(data[i]);
      }
    }

    // How many things are stored in this list? 
    int NodeCount() const {
      return nodeCount;
    }

    // Iterator through all of the nodes and print out their values, one a time. 
    void PrintForward() const {
      Node* temp = head;
      while (temp != nullptr) {
        std::cout << temp -> data << std::endl;
        temp = temp -> next;
      }
    }

    // Print out the values in reverse order. (doesn't work now)
    void PrintReverse() const {
      Node* temp = tail;
      while (temp != nullptr) {
        std::cout << temp->data << std::endl;
        temp = temp->next;
      }
    }
};