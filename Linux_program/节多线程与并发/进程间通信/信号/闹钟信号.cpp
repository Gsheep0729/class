#include <stdio.h>
#include <unistd.h>

int main()
{
    // 设置闹钟为5s
    alarm(1);
    for (int i = 1; i < 1000000; i++)
    {
        printf("i = %d\n", i);
    }

    int a = alarm(0); // 取消闹钟,将原来闹钟没有执行的时间返回(接收到了sigalarm信号 终止进程 后面不会被执行)

    printf("a = %d\n", a);

    return 0;
}