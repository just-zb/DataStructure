/*
题目描述
给定一个常数项为0的二元一次多项式，求该多项式的幂。

设未知数为x,y，输入为x和y的整数系数a,b以及整数幂n，输出形如以下样式

求幂运算的结果，按照x的幂降序排列

Input Format
输入未知数整数系数 a,b (-1000<a,b<1000),n (2<n<20)

Output Format
幂运算的结果的多项式，按照x幂降序排列  

Example
Input
99 100 15  

Output
860058354641288524893953951499x^15+13031187191534674619605362901500x^14y+92139707414891638724482363950000x^13y^2+403305116630838822699754455000000x^12y^3+1222136717063147947575013500000000x^11y^4+2715859371251439883500030000000000x^10y^5+4572153823655622699495000000000000x^9y^6+5937862108643665843500000000000000x^8y^7+5997840513781480650000000000000000x^7y^8+4712108147752005000000000000000000x^6y^9+2855823119849700000000000000000000x^5y^10+1311213553650000000000000000000000x^4y^11+441486045000000000000000000000000x^3y^12+102910500000000000000000000000000x^2y^13+14850000000000000000000000000000xy^14+1000000000000000000000000000000y^15

说明
幂为1时不输出^1

系数为1时不输出系数，-1只输出负号。

*/
#include <iostream>
using namespace std;
#include "string"
#include "vector"
#include "algorithm"
string addStrings(string num1, string num2) {
        string str;
        int cur = 0, i = num1.size()-1, j = num2.size()-1;
        while (i >= 0 || j >= 0 || cur != 0) {
            if (i >= 0) cur += num1[i--] - '0';
            if (j >= 0) cur += num2[j--] - '0';
            str += to_string (cur % 10);
            cur /= 10;
        }
        reverse(str.begin(), str.end());
        return str;
    }
    string multstrings(string num1,string num2){
        string str1="0",str2;
        int cur=0,i,j=num2.size()-1;
        while (j>=0) {
            i=num1.size()-1;
            while (i >= 0 || cur != 0) {
                int temp=0;
                if (i >= 0)temp += (num1[i--] - '0');
                temp *= (num2[j] - '0');
                str2 += to_string((cur + temp) % 10);
                cur=(cur+temp)/10;
            }
            reverse(str2.begin(),str2.end());
            for (int k = j; k <num2.size()-1; ++k) {
                str2+='0';
            }
            //cout<<"str2:"<<str2<<' '<<"str1:"<<str1<<endl;
            str1=addStrings(str1,str2);
            str2.clear();
            j--;
        }
        return str1;
    }
string jiecheng(string str,int n){
    string sum="1";
    if(n==0)
        return sum;
    else {
        for (int i = 1; i <= n; i++) {
            sum =multstrings(sum,str);
        }
        return sum;
    }
}
long erxiangshixishu(int n,int k){//qiu Cnk//
    long sum;
    if(k>n){
        sum=0;
    }
    else if(k==0){
        sum=1;
    }
    else
        sum=erxiangshixishu(n-1,k-1)+erxiangshixishu(n-1,k);
    return sum;
}
int main() {
    int a,b; int n;
    cin>>a>>b>>n;
    //判断全式为0
    if(a==0&&b==0){//输入值a，b为0
        cout<<0;
        return 0;
    }
    if(a==0) {
        if(b==-1&&(n%2!=0))cout<<'-'<<"y^"<<n;
        else if (b==-1&&(n%2==0)||b==1)cout<<"y^"<<n;
        else cout << jiecheng(to_string(b),n)<< "x^" << n;
        return 0;
    }
    else if (b==0) {
        if(a==-1&&(n%2!=0))cout<<'-'<<"y^"<<n;
        else if (a==-1&&(n%2==0)||a==1)cout<<"y^"<<n;
        else cout << jiecheng(to_string(a),n)<< "x^" << n;
        return 0;
    }
    else {
        int m = 0;
        bool IsApos= true;bool IsBpos= true;
        if(a<0) { IsApos = false, a *= -1; }
        if(b<0) { IsBpos = false, b *= -1; }
        while (m <= n) {
            string i = multstrings(multstrings(jiecheng(to_string(a),n-m),jiecheng(to_string(b),m)),to_string(erxiangshixishu(n,m)));//pow(a, n - m) * pow(b, m) * jiecheng(n) / jiecheng(m) / jiecheng(n - m);
            if (!(IsApos&&IsBpos||IsBpos&&(!(n-m)%2)||IsApos&&(!m%2)||!((n-m)%2)&&!(m%2)||(!IsApos&&!IsBpos&&m%2&&(n-m)%2)||(!IsApos&&IsBpos&&!((n-m)%2))||(IsApos&&!IsBpos&&!(m%2)))) {
                if (i == "1")
                    cout << '-';
                else
                    cout <<'-'<< i;

            }
            else {
                if (m != 0) {
                    if (i == "1")cout << '+';
                    else cout << '+' << i;
                }
                else {
                    if (i != "1")cout << i;
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

