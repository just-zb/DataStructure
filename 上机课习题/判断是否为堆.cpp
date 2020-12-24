/*
题目描述
请判断输入的整数序列是否为堆。

如果为最大堆，请输出“max ”以及整理后的最小堆，整数序列数字之间有空格，最后无空格。

如果为最小堆，请输出“min ” 以及整理后的最大堆，整数序列数字之间有空格，最后无空格。

如果不为堆，请输出整理后的最大堆，整数序列数字之间有空格，最后无空格。

如果既是最大堆也是最小堆，请只输出“max min ”

Input Format

先输入整数序列个数n 0<n<1000

然后输入n个整数序列，整数取值范围【-100000，100000】

Output Format
最大堆或最小堆序列

Example
Input
10
-8 8 -9 10 -2 1 -6 -9 7 2 

Output
10 8 1 7 2 -9 -6 -9 -8 -2
*/
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include "math.h"
using namespace std;
int judge(int*a,int n){
    int i,career=30;
    for (i = 0; i < n;i++) {//最小堆
        if ((a[i] > a[i * 2+1] && 2 * i +1< n) || (a[i] > a[i * 2 + 2] && (2 * i + 2) < n)) {
            career-=10;
            break;
        }
    }
    for (i = 0; i < n;i++) {//最大堆
        if ((a[i] < a[i * 2+1] && 2 * i+1 < n) || (a[i] < a[i * 2 + 2] && (2 * i + 2) < n)){
            career-=20;
            break;
        }
    }
    return career;
}
void adjust1(int arr[], int len, int index)
{
    int left = 2*index + 1;
    int right = 2*index + 2;
    int maxIdx = index;
    if(left<len && arr[left] >= arr[maxIdx]) maxIdx = left;
    if(right<len && arr[right] >= arr[maxIdx]) maxIdx = right;  // maxIdx是3个数中最大数的下标
    if (arr[left]==arr[right]&&right<len&&left<len&&arr[right] >= arr[maxIdx])maxIdx=right;//youchen
    if(maxIdx != index)                 // 如果maxIdx的值有更新
    {
        swap(arr[maxIdx], arr[index]);
        adjust1(arr, len, maxIdx);       // 递归调整其他不满足堆性质的部分
    }
}
void adjust2(int arr[], int len, int index){
    int left = 2*index + 1;
    int right = 2*index + 2;
    int minIdx = index;
    if(left<len && arr[left] <= arr[minIdx]) minIdx = left;
    if(right<len && arr[right] <=arr[minIdx]) minIdx = right;  // minIdx是3个数中最小数的下标
    if (arr[left]==arr[right]&&right<len&&left<len&&arr[right] <=arr[minIdx])minIdx=right;//youchen
    if(minIdx != index)                 // 如果maxIdx的值有更新
    {
        swap(arr[minIdx], arr[index]);
        adjust2(arr, len, minIdx);       // 递归调整其他不满足堆性质的部分
    }
}
void heapSort1(int arr[], int size)
{
    for(int i=size/2 - 1; i >= 0; i--)  // 对每一个非叶结点进行堆调整(从最后一个非叶结点开始)
    {
        adjust1(arr, size, i);
    }
}
void heapSort2(int arr[], int size)
{
    for(int i=size/2 - 1; i >= 0; i--)  // 对每一个非叶结点进行堆调整(从最后一个非叶结点开始)
    {
        adjust2(arr, size, i);
    }
    /*for(int i = size - 1; i >= 1; i--)
    {
        swap(arr[0], arr[i]);           // 将当前最大的放置到数组末尾
        adjust(arr, i, 0);              // 将未完成排序的部分继续进行堆排序
    }*/
}
int main()
{   int n;
cin>>n;
int array[n];
    for (int i = 0; i < n; ++i) {
        cin>>array[i];
    }
    int temp=judge(array,n);
    if (temp==30)cout<<"max min ";
    else if (temp==20){
        cout<<"max ";
        heapSort2(array,n);
        for (int i = 0; i < n; ++i) {
            cout<<array[i];
            if (i!=n-1)
                cout<<' ';
        }
    }
    else if (temp==10) {
        cout << "min ";
        heapSort1(array,n);
        for (int i = 0; i < n; ++i) {
            cout<<array[i];
            if (i!=n-1)
                cout<<' ';
        }
    }
    else{
        heapSort1(array,n);
        for (int i = 0; i < n; ++i) {
            cout<<array[i];
            if (i!=n-1)
                cout<<' ';
        }
    }
    return 0;
}
