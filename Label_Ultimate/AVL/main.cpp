#include<iostream>
#include "windows.h"
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
double* TestInsert(AVL<int> bTree)
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
    return Insert;
}
double TestSearch(AVL<int> bst)
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
    return (t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart;
}
double *TestDelete(AVL<int> bst)
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
    return Delete;
}
int main()
{
    AVL<int> btree1,btree2,btree3;
    int N=10000;
    double Insert[50],*Insert1,*Insert2,*Insert3;
    double Search,Search1,Search2,Search3;
    double Delete[50],*Delete1,*Delete2,*Delete3;
    Insert1=TestInsert(btree1);
    Insert2=TestInsert(btree2);
    Insert3=TestInsert(btree3);
    for (int i = 0; i < 50; ++i) {
        Insert[i]=(Insert1[i]+Insert2[i]+Insert3[i])/3;
    }
    Search1=TestSearch(btree1);
    Search2=TestSearch(btree2);
    Search3=TestSearch(btree3);
    Search=(Search1+Search2+Search3)/3;

    Delete1=TestDelete(btree1);
    Delete2=TestDelete(btree2);
    Delete3=TestDelete(btree3);
    for (int i = 0; i < 50; ++i) {
        Delete[i]=(Delete1[i]+Delete2[i]+Delete3[i])/3;
    }
    for (int i = 0; i < 50; ++i) {
        cout<<"N="<<N<<" insert time "<<Insert[i]<<"ms"<<endl;
        N+=10000;
    }
    cout<<"Search time: "<< Search <<" ms"<<endl;
    N=10000;
    for (int i = 0; i < 50; ++i) {
        cout<<"N="<<N<<" delete time "<<Delete[i]<<"ms"<<endl;
        N+=10000;
    }

    return 0;
}
