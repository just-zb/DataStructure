#include <iostream>
#include "vector"
using namespace std;
class Solution {
public:
    vector<int> p;

    // 找到跟他联通的最远的节点 路径压缩版本
    int find(int x){
        if(p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int N = edges.size();
        // 最开始 每个点都是单独的 指向自己
        for(int i =0; i<N+1; i++)  p.push_back(i);
        // 加入每条边的时候 判断两个点是不是联通的 没联通的话 连起来 否则就返回
        for(auto a : edges)
        {
            int u = a[0]; int v = a[1];
            if(find(u) != find(v)) p[find(v)] = find(u);
            else return {u,v};
        }
        return {};
    }
};
int main(){
    return 0;
}