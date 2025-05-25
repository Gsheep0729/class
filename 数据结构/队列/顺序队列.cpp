#include <iostream>
using namespace std;

// 定义最大长度
#define SIZE 100

// 定义顺序队列
typedef struct
{
    int buf[SIZE];
    int head;
    int tail;
} queue;

// 队列的初始化函数
void queue_init(queue *p_queue)
{
    p_queue->head = 0;
    p_queue->tail = 0;
}

// 获得队列里的数字个数
int queue_size(const queue *p_queue)
{
    // 队尾下标 - 队首下标
    return p_queue->tail - p_queue->head;
}

// 判断队列是否为空的函数
bool queue_empty(const queue *p_queue)
{
    return p_queue->tail == p_queue->head;
}

// 判断队列是否为满的函数
bool queue_full(const queue *p_queue)
{
    // 尾到达最大下标
    return p_queue->tail >= SIZE;
}

// 向队列里面加入数字的函数
bool queue_push(queue *p_queue, int num)
{
    // 队列满了
    if (queue_full(p_queue))
    {
        cout << "队列满了" << endl;
        return false;
    }

    // 尾部下标 + 1
    p_queue->tail++;

    cout << p_queue->head << endl;
    cout << p_queue->tail << endl;
    // 尾部插入
    p_queue->buf[p_queue->tail] = num;
    return true;
}

// 从队列里获得数字的函数(会删除数字)
bool queue_pop(queue *p_queue, int *p_num)
{
    // 队列为空
    if (queue_empty(p_queue))
    {
        cout << "队列为空" << endl;
        return false;
    }
    // head ==0  +1
    //  1.获取数字
    *p_num = p_queue->buf[p_queue->head];
    // 2.对头后移
    p_queue->head++;
    return true;
}

// 从队列里获得数字的函数(不会删除数字)
bool queue_front(const queue *p_queue, int *p_num)
{
    // 队列为空
    if (queue_empty(p_queue))
    {
        cout << "队列为空" << endl;
        return false;
    }
    *p_num = p_queue->buf[p_queue->head];
    return true;
}

int main()
{
    queue q = {0};
    queue_init(&q);
    queue_push(&q, 1);
    queue_push(&q, 2);
    queue_push(&q, 3);

    int popNum = 0;
    if (queue_pop(&q, &popNum))
    {
        cout << "队列出队元素是：" << popNum << endl;
    }

    if (queue_pop(&q, &popNum))
    {
        cout << "队列出队元素是：" << popNum << endl;
    }

    int frontNum = 0;
    if (queue_front(&q, &frontNum))
    {
        cout << "队列头部元素是：" << frontNum << endl;
    }

    return 0;
}