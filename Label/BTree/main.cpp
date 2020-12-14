#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include"BTree.h"
using namespace std;

void Test()
{
    BTree<int,512> bt;
    int temp;
    for (int i = 1; i <= 10000; ++i) {
        bt.Insert(i);
    }
    bt.InOrder();
}
int main()
{
    Test();
    system("pause");
    return 0;
}