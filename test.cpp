#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<stdlib.h>
#include<queue>
#include<chrono>
#include<thread>
using namespace std;
using namespace chrono;
class Node {
   public:
  string key;
  Node *left;
  Node *right;
  int height;
};

int maxx(int a, int b);

// Calculate height
int height(Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int maxx(int a, int b) {
  return (a > b) ? a : b;
}

// New node creation
Node *newNode(string key) {
  Node *node = new Node();
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Rotate right
Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = maxx(height(y->left),
          height(y->right)) +
        1;
  x->height = maxx(height(x->left),
          height(x->right)) +
        1;
  return x;
}

// Rotate left
Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = maxx(height(x->left),
          height(x->right)) +
        1;
  y->height = maxx(height(y->left),
          height(y->right)) +
        1;
  return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) -
       height(N->right);
}

// Insert a node
Node *insertNode(Node *node, string key) {
  // Find the correct postion and insert the node
  if (node == NULL)
    return (newNode(key));
  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  // Update the balance factor of each node and
  // balance the tree
  node->height = 1 + maxx(height(node->left),
               height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (key < node->left->key) {
      return rightRotate(node);
    } else if (key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (key > node->right->key) {
      return leftRotate(node);
    } else if (key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

// Node with minimum value
Node *nodeWithMimumValue(Node *node) {
  Node *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

// Delete a node
Node *deleteNode(Node *root, string key) {
  // Find the node and delete it
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == NULL) ||
      (root->right == NULL)) {
      Node *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      Node *temp = nodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right,
                   temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + maxx(height(root->left),
               height(root->right));
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1) {
    if (getBalanceFactor(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}
bool AVLsearch(Node* root, string key)
{
    // If root is NULL
    if (root == NULL)
        return false;
  
    // If found, return true
    else if (root->key == key){
        cout<<root->key<<"LESSS GOOO"<<endl;
        return true;
    }
        
  
    // Recur to the left subtree if
    // the current node's value is
    // greater than key
    else if (root->key > key) {
        bool val = AVLsearch(root->left, key);
        return val;
    }
  
    // Otherwise, recur to the
    // right subtree
    else {
        bool val = AVLsearch(root->right, key);

                return val;
    }
}
// Print the tree
void printTree(Node *root, string indent, bool last) {
  if (root != nullptr) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "   ";
    } else {
      cout << "L----";
      indent += "|  ";
    }
    cout << root->key << endl;
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
  }
}
ifstream readFile1("passwords_22.txt");
Node* root1 = NULL;
Node* root2 = NULL;
Node* root3 = NULL;
void startFromStart(){
    ifstream readFile2("passwords_22.txt");
    string line;
    int lineNo = 0;
    while(lineNo != 5000000-1){
        getline(readFile1,line);
        string newLine = "";
        for(int i=0;i<40;i++){
            newLine += line[i];
        }
        root1 = insertNode(root1,newLine);
        lineNo++;
    }
}
void startFromHalf(){
     string line;
     int lineNo = 0;
    while(lineNo != 5000000-1){
        getline(readFile1,line);
        lineNo++;
    }
    while(getline(readFile1,line)){
        string newLine = "";
        for(int i=0;i<40;i++){
            newLine += line[i];
        }
        root2 = insertNode(root2,newLine);
    }
    
}

int main(){
   
    string searchThis = "58333D43B4465B133B9C39761D28F854A7B1DCF2";
    ifstream readFile1("passwords_22.txt");
    // ifstream readFile2("passwords_1.txt");
    // ifstream readFile3("passwords_3.txt");
    auto start = steady_clock::now();
        thread th1(startFromStart);
        thread th2(startFromHalf);
        
    auto end = steady_clock::now();
    float duration = duration_cast<microseconds>(end-start).count();
    cout<<endl<<duration/1000000;
    th1.join();
    th2.join();
    // thread th2(startFromHalf,readFile2,root2);
    // thread th3(startFromHalf,readFile3,root3);

}