#include <iostream>
#include <cstdlib>
using namespace std;

// 定义队列节点
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 定义队列
typedef struct Queue
{
    Node *front; // 指向队列头部的指针
    Node *rear;  // 指向队列尾部的指针
    int size;    // 队列中元素的数量
} Queue;

// 初始化队列
void initQueue(Queue *q)
{
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

// 入队
void enqueue(Queue *q, int data)
{
    Node *newNode = new Node;
    if (!newNode)
    {
        cout << "申请内存失败" << endl;
        return;
    }
    // 新节点赋值
    newNode->data = data;
    newNode->next = NULL;

    // 队列为空
    if (q->front == NULL)
    {
        // 队头和队尾都是当前节点
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        // 队尾的next指向新节点
        q->rear->next = newNode;
        // 更新队尾
        q->rear = newNode;
    }
    // 长度 + 1
    q->size++;
}

// 出队
int dequeue(Queue *q)
{
    // 队列为空
    if (q->front == NULL)
    {
        cout << "队列为空" << endl;
        exit(-1);
    }

    // 保存原来队头
    Node *oldFront = q->front;
    // 保存原来对头的值
    int data = oldFront->data;
    // 更新队头
    q->front = q->front->next;

    // 如果出队后队列为空
    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    // 释放内存
    delete oldFront;
    oldFront = NULL;
    // 长度 - 1
    q->size--;

    return data;
}

// 打印队列
void printQueue(Queue *q)
{
    Node *current = q->front;
    while (current)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// 释放队列占用的内存
void freeQueue(Queue *q)
{
    Node *current = q->front;
    Node *next = NULL;
    while (current)
    {
        // 记录下一个节点
        next = current->next;
        delete current;
        current = next;
    }

    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

int main()
{
    Queue q = {0};
    initQueue(&q);
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    enqueue(&q, 4);

    cout << dequeue(&q) << endl;

    printQueue(&q);

    freeQueue(&q);

    return 0;
}