#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void sigint_handler(int sig_num)
{
    printf("Caught SIGINT! Exiting program...\n");
    exit(0); // 退出程序
}

int main()
{
    // 设置SIGINT信号的处理函数
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
    {
        perror("Failed to set SIGINT handler");
        return 1;
    }

    // 模拟程序正在执行一些长时间运行的任务
    printf("Program is running. Try pressing Ctrl+C to exit.\n");
    while (1)
    {
        sleep(1); // 休眠1秒，模拟工作
    }

    return 0;
}