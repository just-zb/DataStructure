#include<iostream>

using namespace std;
int main()
{
    int matrix[20][20];
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = 999999;
        }
    }
    int vertexNum, sideNum;
    int x, y, w;
    cin >> vertexNum >> sideNum;
    for (int i = 0; i < sideNum; i++)
    {
        cin >> x >> y >> w;
        if (x!=y)
        matrix[x][y] = w;
    }
    for (int k = 0; k < vertexNum; k++)
        for (int i = 0; i < vertexNum; i++)
            for (int j = 0; j < vertexNum; j++)
                if (matrix[i][j]>matrix[i][k] + matrix[k][j])
                    matrix[i][j] = matrix[i][k] + matrix[k][j];

    for (int i = 0; i < vertexNum; ++i) {
        for (int j = 0; j < vertexNum; ++j) {
            if (matrix[i][j]==999999)
                matrix[i][j]=-1;
        }
    }
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            cout<<matrix[i][j];
            if (j!=vertexNum-1)
                cout<<' ';
        }
        if (i!=vertexNum-1)cout << endl;
    }
    return 0;
}

