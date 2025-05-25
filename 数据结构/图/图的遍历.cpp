#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

// 定义图的边（顶点值默认从0开始）用两个顶点之间的连接表示边
typedef struct Node
{
    int vertex;        // 下一个顶点（邻接点）的值
    struct Node *link; // 下一条边
} Node;

// 定义图
typedef struct Graph
{
    int numVertices; // 顶点数
    Node **adjLists; // 邻接表，每个顶点的邻接表
    bool *isVisited; // 标记是否被访问过了,数组的大小numVertices
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
        graph->adjLists[i] = NULL;
    }

    // 为标志位申请内存
    graph->isVisited = new bool[vertices]{0};

    return graph;
}

// 添加边 src起点 dest终点
void addEdge(Graph *graph, int src, int dest)
{
    // 创建边
    Node *newNode = new Node;
    // 设置邻接点
    newNode->vertex = dest;

    // 将新边添加到起点的邻接表中
    newNode->link = graph->adjLists[src];
    // 更新第一条边
    graph->adjLists[src] = newNode;

    //// 如果是无向图，也需要添加反向边
    ////Node* newNode2 = (Node*)malloc(sizeof(Node));
    // Node* newNode2 = new Node;
    // newNode2->vertex = src;
    // newNode2->link = graph->adjLists[dest];
    // graph->adjLists[dest] = newNode2;
}

// 深度优先遍历 v起点  2（已读）：    0（已读）-》 1（已读）：2（跳过）    3（已读）
void DFS(Graph *graph, int v)
{
    // 输出遍历到的节点
    cout << v << " ";

    // 递归访问所有未访问的邻接顶点
    Node *adjList = graph->adjLists[v];
    while (adjList)
    {
        // 标记当前节点为已访问
        graph->isVisited[v] = true;

        // 邻接点未被访问到
        if (!graph->isVisited[adjList->vertex])
        {
            DFS(graph, adjList->vertex);
        }

        // 往后遍历每一条边
        adjList = adjList->link;
    }
}

// 广度优先遍历
void BFS(Graph *graph, int startVertex)
{
    // 初始化队列
    std::queue<int> queue;

    // 标记所有顶点为未访问
    for (int i = 0; i < graph->numVertices; ++i)
    {
        graph->isVisited[i] = false;
    }

    // 将起始顶点加入队列，并标记为已访问
    queue.push(startVertex);
    graph->isVisited[startVertex] = true;

    while (!queue.empty())
    {
        // 从队列中取出一个顶点
        int vertex = queue.front();
        // 出队
        queue.pop();

        // 访问该顶点
        std::cout << "Visited " << vertex << std::endl;

        // 遍历该顶点的所有邻接点
        Node *adjList = graph->adjLists[vertex];
        while (adjList)
        {
            // 邻接点
            int adjVertex = adjList->vertex;

            // 如果邻接点未被访问，则加入队列并标记为已访问
            if (!graph->isVisited[adjVertex])
            {
                queue.push(adjVertex);
                graph->isVisited[adjVertex] = true;
            }

            // 移动到下一个邻接点
            adjList = adjList->link;
        }
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
    // 创建一个包含4个顶点的图
    Graph *graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);

    addEdge(graph, 1, 2);

    addEdge(graph, 2, 3);
    addEdge(graph, 2, 0);

    // 深度优先遍历图
    cout << "深度优先遍历（从顶点2开始）:" << endl;
    DFS(graph, 2);
    cout << endl;

    cout << "广度优先遍历（从顶点2开始）:" << endl;


    BFS(graph, 2);

    freeGraph(graph);
    graph = NULL;

    return 0;
}