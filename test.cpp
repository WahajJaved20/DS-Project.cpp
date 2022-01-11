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
template<class T>
class Node{
    public:
    Node *left, *right;
    T data;
    int height;
    Node(T data){
        this->data = data;
        left = NULL;
        right = NULL;
        height = 0;
    }
};
template<class T>
class AVL{
    public:
    Node<T> *root;
    int calcheight(Node<T> *root) {
        if (root == NULL)
            return 0;
        return root->height;
    }
    AVL(){
        root = NULL;
    }
    int max(int a, int b) {
        return (a > b) ? a : b;
    }
    int getBalance(Node<T> *root){
        if(root==NULL)
            return 0;
        return calcheight(root->left)-calcheight(root->right);
    }
    Node<T>* insert(Node<T> *root,T data){
        if(root==NULL){
            root = new Node<T>(data);
            
            return root;
        }
        if(root->data<data){
            root->right = insert(root->right, data);
        }
        else if(root->data>data){
            root->left = insert(root->left, data);
        }
        else{
            return root;
        }
        root->height = 1+max(calcheight(root->left), calcheight(root->right));
        int bf = getBalance(root);
        if(bf>1 &&getBalance(root->left)>=0){
            return rightRotate(root);
        }
        if(bf>1 && getBalance(root->left)<0){
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if(bf<-1&&getBalance(root->right)<=0){
            return leftRotate(root);
        }
        if(bf<-1&&getBalance(root->right)>0){
            root->right = leftRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
    // Rotate right
    Node<T> *rightRotate(Node<T> *y) {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(calcheight(y->left),calcheight(y->right))+1;
        x->height = max(calcheight(x->left),calcheight(x->right))+1;
        return x;
    }

    // Rotate left
    Node<T> *leftRotate(Node<T> *x) {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(calcheight(x->left),calcheight(x->right))+1;
        y->height = max(calcheight(y->left),calcheight(y->right))+1;
        return y;
    }
    void inorder(Node<T> *root){
        if(root==NULL){
            return;
        }
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
    Node<T>* deleteNode(Node<T> *root, T key){
        if(root==NULL){
            return NULL;
        }
        if(root->data>key){
            root->left = deleteNode(root->left, key);
        }
        else if(root->data<key){
            root->right = deleteNode(root->right, key);
        }
        else {
            if ((root->left == NULL) ||(root->right == NULL)) {
            Node<T> *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
                free(temp);
            } else {
                Node<T> *temp = nodeWithMimumValue(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right,temp->data);
            }
        }
        if(root==NULL){
            return NULL;
        }
        root->height = 1+max(calcheight(root->left), calcheight(root->right));
        int bf = getBalance(root);
        if(bf>1 &&getBalance(root->left)>=0){
            return rightRotate(root);
        }
        if(bf>1 && getBalance(root->left)<0){
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if(bf<-1&&getBalance(root->right)<=0){
            return leftRotate(root);
        }
        if(bf<-1&&getBalance(root->right)>0){
            root->right = leftRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
    Node<T> *nodewithmaxValue(Node<T> *root){
        if(root->right==NULL){
            return root;
        }
        return nodewithmaxValue(root->right);
    }
    Node<T> *nodeWithMimumValue(Node<T> *node) {
        Node<T> *current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }
    void BFS(Node<T> *root){
        if(root==NULL){
            return;
        }
        queue<Node<T>*>q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *temp = q.front();
            cout<<temp->data<<" ";
            q.pop();
            if(temp->left!=NULL){
                q.push(temp->left);
            }
            if(temp->right!=NULL){
                q.push(temp->right);
            }
        }
        
    }
};
ifstream readFile1("passwords_22.txt");
Node<string>* root1 = NULL;
Node<string>* root2 = NULL;
Node<string>* root3 = NULL;
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