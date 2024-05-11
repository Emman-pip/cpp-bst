#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

struct Node {
  int data;
  Node *left = NULL;
  Node *right = NULL;
  Node(int value, Node *left = NULL, Node *right = NULL) {
    this->left = left;
    this->right = right;
    this->data = value;
  }
};

class Tree {
private:
  Node *buildTree(vector<int> arr) {
    if (arr.size() == 0) {
      Node *nul = NULL;
      return nul;
    }
    int mid = ceil(arr.size() / 2);
    vector<int> right;
    vector<int> left;

    if (mid == 1) {
      right = vector<int>(arr.begin() + mid + 1, arr.end());
      left = vector<int>(arr.begin(), arr.end() - mid);
    } else {
      left = vector<int>(arr.begin(), arr.end() - mid - 1);
      right = vector<int>(arr.begin() + mid + 1, arr.end());
    }
    Node *root = new Node(arr[mid], buildTree(left), buildTree(right));
    return root;
  }

  // optimize this. Make one function.
  Node *insertBack(int value, Node *node) {
    if (node == NULL) {
      Node *newnode = new Node(value);
      return newnode;
    } else if (value < node->data) {
      node->left = insertBack(value, node->left);
    } else if (value > node->data) {
      node->right = insertBack(value, node->right);
    }
    return node;
  };

public:
  Node *root;
  Tree(vector<int> arr) { this->root = buildTree(arr); };
  bool insert(int value) { return this->insertBack(value, root); };
  // create the delete node functionality
  bool deleteNode(int value) {
    // save the prev, direction, and the current node
    Node *prev = NULL;
    Node *current = root;
    bool isLeft;
    // loop to find the node
    while (current->data != value) {
      prev = current;
      if (current->data > value) {
        current = current->left;
        isLeft = true;
        continue;
      }
      current = current->right;
      isLeft = false;
    }
    if (!current)
      return false;

    // do with multiple chilren
    if (current->left && current->right) {
      cout << "Di pa nagagawa toh. " << endl;
    }
    // do with one child
    else if (current->left) {
      (isLeft) ? prev->left = current->left : prev->right = current->left;

    } else if (current->right) {
      (isLeft) ? prev->left = current->right : prev->right = current->right;
    }
    // do with no child -- DONE
    else {
      (isLeft) ? prev->left = NULL : prev->right = NULL;
    }
    return true;
  };
};

void prettyPrint(Node *node, string prefix = "", bool isLeft = true) {
  if (!node) {
    return;
  }
  if (node->right) {
    prettyPrint(node->right, prefix + (isLeft ? "|   " : "    "), false);
  }
  cout << prefix << (isLeft ? "└── " : "┌── ") + to_string(node->data) << endl;
  if (node->left) {
    prettyPrint(node->left, prefix + (isLeft ? "    " : "|   "), true);
  }
}
int main() {
  vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 3289};
  Tree *tree = new Tree(arr);
  tree->insert(20);
  tree->insert(10);
  tree->insert(0);
  tree->insert(30);
  tree->insert(10);
  tree->insert(-80);
  cout << tree->deleteNode(4) << endl;
  cout << tree->deleteNode(10) << endl;
  cout << tree->deleteNode(3289) << endl;
  prettyPrint(tree->root);

  return 0;
}
