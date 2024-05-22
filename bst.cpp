#include <cinttypes>
#include <cmath>
#include <cstdlib>
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

// TODO:
// 1. depth of the tree of a value -- number of edges of a node from the root.
// 5. tie it all together ( generate random numbers for the tree, confirm is
// balanced, print traversals, )

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
    Node *root = new Node(arr[mid], buildTree(left), buildTree(right));
    return root;
  }

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
    while (ptr) {
      if (!ptr->left)
        break;
      prevPtr = ptr;
      ptr = ptr->left;
    }
    if (!prevPtr) {
      (ptr->data < target->left->data) ? ptr->right = target->left
                                       : ptr->left = target->left;
    } else {
      prevPtr->left = ptr->right;
      ptr->right = target->right;
      ptr->left = target->left;
    }
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
    if (ptr) {
      stack.push_back(ptr);
      return postorder(ptr->left, stack, res);
    } else if (stack.size() > 0 && stack[stack.size() - 1]->right) {
      Node *rootPtr = stack[stack.size() - 1];
      vector<Node *> newStack;
      stack.pop_back();
      postorder(rootPtr->right, newStack, res);
      res.push_back(rootPtr->data);
      return postorder(ptr, stack, res);
    } else if (stack.size() > 0) {
      res.push_back(stack[stack.size() - 1]->data);
      stack.pop_back();
      return postorder(ptr, stack, res);
    }
    return;
  }

  void last(Node *node, int &count) {
    int countLeft = 0, countRight = 0;
    if (!node)
      return;
    last(node->left, countLeft);
    countLeft++;
    last(node->right, countRight);
    countRight++;
    count = max(countRight, countLeft);
  }

public:
  Node *root;
  Tree(vector<int> arr) { this->root = buildTree(arr); };
  bool insert(int value) { return this->insertBack(value, root); }
  // create the delete node functionality
  bool deleteNode(int value) {
    // save the prev, direction, and the current node
    Node *prev = NULL;
    Node *current = root;
    bool isLeft;
    // loop to find the node
    while (current && current->data != value) {
      prev = current;
      if (current->data > value) {
        current = current->left;
        isLeft = true;
        continue;
      }
      current = current->right;
      isLeft = false;
    }
    if (!current) {
      return false;
    }

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
  void rebalance() {
    vector<int> ordered = inorderTraversal();
    root = buildTree(ordered);
  }

  int height(int val) {
    Node *ptr = root;
    int height = 0;
    while (val != ptr->data && ptr) {
      if (val < ptr->data) {
        ptr = ptr->left;
      } else {
        ptr = ptr->right;
      }
      height++;
    }
    return (val == ptr->data) ? height : -1;
  }
  bool isBalanced() {
    bool balanced;
    int left = 0, right = 0;
    last(root->left, left);
    last(root->right, right);
    return (max(left, right) - min(left, right) <= 1) ? true : false;
  }
  int depth(int value) {
    Node *node = find(value);
    if (!node) {
      return -1;
    }
    int left = 0, right = 0;
    Node *ptrNode = node->left, *ptrNode2 = node->right;
    if (ptrNode) {
      last(ptrNode, left);
    }
    if (ptrNode2) {
      last(ptrNode2, right);
    }
    return max(left, right);
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
void bubbleSort(vector<int> &arr) {
  int i, prev;
  bool flag = false;
  while (!flag) {
    prev = 0;
    flag = true;
    for (i = 1; i < arr.size(); i++) {
      if (prev >= 0 && arr[prev] > arr[i]) {
        swap(arr[prev], arr[i]);
        flag = false;
      }
      prev++;
    }
    if (flag) {
      return;
    }
  }
}

class Display {
private:
  Tree *tree = NULL;
  int randomNumberNoRepetition(vector<int> arr, int n) {
    int randomNum = rand() % n;
    for (int i = 0; i < arr.size(); i++) {
      if (i == randomNum) {
        randomNum = rand();
      }
    }
    return randomNum;
  }

  bool checkIfRepeating(vector<int> arr, int n) {
    for (int i : arr) {
      if (i == n) {
        return true;
      }
    }
    return false;
  }

  void setup() {
    system("clear");
    int size;
    string randomized;
    vector<int> arr;
    cout << "Enter the input size of the initial array (max:1000): " << endl;
    cin >> size;
    cout << "Do you want the array values to be randomized?(y/n) ";
    cin >> randomized;
    // add error catching here
    bool random = (randomized == "n") ? false : true;

    if (!random) {
      cout
          << "Enter the values for your BST (repeating values are not allowed)."
          << endl;
      for (int i = 0; i < size; i++) {
        int val;
        cout << "Enter value #" << i + 1 << ": ";
        cin >> val;

        if (checkIfRepeating(arr, val)) {
          cout << "Repeating values are not allowd. Enter another value"
               << endl;
          i--;
          continue;
        }

        arr.push_back(val);
      }
    } else {
      cout << "The values generated will mostly be in between 0 and 1000"
           << endl;
      for (int i = 0; i < size; i++) {
        int randomNum = randomNumberNoRepetition(arr, 1000);
        arr.push_back(randomNum);
      }
    }
    bubbleSort(arr);
    tree = new Tree(arr);
  }

  void deleteItem() {
    system("clear");
    prettyPrint(tree->root);
    cout << endl << "Choose a node (number) to delete: ";
    int node;
    cin >> node;
    bool flag = tree->deleteNode(node);
    if (flag) {
      cout << "Node containing the value " << node << " was deleted." << endl;
    } else {
      cout << "The node containing the value " << node << " does not exist"
           << endl;
    }
    cout << endl;
    system("sleep 1");
  }

  void insertItem() {
    system("clear");
    prettyPrint(tree->root);
    cout << "Duplicated are not allowed." << endl;
    cout << endl << "Choose a number to insert: ";
    int node;
    cin >> node;
    bool flag = tree->insert(node);
    cout << "Insertion successful" << endl;
    cout << endl;
    system("sleep 1");
  }

  void getDepth() {
    system("clear");
    prettyPrint(tree->root);
    cout << endl << "Choose a node to search: ";
    int node;
    cin >> node;
    int dep = tree->depth(node);
    if (dep == -1)
      cout << "The node does not exist in the tree." << endl;
    else
      cout << "The depth of " << node << " is " << dep << endl;
    cout << endl;
    system("sleep 3");
  }

  void rebalanceTree() {
    system("clear");
    prettyPrint(tree->root);
    tree->rebalance();
    cout << string(60, '*') << endl;
    prettyPrint(tree->root);
    cout << "Tree has been rebalanced" << endl;
    system("sleep 2");
  }

  void isBalanced() {
    system("clear");
    prettyPrint(tree->root);
    if (tree->isBalanced())
      cout << "Tree is balanced" << endl;
    else
      cout << "Tree is not balanced" << endl;
    system("sleep 2");
  }

  void nodeHeight() {
    system("clear");
    prettyPrint(tree->root);
    cout << "Enter the node value: ";
    int node;
    cin >> node;
    cout << "The height of the node (value " << node << ") is "
         << tree->height(node) << endl;
    system("sleep 2");
  }

  void printVector(string title, vector<int> arr) {
    cout << title << endl;
    cout << "[ ";
    for (int i : arr) {
      cout << i << "  ";
    }
    cout << "]" << endl;
  }

  void traversals() {
    system("clear");
    prettyPrint(tree->root);
    cout << endl;
    printVector("Inorder traversal", tree->inorderTraversal());
    cout << endl;
    printVector("Preorder traversal", tree->preorderTraversal());
    cout << endl;
    printVector("Postorder traversal", tree->postorderTraversal());
    cout << endl;

    system("sleep 10");
  }

  void searchNode() {
    system("clear");
    prettyPrint(tree->root);
    cout << "Enter the value to search for: ";
    int node;
    cin >> node;
    Node *val = tree->find(node);
    if (val) {
      prettyPrint(val);
      cout << endl
           << "Node found! The nodes connected are printed above" << endl;
    } else {
      cout << "Node does not exist in the tree" << endl;
    }
    system("sleep 5");
  }

  void options() {
    bool flag = true;
    while (flag) {
      system("clear");
      prettyPrint(tree->root);
      cout << "^^^^^^ Generated Binary Search Tree ^^^^^^" << endl;
      cout << "Actions: " << endl;
      cout << "1. Insert new values to the tree." << endl;
      cout << "2. Delete nodes." << endl;
      cout << "3. Get Depth of a node." << endl;
      cout << "4. Rebalance the tree." << endl;
      cout << "5. Check if the tree is balanced." << endl;
      cout << "6. Get the height of the node." << endl;
      cout << "7. See depth first traversals (inorder, preorder, and postorder "
              "traversals)."
           << endl;
      cout << "8. Find a node." << endl;
      cout << "9. Rebuild the tree." << endl;
      cout << "10.Exit" << endl;

      int choice;
      cout << endl << "Choose: " << endl;
      cin >> choice;

      switch (choice) {
      case 1:
        insertItem();
        continue;
      case 2:
        deleteItem();
        continue;
      case 3:
        getDepth();
        continue;
      case 4:
        rebalanceTree();
        continue;
      case 5:
        isBalanced();
        continue;
      case 6:
        nodeHeight();
        continue;
      case 7:
        traversals();
        continue;
      case 8:
        searchNode();
        continue;
      case 9:
        setup();
        continue;
      case 10:
        cout << "Thank you for using this service." << endl;
        flag = false;
        break;
      default:
        cout << "Invalid input." << endl;
        flag = false;
        break;
      }
    }
  }

public:
  Display() {
    setup();
    options();
  }
};
int main() {
  Display();
  return 0;
}
