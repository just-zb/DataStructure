/*
题目描述
自然界有一种物质，同种两个物质结合需要消耗的能量为两个物质的质量和。假设只能两两结合，根据输入的该类物质碎片质量，求全部碎片结合成一个整体，需要的最小能量。

Input Format

碎片总个数0<n<=50

n个碎片的质量【取值范围（0，10000）的n个整数】 

Output Format
两两结合需要的最小能量 

Example
Input
5
1 4 5 2 6

Output
39
*/
#include <iostream>
using namespace std;
#include "vector"
int find(vector<int>a,int n){//找出a中的最小值和次要小的值，并删除后返回
    int team=0;
    for (int k = 0; k < n-1; ++k) {
        int temp=a[0],j=0;
        for (int i = 0; i < a.size(); ++i) {
            if (a[i]<=temp) {
                temp = a[i];
                j = i;
            }
        }
        auto it =a.begin()+j;
        a.erase(it);
        int temp1=a[0];
        for (int i = 0; i < a.size(); ++i) {
            if (a[i]<=temp1) {
                temp1 = a[i];
                j = i;
            }
        }
        it =a.begin()+j;
        a.erase(it);
        temp+=temp1;
        a.push_back(temp);
        team+=temp;
    }
    return team;
}
int main() {
    int size,temp;
    cin>>size;
    vector<int>a;
    for (int i = 0; i < size; ++i) {
        cin>>temp;
        a.push_back(temp);
    }
    cout<<find(a,size);
    return 0;
}
