#include <iostream>
#include "vector"
#include "stack"
#define NoEdge 999999
using namespace std;
class dijkstra{
public:
    int n,*parent,*dist,**a;
    vector<int>L;
    dijkstra(int n,int **a,int p);
    int* getroad();
    int getdistance(int temp) const;
};
dijkstra::dijkstra(int n, int **a, int p) {
    this->n=n;this->a=a;
    parent=new int [n];dist=new int [n];
    //对所有p[i]不为0的点建立L表，初始化
    for (int i = 0; i < n; ++i) {
        dist[i]=a[p][i];
        if (dist[i]==NoEdge||i==0)parent[i]=0;//不让0放在L中
        else{
            parent[i]=p;
            L.push_back(i);
        }
    }
}
int  dijkstra::getdistance(int temp) const {
    return dist[temp-1];
}
int * dijkstra::getroad() {
    while (!L.empty()){
        int key,min=dist[0];
        for (int i = 0; i < L.size(); ++i) {
            if (dist[i]<min){
                key=i;
                min=dist[i];
            }
        }

        int i=L[key];//i点为L中最小的那个点
        L.erase(L.begin()+key);

        for (int j = 0; j < n; ++j) {
            if (a[i][j]!=NoEdge&&(!parent[j]||dist[j]>dist[i]+a[i][j])){
                dist[j]=dist[i]+a[i][j];
                if (!parent[j])L.push_back(j);
                parent[j]=i;
            }
        }
    }


    return parent;
}
int main() {
    int n,m;
    cin>>n>>m;
    int **a=new int*[n];
    for (int i = 0; i < n; ++i) {
        a[i]=new int [n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j]=NoEdge;
        }
    }
    for (int i = 0; i < m; ++i) {
        int temp1,temp2,temp3;
        cin>>temp1>>temp2>>temp3;
        a[temp1-1][temp2-1]=temp3;
    }
    //接收原点编号P
    int P,No=1,*path;
    cin>>P;
    dijkstra solution(n,a,P-1);
    path= solution.getroad();//将所有的路径都放在path中
    vector<int>CANNNOT;
    for (int i = 0; i <n; ++i) {
        if (i!=P-1){
            if (path[i]!=NoEdge) {
                cout << "No." << No << ' ' << ":" << ' ';//输出路径的节点
                int still=i;
                stack<int>temp;
                temp.push(still);
                while (path[still]!=0){//如果顶点i到原点的路径均存在
                    temp.push(path[still]);
                    still=path[still];
                    if (!still){
                        //如果still是0，就在执行一步，将0压入栈中然后结束
                        temp.push(still);
                        break;
                    }
                }
                cout<<P<<' ';
                while (!temp.empty()){
                    cout<<"->"<<' '<<temp.top()+1<<' ';
                    temp.pop();
                }
                cout<<","<<' '<<"d"<<' '<<"="<<' '<<solution.getdistance(i)<<endl;
            }
            else{
                CANNNOT.push_back(i);
            }
            No++;
        }
    }
    if (!CANNNOT.empty()) {
        cout<<"No."<<No<<' '<<":"<<' '<<"No"<<' '<<"Path"<<' '<<"to";
        for (int i = 0; i < CANNNOT.size(); ++i) {
            cout<<' '<<CANNNOT[i]+1;
        }
    }
/////end
    return 0;
}

