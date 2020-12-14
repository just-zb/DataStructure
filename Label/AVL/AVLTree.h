//
// Created by 14535 on 2020/12/8.
//

#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H
#pragma once

//	AVL树的节点类
struct AVLTreeNode
{
    int _key;
    int  _bf;			//平衡因子 -1,0,1		(每个节点的平衡因子等于右子树的高度减去左子树的高度)
    AVLTreeNode* _parent;	//指向父节点的指针
    AVLTreeNode* _left;			//指向左孩子的指针
    AVLTreeNode* _right;		//指向右孩子的指针

    AVLTreeNode(const int& key =0)
            :_key(key)
            , _bf(0)
            , _parent(NULL)
            , _left(NULL)
            , _right(NULL)
    {}
};


class AVLTree
{
public:
    AVLTree():_root(NULL){}
    bool Insert(const int& key);
    bool Delete(const int& key);
    bool Search(const int& key);
    void  InOrder(){_InOrder(_root);cout << endl;}
    bool IsBalance(){return _IsBalance(_root);}
    int Height(){return _Height(_root);}
protected:
    void _RotateR(AVLTreeNode*&  parent);
    void _RotateL(AVLTreeNode*&  parent);
    void _RotateLR(AVLTreeNode*&  parent);
    void _RotateRL(AVLTreeNode*&  parent);
    void _InOrder(AVLTreeNode* root);
    bool _IsBalance(AVLTreeNode* root);
    int _Height(AVLTreeNode* root);
protected:
    AVLTreeNode* _root; //根节点
};
//插入
bool AVLTree::Insert(const int& key)
{
    //1.空树
    if (_root == NULL)
    {
        _root = new AVLTreeNode(key);
        return true;
    }

    //2.AVL树不为NULL
    AVLTreeNode* parent = NULL;
    AVLTreeNode* cur = _root;
    //找到数据插入位置
    while (cur)
    {
        if (cur->_key < key)
        {
            parent = cur;
            cur = cur->_right;
        }
        else	if (cur->_key > key)
        {
            parent = cur;
            cur = cur->_left;
        }
        else
        {
            return false;
        }
    }
    //插入数据
    cur = new AVLTreeNode(key);
    cur->_parent = parent;
    if (parent->_key > key)
        parent->_left = cur;
    else
        parent->_right = cur;

    while (parent)
    {
        //更新平衡因子
        if (cur == parent->_left)
            parent->_bf--;
        else if (cur == parent->_right)
            parent->_bf++;

        //检验平衡因子是否合法
        if (parent->_bf == 0)
            break;
        else if (parent->_bf == -1 || parent->_bf == 1)
        {	// 回溯上升 更新祖父节点的平衡因子并检验合法性
            cur = parent;
            parent = cur->_parent;
        }
        else   //	2 -2 平衡因子不合法 需要进行旋转 降低高度
        {
            if (parent->_bf == 2)
            {
                if (cur->_bf == 1)
                    _RotateL(parent);
                else
                    _RotateRL(parent);
            }
            else if (parent->_bf == -2)
            {
                if (cur->_bf == -1)
                    _RotateR(parent);
                else
                    _RotateLR(parent);
            }
            break;
        }
    }
}
//删除
bool AVLTree::Delete(const int &key)
{

}
//搜索
bool AVLTree::Search(const int &key)
{

}
//右旋
void AVLTree::_RotateR(AVLTreeNode*&  parent)
{
    AVLTreeNode* subL = parent->_left;
    AVLTreeNode* subLR = subL->_right;
    AVLTreeNode* ppNode = parent->_parent;		//标记祖先节点
    //1.构建parent子树 将parent和subLR链接起来
    parent->_left = subLR;
    if (subLR) subLR->_parent = parent;
    //2.构建subL子树 将subL与parent链接起来
    subL->_right = parent;
    parent->_parent = subL;
    //3.将祖先节点与sunL链接起来
    if (ppNode == NULL)
    {	//如果祖先为NULL，说明当前subL节点为根节点
        subL->_parent = NULL;
        _root = subL;
    }
    else
    {
        subL->_parent = ppNode;
        if (ppNode->_left == parent)
            ppNode->_left = subL;
        else if (ppNode->_right == parent)
            ppNode->_right = subL;
    }
    //4.重置平衡因子
    parent->_bf = 0;
    subL->_bf = 0;
    //5.更新subL为当前父节点
    parent = subL;
}
//左旋
void AVLTree::_RotateL(AVLTreeNode*&  parent)
{
    AVLTreeNode* subR = parent->_right;
    AVLTreeNode* subRL = subR->_left;
    AVLTreeNode* ppNode = parent->_parent;		//标记祖先节点

    //1.构建parent子树 链接parent和subRL
    parent->_right = subRL;
    if (subRL) subRL->_parent = parent;
    //2.构建subR子树 链接parent和subR
    subR->_left = parent;
    parent->_parent = subR;
    //3.链接祖先节点和subR节点
    subR->_parent = ppNode;
    if (ppNode== NULL)
    {//如果祖先节点为NULL，说明目前的根节点为subR
        _root = subR;
    }
    else
    {	//将祖先节点和subR节点链接起来
        if (parent == ppNode->_left)
            ppNode->_left = subR;
        else
            ppNode->_right = subR;
    }
    //4.重置平衡因子
    parent->_bf = 0;
    subR->_bf = 0;
    //5.更新subR为当前父节点
    parent = subR;
}
//左右双旋
void AVLTree::_RotateLR(AVLTreeNode*&  parent)
{
    AVLTreeNode* pNode = parent;
    AVLTreeNode* subL = parent->_left;
    AVLTreeNode* subLR = subL->_right;
    int bf = subLR->_bf;

    _RotateL(parent->_left);
    _RotateR(parent);

    if (bf == 1)
    {
        pNode->_bf = 0;
        subL->_bf = -1;
    }
    else if (bf == -1)
    {
        pNode->_bf = 1;
        subL->_bf = 0;
    }
    else
    {
        pNode->_bf = 0;
        subL->_bf = 0;
    }

}
//右左双旋
void AVLTree::_RotateRL(AVLTreeNode*&  parent)
{
    AVLTreeNode* pNode = parent;
    AVLTreeNode* subR = parent->_right;
    AVLTreeNode* subRL = subR->_left;
    int bf = subRL->_bf;

    _RotateR(parent->_right);
    _RotateL(parent);

    if (bf == 1)
    {
        pNode->_bf = 0;
        subR->_bf = -1;
    }
    else if (bf == -1)
    {
        pNode->_bf = 1;
        subR->_bf = 0;
    }
    else
    {
        pNode->_bf = 0;
        subR->_bf = 0;
    }
}
//中序打印
void AVLTree::_InOrder(AVLTreeNode* root)
{
    if (root == NULL)
        return;
    _InOrder(root->_left);
    cout << root->_key << " ";
    _InOrder(root->_right);
}
//求AVL树的高度
int AVLTree::_Height(AVLTreeNode* root)
{
    if (root == NULL)
        return 0;

    int high = 0;
    int left = _Height(root->_left);
    int right = _Height(root->_right);

    if (left > right)
        high = left;
    else
        high = right;

    if (root != _root)return 1 + high;
    else
        return high;
}
//检验AVL树是否失衡
bool AVLTree::_IsBalance(AVLTreeNode* root)
{
    if (root == NULL)
        return true;
    int bf = _Height(root->_right) - _Height(root->_left);
    if (root->_bf != bf)
    {
        cout << root->_key<<endl;
        return false;
    }
    //bf的绝对值小于2，并且左树和右树都平衡则以root为根的子树才处于平衡状态
    return abs(bf)<2&&_IsBalance(root->_left) && _IsBalance(root->_right);
}



#endif //AVL_AVLTREE_H
