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
bool TreeCreated= false;

template <class T>
class Node{
public:
    Node *left, *right;
    T data;
    string frequency;
    int height;
    Node(T data,string frequency){
        this->frequency = frequency;
        this->data = data;
        left = NULL;
        right = NULL;
        height = 0;
    }
    Node(){
        left = right = NULL;
    }
};
template <class T>
class AVL{
    public:
        Node<T> *root;
        AVL(){
            root = NULL;
        }

        int calcheight(Node<T> *root){
            if (root == NULL)
                return 0;
            return root->height;
        }
        int maxx(int a, int b){
            return (a > b) ? a : b;
        }
        int getBalance(Node<T> *root){
            if (root == NULL)
                return 0;
            return calcheight(root->left) - calcheight(root->right);
        }
        Node<T> *insert(Node<T> *root, T data,string frequency){
            if (root == NULL){
                root = new Node<T>(data,frequency);
                return root;
            }
            if (root->data < data){
                root->right = insert(root->right, data,frequency);
            }else if (root->data > data){
                root->left = insert(root->left, data,frequency);
            }else{
                return root;
            }
            root->height = 1 + max(calcheight(root->left), calcheight(root->right));
            int bf = getBalance(root);
            if (bf > 1 && getBalance(root->left) >= 0){
                return rightRotate(root);
            }
            if (bf > 1 && getBalance(root->left) < 0){
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
            if (bf < -1 && getBalance(root->right) <= 0){
                return leftRotate(root);
            }
            if (bf < -1 && getBalance(root->right) > 0){
                root->right = leftRotate(root->right);
                return leftRotate(root);
            }
            return root;
        }
        // Rotate right
        Node<T> *rightRotate(Node<T> *y){
            Node<T> *x = y->left;
            Node<T> *T2 = x->right;
            x->right = y;
            y->left = T2;
            y->height = maxx(calcheight(y->left), calcheight(y->right)) + 1;
            x->height = maxx(calcheight(x->left), calcheight(x->right)) + 1;
            return x;
        }

        // Rotate left
        Node<T> *leftRotate(Node<T> *x){
            Node<T> *y = x->right;
            Node<T> *T2 = y->left;
            y->left = x;
            x->right = T2;
            x->height = maxx(calcheight(x->left), calcheight(x->right)) + 1;
            y->height = maxx(calcheight(y->left), calcheight(y->right)) + 1;
            return y;
        }

        void inorder(Node<T> *root){
            if (root == NULL){
                return;
            }
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }

        Node<T> *deleteNode(Node<T> *root, T key){
            if (root == NULL){
                return NULL;
            }
            if (root->data > key){
                root->left = deleteNode(root->left, key);
            }else if (root->data < key){
                root->right = deleteNode(root->right, key);
            }else{
                if ((root->left == NULL) || (root->right == NULL)){
                    Node<T> *temp = root->left ? root->left : root->right;
                    if (temp == NULL){
                        temp = root;
                        root = NULL;
                    }else{
                        *root = *temp;
                    }
                free(temp);
                }else{
                    Node<T> *temp = nodeWithMimumValue(root->right);
                    root->data = temp->data;
                    root->right = deleteNode(root->right, temp->data);
                }
            }
            if (root == NULL){
                return NULL;
            }
            root->height = 1 + maxx(calcheight(root->left), calcheight(root->right));
            int bf = getBalance(root);
            if (bf > 1 && getBalance(root->left) >= 0){
                return rightRotate(root);
            }
            if (bf > 1 && getBalance(root->left) < 0){
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
            if (bf < -1 && getBalance(root->right) <= 0){
                return leftRotate(root);
            }
            if (bf < -1 && getBalance(root->right) > 0){
                root->right = leftRotate(root->right);
                return leftRotate(root);
            }
            return root;
        }

        Node<T> *nodewithmaxValue(Node<T> *root){
            if (root->right == NULL){
                return root;
            }
            return nodewithmaxValue(root->right);
        }

        Node<T> *nodeWithMimumValue(Node<T> *node){
            Node<T> *current = node;
            while (current->left != NULL)
                current = current->left;
            return current;
        }

        void printTree(Node<T> *root, string indent, bool last){
            if (root != nullptr){
                cout << indent;
                if (last){
                    cout << "R----";
                    indent += "   ";
                }else{
                    cout << "L----";
                    indent += "|  ";
                }
            cout << root->data << endl;
            printTree(root->left, indent, false);
            printTree(root->right, indent, true);
            }
        }

        bool AVLsearch(Node<T>* root, string key){
            // If root is NULL
            if (root == NULL){
                return false;
            }
            // If found, return true
            else if (root->data == key){
                cout<<"The SHA-1 of your password is: "<<root->data<<endl;
                cout<<"Your password has appeared "<<root->frequency<<" times in data breaches." <<endl;
                cout<<"This implies that your password is insecure. "<<endl;
                return true;
            }
            // Recur to the left subtree if
            // the current node's value is
            // greater than key
            else if (root->data > key) {
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
        void deleteTree(Node<T> *node){
            if (node == NULL)
                return;
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
            node = NULL;
        }
};
void names()
{
    system("cls");
    cout << "\n--------------------------------------------------------------------------------------------------------------\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                          Welcome to PWNED PASSWORD DATASET                                 -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                      Developed by:                                         -\n";
    cout << "-                                              Wahaj Javed Alam 20K-0208                                     -\n";
    cout << "-                                               Muhammad Hatif Mujahid 20K-0218                              -\n";
    cout << "-                                                 Minhal Irfan 20K-0316                                      -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "-                                                                                                            -\n";
    cout << "--------------------------------------------------------------------------------------------------------------\n";
    system("PAUSE");
    }
    void loading_screen_start()
    {
        names();
        printf("%c", 219);
        for (int a = 1; a < 50; a++)
        {
            Sleep(20);
            printf("%c", 219);
        }
        Sleep(30);
        system("cls");
    }
    void loading_screen_search(){
        cout << "\n\n\t\t\t\t Searching dataset...\n\n\n\t\t\t\t";
        printf("%c", 219);
        int counter = 0;
        while (!TreeCreated)
        {
            Sleep(360);
            printf("%c", 219);
            counter++;
            if(counter == 30){
                counter = 0;
                system("cls");
                cout << "\n\n\t\t\t\t Searching dataset...\n\n\n\t\t\t\t";
                printf("%c", 219);
            }
        }
        Sleep(30);
        system("cls");
    }

    AVL<string> AVL1, AVL2;

    vector<string> createFileNames(){
        vector<string> fileNames;
        for (int i = 1; i <= 49; i++){
            string fileN = "passwords_";
            fileN += to_string(i);
            fileN += ".txt";
            fileNames.push_back(fileN);
            fileN.clear();
        }
        return fileNames;
    }

    void startFromStart(string F_name){
        ifstream readFile2(F_name);
        string line;
        int lineNo = 0;
        while (lineNo != 5000000 - 1){
            getline(readFile2, line);
            string newLine = "";
            string frequency = "";
            for (int i = 0; i < 40; i++){
                newLine += line[i];
            }
            for(int i=41;i<line.size();i++){
                frequency += line[i];
            }
            AVL1.root = AVL1.insert(AVL1.root, line,frequency);
            lineNo++;
        }
    }

    void startFromHalf(string F_name){
        ifstream readFile1(F_name);
        string line;
        int lineNo = 0;
        while (lineNo != 5000000 - 1){
            getline(readFile1, line);
            lineNo++;
        }
        while (getline(readFile1, line)){
            string newLine = "";
            string frequency = "";
            for (int i = 0; i < 40; i++){
                newLine += line[i];
            }
            for(int i=41;i<line.size();i++){
                frequency += line[i];
            }
            AVL2.root = AVL2.insert(AVL2.root, newLine,frequency);
        }
    }
    void createTree(string name){
        thread th1(startFromStart,name);
        thread th2(startFromHalf, name);
        //thread th3(loading_screen_search);
        th1.join();
        th2.join();
        //TreeCreated = true;
        //th3.join();
    }
    string searchFile(vector<string> fileNames, string data){
        int i = 0;
        for (i = 0; i < fileNames.size(); i++){
            ifstream current(fileNames[i]);
            string line;
            getline(current, line);
            string newLine = "";
            for (int i = 0; i < 40; i++){
                newLine += line[i];
            }
            if (newLine > data){
                i--;
                break;
            }
            current.close();
        }
        return fileNames[i];
    }

    const string sha1func(const string input){
        SHA1 checksum;
        checksum.update(input);
        string hash = checksum.final();
        for (int i = 0; i < hash.size(); i++){
            if (isalpha(hash[i])){
                hash[i] -= 32;
            }
        }
        return hash;
    }

    bool searching(string hash){
        Node<string> *max1;
        max1 = AVL1.nodewithmaxValue(AVL1.root);
        if(hash>max1->data){
            bool result = AVL2.AVLsearch(AVL2.root,hash);
            return result;
        }else{    
            bool result = AVL1.AVLsearch(AVL1.root, hash);
            return result;
        }
        return false;
    }
    void searchResults(string hash){
        auto start = steady_clock::now();
        bool SearchFound = searching(hash);
        if(!SearchFound){
            cout<<"The password you entered is safe."<<endl;
            return;
        }
        auto end = steady_clock::now();
        float duration1 = duration_cast<microseconds>(end - start).count();
        cout << endl<< "Search Duration: "<<duration1/1000000<<endl;
    }  
   
int main()
{
    //loading_screen_start();
    vector<string> fileNamesList;
    fileNamesList = createFileNames();
    string searchThis;
    string choice;
    string currentFile = "";
    while(true){
        fflush(stdin);
        searchThis.clear();
        cout << "Enter your password: ";
        getline(cin, searchThis);
        fflush(stdin);
        string hash = sha1func(searchThis);
        system("cls");
        if(currentFile == searchFile(fileNamesList,hash)){
            cout<<"Data should exist in FILE_{";
	        cout<<currentFile<<"}"<<endl;
            searchResults(hash);
        }else{
            if(AVL1.root){
                AVL1.deleteTree(AVL1.root);
                AVL2.deleteTree(AVL2.root);
            }
            currentFile = searchFile(fileNamesList,hash);
            auto start = steady_clock::now();
            createTree(currentFile);
            auto end = steady_clock::now();
            cout<<"Data should exist in FILE_{";
	        cout<<currentFile<<"}"<<endl;
            float duration = duration_cast<microseconds>(end - start).count();
            cout<<"Time Taken to load the file into memory: ";
            cout << duration / 1000000<<" seconds. "<<endl;
            searchResults(hash);
        
        }
        cout<<"Do you want to search another password?(Y/N) ";
        cin>>choice;
        if(choice == "Y" || choice == "y"){
                continue;
        }else{
            system("cls");
            cout<<"\n\n\t\t\t\t Thank You...\n\n\n\t\t\t\t";
            exit(0);
        }
    }
}
