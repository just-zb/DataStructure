/*
题目描述
根据KMP算法的next数组值，推断模式字符串。

假设模式字符串中只存在0，1两种字符。给出首字符和next数组。请输出模式字符串。如果next数组不合法则输出ERROR

Input Format
先输入模式字符串首字符0或者1，然后输入尾字符0或者1

再输入 模式字符串长度n，n<=30

最后输入n个以 -1，0，起始的整数。

Output Format

模式字符串 或者 ERROR 
*/
#include <iostream>
using namespace std;
#include "vector"
//出现bug的原因是有的时候判断模式字符串的一位，需要用到下一位的next数组，是由next数组推出模式字符串，而不是由模式字符串推出数组。
int buildnext(vector<int>p){
    int j=0;
    int *N=new int[p.size()];
    int t=-1;
    N[0]=-1;
    while (j<p.size()-1){
        if(0>t||p[j]==p[t]){
            j++;t++;
            N[j]=t;
        } else
            t=N[t];
    }
    return N[p.size()-1];
}
void solution( const int*p,int front,int end,int n){
    vector<int>a;
    if(p[0]!=-1||p[1]!=0) { cout << "ERROR"; return;}
    if (front!=1&&front!=0||end!=1&&end!=0){ cout << "ERROR"; return;}
    if (n==2){
        cout<<front<<end;
        return;
    } else if (n<2)
    {
        cout<<"ERROR";
        return;
    }
    int i=2;
    a.push_back(front);
    while (i<n){
        if (i==n-1){
            a.push_back(1);
            a.push_back(1);
            if (buildnext(a)!=p[i]){
                a.pop_back();
                a.pop_back();
                a.push_back(0);
                a.push_back(1);
                if (buildnext(a)!=p[i]) {
                    cout << "ERROR";
                    return;
                }
                else a.pop_back();
            } else a.pop_back();
             a.push_back(end);
        }
        else
        {
            a.push_back(1);
            a.push_back(1);
            if (buildnext(a) != p[i]) {
                a.pop_back();
                a.pop_back();
                a.push_back(0);
                a.push_back(1);
                if (buildnext(a) != p[i]) {
                    cout<<"ERROR";
                    return;
                } else
                a.pop_back();
            } else
            a.pop_back();
        }
    i++;
    }
        for (int j = 0; j < n; ++j) {
            cout<<a[j];
            if (a[j]!=0&&a[j]!=1){
                cout<<"ERROR";
                return;
            }
        }

}
int main() {
    int front,end,n;
    cin>>front>>end>>n;
    int b[n];
    for(int i=0;i<n;i++)
    {
        cin>>b[i];
        if (b[i]<-1){
            cout<<"ERROR";
            return 0;
        }
    }
    solution(b,front,end,n);
    return 0;
}

