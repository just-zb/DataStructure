#include<iostream>
#include "windows.h"
#include "time.h"
#include "stdlib.h"
using namespace std;

template <typename T>
class AVL{
public:
    class node{
    public:
        T key;
        int height;
        node * left;
        node * right;
        node(T k){
            height = 1;
            key = k;
            left = NULL;
            right = NULL;
        }

    };
    node * root = NULL;
    int n;
    void insert(T x){
        root=insertUtil(root, x);
    }
    void remove(T x){
        root=removeUtil(root, x);
    }
    node * search(T x){
        return searchUtil(root,x);
    }
    bool IsFind(T x)
    {
        if (search(x)!=NULL)
            return true;
        return false;
    }
private:
    int height(node * head){
        if(head==NULL) return 0;
        return head->height;
    }
    node * rightRotation(node * head){
        node * newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    node * leftRotation(node * head){
        node * newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    void inorderUtil(node * head){
        if(head==NULL) return ;
        inorderUtil(head->left);
        cout<<head->key<<" ";
        inorderUtil(head->right);
    }

    node * insertUtil(node * head, T x){
        if(head==NULL){
            n+=1;
            node * temp = new node(x);
            return temp;
        }
        if(x < head->key) head->left = insertUtil(head->left, x);
        else if(x > head->key) head->right = insertUtil(head->right, x);
        head->height = 1 + max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if(bal>1){
            if(x < head->left->key){
                return rightRotation(head);
            }else{
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }else if(bal<-1){
            if(x > head->right->key){
                return leftRotation(head);
            }else{
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }
    node * removeUtil(node * head, T x){
        if(head==NULL) return NULL;
        if(x < head->key){
            head->left = removeUtil(head->left, x);
        }else if(x > head->key){
            head->right = removeUtil(head->right, x);
        }else{
            node * r = head->right;
            if(head->right==NULL){
                node * l = head->left;
                delete(head);
                head = l;
            }else if(head->left==NULL){
                delete(head);
                head = r;
            }else{
                while(r->left!=NULL) r = r->left;
                head->key = r->key;
                head->right = removeUtil(head->right, r->key);
            }
        }
        if(head==NULL) return head;
        head->height = 1 + max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if(bal>1){
            if(x > head->left->key){
                return rightRotation(head);
            }else{
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }else if(bal < -1){
            if(x < head->right->key){
                return leftRotation(head);
            }else{
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }
    node * searchUtil(node * head, T x){
        if(head == NULL) return NULL;
        T k = head->key;
        if(k == x) return head;
        if(k > x) return searchUtil(head->left, x);
        if(k < x) return searchUtil(head->right, x);
    }
};
void TestInsert(AVL<int> bTree)
{
    int N=10000,j=0;
    double Insert[50];
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 1; i <=500000; ++i) {
        bTree.insert(i);
        if (i==N)
        {
            QueryPerformanceCounter(&t2);
            Insert[j]=(t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart;
            j++;
            N+=10000;
        }
    }
    N=10000;
    for (double i : Insert) {
        cout<<i<<endl;
        N+=10000;
    }
}
void TestSearch(AVL<int> bst)
{
    int Number[1000];
    for (int i = 0; i < 1000; ++i) {
        Number[i]=rand() % (500000)+1;
    }
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for (int i = 0; i < 1000; ++i) {
        bst.IsFind(Number[i]);
    }
    QueryPerformanceCounter(&t2);
    cout<<"Search time: "<< (t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart<<endl;
}
void TestDelete(AVL<int> bst)
{
    int N=10000,j=0;
    double Delete[50];
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 1; i <=500000; ++i) {
        bst.remove(i);
        if (i==N)
        {
            QueryPerformanceCounter(&t2);
            Delete[j]=(t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart;
            j++;
            N+=10000;
        }
    }
    N=10000;
    for (double i : Delete) {
        cout<<i<<endl;
        N+=10000;
    }
}
void TestDelete_Back(AVL<int> bst) {
    int N = 10000, j = 0;
    double Delete[50];
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 500000; i >= 1; i--) {
        bst.remove(i);
        if (500001 - i == N) {
            QueryPerformanceCounter(&t2);
            Delete[j] = ((t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart);
            j++;
            N += 10000;
        }
    }
    N = 10000;
    for (double i : Delete) {
        cout  << i << endl;
        N += 10000;
    }
}
void Random_Insert(AVL<int> bst)
{
    int N=10000,j=0;
    double Insert[50];
    int x[500000];//生成随机序列x
    srand((int)time(0));
    for(int i = 0; i < 500000; i++)
    {
        x[i] = i;
    }
    for(int i = 0; i < 500000; i++)
    {
        int t = (rand() % (500000-i))+i;
        swap(x[i], x[t]);
    }
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 0; i <500000; ++i) {
        bst.insert(x[i]);
        if (i==N-1)
        {
            QueryPerformanceCounter(&t2);
            Insert[j] = ((t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart);
            j++;
            N+=10000;
        }
    }
    N=10000;
    for (double i : Insert) {
        cout<<i<<endl;
        N+=10000;
    }
}
void Random_Delete(AVL<int> bst)
{
    int N=10000,j=0;
    double Delete[50];
    int x[500000];//生成随机序列x
    srand((int)time(0));
    for(int i = 0; i < 500000; i++)
    {
        x[i] = i;
    }
    for(int i = 0; i < 500000; i++)
    {
        int t = (rand() % (500000-i))+i;
        swap(x[i], x[t]);
    }
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 0; i <500000; ++i) {
        bst.remove(x[i]);
        if (i==N-1)
        {
            QueryPerformanceCounter(&t2);
            Delete[j] = ((t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart);
            j++;
            N+=10000;
        }
    }
    N=10000;
    for (double i : Delete) {
        cout<<i<<endl;
        N+=10000;
    }
}
int main()
{
    AVL<int> AVLTree;
    Random_Insert(AVLTree);
    //TestInsert(AVLTree);
    TestSearch(AVLTree);
    //TestDelete(AVLTree);
    //TestDelete_Back(AVLTree);//相反顺序删除
    Random_Delete(AVLTree);

    return 0;
}
