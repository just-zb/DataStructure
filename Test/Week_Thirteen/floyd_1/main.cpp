#include <iostream>
using namespace std;
int main() {
    int n,m;
    cin>>n>>m;
    int **a=new int*[n];
    for (int i = 0; i < n; ++i) {
        a[i]=new int[n];
    }
    for (int i = 0; i < m; ++i) {
        int temp1,temp2,temp3;
        cin>>temp1>>temp2>>temp3;
        a[temp1][temp2]=temp3;
    }
    return 0;
}
