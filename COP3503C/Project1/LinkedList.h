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
  unsigned int nodeCount;

  // Default constructor. How many nodes in an empty list? (Answer: 0) What is head pointing to? What is tail pointing to? (Answer: nullptr) Initialize your variables! 
  LinkedList() {
  head = tail = nullptr;
  nodeCount = 0;
  };

  // Sets “this” to a copy of the passed in LinkedList. For example, if the other list has 10 nodes, with values of 1-10? “this” should have a copy of that same data. 
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
    Clear();
  };

// Insertion
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
    newNode->next = nullptr;
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

  // Given a pointer to a node, create a new node to store the passed in value, after the indicated node.
  void InsertAfter(Node* node, const T& data) {
    if (node == nullptr) {
      AddHead(data);
    } else if (node == tail) {
      AddTail(data);
    } else {
      Node *newNode = new Node(data);
      newNode->next = node->next;
      newNode->prev = node;
      node->next->prev = newNode;
      node->next = newNode;
      nodeCount++;
    }
  };

  // Ditto, except insert the new node before the indicated node.
  void InsertBefore(Node* node, const T& data) {
    if (node == nullptr) {
      AddTail(data);
    } else if (node == head) {
      AddHead(data);
    } else {
      Node *newNode = new Node(data);
      newNode->next = node;
      newNode->prev = node->prev;
      node->prev->next = newNode;
      node->prev = newNode;
      nodeCount++;
    }
  };

  // Inserts a new Node to store the first parameter, at the index-th location. So if you specified 3 as the index, the new Node should have 3 Nodes before it. Throws an out_of_range exception if given an invalid index. 
  void InsertAt(const T& data, unsigned int index) {
    if (index > nodeCount) {
      throw out_of_range("");
    }
    if (index == 0) {
      AddHead(data);
    } else if (index == nodeCount) {
      AddTail(data);
    } else {
      Node *temp = head;
      for (unsigned int i = 0; i < index; i++) {
        temp = temp->next;
      }
      InsertBefore(temp, data);
    }
  };

// Removal
  // Deletes the first Node in the list. Returns whether or not the Node was removed.
  bool RemoveHead() {
    if (head == nullptr) {
      return false;
    } else if (head == tail) {
      delete head;
      head = tail = nullptr;
      nodeCount--;
      return true;
    } else {
      Node *temp = head;
      head = head->next;
      head->prev = nullptr;
      delete temp;
      nodeCount--;
      return true;
    }
  };
  
  // Deletes the last Node, returning whether or not the operation was successful. 
  bool RemoveTail() {
    if (head == nullptr) {
      return false;
    } else if (head == tail) {
      delete head;
      head = tail = nullptr;
      nodeCount--;
      return true;
    } else {
      Node *temp = tail;
      tail = tail->prev;
      tail->next = nullptr;
      delete temp;
      nodeCount--;
      return true;
    }
  };

  // Remove ALL Nodes containing values matching that of the passed-in. Returns how many instances were removed. 
  unsigned int Remove(const T& value) {
    int count = 0;
    Node* temp2 = head;
    while (temp2 != nullptr) {
      if (temp2->data == value) {
        if (temp2 == head) {
          RemoveHead();
          temp2 = head;
        }
        else if (temp2 == tail) {
          RemoveTail();
          temp2 = nullptr;
        }
        else {
          Node* temp = temp2;
          temp2 = temp2->next;
          temp->prev->next = temp2;
          temp2->prev = temp->prev;
          delete temp;
          nodeCount--;
        }
        count++;
      }
      else {
        temp2 = temp2->next;
      }
   }
    return count;
  };

  // Deletes the index-th Node from the list, returning whether or not the operation was successful.
  bool RemoveAt(unsigned int index) {
    if (index >= nodeCount) {
      return false;
    }
    if (index == 0) {
      RemoveHead();
    } else if (index == nodeCount - 1) {
      RemoveTail();
    } else {
      Node *temp = head;
      for (unsigned int i = 0; i < index; i++) {
        temp = temp->next;
      }
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
      delete temp;
      nodeCount--;
    }
    return true;
  };

  // Deletes all Nodes. Don’t forget the node count how many nodes do you have after you deleted all of them?
  void Clear() {
    Node *temp = head;
    while (temp != nullptr) {
      Node *temp2 = temp;
      temp = temp->next;
      delete temp2;
    }
    head = tail = nullptr;
    nodeCount = 0;
  }

    // How many things are stored in this list? 
    unsigned int NodeCount() const {
      return nodeCount;
    };

// Behaviors

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

  // This function takes in a pointer to a Node—a starting node. From that node, recursively visit each node that follows, in forward order, and print their values. This function MUST be implemented using recursion, or tests using it will be worth no points. Check your textbook for a reference on recursion. 
  void PrintForwardRecursive(Node* node) const {
    if (node == nullptr) {
      return;
    }
    cout << node->data << endl;
    PrintForwardRecursive(node->next);
  };

  // Same deal as PrintForwardRecursive, but in reverse.
  void PrintReverseRecursive(Node* node) const {
    if (node == nullptr) {
      return;
    }
    cout << node->data << endl;
    PrintReverseRecursive(node->prev);
  };


// Accessors
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
  Node* Find(const T& data) const {
    Node *temp = head;
    while (temp != nullptr) {
      if (temp->data == data) {
        return temp;
      }
      temp = temp->next;
    }
    return nullptr;
  };

  // Find all nodes which match the passed in parameter value, and store a pointer to that node in the passed in vector. Use of a parameter like this (passing a something in by reference, and storing data for later use) is called an output parameter. 
  void FindAll(vector<Node*>& outData, const T& value) const {
    Node *temp = head;
    while (temp != nullptr) {
      if (temp->data == value) {
        outData.push_back(temp);
      }
      temp = temp->next;
    }
  };

// Operators
  // Overloaded subscript operator. Takes an index, and returns data from the index-th node. Throws an out_of_range exception for an invalid index. Const and non-const versions. 
  const T& operator[](unsigned int index) const;
  T& operator[](unsigned int index) {
    if (index >= nodeCount) {
      throw out_of_range("");
    }
    Node *temp = head;
    for (unsigned int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  };

  // Overloaded equality operator. Given listA and listB, is listA equal to listB? What would make one Linked List equal to another? If each of its nodes were equal to the corresponding node of the other. (Similar to comparing two arrays, just with non-contiguous data). 
  bool operator==(const LinkedList<T>& rhs) const {
    if (nodeCount != rhs.nodeCount) {
      return false;
    }
    Node *temp = head;
    Node *temp2 = rhs.head;
    while (temp != nullptr) {
      if (temp->data != temp2->data) {
        return false;
      }
      temp = temp->next;
      temp2 = temp2->next;
    }
    return true;
  };

  // Assignment operator. After listA = listB, listA == listB is true. Can of your existing functions to make write this one? (Hint: Yes you you utilize any can.) 
  LinkedList<T>& operator=(const LinkedList<T>& rhs) {
    if (this == &rhs) {
      return *this;
    }
    Node *temp = head;
    while (temp != nullptr) {
      Node *temp2 = temp;
      temp = temp->next;
      delete temp2;
    }
    head = tail = nullptr;
    nodeCount = 0;
    temp = rhs.head;
    while (temp != nullptr) {
      AddTail(temp->data);
      temp = temp->next;
    }
    return *this;
  };

};
#endif