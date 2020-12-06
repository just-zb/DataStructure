#include <iostream>
#include "vector"
using namespace std;
class node{
public:
    enum status{
        FIND,
        UN_FIND
    };
    enum status status1;
    node(){status1=UN_FIND;}
};
bool ISCRICLE(int**a,int*x,int*y){

}
int KRUSKAL(int*x,int *y,int*z,int**a,node*p,int m,int n){
    vector<int>T;//存放边的权值
    //进行排序算法，一次对排序后的权值从小到大，满足条件压入，否则不压入
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (z[i]>z[j]){
                int temp;
                temp=z[j];
                z[j]=z[i];
                z[i]=temp;
                temp=x[j];
                x[j]=x[i];
                x[i]=temp;
                temp=y[j];
                y[j]=y[i];
                y[i]=temp;
            }
        }
    }
    int index=0;
    while (T.size()!=m-1&&index<n){
        a[x[index]][y[index]]+=1;
        a[y[index]][x[index]]+=1;
        //如果权值对应的两个顶点都FIND，不压入，否则压入//出现错误，保证不出现环路的方法不是保证两个顶点不被发现，但是我现在实现不了，因为关于图的有无环的判断不熟悉
        if (p[x[index]].status1==node::UN_FIND || p[y[index]].status1 == node::UN_FIND){
            T.push_back(z[index]);
            p[x[index]].status1=node::FIND;
            p[y[index]].status1 = node::FIND;
        }
        index++;
    }
    int rest=0;
    for (int i : T) {
        rest+=i;
    }
    int total=0;
    for (int i = 0; i < n; ++i) {
        total+=z[i];
    }
    return total-rest;
}
int main() {
    int m,n;//m表示点的数量，n表示边的数量
    cin>>m>>n;
    int**a=new int*[m];
    for (int i = 0; i < m; ++i) {
        a[i]=new int[m];
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j]=0;
        }
    }
    node*p=new node[m];
    int x[n],y[n],z[n];
    for (int i = 0; i < n; ++i) {
        cin>>x[i]>>y[i]>>z[i];
    }
    cout<<KRUSKAL(x,y,z,a,p,m,n);
    return 0;
}
//这一题的另一种解法是并查集，放在12.3.2中