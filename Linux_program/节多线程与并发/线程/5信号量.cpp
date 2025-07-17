#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <semaphore.h>

sem_t semaphore;

int Salary; // 全局资源 不再必须了  记录可用资源数

using namespace std;

// 消费者
void *women(void *arg)
{
    while (1)
    {
        sem_wait(&semaphore);
        // 消费
        Salary--;
        cout << "花了1块钱, Salary = " << Salary << endl;

        // 休眠一段时间，模拟消费过程耗时
        sleep(2);
    }
}

// 生产者
void *man(void *arg)
{
    while (1)
    {
        sem_post(&semaphore);
        // 生产
        Salary++;
        cout << "挣了1块钱, Salary = " << Salary << endl;

        // 休眠一段时间，模拟生产过程耗时
        sleep(1);
    }
}

int main()
{
    // 初始化信号量，初始值为0
    if (sem_init(&semaphore, 0, 0) == -1)
    {
        perror("sem_init");
        return 1;
    }

    pthread_t Man, Woman;

    // 创建线程
    pthread_create(&Man, NULL, man, NULL);
    pthread_create(&Woman, NULL, women, NULL);

    // 等待线程结束
    pthread_join(Man, NULL);
    pthread_join(Woman, NULL);

    // 销毁信号量
    if (sem_destroy(&semaphore) == -1)
    {
        perror("sem_destroy");
        return 1;
    }

    return 0;
}