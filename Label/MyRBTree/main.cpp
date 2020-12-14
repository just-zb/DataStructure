#include <iostream>
#include "vector"
using namespace std;
enum Color
{
    RED,
    BLACK
};

struct RBTreeNode
{
    int _key;
    Color _color;
    RBTreeNode* _left;
    RBTreeNode* _right;
    RBTreeNode* _parent;

    RBTreeNode(const int& key)
            :_key(key)
            , _color(RED)
            , _left(NULL)
            , _right(NULL)
            , _parent(NULL)
    {}
};
class RBTree
{
public:
    RBTree():_root(NULL){}
    bool Insert(const int& key);
    //void Delete(const int& key);
    RBTreeNode*Search(RBTreeNode*root,const int& key);
    int GetMax();
    int GetMin();
    bool del(int key);
    void PreOrder()
    {
         _PreOrder(_root);
    }
    RBTreeNode*_root;
protected:
    void RotateL(RBTreeNode*& parent);
    void RotateR(RBTreeNode*& parent);
    //void Repair(RBTreeNode*& Goal);
    //RBTreeNode* Succeed(RBTreeNode*& Goal,RBTreeNode*root);
    void delLeafFix(RBTreeNode*DeleteNode);
    RBTreeNode*GetBrother(RBTreeNode*Goal);
    bool delNode(int key,RBTreeNode*cur,RBTreeNode*parent);
    void delLeafNode(RBTreeNode* target, RBTreeNode* replaceNode);
    void delOneChildNode(RBTreeNode*DelNode);
    void delTwoChildrenNode(RBTreeNode*target);
    RBTreeNode* success(RBTreeNode*node);
    void _PreOrder(RBTreeNode* root);
};
int RBTree::GetMax()
{
    RBTreeNode*root=_root;
    RBTreeNode*cur=NULL;
    while (root!=NULL)
    {
        cur=root;
        root=root->_right;
    }
    return cur->_key;
}
int RBTree::GetMin()
{
    RBTreeNode*root=_root;
    RBTreeNode*cur=NULL;
    while (root!=NULL)
    {
        cur=root;
        root=root->_left;
    }
    return cur->_key;
}
bool RBTree::Insert(const int& key)
{
    if (_root == NULL)
    {
        _root = new RBTreeNode(key);
        _root->_color = BLACK;
        return true;
    }
    RBTreeNode* cur = _root;
    RBTreeNode* parent = NULL;
    while (cur)
    {
        if (cur->_key > key)
        {
            parent = cur;
            cur = cur->_left;
        }
        else if (cur->_key < key)
        {
            parent = cur;
            cur = cur->_right;
        }
        else
        {
            return false;
        }
    }
    cur = new RBTreeNode(key);//now change cur to a new node,give the node key
    cur->_parent = parent;
    if (parent->_key > key)
        parent->_left = cur;
    else if (parent->_key < key)
        parent->_right = cur;
    while (parent&&parent->_color==RED)//the process of rotate
    {
        RBTreeNode* grandfather = parent->_parent;
        if (parent == grandfather->_left)
        {
            RBTreeNode* uncle = grandfather->_right;//node uncle
            if (uncle&&uncle->_color == RED)
            {
                grandfather->_color = RED;
                parent->_color =BLACK;
                uncle->_color = BLACK;

                cur = grandfather;
                parent = grandfather->_parent;//change the grandfather node into cur node
            }
            else if( (uncle&&uncle->_color==BLACK)||uncle==NULL)
            {
                if (cur == parent->_left)
                {
                    parent->_color = BLACK;
                    grandfather->_color = RED;
                    RotateR(grandfather);//for rotate right:because cur is the left node of the parent node
                }
                else//cur==parent->_right
                {
                    RotateL(parent);//for rotate left because cur is the right node
                    parent->_color = BLACK;
                    grandfather->_color = RED;
                    RotateR(grandfather);//rotate right,so why this step exist?
                }
                break;
            }
        }
        else if (parent == grandfather->_right)
        {
            RBTreeNode* uncle = grandfather->_left;
            if (uncle&&uncle->_color == RED)
            {
                grandfather->_color = RED;
                parent->_color = BLACK;
                uncle->_color = BLACK;

                cur = grandfather;
                parent = cur->_parent;
            }
            else if( (uncle&&uncle->_color == BLACK)||uncle==NULL)
            {
                if (cur == parent->_right)
                {
                    parent->_color = BLACK;
                    grandfather->_color = RED;
                    RotateL(grandfather);
                }
                else if (cur==parent->_left)
                {
                    RotateR(parent);
                    parent->_color = BLACK;
                    grandfather->_color = RED;
                    RotateL(grandfather);
                }
                break;
            }
        }
    }
    _root->_color = BLACK;
    return true;
}
RBTreeNode * RBTree::Search(RBTreeNode*root,const int &key)
{
    if (root==NULL)
    {
        return NULL;
    }
    else if (root->_key==key)
    {
        return root;
    }
    else if (root->_key<key)
    {
        return Search(root->_right,key);
    }
    else if(root->_key>key)
    {
        return Search(root->_left,key);
    }
}
bool RBTree::del(int key)
{
    if(_root!=NULL){
        return delNode(key, _root, NULL);
    }
    return false;
}
bool RBTree::delNode(int key, RBTreeNode *current, RBTreeNode *parent)
{
    if(NULL != current)
    {
        if(key>current->_key)
        {
            return delNode(key, current->_right, current);
        }
        if(key<current->_key)
        {
            return delNode(key, current->_left, current);
        }
        if(key==current->_key)
        {
            if((NULL != current->_left) && (NULL != current->_right))
            {
                delTwoChildrenNode(current);
                return true;
            }else{
                if((NULL == current->_left) && (NULL == current->_right))
                {
                    if (current==_root) { _root = NULL;return true;}
                    delLeafFix(current);
                    if(current->_key>parent->_key)
                    {
                        parent->_right = NULL;
                    }
                    else
                        {
                        parent->_left = NULL;
                    }
                    return true;
                }
                else
                    {
                    delOneChildNode(current);
                    return true;
                }
            }
        }
    }
    return false;
}

void RBTree::delLeafFix(RBTreeNode *deletedNode)
{
    while((deletedNode != _root) && (BLACK == deletedNode->_color)){
        RBTreeNode *parent = deletedNode->_parent;
        RBTreeNode *brother = GetBrother(deletedNode);
        if (brother==NULL)return;
        if(deletedNode->_key>parent->_key){
            if(RED == brother->_color){
                brother->_color = BLACK;
                brother->_right->_color = RED;
                RotateR(parent);
                break;
            }else{
                if((NULL == brother->_left) && (NULL == brother->_right)){
                    brother->_color = RED;
                    deletedNode = parent;
                }else{
                    if((NULL != brother->_left) && (RED == brother->_left->_color)){
                        brother->_color= parent->_color;
                        parent->_color = BLACK;
                        brother->_left->_color = BLACK;
                        RotateR(parent);
                        break;
                    }else{
                        brother->_right->_color= BLACK;
                        brother->_color= RED;
                        RotateL(brother);
                    }
                }
            }
        }else{
            if(RED == brother->_color){
                brother->_color = BLACK;
                brother->_left->_color = RED;
                RotateL(parent);
                break;
            }else{
                if((NULL == brother->_left) && (NULL == brother->_right))
                {
                    brother->_color = RED;
                    deletedNode = parent;
                }
                else
                {
                    if((NULL != brother->_right) && (RED == brother->_right->_color))
                    {
                        brother->_color = parent->_color;
                        parent->_color = BLACK;
                        brother->_right->_color = BLACK;
                        RotateL(parent);
                        break;
                    }
                    else
                    {
                        if (brother->_left!=NULL) { brother->_left->_color = BLACK; }
                        brother->_color = RED;
                        RotateR(brother);
                    }
                }
            }
        }
    }
    deletedNode->_color = BLACK;
}
void RBTree::delLeafNode(RBTreeNode* target, RBTreeNode* replaceNode)
{
    target->_key = replaceNode->_key;
    delLeafFix(replaceNode);
    if(replaceNode == replaceNode->_parent->_right){
        replaceNode->_parent->_right = NULL;
    }else{
        replaceNode->_parent->_left  =  NULL;
    }
}
void RBTree::delOneChildNode(RBTreeNode*delNode)
{
    RBTreeNode* replaceNode = (NULL == delNode->_left) ? delNode->_right : delNode->_left;
    delLeafNode(delNode, replaceNode);
}
void RBTree::delTwoChildrenNode(RBTreeNode *target)
{
    RBTreeNode* replaceNode = success(target);
    if((NULL == replaceNode->_right) && (NULL == replaceNode->_left)){
        delLeafNode(target, replaceNode);
    }else{
        target->_key = replaceNode->_key;
        delOneChildNode(replaceNode);
    }
}



void RBTree::RotateL(RBTreeNode*& parent)
{
    RBTreeNode* ppNode = parent->_parent;
    RBTreeNode* subR = parent->_right;
    RBTreeNode* subRL = subR->_left;

    parent->_right = subRL;
    if (subRL) subRL->_parent = parent;

    subR->_left = parent;
    parent->_parent = subR;

    if (ppNode == NULL)
    {
        subR->_parent = NULL;
        _root = subR;
    }
    else
    {
        subR->_parent = ppNode;
        if (ppNode->_left == parent)
            ppNode->_left = subR;
        else if (ppNode->_right == parent)
            ppNode->_right = subR;
    }
    parent = subR;
}
void RBTree::RotateR(RBTreeNode*& parent)
{
    RBTreeNode* ppNode = parent->_parent;
    RBTreeNode* subL = parent->_left;
    RBTreeNode* subLR = subL->_right;

    parent->_left = subLR;
    if (subLR) subLR->_parent = parent;

    subL->_right = parent;
    parent->_parent = subL;

    if (ppNode==NULL)
    {
        subL->_parent = NULL;
        _root = subL;
    }
    else
    {
        subL->_parent = ppNode;
        if (parent == ppNode->_left)
            ppNode->_left = subL;
        else
            ppNode->_right = subL;
    }
    parent = subL;
}
/*void RBTree::Delete(const int &key)
{
    RBTreeNode* cur = Search(_root,key);
    if (cur==NULL)
    {
        return;
    }
    RBTreeNode*parent=cur->_parent;
            if (cur->_left==NULL&&cur->_right==NULL&&cur->_color==RED)//just delete ,mode A
            {
                if (cur->_color==RED)
                {
                    if(parent->_left==cur)parent->_left=NULL;
                    else parent->_right=NULL;
                }
                else
                {
                    Repair(cur);
                }
            }
            else if (cur->_left!=NULL&&cur->_right==NULL)//mode C
            {
                cur->_key=cur->_left->_key;
                //for cur->_left:it's always a leaf,just change it with cur,but not change color
                if (cur->_left->_color==RED)
                {
                    cur->_left=NULL;
                }
                else
                {
                    Repair(cur->_left);//repair
                }
            }
            else if (cur->_left==NULL&&cur->_right!=NULL)//mode C
            {
                cur->_key=cur->_right->_key;
                //for cur->_right:it's always a leaf,just change it with cur,but not change color
                if (cur->_right->_color==RED)
                {
                    cur->_right=NULL;
                }
                else
                {
                    Repair(cur->_right);//repair
                }
            }
            else//mode D
            {
                //how to find succeed?
                RBTreeNode*succeed=Succeed(cur,_root);
                cur->_key=succeed->_key;//It's no need to change the color,only change the key
                if (succeed->_right==NULL&&succeed->_left!=NULL)//c
                {
                    succeed->_key=succeed->_left->_key;
                    if (succeed->_left->_color==RED)//A
                    {
                        succeed->_left=NULL;
                    }
                    else//B
                    {
                        Repair(succeed->_left);
                    }
                }
                else if (succeed->_right!=NULL&&succeed->_left==NULL)
                {
                    succeed->_key=succeed->_right->_key;
                    if (succeed->_right->_color==RED)//A
                    {
                        succeed->_right=NULL;
                    }
                    else//B
                    {
                        Repair(succeed->_right);
                    }
                }
                else
                {
                    if (succeed->_color==RED)//A
                    {
                        if (succeed->_parent->_left==succeed)succeed->_parent->_left=NULL;
                        else succeed->_parent->_right=NULL;
                    }
                    else//B
                    {
                        Repair(succeed);
                    }
                }

            }
}*/
/*void RBTree::Repair(RBTreeNode *& Goal)
{
    //to change the structure of the tree and delete node Goal
    RBTreeNode*parent=Goal->_parent;
    RBTreeNode*brother;
    if (parent->_left==Goal)
    {
        brother=parent->_right;
        parent->_left=NULL;
        if (brother->_color==RED)
        {
            brother->_color=BLACK;
            brother->_left->_color=RED;
            RotateL(parent);
        }
        else
        {
            if (brother->_left!=NULL&&brother->_right!=NULL)
            {
                brother->_color=parent->_color;
                brother->_right->_color=BLACK;
                parent->_color=BLACK;
                RotateL(parent);
            }
            else if (brother->_left==NULL&&brother->_right!=NULL)
            {
                brother->_color=parent->_color;
                parent->_color=BLACK;
                brother->_right->_color=BLACK;
                RotateL(parent);
            }
            else if(brother->_left!=NULL&&brother->_right==NULL)
            {
                brother->_left->_color=BLACK;
                brother->_color=RED;
                RotateR(brother);
                /////////////////////////
                //the change upside change
                brother=Goal->_parent->_right;
                parent=Goal->_parent;
                /////////////////////////
                brother->_color=parent->_color;
                parent->_color=BLACK;
                brother->_right->_color=BLACK;
                RotateL(parent);
            }
            else
            {
                brother->_color=RED;
            }
        }
    }
    else
    {
        brother=parent->_left;
        parent->_right=NULL;
        if (brother->_color==RED)
        {
            brother->_color=BLACK;
            brother->_right->_color=RED;
            RotateR(parent);
        }
        else
        {
            if (brother->_right!=NULL&&brother->_left!=NULL)
            {
                brother->_color=parent->_color;
                brother->_left->_color=BLACK;
                parent->_color=BLACK;
                RotateR(parent);
            }
            else if (brother->_right==NULL&&brother->_left!=NULL)
            {
                brother->_color=parent->_color;
                parent->_color=BLACK;
                brother->_left->_color=BLACK;
                RotateR(parent);
            }
            else if(brother->_right!=NULL&&brother->_left==NULL)
            {
                brother->_right->_color=BLACK;
                brother->_color=RED;
                RotateL(brother);
                /////////////////////////
                brother=Goal->_parent->_right;
                parent=Goal->_parent;
                ////////////////////////
                brother->_color=parent->_color;
                parent->_color=BLACK;
                brother->_left->_color=BLACK;
                RotateR(parent);
            }
            else
            {
                brother->_color=RED;
            }
        }
    }
}*/
/*RBTreeNode* RBTree::Succeed(RBTreeNode *&Goal,RBTreeNode*root)
{
    if (root==NULL)
    {
        return NULL;
    }
    if (Goal->_key>=root->_key)
    {
        return Succeed(Goal,root->_right);
    }
    else
    {
        RBTreeNode *left=Succeed(Goal,root->_left);
        return left==NULL?root:left;
    }
}*/
void RBTree::_PreOrder(RBTreeNode *root) {
    if (root == NULL)
        return;
    cout << root->_key;
    if (root->_color==RED)cout<<"(R) ";
    else cout<<"(B) ";
    _PreOrder(root->_left);
    _PreOrder(root->_right);

}
RBTreeNode * RBTree::GetBrother(RBTreeNode *node)
{
    if(NULL== node){
        return NULL;
    }
    RBTreeNode* parent = node->_parent;
    if(NULL == parent){
        return NULL;
    }
    if(node->_key>parent->_key){
        return parent->_left;
    }else{
        return parent->_right;
    }
}
RBTreeNode*RBTree::success(RBTreeNode* node) {
    if (node == NULL){
        return NULL;
    }
    if (NULL != node->_right) {
        RBTreeNode* p = node->_right;
        while (NULL != p->_left){
            p = p->_left;
        }
        return p;
    } else {
        RBTreeNode* p = node->_parent;
        RBTreeNode* ch = node;
        while (p != NULL && ch == p->_right) {
            ch = p;
            p = p->_parent;
        }
        return p;
    }
}


int main() {
    int N;cin>>N;
    int temp;
    RBTree MyRBTree;
    for (int i = 0; i < N; ++i) {
        cin>>temp;
        MyRBTree.Insert(temp);
    }
    int DeleteNum;cin>>DeleteNum;
    vector<int>a;
    for (int i = 0; i < DeleteNum; ++i) {
        cin>>temp;
        a.push_back(temp);
    }
    MyRBTree.PreOrder();
    cout<<endl;
    cout<<MyRBTree.GetMin()<<' '<<MyRBTree.GetMax()<<endl;
    for (int i = 0; i < DeleteNum; ++i) {
        MyRBTree.del(a[i]);
    }
    if(MyRBTree._root==NULL)cout<<"Null";
    else MyRBTree.PreOrder();
    return 0;
}
