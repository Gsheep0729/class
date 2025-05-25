#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <semaphore.h>

// 定义任务  线程创建时的函数
typedef void *(*thread_fun)(void *);

// 任务函数
typedef struct
{
    thread_fun fun; //// 函数指针
    void *arg;      // 参数
} Task;

typedef struct
{
    pthread_t *thread; // 线程数组
    Task *task_queue;  // 任务队列
    int threads_num;   // 线程数
    int stop;          // 线程池是否停止，停止为1.否则为0
    int queue_size;    // 这里使用的是数组来实现循环队列，queue_size是数组大小，实际队列可用的容量是size-1
    int queue_front;   // 指向队列头部
    int queue_end;     // 指向队列尾部

    pthread_mutex_t thread_mutex; // 线程池中的互斥锁
    pthread_cond_t thread_cond;   // 线程池中的条件变量

} ThreadPool;

// 工作线程函数  轮询：从队列取出任务并操作
// 参数 threadPool:线程池
void *loopTask(void *threadPool)
{
    ThreadPool *pool = (ThreadPool *)threadPool;

    while (1)
    {
        // 从任务队列中获取任务时，先将任务队列上锁
        pthread_mutex_lock(&pool->thread_mutex);
        // 当任务队列没有任务 while防止虚假唤醒
        while (pool->queue_front == pool->queue_end)
        {
            // 若任务队列为空，则应该一直阻塞
            pthread_cond_wait(&pool->thread_cond, &pool->thread_mutex);

            // 直到线程池关闭
            if (pool->stop)
            {
                break;
            }
        }

        // 线程池关闭
        if (pool->stop)
        {
            // 解锁
            pthread_mutex_unlock(&pool->thread_mutex);
            break;
        }

        // 当任务队列存在任务
        //  任务出队
        Task task = pool->task_queue[pool->queue_front];
        // 更新队头
        pool->queue_front = (pool->queue_front + 1) % pool->queue_size;

        // 解锁任务队列
        pthread_mutex_unlock(&pool->thread_mutex);
        // 执行任务函数
        task.fun(task.arg);
    }

    // 结束线程
    pthread_exit(NULL);
    return NULL;
}

// 创建线程池
void createPool(ThreadPool *pool, int thread_num, int task_queue_size)
{
    // 线程池状态设置为开始
    pool->stop = 0;
    // 设置线程数
    pool->threads_num = thread_num;
    // 为线程数组申请空间
    pool->thread = (pthread_t *)malloc(sizeof(pthread_t) * thread_num);
    if (!pool->thread)
    {
        printf("申请内存失败.\n");
        exit(-1);
    }

    int ret = 0;
    // 创建线程
    for (int i = 0; i < thread_num; i++)
    {
        ret = pthread_create(&pool->thread[i], NULL, &loopTask, pool);
        if (ret != 0)
        {
            printf("线程创建失败\n");
            exit(-1);
        }
    }

    // 设置任务数
    pool->queue_size = task_queue_size;
    // 为任务队列申请空间
    pool->task_queue = (Task *)malloc(sizeof(Task) * task_queue_size);
    if (!pool->task_queue)
    {
        printf("申请内存失败.\n");
        exit(-1);
    }

    // 初始化队列的对头和队尾下标
    pool->queue_front = 0;
    pool->queue_end = 0;

    // // 初始化条件变量
    ret = pthread_cond_init(&pool->thread_cond, NULL);
    if (ret != 0)
    {
        printf("条件变量初始化失败\n");
        exit(-1);
    }

    // 初始化互斥锁
    ret = pthread_mutex_init(&pool->thread_mutex, NULL);
    if (ret != 0)
    {
        printf("互斥锁初始化失败\n");
        exit(-1);
    }

    printf("线程池创建成功.\n");
}

// 向线程池中添加任务
int addTask(ThreadPool *pool, Task task)
{
    // 加锁
    pthread_mutex_lock(&pool->thread_mutex);

    // 队列已满
    if ((pool->queue_end + 1) % pool->queue_size == pool->queue_front)
    {
        // 队列已满
        printf("队列满了\n");
        // 解锁
        pthread_mutex_unlock(&pool->thread_mutex);
        return -1;
    }

    // 任务入队
    pool->task_queue[pool->queue_end] = task;
    // 更新队尾
    pool->queue_end = (pool->queue_end + 1) % pool->queue_size;
    // 解锁
    pthread_mutex_unlock(&pool->thread_mutex);
    // printf("%d任务入队成功\n", *(int *)task.arg);

    // 通知
    pthread_cond_broadcast(&pool->thread_cond);

    return 1;
}

// 销毁线程池
void destroypool(ThreadPool *pool)
{
    // 加锁
    pthread_mutex_lock(&pool->thread_mutex);
    // 设置销毁标志
    pool->stop = 1;
    // 解锁
    pthread_mutex_unlock(&pool->thread_mutex);

    // 唤醒所有线程
    pthread_cond_broadcast(&pool->thread_cond);
    for (int i = 0; i < pool->threads_num; i++)
    {
        // 等待所有线程结束
        pthread_join(pool->thread[i], NULL);
        printf("第%d个线程结束了,线程id：%lu\n", i + 1, pool->thread[i]);
    }

    printf("线程销毁完毕\n");
    // 释放空间
    free(pool->thread);
    pool->thread = NULL;
    free(pool->task_queue);
    pool->task_queue = NULL;

    if (pthread_cond_destroy(&pool->thread_cond) == -1)
    {
        perror("error\n");
    }
    printf("条件变量销毁完毕\n");

    // 销毁锁
    pthread_mutex_destroy(&pool->thread_mutex);
    printf("锁销毁完毕\n");

    printf("线程池销毁成功...\n");
}

void *func(void *id)
{
    int t = rand() % 1000 + 1;
    // 休眠（单位微秒）
    usleep(t * 1000);

    printf("任务ID: %d，休眠 %d 毫秒\n", *((int *)id), t / 1);
    return id;
}

int main()
{
    ThreadPool *pool = (ThreadPool *)malloc(sizeof(ThreadPool));
    // // 创建一个包含5个线程的，100个任务的线程池
    createPool(pool, 5, 100);

    int ids[50]; // 创建一个整数数组来存储任务ID
    for (int i = 1; i <= 50; i++)
    {
        ids[i - 1] = i; // 初始化数组元素

        Task t;
        t.fun = func;
        t.arg = (void *)&ids[i - 1];
        addTask(pool, t);
    }

    sleep(50); // 要保证所有线程任务都已结束
    printf("任务全部执行完毕\n");

    destroypool(pool);
    free(pool);

    return 0;
}