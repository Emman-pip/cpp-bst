#include <cmath>
#include <iostream>
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
  bool insertBack(int value, Node *node) {
    if (node == NULL || node->data == value) {
      return 0;
    } else if (node->data > value && node->left == NULL) {
      Node *newnode = new Node(value);
      node->left = newnode;
      return 1;
    } else if (node->data < value && node->right == NULL) {
      Node *newnode = new Node(value);
      node->right = newnode;
      return 1;
    } else if (node->data > value) {
      return insertBack(value, node->left);
    } else if (node->data < value) {
      return insertBack(value, node->right);
    }
    return 1;
  };

public:
  Node *root;
  Tree(vector<int> arr) { this->root = buildTree(arr); };
  bool insert(int value) { return this->insertBack(value, root); };
  // create the delete node functionality
  bool deleteNode(int value) { return false; };
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
  tree->insert(30);
  tree->insert(10);
  tree->insert(-80);
  prettyPrint(tree->root);

  return 0;
}
