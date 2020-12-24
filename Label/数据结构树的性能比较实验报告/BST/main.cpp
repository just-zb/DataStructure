#include<iostream>
#include<stack>
#include "time.h"
#include "windows.h"
#include "stdlib.h"
using namespace std;

struct BSTNode
{
    int _key;
    BSTNode* _left;
    BSTNode* _right;
    BSTNode(const int& key):_key(key), _left(nullptr),_right(nullptr){}
};


class BSTree
{
public:
    BSTree():_root(nullptr){}
    BSTNode* Find_R(const int& key)
    {
        return Find_R(_root, key);
    }
    bool IsFind_R(const int&key)
    {
        if (Find_R(key)!=NULL)
            return true;
        return false;
    }
    bool Remove_R(const int& key)
    {
        return Remove_R(_root, key);
    }
    bool Insert(const int& key);
protected:

    BSTNode* Find_R(BSTNode*& root, const int& key);
    bool Remove_R(BSTNode*& root, const int& key);
protected:
    BSTNode* _root;
};
bool BSTree::Insert(const int& key)
{
    if (_root == NULL)
    {
        _root = new BSTNode(key);
        return true;
    }
    BSTNode* cur = _root;
    BSTNode* parent = _root;
    while (cur)
    {
        if (cur->_key < key)
        {
            parent = cur;
            cur = cur->_right;
        }
        else if (cur->_key>key)
        {
            parent = cur;
            cur = cur->_left;
        }
        else
            return false;
    }
    if (key > parent->_key)
        parent->_right = new BSTNode(key);
    else
        parent->_left = new BSTNode(key);
    return true;
}

BSTNode*  BSTree::Find_R(BSTNode*& root, const int& key)
{
    if (root == nullptr)
        return nullptr;
    if (root->_key == key)
        return root;
    else if (root->_key > key)
        return Find_R(root->_left, key);
    else
        return Find_R(root->_right, key);
}

bool BSTree::Remove_R(BSTNode*& root, const int& key)
{
    if (root == nullptr)
        return false;
    if (root->_left == nullptr&&root->_right == nullptr)
    {
        if (root->_key == key)
        {
            delete root;
            root = nullptr;
            return true;
        }
        else
            return false;
    }
    if (root->_key > key)
    {
        return Remove_R(root->_left, key);
    }
    else if (root->_key < key)
    {
        return Remove_R(root->_right, key);
    }
    else
    {
        if (root->_left == nullptr)
        {
            root = root->_right;
        }
        else if (root->_right == nullptr)
        {
            root= root->_left ;
        }
        else
        {
            BSTNode* First_Left = root->_right;
            BSTNode* parent = root;
            while (First_Left->_left)
            {
                parent = First_Left;
                First_Left = First_Left->_left;
            }
            swap(First_Left->_key, root->_key);
            if (parent->_left == First_Left)
            {
                parent->_left = First_Left->_right;
            }
            else if (root->_right == First_Left)
            {
                root->_right = First_Left->_right;
            }
            delete First_Left;
            return true;
        }
    }
}

void TestInsert(BSTree bTree)
{
    int N=10000,j=0;
    double Insert[50];
    clock_t t1,t2;
    t1=clock();
    for (int i = 1; i <=500000; ++i) {
        bTree.Insert(i);
        if (i==N)
        {
            t2=clock();
            Insert[j]=((t2-t1)/CLOCKS_PER_SEC);
            j++;
            N+=10000;
        }
    }
    N=10000;
    for (double i : Insert) {
        cout<<"N  "<<N<<" Insert Time:"<<i<<"s"<<endl;
        N+=10000;
    }
}
void TestSearch(BSTree bst)
{
    int Number[1000];
    LARGE_INTEGER t1,t2,tc;
    for (int i = 0; i < 1000; ++i) {
        Number[i]=rand() % (500000)+1;
    }
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 0; i < 1000; ++i) {
        bst.IsFind_R(Number[i]);
    }
    QueryPerformanceCounter(&t2);
     cout<<"Search Time: "<<(t2.QuadPart-t1.QuadPart)*1000.0 /tc.QuadPart <<"ms"<<endl;
}
void TestDelete(BSTree bTree)
{
    int N=10000,j=0;
    double Delete[50];
    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 1; i <=500000; ++i) {
        bTree.Remove_R(i);
        if (i==N)
        {
            QueryPerformanceCounter(&t2);
            Delete[j]=((t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart);
            j++;
            N+=10000;
        }
    }
    N=10000;
    for (double i : Delete) {
        cout<<"N  "<<N<<" Delete Time:"<<i<<"ms"<<endl;
        N+=10000;
    }
}
void TestDelete_Back(BSTree bTree) {
    int N = 10000, j = 0;
    double Delete[50];
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 500000; i >= 1; i--) {
        bTree.Remove_R(i);
        if (500001 - i == N) {
            QueryPerformanceCounter(&t2);
            Delete[j] = ((t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart);
            j++;
            N += 10000;
        }
    }
    N = 10000;
    for (double i : Delete) {
        cout << "N  " << N << " Delete Time:" << i << "ms" << endl;
        N += 10000;
    }
}
void Random_Insert(BSTree bst)
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
        bst.Insert(x[i]);
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
void Random_Delete(BSTree bst)
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
        bst.Remove_R(x[i]);
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
    BSTree btree;
    Random_Insert(btree);
    //TestInsert(btree);
    TestSearch(btree);
    //TestDelete(btree);
    //TestDelete_Back(btree);
    Random_Delete(btree);

    return 0;
}