/*
题目描述
给定一个常数项为0的二元一次多项式，求该多项式的幂。

设未知数为x,y，输入为x和y的整数系数a,b以及整数幂n，输出形如以下样式

求幂运算的结果，按照x的幂降序排列

Input Format
输入未知数整数系数 a,b (-100<a,b<100),n (1<n<6)

Output Format
幂运算的结果的多项式，按照x幂降序排列  

Example
Input
 2 3 2

Output
4x^2+12xy+9y^2

说明
幂为1时不输出^1

系数为1时不输出系数，-1只输出负号。
*/
#include <iostream>
#include "string"
#include "cmath"
using namespace std;
int jiecheng(int n){
    long sum=1;
    if(n==0)
        return sum;
    else {
        for (int i = 1; i <= n; i++) {
            sum *= i;
        }
        return sum;
    }
}
int main() {
    int a,b,n;
    cin>>a>>b>>n;
    //判断全式为0
    if(a==0&&b==0){
        cout<<0;
        return 0;
    }
    if(n==0) {
        cout << 1;
        return 0;
    }
    else if(a==0) {
        if(pow(b, n)==1)
            cout<<"y^"<<n;
        else
            cout << pow(b, n) << "y^" << n;//TODO
        return 0;
    }
    else if (b==0) {
        if(pow(a, n)==1)
            cout<<"y^"<<n;
        else
            cout << pow(a, n) << "x^" << n;//TODO
        return 0;
    }
    else {
        int m = 0;
        while (m <= n) {
            long i = pow(a, n - m) * pow(b, m) * jiecheng(n) / jiecheng(m) / jiecheng(n - m);
            if (i < 0) {
                if (i == -1)
                    cout << '-';
                else
                    cout << i;

            } else if (i > 0) {
                if (m != 0) {
                    if (i == 1)
                        cout << '+';
                    else
                        cout << '+' << i;
                } else {
                    if (i != 1)
                        cout << i;
                }

            }
            //输出x,y
            if (n - m != 0 && m != 0) {
                if (n - m == 1 || m == 1) {
                    if (n - m == 1)
                        cout << 'x';
                    else
                        cout << "x^" << n - m;
                    if (m == 1)
                        cout << 'y';
                    else
                        cout << "y^" << m;
                } else
                    cout << "x^" << n - m << "y^" << m;
            } else if (n == m)
                cout << "y^" << n;
            else if (m == 0)
                cout << "x^" << n;

            m++;
        }
        return 0;
    }
}