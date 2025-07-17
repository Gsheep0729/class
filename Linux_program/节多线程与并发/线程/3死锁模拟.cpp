#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

// 定义互斥锁
pthread_mutex_t lock1;
pthread_mutex_t lock2;

void *thread1_func(void *arg)
{
    // 线程1尝试先锁定lock1，然后锁定lock2
    pthread_mutex_lock(&lock1);
    printf("Thread 1: locked lock1\n");
    sleep(1); // 模拟一些工作

    // 在这里，线程1等待lock2，但如果线程2已经锁定了lock2并正在等待lock1，则会发生死锁
    pthread_mutex_lock(&lock2);
    printf("Thread 1: locked lock2\n");

    // 释放锁
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    return NULL;
}

void *thread2_func(void *arg)
{
    // 线程2尝试先锁定lock2，然后锁定lock1

    pthread_mutex_lock(&lock2);
    printf("Thread 2: locked lock2\n");
    sleep(1); // 模拟一些工作

    // 在这里，线程2等待lock1，但如果线程1已经锁定了lock1并正在等待lock2，则会发生死锁
    pthread_mutex_lock(&lock1);
    printf("Thread 2: locked lock1\n");

    // 释放锁
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    // 初始化互斥锁
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    // 创建线程
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    // 等待线程完成（但在这个例子中，它们可能永远不会完成，因为发生了死锁）
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    cout << "---------------------" << endl;

    // 销毁互斥锁（这行代码在死锁发生时永远不会被执行）
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    return 0;
}