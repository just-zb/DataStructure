/*
题目描述
判断一个输入序列是否为某一个序列的栈混洗。设输入序列为1-N的数字。

输入：

n，随后输入一个包含n个数字序列。范围从1到n的不同数字

输出：

如果是合法的栈混洗输出ture,否则输出false;

要求O(N)时间复杂度
*/
#include <iostream>
using namespace std;
void judge(int n,int*P){
    int i=0,k=n-1; bool is= true;
    for(int j=1;j<n-1;j++){
        if(i<j&&j<k&&P[i]>P[k]&&P[k]>P[j]){
            is= false;
            break;
        } else if (i+1==j||k-1==j){
            i=0;
            k=n-1;
            continue;
        } else{
            i++;
            k--;
        }
    }
    if(is)
        cout<<"true";
    else
        cout<<"false";
}
int main() {
    int n;
    cin>>n;
    int P[n];
    for(int i=0;i<n;i++){
        cin>>P[i];
    }
    judge(n,P);
    return 0;
}
