/*
题目描述
给定一个非最简的Linux文件绝对路径，将其简化为标准的Linux文件绝对路径。

在Linux文件路径中，一个英文句号 . 表示当前目录，两个连续的英文句号 .. 表示返回到上一级目录。

标准的Linux文件绝对路径具有以下特点

第一个字符为斜杠 /

两个目录名称直接有且仅有一个斜杠 /

除根目录外，路径结尾不能为斜杠 /

不会出现一个英文句号 . 或者两个连续的英文句号 ..

Input Format
输入由一行字符串组成，为非最简的Linux文件绝对路径。

Output Format
输出一行，为最简化的Linux文件绝对路径。

Example
Input
/aaa/../../bbb/ccc/..///./..

Output
/

说明
路径从根目录开始从左往右进行解析

aaa 表示进入根目录下 aaa 目录

.. 表示返回上一级目录，即返回根目录

.. 表示返回上一级目录，但当前目录为根目录，无上一级目录。故仍处于根目录。

bbb 表示进入根目录下 bbb 目录

ccc 表示进入 bbb 目录下 ccc 目录

.. 表示返回上一级目录，即返回 bbb 目录

后续若干个连续的斜杠 / 间没有目录名称，直接删除

. 表示当期文件夹，故仍处于 bbb 目录

.. 表示返回上一级目录，即返回根目录

根目录用斜杠 / 表示，故输出斜杠 /
*/
#include <iostream>
#include "stack"
#include "sstream"
//#include "algorithm"
using namespace std;
class solution{
public:
    string simple(string str){
        stack<string>linux;
        istringstream stream(str);
        string string1;
        while (getline(stream,string1,'/')){
         if(!string1.empty()&&string1!="."&&string1!=".."){
            linux.push(string1);
         }
         if(string1==".."&&!linux.empty())
             linux.pop();
        }
        string1.clear();
        if(linux.empty())
            return '/'+string1;
    while (!linux.empty()){
        string1=linux.top()+string1;
        linux.pop();
        if (!linux.empty()) {
            string1='/'+string1;
        }
    }
    //reverse(string1.begin(),string1.end());
        return '/'+string1;
    }
};
int main() {

    string str;
    cin>>str;
    solution solution1;
    cout<<solution1.simple(str);
    return 0;
}
