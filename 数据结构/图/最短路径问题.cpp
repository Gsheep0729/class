#include <iostream>
#include <queue>
#include <climits>
using namespace std;

// 定义图的边（顶点值默认从0开始）用两个顶点之间的连接表示边
typedef struct Node
{
    int vertex;        // 下一个顶点（邻接点）的值
    int weight;        // 边的权重
    struct Node *link; // 下一条边
} Node;

// 定义图
typedef struct Graph
{
    int numVertices; // 顶点数
    Node **adjLists; // 邻接表，
    bool *isVisited; // 标记是否被访问过了 数组的大小numVertices
} Graph;

// 创建一个图，包含vertices个顶点
Graph *createGraph(int vertices)
{
    Graph *graph = new Graph;
    // 初始化顶点数
    graph->numVertices = vertices;

    // 为邻接表申请内存
    graph->adjLists = new Node *[vertices];
    for (int i = 0; i < vertices; ++i)
    {
        // 初始化为空
        graph->adjLists[i] = NULL;
    }

    // 为标志位申请内存
    graph->isVisited = new bool[vertices]{0};

    return graph;
}

// 添加边 src起点 dest终点
void addEdge(Graph *graph, int src, int dest, int weight)
{
    Node *newNode = new Node;
    // 设置邻接点
    newNode->vertex = dest;
    // 设置权重
    newNode->weight = weight;

    // 将新边添加到起点的链表中
    newNode->link = graph->adjLists[src];
    // 更新第一条边
    graph->adjLists[src] = newNode;

    // 如果是无向图，也需要添加反向边
    Node *newNode2 = new Node;
    // 设置邻接点
    newNode2->vertex = src;
    // 设置权重
    newNode2->weight = weight;

    // 将新边添加到起点的链表中
    newNode2->link = graph->adjLists[dest];
    // 更新第一条边
    graph->adjLists[dest] = newNode2;
}

// 迪杰斯特拉算法  src:起点
void dijkstra(Graph *graph, int src)
{
    // 距离定义一个包含numVertices个元素的vector，每个成员用INT_MAX（∞）初始化  U
    std::vector<int> dist(graph->numVertices, INT_MAX);
    // 标记顶点是否被处理过了
    std::vector<bool> sptSet(graph->numVertices, false);

    dist[src] = 0; // 源顶点到自己的距离总是0

    //-1的原因是最后一部实际上已经没必要再执行了，即A的遍历，因为最短距离已经计算出来了
    for (int count = 0; count < graph->numVertices - 1; count++)
    {
        // 最小距离的顶点坐标信息，
        int minVertices = -1;
        // 最小距离
        int minDistance = INT_MAX;
        // 遍历所有顶点更新最短距离（第一步选中的必定是自身，因为自身的距离是0，肯定最小）   找到U里面最短距离及其下标
        for (int i = 0; i < graph->numVertices; i++)
        {
            // 顶点未被处理并且距离小于最小值
            if (!sptSet[i] && dist[i] < minDistance)
            {
                // 更新最小值
                minDistance = dist[i];
                // 记录顶点
                minVertices = i;
            }
        }

        // 该顶点标记为已处理
        sptSet[minVertices] = true;

        // 更新该顶点的所有邻接点（未被标记过的）的最短距离
        Node *adj = graph->adjLists[minVertices];
        while (adj)
        {
            // 邻接点
            int adjVertex = adj->vertex;
            // 邻接点未被标记过 && 最小距离不是无穷(意味着他到源顶点是可达的)&& 新距离小于原来的距离
            if (!sptSet[adjVertex] && dist[minVertices] != INT_MAX && dist[minVertices] + adj->weight < dist[adjVertex])
            {
                // 更新距离信息
                dist[adjVertex] = dist[minVertices] + adj->weight;
            }
            // 遍历所有的邻接点
            adj = adj->link;
        }
    }

    // 打印构造的距离数组
    for (int i = 0; i < graph->numVertices; i++)
    {
        std::cout << "Vertex " << i << " Distance from Source: " << dist[i] << std::endl;
    }
}

// 清理Graph对象
void freeGraph(Graph *graph)
{
    if (!graph)
    {
        return; // 如果指针为空，则直接返回
    }

    // 释放邻接表中每个链表占用的内存
    for (int i = 0; i < graph->numVertices; ++i)
    {
        Node *current = graph->adjLists[i];
        Node *next = NULL;
        while (current)
        {
            next = current->link; // 保存下一条边的指针
            delete current;       // 释放当前边的内存
            current = next;       // 移动到下一条边
        }
    }

    // 释放邻接表数组本身占用的内存
    delete[] graph->adjLists;

    // 释放访问标记数组占用的内存
    delete[] graph->isVisited;
}

int main()
{
    Graph *graph = createGraph(7);
    addEdge(graph, 0, 1, 12);
    addEdge(graph, 0, 5, 16);
    addEdge(graph, 0, 6, 14);

    addEdge(graph, 1, 2, 10);
    addEdge(graph, 1, 5, 7);

    addEdge(graph, 2, 3, 3);
    addEdge(graph, 2, 4, 5);
    addEdge(graph, 2, 5, 6);

    addEdge(graph, 3, 4, 4);

    addEdge(graph, 4, 5, 2);
    addEdge(graph, 4, 6, 8);

    addEdge(graph, 5, 6, 9);

    dijkstra(graph, 3);

    delete graph;
    graph = NULL;

    return 0;
}