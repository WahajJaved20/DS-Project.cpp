#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <queue>
#include <chrono>
#include <thread>
#include <vector>
#include <ctype.h>
#include "sha1.hpp"
using namespace std;
using namespace chrono;
template <class T>
class Node
{
public:
    Node *left, *right;
    T data;
    int height;
    Node(T data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
        height = 0;
    }
};
template <class T>
class AVL
{
public:
    Node<T> *root;
    AVL()
    {
        root = NULL;
    }

    int calcheight(Node<T> *root)
    {
        if (root == NULL)
            return 0;
        return root->height;
    }
    int maxx(int a, int b)
    {
        return (a > b) ? a : b;
    }
    int getBalance(Node<T> *root)
    {
        if (root == NULL)
            return 0;
        return calcheight(root->left) - calcheight(root->right);
    }
    Node<T> *insert(Node<T> *root, T data)
    {
        if (root == NULL)
        {
            root = new Node<T>(data);

            return root;
        }
        if (root->data < data)
        {
            root->right = insert(root->right, data);
        }
        else if (root->data > data)
        {
            root->left = insert(root->left, data);
        }
        else
        {
            return root;
        }
        root->height = 1 + max(calcheight(root->left), calcheight(root->right));
        int bf = getBalance(root);
        if (bf > 1 && getBalance(root->left) >= 0)
        {
            return rightRotate(root);
        }
        if (bf > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (bf < -1 && getBalance(root->right) <= 0)
        {
            return leftRotate(root);
        }
        if (bf < -1 && getBalance(root->right) > 0)
        {
            root->right = leftRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
    // Rotate right
    Node<T> *rightRotate(Node<T> *y)
    {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = maxx(calcheight(y->left), calcheight(y->right)) + 1;
        x->height = maxx(calcheight(x->left), calcheight(x->right)) + 1;
        return x;
    }

    // Rotate left
    Node<T> *leftRotate(Node<T> *x)
    {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = maxx(calcheight(x->left), calcheight(x->right)) + 1;
        y->height = maxx(calcheight(y->left), calcheight(y->right)) + 1;
        return y;
    }
    void inorder(Node<T> *root)
    {
        if (root == NULL)
        {
            return;
        }
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
    Node<T> *deleteNode(Node<T> *root, T key)
    {
        if (root == NULL)
        {
            return NULL;
        }
        if (root->data > key)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (root->data < key)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            if ((root->left == NULL) || (root->right == NULL))
            {
                Node<T> *temp = root->left ? root->left : root->right;
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                free(temp);
            }
            else
            {
                Node<T> *temp = nodeWithMimumValue(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }
        if (root == NULL)
        {
            return NULL;
        }
        root->height = 1 + maxx(calcheight(root->left), calcheight(root->right));
        int bf = getBalance(root);
        if (bf > 1 && getBalance(root->left) >= 0)
        {
            return rightRotate(root);
        }
        if (bf > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (bf < -1 && getBalance(root->right) <= 0)
        {
            return leftRotate(root);
        }
        if (bf < -1 && getBalance(root->right) > 0)
        {
            root->right = leftRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
    Node<T> *nodewithmaxValue(Node<T> *root)
    {
        if (root->right == NULL)
        {
            return root;
        }
        return nodewithmaxValue(root->right);
    }
    Node<T> *nodeWithMimumValue(Node<T> *node)
    {
        Node<T> *current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }
    void printTree(Node<T> *root, string indent, bool last)
    {
        if (root != nullptr)
        {
            cout << indent;
            if (last)
            {
                cout << "R----";
                indent += "   ";
            }
            else
            {
                cout << "L----";
                indent += "|  ";
            }
            cout << root->data << endl;
            printTree(root->left, indent, false);
            printTree(root->right, indent, true);
        }
    }
};
AVL<string> AVL1, AVL2;
vector<string> createFileNames()
{
    vector<string> fileNames;
    for (int i = 1; i <= 26; i++)
    {
        string fileN = "passwords_";
        fileN += to_string(i);
        fileN += ".txt";
        fileNames.push_back(fileN);
        fileN.clear();
    }
    return fileNames;
}
void startFromStart(string F_name)
{
    ifstream readFile2(F_name);
    string line;
    int lineNo = 0;
    while (lineNo != 5000000 - 1)
    {
        getline(readFile2, line);
        string newLine = "";
        for (int i = 0; i < 40; i++)
        {
            newLine += line[i];
        }
        AVL1.root = AVL1.insert(AVL1.root, line);
        lineNo++;
    }
}
void startFromHalf(string F_name)
{
    ifstream readFile1(F_name);
    string line;
    int lineNo = 0;
    while (lineNo != 5000000 - 1)
    {
        getline(readFile1, line);
        lineNo++;
    }
    while (getline(readFile1, line))
    {
        string newLine = "";
        for (int i = 0; i < 40; i++)
        {
            newLine += line[i];
        }
        AVL2.root = AVL2.insert(AVL2.root, newLine);
    }
}
void createTree(string name)
{
    thread th1(startFromStart, name);
    thread th2(startFromHalf, name);
    th1.join();
    th2.join();
}
string searchFile(vector<string> fileNames, string data)
{
    int i = 0;
    for (i = 0; i < fileNames.size(); i++)
    {
        ifstream current(fileNames[i]);
        string line;
        getline(current, line);
        string newLine = "";
        for (int i = 0; i < 40; i++)
        {
            newLine += line[i];
        }
        if (newLine > data)
        {
            i--;
            break;
        }
        current.close();
    }
    return fileNames[i];
}
const string sha1func(const string input)
{
    SHA1 checksum;
    checksum.update(input);
    string hash = checksum.final();
    for (int i = 0; i < hash.size(); i++)
    {
        if (isalpha(hash[i]))
        {
            hash[i] -= 32;
        }
    }
    return hash;
}
int main()
{
    vector<string> fileNamesList;
    fileNamesList = createFileNames();
    string searchThis;
    cout << "Enter password: ";
    getline(cin, searchThis);
    string hash = sha1func(searchThis);
    cout << "The SHA-1 of " << searchThis << " is: " << hash << endl;

    // ifstream readFile1("passwords_22.txt");
    // // ifstream readFile2("passwords_1.txt");
    // // ifstream readFile3("passwords_3.txt");

    //     thread th1(startFromStart);
    //     thread th2(startFromHalf);

    // th1.join();
    // th2.join();
    auto start = steady_clock::now();
    createTree(searchFile(fileNamesList, searchThis));
    auto end = steady_clock::now();
    float duration = duration_cast<microseconds>(end - start).count();
    cout << endl<< duration / 1000000;
}