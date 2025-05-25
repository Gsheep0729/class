#include <iostream>

using namespace std;

// 定义常量以限制顶点数（实际应用中可能通过动态内存分配来处理更多顶点）
#define MAX_VERTICES 100

// 定义边
typedef struct EdgeNode
{
    int adjvex;            // 邻接点  终点
    struct EdgeNode *next; // 下一条边 这个指针用于连接同一起点的多条边。
} EdgeNode;

// 定义顶点
typedef struct VertexNode
{
    int data;            // 顶点信息  起点
    EdgeNode *firstedge; // 这个指针用于从顶点出发找到其第一条边 。
} VertexNode;

// 图的结构体
typedef struct GraphAdjList
{
    VertexNode adjList[MAX_VERTICES]; // 顶点数组
    int numVertices;                  // 顶点数
    int numEdges;                     // 边数

} GraphAdjList;

// 初始化图 n顶点数
void InitGraph(GraphAdjList *G, int n)
{
    // 顶点n
    G->numVertices = n;
    // 边0
    G->numEdges = 0;
    for (int i = 0; i < n; i++)
    {
        G->adjList[i].data = i;         // 插入顶点
        G->adjList[i].firstedge = NULL; // 初始化边
    }
}

// 向图中添加边 u起始顶点 v邻接点(终点)
void AddEdge(GraphAdjList *G, int u, int v)
{
    EdgeNode *newNode = (EdgeNode *)malloc(sizeof(EdgeNode)); // 创建新边节点
    if (!newNode)
    {
        printf("申请内存失败\n");
        exit(-1);
    }
    newNode->adjvex = v; // 设置邻接点

    // 头插法 u
    newNode->next = G->adjList[u].firstedge; // 下一条边 = 原来的第一条边
    G->adjList[u].firstedge = newNode;       // 更新第一条边
    G->numEdges++;                           // 边数加1

    //// 如果是无向图 还需要再添加一条边
    // EdgeNode* newNodeV = (EdgeNode*)malloc(sizeof(EdgeNode)); // 创建新边节点
    // if (!newNodeV)
    //{
    //     printf("申请内存失败\n");
    //     exit(-1);
    // }
    // newNodeV->adjvex = u;                     // 设置邻接点
    ////头插法
    // newNodeV->next = G->adjList[v].firstedge; // 下一条边 = 原来的第一条边
    // G->adjList[v].firstedge = newNodeV;       // 更新第一条边
}

// 打印邻接表
void PrintGraph(GraphAdjList G)
{
    printf("Graph with %d vertices and %d edges:\n", G.numVertices, G.numEdges);
    // 根据顶点数遍历
    for (int i = 0; i < G.numVertices; i++)
    {
        // 顶点
        printf("Vertex %d: ", G.adjList[i].data);
        // 找到第一条边
        EdgeNode *p = G.adjList[i].firstedge;
        // 所有邻接的终点信息打印出来
        while (p)
        {
            // // 邻接点(终点)
            printf("%d ", p->adjvex);
            p = p->next;
        }
        printf("\n");
    }
}

// 释放图占用的内存
void freeGraph(GraphAdjList *graph)
{
    if (graph == NULL)
    {
        return;
    }
    // 释放边
    for (int i = 0; i < graph->numVertices; i++)
    {
        EdgeNode *current = graph->adjList[i].firstedge;
        EdgeNode *temp = NULL;
        // 遍历并释放当前顶点的所有边
        while (current)
        {
            temp = current;
            current = current->next;
            free(temp);
            temp = NULL;
        }
    }
}

// 主函数示例
int main()
{
    GraphAdjList G;

    // 初始化图
    InitGraph(&G, 5);

    // 添加边
    AddEdge(&G, 0, 1);
    AddEdge(&G, 0, 4);

    AddEdge(&G, 1, 2);
    AddEdge(&G, 1, 3);

    AddEdge(&G, 2, 3);

    // 打印图
    PrintGraph(G);

    freeGraph(&G);

    return 0;
}