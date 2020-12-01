#include <iostream>
using namespace std;
class nevermind{
    int* parents;
    // 初始化
public:
    nevermind(int n){//在初始化时，让所有节点的父节点都是它本身
        parents = new int[n];
        for(int i=0;i<n;i++){
            parents[i] = i;
        }
    }

    // 合并
    void unionkey(int node1,int node2){//组合两个村庄，让两个村庄在同一个集合
        int root1 = find(node1);
        int root2 = find(node2);
        if(root1!=root2){//如果node1的祖宗节点不是node2的祖宗节点，那么让node2的祖宗节点指向node1的祖父节点
            parents[root2] = root1;
        }
    };
    // 查找
    int find(int node){//找到该节点的祖父节点，只有祖父节点的父节点是祖父节点本身
        while(parents[node]!=node){
            parents[node] = parents[parents[node]];
            node = parents[node];
        }
        return node;
    }

    // 看是否在同一个集合
bool isConnected(int node1,int node2){//观察两个节点的祖宗节点是否相同，只有相同了之后才能连通
        return find(node1) == find(node2);
    };
};
//在这里展现出并查集的代表（就是根节点的重要性，这种方法为什么能解决村庄联通的问题？）
int main() {
    int m,n;
    cin>>m>>n;
    nevermind haha(m);
    for (int i = 0; i < n; ++i) {
        int temp1,temp2;
        cin>>temp1>>temp2;
        haha.unionkey(temp1,temp2);
    }
    int sum;
    cin>>sum;
    int temp1[sum],temp2[sum];
    for (int i = 0; i < sum; ++i) {
        cin>>temp1[i]>>temp2[i];
    }
    for (int i = 0; i < sum; ++i) {
        if (haha.isConnected(temp1[i],temp2[i]))cout<<"true"<<endl;
        else cout<<"false"<<endl;
    }

    return 0;
}
