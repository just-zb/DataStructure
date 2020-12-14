// Driver Program for Red Black Tree

#include <iostream>
#include "windows.h"
#include "RBTree.h"
using namespace std;

double* TestInsert(RBTree bTree)
{
    int N=10000,j=0;
    double Insert[50];
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 1; i <=500000; ++i) {
        bTree.insertValue(i);
        if (i==N)
        {
            QueryPerformanceCounter(&t2);
            Insert[j]=(t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart;
            j++;
            N+=10000;
        }
    }
    return Insert;
}
double TestSearch(RBTree bst)
{
    int Number[1000];
    for (int i = 0; i < 1000; ++i) {
        Number[i]=rand() % (500000)+1;
    }
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for (int i = 0; i < 1000; ++i) {
        bst.find(Number[i]);
    }
    QueryPerformanceCounter(&t2);
    return (t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart;
}
double *TestDelete(RBTree bst)
{
    int N=10000,j=0;
    double Delete[50];
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 1; i <=500000; ++i) {
        bst.deleteValue(i);
        if (i==N)
        {
            QueryPerformanceCounter(&t2);
            Delete[j]=(t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart;
            j++;
            N+=10000;
        }
    }
    return Delete;
}
int main()
{
    RBTree btree1,btree2,btree3;
    int N=10000;
    double Insert[50],*Insert1,*Insert2,*Insert3;
    double Search,Search1,Search2,Search3;
    double Delete[50],*Delete1,*Delete2,*Delete3;
    Insert1=TestInsert(btree1);
    Insert2=TestInsert(btree2);
    Insert3=TestInsert(btree3);
    for (int i = 0; i < 50; ++i) {
        Insert[i]=(Insert1[i]+Insert2[i]+Insert3[i])/3;
    }
    Search1=TestSearch(btree1);
    Search2=TestSearch(btree2);
    Search3=TestSearch(btree3);
    Search=(Search1+Search2+Search3)/3;

    Delete1=TestDelete(btree1);
    Delete2=TestDelete(btree2);
    Delete3=TestDelete(btree3);
    for (int i = 0; i < 50; ++i) {
        Delete[i]=(Delete1[i]+Delete2[i]+Delete3[i])/3;
    }
    for (int i = 0; i < 50; ++i) {
        cout<<"N="<<N<<" insert time "<<Insert[i]<<"ms"<<endl;
        N+=10000;
    }
    cout<<"Search time:"<< Search <<" ms"<<endl;
    N=10000;
    for (int i = 0; i < 50; ++i) {
        cout<<"N="<<N<<" delete time "<<Delete[i]<<"ms"<<endl;
        N+=10000;
    }

    return 0;
}