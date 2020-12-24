/*
题目描述
给定一个仅含有英文大小写字母的字符串序列 s，若其中任意两个相邻字符都不是同一个字母的大小写形式，则称其为互斥字符串。

程序需要将给定的字符串转换为互斥字符串。aa为互斥，aA和Aa为非互斥。

程序的每次操作可以从字符串中选出满足上述条件的两个相邻字符并删除，直到字符串整理好为止。

注：若最终结果为空字符串，请输出 -1。

要求时间复杂度O(n)

Input Format
输入由一行字符串组成。测试样例保证答案唯一。

Output Format
输出一行，为输入字符串经过若干次删除操作得到的互斥字符串。

Example
Input
abBAcCc

Output
c
*/
#include <iostream>
#include <stack>
using namespace std;
int main() {
    stack<int> s;
    string str;
    cin>>str;
for(int i=(int)(str.size()-1);i>-1;i--){
    if(s.empty())
        s.push(str[i]);
    else if(s.top()==str[i]-32||s.top()==str[i]+32)
        s.pop();
    else
        s.push(str[i]);
}
if(s.empty())
    cout<<-1;
while (!s.empty()){
    cout<<(char)s.top();
    s.pop();
}
    return 0;
}
