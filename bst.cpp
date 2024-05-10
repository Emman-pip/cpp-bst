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

public:
  Node *root;
  Tree(vector<int> arr) { this->root = buildTree(arr); }
};

// const prettyPrint = (node, prefix = "", isLeft = true) => {
// 	if (node == null) {
// 		return;
// 	}
// 	if (node.right != null) {
// 		prettyPrint(node.right, `${prefix}${isLeft ? "│   " : "    "}`,
// false);
// 	}
// 	console.log(`${prefix}${isLeft ? "└── " : "┌── "}${node.value}`);
// 	if (node.left != null) {
// 		prettyPrint(node.left, `${prefix}${isLeft ? "    " : "│   "}`,
// true);
// 	}
// };

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
  vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Tree *tree = new Tree(arr);
  prettyPrint(tree->root);

  return 0;
}
