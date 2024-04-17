#include "AVLTree.h"

AVLTree::AVLTree() {
  root = nullptr;
}

AVLTree::~AVLTree() {
  destroyTree(root);
}

void AVLTree::destroyTree(Node* node) {
  if (node == nullptr) {
    return;
  }
  // Recursively delete left and right subtrees
  destroyTree(node->left);
  destroyTree(node->right);
  delete node;
}

AVLTree::Node* AVLTree::rotateLeft(Node *node) {
  if (node == nullptr) {
    return node;
  }

  // Preform rotation
  Node* newRoot = node->right;
  node->right = newRoot->left;
  newRoot->left = node;

  // Update heights of both nodes
  updateHeight(node);
  updateHeight(newRoot);
  return newRoot;
}

AVLTree::Node* AVLTree::rotateRight(Node *node) {
  if (node == nullptr) {
    return node;
  }

  // Preform rotation
  Node* newRoot = node->left;
  node->left = newRoot->right;
  newRoot->right = node;

  // Update heights of both nodes
  updateHeight(node);
  updateHeight(newRoot);
  return newRoot;
}

AVLTree::Node* AVLTree::rotateLeftRight(Node *node) {

  // Rotate using rotation functions
  node->left = rotateLeft(node->left);
  return rotateRight(node);
}

AVLTree::Node* AVLTree::rotateRightLeft(Node *node) {

  // Rotate using rotation fucntions
  node->right = rotateRight(node->right);
  return rotateLeft(node);
}

int AVLTree::height(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return 1 + max(height(node->left), height(node->right));
}

int AVLTree::updateHeight(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  node->height = 1 + max(height(node->left), height(node->right));
  return node->height;
}

int AVLTree::balanceFactor(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return height(node->left) - height(node->right);
}


void AVLTree::insertNode(string name, string id) {
  root = insertNodeHelper(root, name, id);
}

AVLTree::Node* AVLTree::insertNodeHelper(Node* node, string name, string id) {
  if (node == nullptr) {
    return new Node(name, id);
  }
  // Check if id already exists
  else if (findNodeById(node, id) != nullptr) {
    cout << "unsuccessful" << endl;
  }
  // Id does not exist, find where to insert and insert
  else if (id < node->id) {
    node->left = insertNodeHelper(node->left, name, id);
  } else if (id > node->id) {
    node->right = insertNodeHelper(node->right, name, id);
  }
  // Update height and balance tree
  node->height = updateHeight(node);
  return balance(node);
}

void AVLTree::searchId(string id) {
  Node* node = findNodeById(root, id);
  if (node == nullptr) {
    cout << "unsuccessful" << endl;
  } else {
    cout << node->name << endl;
  }
}

void AVLTree::searchName(string name) {
  vector<Node*> nodes;
  searchNameHelper(root, name, nodes);
  if (nodes.empty()) {
    cout << "unsuccessful" << endl;
  } else {
    for (Node* node : nodes) {
      cout << node->id << endl;
    }
  }
}

void AVLTree::searchNameHelper(Node* node, string name, vector<Node*>& nodes) {
  if (node == nullptr) {
    return;
  } else if (name == node->name) {
    nodes.push_back(node);
  }
  searchNameHelper(node->left, name, nodes);
  searchNameHelper(node->right, name, nodes);
}

void AVLTree::removeNode(string id) {
  root = removeNodeHelper(root, id);
}

AVLTree::Node* AVLTree::removeNodeHelper(Node* node, string id) {
  if (node == nullptr) {
    return node;
  }
  if (id == node->id) {
    // Case when node is a leaf node
    if (node->left == nullptr && node->right == nullptr) {
      // Delete leaf node and return nullptr to parent
      delete node;
      return nullptr;
      // Case when node has only right child
    } else if (node->left == nullptr) {
      Node* temp = node->right;
      delete node;
      // Connect parent to right child
      return temp;
      // Case when node has only left child
    } else if (node->right == nullptr) {
      Node* temp = node->left;
      delete node;
      // Connect parent to left child
      return temp;
    } else {
      // Case when node has two children
      // Find inorder successor
      Node* temp = node->right;
      while (temp->left != nullptr) {
        // Traverse left subtree to find inorder successor
        temp = temp->left;
      }
      // Copy inorder successor's data to current node
      node->name = temp->name;
      node->id = temp->id;
      // Remove inorder successor from right subtree
      node->right = removeNodeHelper(node->right, temp->id);
      // Return updated node
      return node;
    }
  } else if (stoi(id) < stoi(node->id)) {
    node->left = removeNodeHelper(node->left, id);
  } else {
    node->right = removeNodeHelper(node->right, id);
  }
  return node;
}

void AVLTree::removeInOrder(int num) {
  vector<Node*> nodes;
  nodes = inOrderTransversal(root, nodes);
  if (num > nodes.size()) {
    cout << "unsuccessful" << endl;
  } else {
    removeNode(nodes[num]->id);
    cout << "successful" << endl;
  }
}

// Print comma separated inorder traversal of names in tree
void AVLTree::printInOrder() {
  vector<Node*> nodes;
  nodes = inOrderTransversal(root, nodes);
  for (int i = 0; i < nodes.size(); i++) {
    cout << nodes[i]->name;
    if (i != nodes.size() - 1) {
      cout << ", ";
    }
  }
  cout << endl;
}

void AVLTree::printPreOrder() {
  vector<Node*> nodes;
  nodes = preOrderTransversal(root, nodes);
  for (int i = 0; i < nodes.size(); i++) {
    cout << nodes[i]->name;
    if (i != nodes.size() - 1) {
      cout << ", ";
    }
  }
  cout << endl;
}

void AVLTree::printPostOrder() {
  vector<Node*> nodes;
  nodes = postOrderTransversal(root, nodes);
  for (int i = 0; i < nodes.size(); i++) {
    cout << nodes[i]->name;
    if (i != nodes.size() - 1) {
      cout << ", ";
    }
  }
  cout << endl;
}

void AVLTree::printLevelCount() {
  int levelCount = 0;
  vector<Node*> nodes;
  nodes = inOrderTransversal(root, nodes);
  for (int i = 0; i < nodes.size(); i++) {
    if (i == 0) {
      levelCount++;
    } else if (nodes[i]->height > nodes[i - 1]->height) {
      levelCount++;
    }
  }
  cout << levelCount << endl;
}

vector<AVLTree::Node*> AVLTree::inOrderTransversal(Node* node, vector<Node*> &nodes) {
  if (node == nullptr) {
    return nodes;
  }
  inOrderTransversal(node->left, nodes);
  nodes.push_back(node);
  inOrderTransversal(node->right, nodes);
  return nodes;
}

vector<AVLTree::Node*> AVLTree::preOrderTransversal(Node* node, vector<Node*> &nodes) {
  if (node == nullptr) {
    return nodes;
  }
  nodes.push_back(node);
  preOrderTransversal(node->left, nodes);
  preOrderTransversal(node->right, nodes);
  return nodes;
}

vector<AVLTree::Node*> AVLTree::postOrderTransversal(Node* node, vector<Node*> &nodes) {
  if (node == nullptr) {
    return nodes;
  }
  postOrderTransversal(node->left, nodes);
  postOrderTransversal(node->right, nodes);
  nodes.push_back(node);
  return nodes;
}

AVLTree::Node* AVLTree::findNodeById(Node* node, string id) {
  if (node == nullptr) {
      return nullptr;
  } else if (id == node->id) {
      return node;
  } else {
      // Recursively search left or right subtree based on id comparison
      return id < node->id ? findNodeById(node->left, id) : findNodeById(node->right, id);
  }
}

AVLTree::Node* AVLTree::balance(Node* node) {
  if (node == nullptr) {
    return node;
  }
  // Recursively balance left and right subtrees
  node->left = balance(node->left);
  node->right = balance(node->right);

  // Check balance factor and rotate if necessary
  int bf = balanceFactor(node);
  // Left heavy
  if (bf > 1) {
    if (balanceFactor(node->left) > 0) {
      node = rotateRight(node);
    } else {
      node = rotateLeftRight(node);
    }
  // Right heavy
  } else if (bf < -1) {
    if (balanceFactor(node->right) > 0) {
      node = rotateRightLeft(node);
    } else {
      node = rotateLeft(node);
    }
  }
  updateHeight(node);
  return node;
}