#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    int fd[2] = {0}; // 文件描述符数组，fd[0]用于读，fd[1]用于写

    char buf[100] = {0};

    // 创建无名管道
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 调用fork()创建子进程
    pid_t pid = fork();

    // 检查fork()的返回值，以确定当前进程是父进程还是子进程
    if (pid < 0)
    {
        // fork()失败
        cout << "fork失败" << endl;
        return -1;
    }
    else if (pid == 0)
    {
        // 子进程
        // 向管道写入数据
        const char *msg = "Hello from child!";
        // 向文件描述符fd[1]指向的写入msg指向的数据
        write(fd[1], msg, strlen(msg) + 1); // 加1是为了包含字符串结束符'\0'

        // 关闭读端
        close(fd[1]);

        _exit(0); // 子进程结束
    }
    else
    {
        // 父进程
        // 从管道读取数据
        ssize_t bytes_read = read(fd[0], buf, sizeof(buf) - 1);
        if (bytes_read == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // 确保字符串以'\0'结尾
        buf[bytes_read] = '\0';

        // 输出读取到的数据
        printf("Received from child: %s\n", buf);

        // 关闭写端（可选）
        close(fd[1]);

        // 等待子进程结束
        wait(NULL);
    }

    return 0;
}