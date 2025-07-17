#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int global = 100;

// 假设arg是int *类型
void *thread_function(void *arg)
{
    pthread_t thread_id = pthread_self();

    // 线程会立即终止
    pthread_exit((void *)123);
    printf("Thread ID: %lu\n", (unsigned long)thread_id);

    sleep(2);

    // printf("arg =  %d\n", *((int *)arg));
    // printf("global =  %d\n", global);
    return NULL;
}

int main()
{
    /* 声明两个POSIX线程标识符变量
 * - pthread_t类型用于唯一标识一个线程，通常为整型或结构指针
 * 这两个变量将用于：
 *   1. 存储新创建线程的ID
 *   2. 作为参数传递给pthread_create()等线程管理函数
 *   3. 用于后续的线程操作（如join/detach等） */
    pthread_t thread1, thread2;

    int num1 = 10;
    int num2 = 20;
    /*
 * 创建新线程并启动执行
 * 
 * @param thread1 [out] 线程标识符指针，用于存储新创建线程的ID
 * @param attr [in] 线程属性指针，NULL表示使用默认属性
 * @param thread_function [in] 线程入口函数指针，函数签名应为void* (*)(void*)
 * @param &num1 [in] 传递给线程函数的参数指针，需要保证参数在线程运行期间有效
 * @return int 线程创建结果，0表示成功，非零表示错误码（需检查errno）
 */
    // 创建两个线程  进入就绪状态
    pthread_create(&thread1, NULL, thread_function, &num1);
    pthread_create(&thread2, NULL, thread_function, &num2);

    // 1 error
    // for (int i = 0; i < 100; i++)
    // {
    //     printf("%d\n", i);
    // }

    // 等待两个线程完成，控制这两个线程的执行顺序。
    // pthread_join(thread1, NULL);
    // pthread_join(thread2, NULL);

    void *thread_return = NULL;

    int return_result = 0;
    return_result = pthread_join(thread1, &thread_return); 
    printf("线程退出状态: %ld\n", (long)thread_return);

    return_result = pthread_join(thread2, &thread_return);
    printf("线程退出状态: %ld\n", (long)thread_return);

    // pthread_detach(thread1);
    // pthread_detach(thread2);

    // 2
    // for (int i = 0; i < 100; i++)
    // {
    //     printf("%d\n", i);
    // }

    return 0;
}