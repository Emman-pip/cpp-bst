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
    int mid = floor(arr.size() / 2);
    vector<int> right;
    vector<int> left;

    if (arr.size() % 2 == 1) {
      right = vector<int>(arr.begin() + mid + 1, arr.end());
      left = vector<int>(arr.begin(), arr.end() - mid - 1);
    } else {
      left = vector<int>(arr.begin(), arr.end() - mid);
      right = vector<int>(arr.begin() + mid + 1, arr.end());
    }
    // left = vector<int>(arr.begin(), arr.end() - mid - 1);
    // right = vector<int>(arr.begin() + mid + 1, arr.end());
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

  void deletePriv(Node *target, Node *prev, bool isLeft) {
    Node *prevPtr = NULL;
    Node *ptr = target->right;
    while (ptr->left != NULL) {
      prevPtr = ptr;
      ptr = ptr->left;
    }
    prevPtr->left = ptr->right;
    ptr->right = target->right;
    ptr->left = target->left;
    if (prev) {
      (isLeft) ? prev->left = ptr : prev->right = ptr;
    } else {
      root = ptr;
    }
    target = ptr;
    return;
  }

  // DF Traversal
  void inorder(Node *ptr, vector<Node *> &stack, vector<int> &res) {
    if (ptr) {
      stack.push_back(ptr);
      return inorder(ptr->left, stack, res);
    }
    if (stack.size() > 0 && stack[stack.size() - 1]->right) {
      Node *right = stack[stack.size() - 1]->right;
      res.push_back(stack[stack.size() - 1]->data);
      stack.pop_back();
      return inorder(right, stack, res);
    } else if (stack.size() > 0) {
      res.push_back(stack[stack.size() - 1]->data);
      stack.pop_back();
      return inorder(ptr, stack, res);
    } else { // base case
      return;
    }
  }

  // DF preorder traversal
  void preorder(Node *ptr, vector<Node *> &stack, vector<int> &res) {
    if (ptr) {
      stack.push_back(ptr);
      res.push_back(ptr->data);
      ptr = ptr->left;
      return preorder(ptr, stack, res);
    } else if (stack.size() > 0 && stack[stack.size() - 1]->right) {
      ptr = stack[stack.size() - 1]->right;
      stack.pop_back();
      return preorder(ptr, stack, res);
    } else if (stack.size() > 0) {
      stack.pop_back();
      return preorder(ptr, stack, res);
    } else {
      return;
    }
  }

  void postorder(Node *ptr, vector<Node *> &stack, vector<int> &res) {
    // if may nasa left, pasok
  }

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

    // do with multiple chilren -- DONE
    if (current->left && current->right) {
      deletePriv(current, prev, isLeft);
    }
    // do with one child -- DONE
    else if (current->left) {
      (isLeft) ? prev->left = current->left : prev->right = current->left;

    } else if (current->right) {
      (isLeft) ? prev->left = current->right : prev->right = current->right;
    }
    // do with no child -- DONE
    else if (!(current->left && current->right)) {
      (isLeft) ? prev->left = NULL : prev->right = NULL;
    }
    return true;
  };
  Node *find(int value) {
    Node *ptr = root;
    if (!ptr) {
      return NULL;
    }
    while (ptr != NULL) {
      if (ptr->data == value) {
        return ptr;
      }
      (ptr->data > value) ? ptr = ptr->left : ptr = ptr->right;
    }
    return ptr;
  };
  vector<int> breadthFirstTraversal() {
    // do stuff here
    vector<Node *> queue;
    vector<int> arr;
    queue.push_back(root);
    Node *ptr;
    for (int i = 0; i < queue.size(); i++) {
      ptr = queue[i];
      if (ptr->left) {
        queue.push_back(ptr->left);
      }
      if (ptr->right) {
        queue.push_back(ptr->right);
      }
      arr.push_back(ptr->data);
    }

    return arr;
  }
  vector<int> inorderTraversal() {
    vector<int> res;
    vector<Node *> stack;
    Node *ptr = root;
    inorder(ptr, stack, res);
    return res;
  }
  vector<int> preorderTraversal() {
    vector<int> res;
    vector<Node *> stack;
    Node *ptr = root;
    preorder(ptr, stack, res);
    for (Node *i : stack) {
      res.push_back(i->data);
    }
    return res;
  }
  vector<int> postorderTraversal() {
    vector<int> res;
    vector<Node *> stack;
    Node *ptr = root;
    postorder(ptr, stack, res);
    return res;
  }
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
  // vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 3289};
  // vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> arr = {1, 2, 3};
  //   vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
  Tree *tree = new Tree(arr);
  // tree->insert(90);
  // tree->insert(-80);
  // tree->insert(-20);
  // tree->insert(-81);
  // tree->insert(100);
  // tree->insert(6);
  prettyPrint(tree->root);
  vector<int> bft = tree->breadthFirstTraversal();

  cout << "This is the breadthFirstTraversal: " << endl;
  for (int i : bft) {
    cout << i << " ";
  }

  cout << endl << endl;

  vector<int> inorder = tree->inorderTraversal();
  cout << "This is the inorder traversal" << endl;
  for (int i : inorder) {
    cout << i << " ";
  }

  cout << endl << endl;

  vector<int> preorder = tree->preorderTraversal();
  cout << "This is the preorder traversal" << endl;
  for (int i : preorder) {
    cout << i << " ";
  }
  cout << endl << endl;

  vector<int> postorder = tree->postorderTraversal();
  cout << "This is the postorder traversal" << endl;
  for (int i : postorder) {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}
