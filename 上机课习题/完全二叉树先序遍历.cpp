/*
题目描述
给出一棵完全二叉树的先序遍历，输出其后序遍历。结点均为不重复的单个英文字母，区分大小写。结点总数小于52。

Input Format

输入先序字符串

Output Format
后序遍历字符串
*/
#include<iostream>
using namespace std;

int n,index = 0;

void getTree(int x,char *tree,string pre){//获取完全二叉树各结点对应的值
    if(x > n)
        return;
    tree[x] = pre[index++];
    getTree(x<<1,tree,pre);
    getTree((x<<1)+1,tree,pre);
}

void getPost(int x,char *tree,char *pos){//求完全二叉树的后序遍历数组
    if(x > n)
        return;
    getPost(x<<1,tree,pos);
    getPost((x<<1)+1,tree,pos);
    pos[index++] = tree[x];
}

int main() {
    index = 0;
    string pre;
    cin>>pre;
    n=pre.size();
    char tree[n],pos[n];
    getTree(1,tree,pre);
    index = 0;
    getPost(1,tree,pos);
    for (int i = 0; i < n; i++)//输出后序遍历
        cout << pos[i];
    return 0;
}
