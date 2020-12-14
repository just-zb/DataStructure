#include "rbtree.h"
#include "vector"
int main(int argc, char* argv[])
{
    int N;cin>>N;
    int temp;
    rb_tree<int> MyRBTree;
    for (int i = 0; i < N; ++i) {
        cin>>temp;
        MyRBTree.insert(temp);
    }
    int DeleteNum;cin>>DeleteNum;
    vector<int>a;
    for (int i = 0; i < DeleteNum; ++i) {
        cin>>temp;
        a.push_back(temp);
    }
    MyRBTree.dump();
    cout<<endl;
    for (int i = 0; i <a.size(); ++i) {
        MyRBTree.erase(a[i]);
    }
    cout<<endl;
     MyRBTree.dump();
    return 0;
}