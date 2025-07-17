#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

// 定义互斥锁
pthread_mutex_t mutex;
// 定义条件变量
pthread_cond_t cond;

int Salary = -2; // 全局资源

// 消费者
void *women(void *arg)
{
    while (1)
    {
        // 加锁
        pthread_mutex_lock(&mutex);

        // 判断 有可能虚假唤醒
        while (Salary <= 0)
        {
            cout << "钱没了，快去赚钱, Salary = " << Salary << endl;
            // 等待可用资源  不需要解锁
            pthread_cond_wait(&cond, &mutex);
        }

        // 消费
        Salary--;
        cout << "花了1块钱, Salary = " << Salary << endl;

        // 释放锁，让其他线程可以访问工资
        pthread_mutex_unlock(&mutex);
        // 休眠一段时间，模拟消费过程耗时
        sleep(2);
    }
}

// 生产者
void *man(void *arg)
{
    while (1)
    {
        // 加锁
        pthread_mutex_lock(&mutex);

        // 生产
        Salary++;
        cout << "挣了1块钱, Salary = " << Salary << endl;

        // 唤醒 通知消费者
        pthread_cond_signal(&cond);

        // 释放锁，让其他线程可以访问工资
        pthread_mutex_unlock(&mutex);
        // 休眠一段时间，模拟生产过程耗时
        sleep(2);//生产的速度更快，所以salary越来越多
    }
}

int main()
{
    // 初始化锁
    pthread_mutex_init(&mutex, NULL);
    // 初始化条件变量
    pthread_cond_init(&cond, NULL);

    pthread_t Man, Woman;
    // 创建线程
    pthread_create(&Man, NULL, man, NULL);
    pthread_create(&Woman, NULL, women, NULL);

    // 等待线程结束
    pthread_join(Man, NULL);
    pthread_join(Woman, NULL);

    // 销毁锁和条件变量
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}