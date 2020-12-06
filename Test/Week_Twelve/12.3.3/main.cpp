#include <iostream>
#include "vector"
using namespace std;
/*本质上这一题是求取最小生成树，所以是基础，需要多加练习，不要畏难
 * 由于用kruskal算法需要判断是否形成环已经在项目12.3.1中尝试，所以这里我用prim算法*/
class Point{
public:
    int number;
    void fill(int temp){number =temp;}
};
class edge{
public:
    Point point1;
    Point point2;
    int weigh;
    void fill(Point temp1,Point temp2,int temp3){point1=temp1,point2=temp2;weigh=temp3;}
};
int prim(vector<edge>E,vector<Point>P,int PointNum){
    //定义一个树为最小生成树，定义所选择边的集合，定义已经在树中的顶点的集合，E为网络中边的集合
    vector<edge>T;
    vector<Point>TV;
    TV.push_back(P[0]);
    //删除P集合中的P[0]点
    P.erase(P.begin());
    while (!E.empty()&&T.size()!=PointNum-1){
        //求最小代价边(u,v)
        int min=9999999,target=-1,u;
        for (int i = 0; i < TV.size(); ++i) {
            for (int j = 0; j < P.size(); ++j) {
                for (int k = 0; k < E.size(); ++k) {
                    if (E[k].point1.number==TV[i].number&&E[k].point2.number==P[j].number||
                            E[k].point2.number==TV[i].number&&E[k].point1.number==P[j].number){
                        if (E[k].weigh<min){
                            min=E[k].weigh;
                            target=k;
                            u=j;
                        }
                    }
                }
            }
        }
        if (target==-1)
            break;
        //在T中加入这条边
        T.push_back(E[target]);
        //从E中删除target这条边
        E.erase(E.begin()+target);
        //对点集合P以及TV的操作,将u顶点加入TV，删除P中的u顶点
        TV.push_back(P[u]);
        P.erase(P.begin()+u);

    }
        int sum=0;
        for (int i = 0; i < T.size(); ++i) {
            sum+=T[i].weigh;
        }
        return sum;
}
int main() {
    int PointNum,EdgeNum,WeighSum=0;
    cin>>PointNum>>EdgeNum;
    edge*E=new edge[EdgeNum];
    Point*P=new Point[PointNum];
    vector<edge>Ex;
    vector<Point>Px;
    for (int i = 0; i < PointNum; ++i) {
        P[i].fill(i);
        Px.push_back(P[i]);
    }
    for (int i = 0; i < EdgeNum; ++i) {
        int temp1,temp2,temp3;
        cin>>temp1>>temp2>>temp3;
        WeighSum+=temp3;
        E[i].fill(P[temp1-1],P[temp2-1],temp3);
        Ex.push_back(E[i]);
    }
    //接收
    cout<<WeighSum-prim(Ex,Px,PointNum);
    return 0;
}
