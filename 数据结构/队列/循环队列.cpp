/*顺序队列*/
#include <iostream>
using namespace std;
#define MAXSIZE 10

typedef struct
{
    int data[MAXSIZE];
    int front;
    int rear;
}queue;


// （1）初始化顺序队列；
void InitQueue(queue &q)
{
    q.front = q.rear = 0;
}


// （2）数据元素入队；
void EnQueue(queue &q, int x)
{
    if ((q.rear + 1) % MAXSIZE == q.front)
    {
        cout << "队列满" << endl;
        return;
    }
    q.data[q.rear] = x;
    q.rear = (q.rear + 1) % MAXSIZE;
    cout << x <<"入队成功" << endl;
}


// （3）数据元素出队；
void DeQueue(queue &q)
{
    if (q.front == q.rear)
    {
        cout << "队列空" << endl;
        return;
    }
    int x = q.data[q.front];
    q.front = (q.front + 1) % MAXSIZE;
    cout << x <<"出队成功" << endl;
}


// （4）读队头元素；
void GetHead(queue &q)
{
    if (q.front == q.rear)
    {
        cout << "队列空" << endl;
        return;
    }
    cout <<"队头元素为：" <<q.data[q.front]<<endl;
}


// （5）判定队列空/满；
bool QueueEmpty(queue &q)
{
    if (q.front == q.rear)
        return true;
    else
        return false;
}


// （6）销毁顺序队列。
void DestroyQueue(queue &q)
{
    q.front = q.rear = 0;
    cout << "队列已销毁" << endl;
}


int main()
{
    queue q;
    InitQueue(q);//初始化队列
    for(int i=0;i<3;i++)
    EnQueue(q,i);//入队
    DeQueue(q);//出队
    GetHead(q);
    DestroyQueue(q);//销毁队列
    return 0;
}