#include <iostream>

using namespace std;

#define MAX_VERTICES 100 // 定义最大顶点数

// 初始化邻接矩阵  int (*p)[MAX_VERTICES]
void initializeGraph(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adjMatrix[i][j] = 0; // 初始化为0，表示没有边
        }
    }
}

// 添加有向边 u起点  v终点
void addDirectedEdge(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int u, int v)
{
    // 只需设置adjMatrix[u][v]为1，表示从u到v有一条有向边
    adjMatrix[u][v] = 1;
    // // 对于无向图，需要同时设置adjMatrix[u][v]和adjMatrix[v][u]
    // adjMatrix[v][u] = 1;
}

// 打印邻接矩阵
void printGraph(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// 主函数示例
int main()
{
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];

    int n = 5; // 假设图有5个顶点

    // 初始化图
    initializeGraph(adjMatrix, n);

    // 添加有向边
    addDirectedEdge(adjMatrix, 0, 1);

    addDirectedEdge(adjMatrix, 1, 0);
    addDirectedEdge(adjMatrix, 1, 4);

    addDirectedEdge(adjMatrix, 3, 2);

    addDirectedEdge(adjMatrix, 4, 0);
    addDirectedEdge(adjMatrix, 4, 2);

    // 打印邻接矩阵
    printGraph(adjMatrix, n);

    return 0;
}