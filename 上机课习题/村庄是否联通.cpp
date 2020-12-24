/*
题目描述
村庄中存在一些路，根据输入的相邻村庄的路，判断某两个村庄是否能够联通。n个村庄使用0到n-1的不同整数标识。路使用取值范围【0，n-1】的整数对表示。例如 3 5，代表村庄3和5之间有一条路。

Input Format

村庄个数 n， 0<n<=20

路的条数 m，0<m<=50

m条路，即为2m个范围在【0，n-1】的整数   

需要判断是否相连的村庄对数 p 0<p<=10

需要判断是否相连的p对村庄，即为2p个范围在【0，n-1】的整数。

Output Format
能够连通输出

true

,不可连通输出

false
*/
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
