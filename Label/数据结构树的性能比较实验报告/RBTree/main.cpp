// Driver Program for Red Black Tree

#include <iostream>
#include "windows.h"
#include "RBTree.h"
#include "time.h"
#include "stdlib.h"
using namespace std;

void TestInsert(RBTree bTree)
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
    N=10000;
    for (double i : Insert) {
        cout<<i<<endl;
        N+=10000;
    }
}
void TestSearch(RBTree bst)
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
    cout<<"Search time: "<< (t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart<<"ms"<<endl;
}
void TestDelete(RBTree bst)
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
    N=10000;
    for (double i : Delete) {
        cout<<i<<endl;
        N+=10000;
    }
}
void TestDelete_Back(RBTree bst) {
    int N = 10000, j = 0;
    double Delete[50];
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 500000; i >= 1; i--) {
        bst.deleteValue(i);
        if (500001 - i == N) {
            QueryPerformanceCounter(&t2);
            Delete[j] = ((t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart);
            j++;
            N += 10000;
        }
    }
    N = 10000;
    for (double i : Delete) {
        cout << i << endl;
        N += 10000;
    }
}
void Random_Insert(RBTree bst)
{
    int N=10000,j=0;
    double Insert[50];
    int x[500000];//生成随机序列x
    srand((int)time(0));
    for(int i = 0; i < 500000; i++)
    {
        x[i] = i;
    }
    for(int i = 0; i < 500000; i++)
    {
        int t = (rand() % (500000-i))+i;
        swap(x[i], x[t]);
    }
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 0; i <500000; ++i) {
        bst.insertValue(x[i]);
        if (i==N-1)
        {
            QueryPerformanceCounter(&t2);
            Insert[j] = ((t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart);
            j++;
            N+=10000;
        }
    }
    N=10000;
    for (double i : Insert) {
        cout<<i<<endl;
        N+=10000;
    }
}
void Random_Delete(RBTree bst)
{
    int N=10000,j=0;
    double Delete[50];
    int x[500000];//生成随机序列x
    srand((int)time(0));
    for(int i = 0; i < 500000; i++)
    {
        x[i] = i;
    }
    for(int i = 0; i < 500000; i++)
    {
        int t = (rand() % (500000-i))+i;
        swap(x[i], x[t]);
    }
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&tc);
    for (int i = 0; i <500000; ++i) {
        bst.deleteValue(x[i]);
        if (i==N-1)
        {
            QueryPerformanceCounter(&t2);
            Delete[j] = ((t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart);
            j++;
            N+=10000;
        }
    }
    N=10000;
    for (double i : Delete) {
        cout<<i<<endl;
        N+=10000;
    }
}
int main()
{
    RBTree btree;
    Random_Insert(btree);
    //TestInsert(btree);
    TestSearch(btree);
    //TestDelete(btree);
    //TestDelete_Back(btree);
    Random_Delete(btree);

    return 0;
}