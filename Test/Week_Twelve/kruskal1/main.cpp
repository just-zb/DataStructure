#include <iostream>
#include "vector"
using namespace std;
int main() {
    int n,road;
    cin>>n>>road;
    vector<vector<int>>b;
    vector<int>temp;
    int i,j;
    cin>>i>>j;
    temp.push_back(i);
    temp.push_back(j);
    b.push_back(temp);
    for (int k = 1; k < road; ++k) {
        cin>>i>>j;
        for (int l = 0; l < b.size(); ++l) {
            for (int m = 0; m < b[l].size(); ++m) {
                bool judge1= false,judge2= false;
                if(i==j) goto here;
                else if (b[l][m]==i) {
                    for (int i1 = 0; i1 < b[l].size(); ++i1) {
                        if (b[l][i1] == j)
                            judge1=true;
                    }
                    if (!judge1)
                    b[l].push_back(j);
                    goto here;
                } else if (b[l][m]==j){
                    for (int i1 = 0; i1 < b[l].size(); ++i1) {
                        if (b[l][i1] == i)
                            judge2=true;
                    }
                    if (!judge2)
                        b[l].push_back(i);
                    goto here;
                }
            }
        }
        temp.clear();
            temp.push_back(i);
            temp.push_back(j);
            b.push_back(temp);
        here:;
    }
    for (int k = 0; k < b.size(); ++k) {
        for (int l = 0; l < b[k].size(); ++l) {
            cout<<b[k][l]<<' ';
        }
        cout<<endl;
    }
    int search;
    cin>>search;
    int temp1[search],temp2[search];
    for (int k = 0; k < search; ++k) {
        cin>>temp1[i]>>temp2[i];
    }
    for (int x = 0; x < search; ++x) {
        for (int k = 0; k < b.size(); ++k) {
            for (int l = 0; l < b[k].size(); ++l) {
                if (b[k][l]==temp1[x]){
                    for (int m = 0; m < b[k].size(); ++m) {
                        if (b[k][m]==temp2[x]) { cout << "true" << endl;goto again; }
                    }
                }
            }
        }
        cout<<"false"<<endl;
        again:;
    }

    return 0;
}
//问题出现的原因是由于二元vector数组无法实现合并的功能，所以出现了不能形成完整的通路，仅仅完成了一部分通路的判断，所以放弃，因为未构思好
