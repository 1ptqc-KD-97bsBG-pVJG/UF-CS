#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class AVLTree {
  private:
    struct Node {
      string name;
      string id;
      int height = 1;
      Node* left = nullptr;
      Node* right = nullptr;
      // Id set as string to handle leading zeros
      Node(string name, string id) : name(name), id(id) {}
    };
    Node* root = nullptr;
    int height(Node* node);
    int updateHeight(Node* node);
    int balanceFactor(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    Node* insertNodeHelper(Node* node, string name, string id);
    Node* removeNode(Node* node, string name);
    Node* findNodeById(Node* node, string id);
    Node* removeNodeHelper(Node* node, string id);
    vector<Node*>inOrderTransversal(Node* node, vector<Node*> &nodes);
    vector<Node*>preOrderTransversal(Node* node, vector<Node*> &nodes);
    vector<Node*>postOrderTransversal(Node* node, vector<Node*> &nodes);
    Node* balance(Node* node);
    void searchNameHelper(Node* node, string name, vector<Node*>& nodes);

  public:
    AVLTree();
    ~AVLTree();
    void destroyTree(Node* node);
    void insertNode(string name, string id);
    void searchId(string id);
    void searchName(string name);
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    void printLevelCount();
    void removeNode(string id);
    void removeInOrder(int num);
    };