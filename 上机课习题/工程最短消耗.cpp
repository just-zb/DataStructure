/*
题目描述
给出一个工程中N个阶段的时间消耗和依赖关系，试求出工程的最短时间消耗。

Input Format
输入N 0<N<=20。

随后输入N行数据，每行包含从1起始的阶段编号S、时间消耗T、以及用分号隔开的所依赖的不同阶段编号【如果不依赖其他阶段则此项为空】

Output Format

输出一行，为完成N个阶段的时间消耗。如果依赖关系不为DAG则输出"error"
//本学期最后一题
*/
#include <iostream>
#include "sstream"
#include "queue"
#include "vector"
#include "string"
using namespace std;
///////该函数寻找入度为0的点并且返回
vector<int> SearchZero(bool **edge,vector<int>deleted,int n)
{
    vector<int>target;
    for (int i = 0; i < n; ++i) {//第i列
        ////////在deleted数组中寻找有没有i
        bool HaveDeleted= false;
        int sum=0;//记录一列的false的个数。当一列都是false时，将该列的编号压入target
        for (int j = 0; j < n; ++j) {//第j行
            if (!edge[j][i])
                sum++;
        }
        for (int j = 0; j < deleted.size(); ++j) {
            if (i==deleted[j])
                HaveDeleted= true;
        }
        if (sum==n&&!HaveDeleted)
            target.push_back(i);
    }
    return target;
}
bool IsEmpty(bool **edge,int n)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (edge[i][j])
                return false;
        }
    }
    return true;
}
void solution(bool **edge,const int *time,int n)
{
    //cout<<"solution begin"<<endl;
    ////////edge二维数组储存单向边，time数组储存每一个顶点的消耗时间///////
    ////////第一步找出入度为0的点，放到队列中去，然后找到时间消耗最大的那个//
    vector<int>Deleted;
    int early_time[n];
    for (int i = 0; i < n; ++i) {
        early_time[i]=0;
    }
    int MAX=0;
    while (true)
    {
        //将入度为0的点储存在数组中
        vector<int>Zero=SearchZero(edge,Deleted,n);
        //如果数组大小为0，说明没有了入度为0的顶点，那么返回
        if (Zero.empty())break;
        //else cout<<"Zero not empty"<<endl;
        //将最大时间消耗用max变量储存
        for (int i = 0; i < Zero.size(); ++i) {
            ///////判断early_time//////////////////
            for (int j = 0; j < n; ++j) {
                if (edge[Zero[i]][j])
                    early_time[j]=max(early_time[j],time[Zero[i]]+early_time[Zero[i]]);
            }
            //////依次删除在edge中的该点的出度边///////

            for (int j = 0; j < n; ++j) {
                edge[Zero[i]][j]= false;
            }
            /////////////将删除的点压入已经删除的点的数组中
            Deleted.push_back(Zero[i]);
        }
    }
    //cout<<"delete ok"<<endl;
    //////////求MAX//////////////////////
    for (int i = 0; i < n; ++i) {//在n个点中，寻找early_time[i]+time[i]最大的
        if (early_time[i]+time[i]>MAX)
            MAX=early_time[i]+time[i];
    }
    //////////判断最后是否还有没有删除的边，如果有就报错，没有就输出MAX//////
    if (IsEmpty(edge,n))
        cout<<MAX;
    else cout<<"error";
}
void test()
{
    //cout<<"test begin"<<endl;
    int n;cin>>n;
    bool **edge=new bool *[n];
    for (int i = 0; i < n; ++i) {
        edge[i]=new bool [n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            edge[i][j]= false;
        }
    }
    int time[n];
    //cout<<"init"<<endl;
    for (int i = 0; i < n; ++i) {
        int temp1,temp2;
        cin>>temp1>>temp2;
        time[i]=temp2;
        string string1;
        string string2;;
        getline(cin,string1);
        for (int j = 1; j < string1.size(); j++) {
            if (string1[j]!=';')
                string2+=string1[j];
            else{
                if (string2.size()==1)
                    edge[string2[0]-'0'-1][i]= true;
                else
                    edge[10+string2[0]-'0'-1][i]= true;
                string2.clear();
            }
        }
        //cout<<"init "<<i<<endl;
    }
    //cout<<"init ok"<<endl;
    solution(edge,time,n);
}
int main() {
    test();
    return 0;
}