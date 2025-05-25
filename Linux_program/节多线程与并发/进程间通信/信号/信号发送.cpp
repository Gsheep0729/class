#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    // 创建子进程
    pid_t child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        // 子进程代码
        printf("Child process running, PID = %d\n", getpid());
        while (1)
        {
            sleep(1); // 无限循环，等待信号
        }
    }
    else
    {
        sleep(2); // 等待子进程启动

        // // 向子进程发送SIGTERM信号 终止进程信号
        if (kill(child_pid, SIGTERM) == -1)
        {
            perror("kill failed");
            exit(EXIT_FAILURE);
        }
        printf("SIGTERM signal sent to child process %d\n", child_pid);
    }

    return 0;
}