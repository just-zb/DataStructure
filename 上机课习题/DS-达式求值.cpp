/*
题目描述
设计一个表达式求值的程序。该程序必须可以接受包含（，），+，-，*，/，%和^(求幂)的中缀表达式，并求出结果。如果表达式正确，则输出表达式的值，如果表达式非法，则输出错误信息。
注意2^2^3转为后缀应为223^^

操作数均转为double运算。

幂运算可以直接使用pow(a,b)

%,操作数转为Int再进行计算。



输入要求：
多个表达式，每个表达式占一行。

输出要求：
对每个表达式，如果为正确表达式则输出结果（精确到小数点后两位），如果为错误表达式则输出“ERROR IN INFIX NOTATION”.
*/
#include <iostream>
using namespace std;
#include "string"
#include "cstdlib"
#include "vector"
#include "stack"
#include "cmath"
bool judegeoperator(char str){
    if(str=='+'||str=='-'||str=='*'||str=='/'||str=='%'||str=='^'||str=='('||str==')')
        return true;
    return false;
}
bool judge(const string& string1){//判断一个字符串是不是一个数，接受string参数
    for(int i=0;i<string1.size();i++){
        if (judegeoperator(string1[i])&&string1[i]!='-')
            return false;
    }
    if(string1.size()==1&&judegeoperator(string1[0]))
        return false;
    return true;
}
double stringtodouble(string str){
    char *s=new char[10];
    for(int i=0;i<str.size();i++){//用atof函数将字符串转化为数字
        s[i]=str[i];
    }
    return atof(s);
}
class problem{
    vector<string> string1;//切割后的中缀表达式
    stack<string> string2;//存放后缀表达式
    stack<string>sign;
public:
    double end;
    bool change();
    bool calculate();
    static bool super(const string& str1,const string& str2);
    problem(vector<string> string1);
};
bool problem::calculate() {//计算后缀表达式的值
    //遍历栈来转换后缀表达式的顺序
    stack<string> temp1;
    stack<double>temp2;
    while(!string2.empty()){//将string2转换顺序，到temp1向量中
        temp1.push(string2.top());
        string2.pop();
    }
    while (!temp1.empty()){
        if(judge(temp1.top())) {//如果temp1的栈顶string字符串是数字字符串，就先将字符串转化为数字，然后输出到temp2栈中
            temp2.push(stringtodouble(temp1.top()));//输入
            temp1.pop();
        } else//如果是符号，就另加考虑：弹出temp2栈中的两个元素计算，所有的符号依次为：'+','-','*','/','%','^'
        {
            double i,j;
            if(temp2.empty())//如果无法弹出，就返回错误值
            {
                return false;
            }
            i=temp2.top();//是可以有小数的，所以要好好考虑，如何将该字符串转化为数字？用哪个函数？需要权重吗？
            temp2.pop();//将前一个数字出栈，然后处理下一个数字
            if(temp2.empty())//如果无法弹出，就返回错误值
            {
                return false;
            }
            j=temp2.top();
            temp2.pop();//将j出栈
            if(temp1.top()=="+")
                temp2.push(j+i);
            else if(temp1.top()=="-")
                temp2.push(j-i);
            else if(temp1.top()=="*")
                temp2.push(j*i);
            else if(temp1.top()=="/") {
                if (i==0)
                    return false;
                else
                    temp2.push(j / i); }
            else if(temp1.top()=="%") {
                if (i == 0)
                    return false;
                else
                    temp2.push((int) j % (int) i);
            }
            else if(temp1.top()=="^")
                temp2.push(pow(j,i));

            temp1.pop();
            //再次压入栈中的应该是j *** i；要判断该运算符是哪一种运算符，bu可以用switch函数
            //如果无法弹出两个数，就是表达式错误，然后返回错误值"ERROR IN INFIX NOTATION";

        }

    }
    end=temp2.top();
    return true;
}
bool problem::super(const string& str1, const string& str2){//若函数返回false，则弹出栈顶，同一优先度的运算符返回false
    if(str1=="+"||str1=="-"){
        if(str2=="*"||str2=="/"||str2=="%"||str2=="^"||str2=="(")
            return true;
    }
    else if (str1=="%"||str1=="*"||str1=="/"){
        if(str2=="^"||str2=="(")
            return true;
    } else if (str1=="(")
        return true;
    else if(str1=="^") {
        if (str2 == "("||str2=="^")
            return true;
        else
            return false;
    }
    return false;
}
bool problem::change() {//将中缀表达式转化为后缀表达式
    for(int i=0; i < string1.size(); i++){
        if(!judge(string1[i])) {
            //考虑符号栈什么都没有时的情况
            if (sign.empty()) {
                if (string2.empty()&&string1[i]!="(")
                    return false;
                sign.push(string1[i]);
            }
            else if (string1[i] == ")") {//右括号的情况//在符号栈里寻找左括号
                while (sign.top() != "(") {
                    string2.push(sign.top());
                    sign.pop();
                    if (sign.empty())//没找到，输出错误
                    {
                        return false;
                    }
                }
                if (sign.top()=="(") {
                    sign.pop();
                }
            }
            else if ( super(sign.top(), string1[i])) {//运算符比栈顶的运算符优先级高
                sign.push(string1[i]);
            } else if (!super(sign.top(), string1[i])) {//运算符不比栈顶的运算符高
                //将sign栈顶弹出，直到sign栈顶优先级比该运算符低
                while (!super(sign.top(), string1[i])) {
                    string2.push(sign.top());//将运算符加入string2中
                    sign.pop();
                    if(sign.empty())
                        break;
                }
                sign.push(string1[i]);
            }//这里出现过bug,不过费了很大劲解决了
        }
        else
            string2.push(string1[i]);//如果是数字字符串就将其压入到后缀表达式栈中
        if (i==string1.size()-1){//将字符串遍历完，然后将符号栈内的所有符号依次弹出，加入到string2中
            while (!sign.empty()){
                string2.push(sign.top());
                sign.pop();
            }
        }
    }
    return true;//遍历完如果不返回false就返回true让接下来的calculate函数计算
}
problem::problem(vector<string> string1) {//赋值构造函数
    end=0.00;
    for (int i = 0; i <string1.size() ; i++) {
        this->string1.push_back(string1[i]);
    }
}
int main() {
        bool error=false;
        vector<string> str2;
        string str1;//原始中缀表达式
        cin>>str1;//输入原始字符串
        //对字符串进行切割
        int i=0;
        while (i<str1.size()){
            if(!(judegeoperator(str1[i]))&&(str1[i]<'0'||str1[i]>'9')){
                error= true;
                break;
            }
            if(judegeoperator(str1[i])&&str1[i]!='-'){//在这里加上一步，若为‘-’就重新考虑
                str2.push_back(str1.substr(i,1));
                i++;
            }
            else if (i==0&&str1[i]=='-'&&str1[i+1]<='9'&&str1[i+1]>='0'){
                int k=i;
                while (str1[i+1] <= '9' && str1[i+1] >= '0' || str1[i+1] == '.') {//读取数字，储存到str2
                    i++;
                }
                str2.push_back(str1.substr(k,i-k+1));
                i++;//将i向后退
            }
            else if(str1[i]=='-'&&(str1[i-1]=='('&&str1[i+1]<='9'&&str1[i+1]>='0')){
                int k=i;
                while (str1[i+1] <= '9' && str1[i+1] >= '0' || str1[i+1] == '.') {//读取数字，储存到str2
                    i++;
                }
                str2.push_back(str1.substr(k,i-k+1));
                i++;//将i向后退
            }
            else if (str1[i]=='-'&&(str1[i-1]!='('&&i!=0)){
                str2.push_back(str1.substr(i,1));
                i++;
            }
            else {
                int k=i;
                while (str1[i] <= '9' && str1[i] >= '0' || str1[i] == '.') {//读取数字，储存到str2
                    i++;
                }
                str2.push_back(str1.substr(k,i-k));
            }
        }
//切割完毕，进行求取
        problem problem1(str2);
        if (problem1.change()&&!error) {
            if(problem1.calculate())//出现bug，如果计算结果是零也输出表达式错误了
            {
                double l = problem1.end;
                printf("%.2f", l);
                cout<<' ';
            } else {
                cout << "ERROR IN INFIX NOTATION";
                cout<<' ';
            }
        } else
        { cout << "ERROR IN INFIX NOTATION";
        cout<<' ';}

    return 0;
}