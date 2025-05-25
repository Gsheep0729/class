#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

// 定义互斥锁为一个全局变量保证了只有一个线程可以访问
pthread_mutex_t lock;

// 共享变量
int shared_counter = 0;

// 10w一次性累加完
void *increment_counter(void *arg)
{
    // 加锁
    pthread_mutex_lock(&lock);

    for (int i = 0; i < 100000; ++i)
    {
        shared_counter++;
    }
    // 解锁
    pthread_mutex_unlock(&lock);

    std::cout
        << "Thread " << pthread_self() << " finished incrementing. Counter value: " << shared_counter << std::endl;
    return NULL;
}

int main()
{
    // 初始化互斥锁
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    pthread_t thread1 = 0;
    // 创建线程1
    int ret = pthread_create(&thread1, NULL, &increment_counter, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "Error: pthread_create() failed\n");
        return 1;
    }

    pthread_t thread2 = 0;
    // 创建线程2
    ret = pthread_create(&thread2, NULL, &increment_counter, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "Error: pthread_create() failed\n");
        return 1;
    }

    // 主线程等待子线程1结束
    ret = pthread_join(thread1, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "Error: pthread_join() failed\n");
        return 1;
    }

    // 主线程等待子线程2结束
    ret = pthread_join(thread2, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "Error: pthread_join() failed\n");
        return 1;
    }

    // 输出最终的共享变量值
    std::cout << "Final counter value: " << shared_counter << std::endl;

    // 销毁互斥锁
    pthread_mutex_destroy(&lock);

    return 0;
}