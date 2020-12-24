#include <iostream>
#include "vector"
#include "stack"
#include "queue"
#define NoEdge 999999
using namespace std;
class dijkstra{
public:
    int n,*parent,*dist,**a;
    vector<int>L;
    dijkstra(int n,int **a,int p);
    int* getroad();
    int* getdistance() const;
};
dijkstra::dijkstra(int n, int **a, int p) {
    this->n=n;this->a=a;
    parent=new int [n+1];dist=new int [n+1];
    //对所有p[i]不为0的点建立L表，初始化
    for (int i = 1; i <= n; ++i) {
        dist[i]=a[p][i];
        if (dist[i]==NoEdge)parent[i]=0;
        else{
            parent[i]=p;
            L.push_back(i);
        }
    }
}
int*  dijkstra::getdistance() const {
    return dist;
}
int * dijkstra::getroad() {
    while (!L.empty()){
        int key=1,min=999999;
        for (int i = 0; i < L.size(); ++i) {
            if (dist[L[i]]<min){
                key=i;
                min=dist[L[i]];//search the min in the group L
            }
        }

        int i=L[key];//i点为L中最小的那个点
        L.erase(L.begin()+key);//delete the key in L

        for (int j = 1; j <= n; ++j) {
            if (a[i][j]!=NoEdge&&(!parent[j]||dist[j]>dist[i]+a[i][j])){// if a[i][j] have no edge and for j have no parent,
                // then put j in L,or distance j is longer than distance i and a[i][j]
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
    int **a=new int*[n+1];
    for (int i = 1; i <=n; ++i) {
        a[i]=new int [n+1];
    }
    for (int i = 1; i <=n; ++i) {
        for (int j = 1; j <=n; ++j) {
            a[i][j]=NoEdge;
        }
    }
    for (int i = 1; i <=m; ++i) {
        int temp1,temp2,temp3;
        cin>>temp1>>temp2>>temp3;
        a[temp1][temp2]=temp3;
    }
    //接收原点编号P
    int P,*path,*distance;
    cin>>P;
    dijkstra solution(n,a,P);
    path= solution.getroad();//将所有的路径都放在path中
    distance=solution.getdistance();
    //按d从小到大输出路径以及d的值
    queue<int>CANNOT;
    stack<int>ROLL;
    vector<int> can;
    int No=1;
    for (int i = 1; i <=n ; ++i) {
        if (distance[i]==NoEdge&&i!=P){
            CANNOT.push(i);
        } else if (i!=P){
            can.push_back(distance[i]);
        }
    }
    //对can数组进行排序
    for (int i = 0; i < can.size()-1; ++i) {
        for (int j = i+1; j < can.size(); ++j) {
            if (can[i]>can[j]){
                int temp=can[i];
                can[i]=can[j];
                can[j]=temp;
            }
        }
    }
    for (int i = 0; i < can.size(); ++i) {
        for (int j = 1; j <=n; ++j) {
            if(distance[j]==can[i])
            {
                int d=distance[j];
                //输出j的路径
                ROLL.push(j);
                while (path[j]!=P) {
                    j=path[j];
                    ROLL.push(j);

                }
                cout<<"No."<<No<<" : "<<P;
                while (!ROLL.empty()){
                    cout<<" -> "<<ROLL.top();
                    ROLL.pop();
                }
                cout<<" , d = "<<d<<endl;
                No++;
                break;
            }
        }
    }
    if (!CANNOT.empty()) {
        cout << "No." << No << ' ' << ":" << ' ' << "No Path to";
        while (!CANNOT.empty()) {
            cout << ' ' << CANNOT.front();
            CANNOT.pop();
        }
    }
/////end
    return 0;
}

