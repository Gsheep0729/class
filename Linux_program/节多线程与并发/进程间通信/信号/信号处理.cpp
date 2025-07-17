#include <stdio.h>

#include <signal.h>
#include <unistd.h>

int main()
{
    // 发送SIGINT 2 信号给当前进程
    // raise(SIGINT);
    raise(2);

    // 不会被执行到，因为进程中止了
    printf("你好");

    return 0;
}