#include <iostream>
#include "vector"
using namespace std;
class node{
public:
    enum status{
        UNFIND,
        FIND
    };
    enum status status1;
    node(){status1=UNFIND;}
};
int kruskal(int **a,node*node,int n){
    vector<int>T;//用来储存边和边的数目
    vector<int>V;//存放顶点
    int min=999999,u=0,v=0;
    node[0].status1=node::FIND;
    V.push_back(0);
    while (T.size()!=n-1){
        for (int i = 0; i <V.size(); ++i) {
            for (int j = 0; j < n; ++j) {
                if (a[V[i]][j] < min && node[j].status1 == node::UNFIND && V[i] != j) {
                    min = a[V[i]][j];
                    u = V[i];
                    v = j;
                }
            }
        }
        node[v].status1 = node::FIND;
        V.push_back(v);
        T.push_back(a[u][v]);
        min = 999999999;
    }
    int sum=0;
    for (int i = 0; i < T.size(); ++i) {
        sum+=T[i];
    }
    return sum;
}
int main() {
    int n;
    cin>>n;
    node*temp=new node[n];
    int **a=new int*[n];
    for (int i = 0; i < n; ++i) {
        a[i]=new int[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int temp1;
            cin>>temp1;
            a[i][j]=temp1;
        }
    }
    int know;
    cin>>know;
    //顶点被访问过后
    for (int i = 0; i < know; ++i) {
        int temp1,temp2;
        cin>>temp1>>temp2;
        a[temp1-1][temp2-1]=0;
        a[temp2-1][temp1-1]=0;
    }
   cout<<kruskal(a,temp,n);
    return 0;
}
