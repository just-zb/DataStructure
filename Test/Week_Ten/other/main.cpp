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
