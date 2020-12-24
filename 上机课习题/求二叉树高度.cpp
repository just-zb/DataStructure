/*
题目描述
给出一棵二叉树的先序遍历和中序遍历序列，计算该二叉树的高度。其中，二叉树的先序和中序遍历序列为不包含重复英文字母（区别大小写）的字符串。

Input Format

二叉树结点的总个数n<=50

然后输入先序和中序遍历序列，两个序列长度均为n。  

Output Format
二叉树高度（整数） ，叶子结点高度为1 

Example
Input
9
ABDGHCEIF
GDHBAEICF

Output
4
*/
#include <iostream>
using namespace std;
class binnode{
public:
    binnode *ri,*le;
    binnode():ri(NULL),le(NULL){}
};
binnode*py(char*pre,char*in,int n){
    int i=0;
    binnode *T=new binnode;
    if (!n)return NULL;
    else{
        while (in[i]!=pre[0])i++;
        T->le=py(pre+1,in,i);
        T->ri=py(pre+i+1,in+i+1,n-i-1);
    }
    return T;
}
int max(int a,int b){return (a>b)?a:b;}
int getHeigh(binnode *root){
    if(!root)return 0;
    else{
        int  heigh=1;
        heigh+=max(getHeigh(root->le),getHeigh(root->ri));
        return heigh;
    }

}
int main() {
    int n;
    cin>>n;
    char pre[n],in[n];
    for (int i = 0; i < n; ++i) {
        cin>>pre[i];
    }
    for (int i = 0; i < n; ++i) {
        cin>>in[i];
    }
    cout<<getHeigh(py(pre,in,n));

    return 0;
}
