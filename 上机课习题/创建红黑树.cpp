/*
题目描述
RB（红黑）树除了是一个二叉搜索树之外，还满足下面规则：
    1）每个结点要么是红的，要么是黑的。

    2）根结点是黑的。

    3）每个叶结点，即空结点是黑的。

    4）如果一个结点是红的，那么它的俩个儿子都是黑的。

    5）对每个结点，从该结点到其子孙结点的所有路径上包含相同数目的黑结点。

在给定插入序列的情况下，创建RB树，并输出最大值、最小值。
输入格式：

对于每种情况，第一行包含一个正整数N(<=20)。后边为N个不同的整数值，每个整数值以空格隔开。

第二行为要删除的节点个数M，后边为M个不同的整数值，以空格隔开。

输出格式：

第一行为RB树的前序遍历序列，以空格隔开，其中节点值后使用(B)和(R)表示节点的颜色；

第二行为RB树的最大值，最小值，以空格隔开；

第三行为删除M个节点之后的RB树的前序遍历序列，以空格隔开，若树为空，则输出Null；
*/
#include <iostream>
#include "vector"
using namespace std;
enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
    int data;
    int color;
    Node *left, *right, *parent;

    explicit Node(int);
};

class RBTree
{
private:
    Node *root;
protected:
    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    void fixInsertRBTree(Node *&);
    void fixDeleteRBTree(Node *&);
    void inorderBST(Node *&);
    void preorderBST(Node *&);
    int getColor(Node *&);
    void setColor(Node *&, int);
    Node *minValueNode(Node *&);
    Node *maxValueNode(Node *&);
    Node* insertBST(Node *&, Node *&);
    Node* deleteBST(Node *&, int);
    int getBlackHeight(Node *);
public:
    RBTree();
    void insertValue(int);
    void deleteValue(int);
    void preorder();
    int GetMax();
    int GetMin();
};
Node::Node(int data) {
    this->data = data;
    color = RED;
    left = right = parent = nullptr;
}
RBTree::RBTree() {
    root = nullptr;
}
int RBTree::getColor(Node *&node) {
    if (node == nullptr)
        return BLACK;

    return node->color;
}
void RBTree::setColor(Node *&node, int color) {
    if (node == nullptr)
        return;

    node->color = color;
}
Node* RBTree::insertBST(Node *&root, Node *&ptr) {
    if (root == nullptr)
        return ptr;

    if (ptr->data < root->data) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->data > root->data) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}
void RBTree::insertValue(int n) {
    Node *node = new Node(n);
    root = insertBST(root, node);
    fixInsertRBTree(node);
}
void RBTree::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}
void RBTree::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}
void RBTree::fixInsertRBTree(Node *&ptr) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}
void RBTree::fixDeleteRBTree(Node *&node) {
    if (node == nullptr)
        return;

    if (node == root) {
        root = nullptr;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}
Node* RBTree::deleteBST(Node *&root, int data) {
    if (root == nullptr)
        return root;

    if (data < root->data)
        return deleteBST(root->left, data);

    if (data > root->data)
        return deleteBST(root->right, data);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    Node *temp = minValueNode(root->right);
    root->data = temp->data;
    return deleteBST(root->right, temp->data);
}
void RBTree::deleteValue(int data) {
    Node *node = deleteBST(root, data);
    fixDeleteRBTree(node);
}
void RBTree::inorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;

    inorderBST(ptr->left);
    cout << ptr->data << " " << ptr->color << endl;
    inorderBST(ptr->right);
}
void RBTree::preorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;
    cout << ptr->data;
    if (ptr->color==RED)cout<<"(R) ";
    else cout<<"(B) ";
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}
void RBTree::preorder() {
    if (root==NULL) { cout << "Null";return; }
    else
        preorderBST(root);
}
Node *RBTree::minValueNode(Node *&node) {

    Node *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}
Node* RBTree::maxValueNode(Node *&node) {
    Node *ptr = node;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}
int RBTree::GetMin()
{
    return minValueNode(root)->data;
}
int RBTree::GetMax()
{
    return maxValueNode(root)->data;
}
int main() {
    int N,temp;cin>>N;
    RBTree MyRBTree;
    for (int i = 0; i < N; ++i) {
        cin>>temp;
        MyRBTree.insertValue(temp);
    }
    int DeleteNum;cin>>DeleteNum;
    vector<int>a;
    for (int i = 0; i < DeleteNum; ++i) {
        cin>>temp;
        a.push_back(temp);
    }
    MyRBTree.preorder();
    cout<<endl;
    cout<<MyRBTree.GetMin()<<' '<<MyRBTree.GetMax()<<endl;
    for (int i = 0; i < DeleteNum; ++i) {
        MyRBTree.deleteValue(a[i]);
    }
    MyRBTree.preorder();
    return 0;
}