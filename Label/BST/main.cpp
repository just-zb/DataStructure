#include<iostream>
#include<stack>
using namespace std;

struct BSTNode
{
    int _key;
    BSTNode* _left;
    BSTNode* _right;
    explicit BSTNode(const int& key,const int& value=1):_key(key), _left(nullptr),_right(nullptr){}
};


class BSTree
{
public:
    BSTree():_root(nullptr){}
    bool Insert(const int& key);
    bool Insert_R(const int& key)
    {
        return Insert_R(_root, key);
    }
    BSTNode* Find(const int& key);
    BSTNode* Find_R(const int& key)
    {
        return Find_R(_root, key);
    }
    bool Remove(const int& key);
    bool Remove_R(const int& key)
    {
        return Remove_R(_root, key);
    }
    void NonR_InOrderPrintTree();
protected:
    bool Insert_R(BSTNode*& root, const int& key);
    BSTNode* Find_R(BSTNode*& root, const int& key);
    bool Remove_R(BSTNode*& root, const int& key);
protected:
    BSTNode* _root;
};

bool BSTree::Insert(const int& key)
{
    if (_root == nullptr)
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
bool BSTree::Insert_R(BSTNode*& root, const int& key)
{
    if (root == nullptr)
    {
        root = new BSTNode(key);
        return true;
    }
    else if (root->_key<key)
    {
        return Insert_R(root->_right, key);
    }
    else if (root->_key>key)
    {
        return Insert_R(root->_left, key);
    }
    else
    {
        return false;
    }
}

BSTNode* BSTree::Find(const int& key)
{
    if (_root == nullptr)
        return nullptr;
    BSTNode* cur = _root;
    while (cur)
    {
        if (cur->_key == key)
            return cur;
        else if (cur->_key > key)
            cur = cur->_left;
        else
            cur = cur->_right;
    }
    return nullptr;
}
BSTNode*  BSTree::Find_R(BSTNode*& root, const int& key)
{
    if (_root == nullptr)
        return nullptr;
    BSTNode* cur = root;

    if (root->_key == key)
        return root;
    else if (root->_key > key)
        return Find_R(root->_left, key);
    else
        return Find_R(root->_right, key);
}

bool BSTree::Remove(const int& key)
{
    if (_root == nullptr)
        return false;
    if (_root->_left == nullptr&&_root->_right == nullptr)
    {
        if (_root->_key == key)
        {
            delete _root;
            _root = nullptr;
            return true;
        }
        else
            return false;
    }
    BSTNode* cur = _root;
    BSTNode* parent =nullptr;
    BSTNode* del = nullptr;
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
        {
            del = cur;
            if (cur->_left == nullptr)
            {
                if (cur->_right != nullptr)
                {
                    if (parent->_left == cur)parent->_left = cur->_right;
                    else if (parent->_right == cur)parent->_right = cur->_right;
                }
                else
                {
                    if (parent->_left == cur)parent->_left = nullptr;
                    else if (parent->_right == cur)parent->_right = nullptr;
                }
            }
            else if (cur->_right == nullptr)
            { //        /   >
                if (parent->_left == cur)parent->_left = cur->_left;
                else if (parent->_right == cur)parent->_right = cur->_left;
            }
            else if (cur->_left && cur->_right)
            {
                BSTNode* FirstLeft = cur->_right;
                while (FirstLeft->_left)
                {
                    parent = FirstLeft;
                    FirstLeft = FirstLeft->_left;
                }
                del = FirstLeft;
                swap(cur->_key, FirstLeft->_key);
                if (parent->_left == FirstLeft)
                {
                    parent->_left = FirstLeft->_right;
                }
                else if (cur->_right == FirstLeft)
                {
                    cur->_right = FirstLeft->_right;
                }
            }
            delete del;
            return true;
        }
    }
    return false;
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
void BSTree::NonR_InOrderPrintTree()
{
    if (_root == nullptr)
        return;
    stack<BSTNode*> sc;
    BSTNode* cur = _root;
    while (cur || !sc.empty())
    {
        while (cur)
        {
            sc.push(cur);
            cur = cur->_left;
        }
        if (!sc.empty())
        {
            cur = sc.top();
            cout << cur->_key << " ";
            sc.pop();
            cur = cur->_right;
        }
    }
    cout << endl;
}


int main()
{
    int N=1000;
        BSTree bst;
        for (int i = 1; i <= N; ++i) {
           bst.Insert(i);
        }
        for (int i = 1; i <=N ; ++i) {
            bst.Remove_R(i);
        }

    cout<<"ALL DOWN";

    return 0;
}