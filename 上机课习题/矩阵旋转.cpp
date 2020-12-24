/*
题目描述
给定一个n*m的矩阵，请以顺、逆时针交替旋转的方式打印出每个元素。
Input Format

第一行n m； 0<n,m<100

后n行，每行m个整数。

Output Format
n*m个矩阵元素，空格隔开。
*/
#include <iostream>
//为了代码优化，可以将矩阵转置，然后再输出
using namespace std;
int main() {
    int m,n;
    cin>>m>>n;
    int matrix[m][n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin>>matrix[i][j];
        }
    }
    int top=0,bottom=m-1,left=0,right=n-1;
    bool order= true;//如果order为真，那么为顺时针，否则为逆时针。
    while (true){
        if (order){
            for (int i = left; i <= right; ++i) {
                cout<<matrix[top][i]<<' ';
            }
            for (int i = top+1; i <=bottom; ++i) {
                cout<<matrix[i][right]<<' ';
            }
            if (top<bottom&&left<right) {
                for (int i = right - 1; i >= left + 1; --i) {
                    cout << matrix[bottom][i] << ' ';
                }
                for (int i = bottom; i >= top + 1; --i) {
                    cout << matrix[i][left] << ' ';
                }
            } else
                break;
            top++;
            left++;
            bottom--;
            right--;
            order=false;
        } else{
            for (int i = top; i <= bottom; ++i) {
                cout<<matrix[i][left]<<' ';
            }
            for (int i = left+1; i <= right; ++i) {
                cout<<matrix[bottom][i]<<' ';
            }
            if (top<bottom&&left<right) {
                for (int i = bottom - 1; i >= top + 1; --i) {
                    cout << matrix[i][right] << ' ';
                }
                for (int i = right; i >= left + 1; --i) {
                    cout << matrix[top][i] << ' ';
                }
            } else
                break;
            top++;
            left++;
            bottom--;
            right--;
            order=true;
        }

    }
    return 0;
}
