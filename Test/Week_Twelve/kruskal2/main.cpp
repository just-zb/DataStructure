#include <iostream>
using namespace std;
class nevermind{
    int* parents;
    // 初始化
public:
    nevermind(int n){
        parents = new int[n];
        for(int i=0;i<n;i++){
            parents[i] = i;
        }
    }

    // 合并
    void unionkey(int node1,int node2){
        int root1 = find(node1);
        int root2 = find(node2);
        if(root1!=root2){
            parents[root2] = root1;
        }
    };
    // 查找
    int find(int node){
        while(parents[node]!=node){
            parents[node] = parents[parents[node]];
            node = parents[node];
        }
        return node;
    }

    // 看是否在同一个集合
bool isConnected(int node1,int node2){
        return find(node1) == find(node2);
    };
};
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
