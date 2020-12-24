/*
题目描述
在AVL树中，任何节点的两个子树的高度最多相差1；如果它们高度相差不止1，则需要重新平衡以恢复这种属性。
现在给定一个插入序列， 一个一个地将键值插入初始为空的AVL树中，输出得到的AVL树的层次顺序遍历序列，并判断它是否是一个完全二叉树。

输入格式：

第一行包含一个正整数N(<= 20)。然后在下一行给出N个不同的整数键。所有数字都用空格隔开。

输出格式：

第一行打印得到的AVL树的层次顺序遍历序列。所有数字都必须用空格隔开，并且行尾必须没有多余的空格。然后在下一行中，如果树为完全二叉树，则打印“Yes”;如果不是，则打印“No”。

样例输入1：

5
88 70 61 63 65 

样例输出1：

70 63 88 61 65

Yes

样例输入2：
10
62 88 58 47 35 73 51 99 37 93 

样例输出2：
62 47 88 35 58 73 99 37 51 93
No  
*/
#include <iostream>
#include "queue"
#include "math.h"
using namespace std;
struct node {
    int val;
    struct node *left, *right;
};
node *rotateLeft(node *root) {
    node *t = root->right;
    root->right = t->left;
    t->left = root;
    return t;
}
node *rotateRight(node *root) {
    node *t = root->left;
    root->left = t->right;
    t->right = root;
    return t;
}
node *rotateLeftRight(node *root) {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
}
node *rotateRightLeft(node *root) {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
}
int getHeight(node *root) {
    if(root == NULL) return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}
node *insert(node *root, int val) {
    if(root == NULL) {
        root = new node();
        root->val = val;
        root->left = root->right = NULL;
    } else if(val < root->val) {
        root->left = insert(root->left, val);
        if(getHeight(root->left) - getHeight(root->right) == 2)
            root = val < root->left->val ? rotateRight(root) : rotateLeftRight(root);
    } else {
        root->right = insert(root->right, val);
        if(getHeight(root->left) - getHeight(root->right) == -2)
            root = val > root->right->val ? rotateLeft(root) : rotateRightLeft(root);
    }
    return root;
}
void travellevel(node*root,int n) {//层序遍历
    queue<node>temp;
    int total=0,lex=0,rix=0;//lex与rix记录在特定条件下左孩子与右孩子入队的个数
    bool isCBT;
    temp.push(*root);
    while (!temp.empty()){
        node x=temp.front();
        cout<<x.val;total+=1;
        temp.pop();
        if (x.left) { temp.push(*x.left);if (total<=ceil(n/2))lex+=1;}
        if (x.right) { temp.push(*x.right);if (total<=floor(n/2)-1)rix+=1;}
        if (total!=n)cout<<' ';
    }
    if (lex==ceil(n/2)&&rix==floor(n/2)-1)cout<<endl<<"Yes";
    else cout<<endl<<"No";
}
int main() {
    int n, val;
    cin>>n;
    node *root = NULL;
    for(int i = 0; i < n; i++) {
        cin>>val;
        root = insert(root, val);
    }
    travellevel(root,n);
    return 0;
}
