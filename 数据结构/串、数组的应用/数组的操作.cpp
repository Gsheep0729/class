/*
（1）建立一个n*n的对称矩阵A，用动态分配的一维数组B对矩阵A进行压缩存储，输出矩阵A和一维数组B；
（2）在B中查找对称矩阵A中第row行，第col列(下标从1开始)的元素，输出该元素值。
*/
#include <iostream>
using namespace std;
#define n 5

int main()
{
    //对称矩阵A
    int A[n][n] =  {{1,0,0,0,0},
                    {0,2,0,0,0},
                    {0,0,3,0,0},
                    {0,0,0,4,0},
                    {0,0,0,0,5}};

    int *B = new int[n * (n + 1) / 2];//分配等差想加个空间
    for (int i = 0, j = 0; i < n; i++)
    {
        for (int k = 0; k <= i; k++)
        {
            B[j++] = A[i][k];//储存对角线及左下角元素
        }
    }
    //输出矩阵A
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    //输出一维数组B
    for (int i = 0; i < n * (n + 1) / 2; i++)
    {
        cout << B[i] << " ";
    }
    cout << endl;

    //查找A中第row行，第col列的元素
    int row, col;
    cout << "请输入行号和列号（从1开始）："<< endl;
    cin >> row >> col;
    if (row < 1 || row > n || col < 1 || col > n)//判断输入的行和列是否合法
    {
        cout << "输入的行或列无效！" << endl;
    }
    else
    {
        int i, j;
        if (row >= col)//行号大于等于列号
        {
            i = row - 1;
            j = col - 1;
        
        }
        else//若行号小于列号，则交换，保证是矩阵对角线及左下角元素
        {
            i = col - 1;
            j = row - 1;
        }
        int index = i * (i + 1) / 2 + j;//计算B中元素的下标
        cout << "A[" << row << "][" << col << "] = " << B[index] << endl;
    }

    delete[] B;
    return 0;
}