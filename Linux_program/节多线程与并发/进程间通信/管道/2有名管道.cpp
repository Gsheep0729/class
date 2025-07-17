#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_PATH "/tmp/myfifo"

using namespace std;

// 子进程（读取进程）
void child_process()
{
    char buf[1024] = {0};

    // 打开有名管道以读取
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 读取数据
    ssize_t bytes_read = read(fd, buf, sizeof(buf) - 1);
    if (bytes_read == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("Child process read: %s\n", buf);
    close(fd);
}

// 父进程（写入进程）
void parent_process()
{
    // 打开有名管道以写入
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 写入数据
    const char *message = "Hello from parent process!";
    if (write(fd, message, strlen(message)) == -1)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

int main()
{
    // 创建有名管道，mkfifo()函数会在文件系统中创建一个特殊的文件
    if (mkfifo(FIFO_PATH, 0666) == -1)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // 创建子进程
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        // 子进程代码
        child_process();
    }
    else
    {
        // 父进程代码
        parent_process();

        // 等待子进程结束 子（读）先父（写）后
        wait(NULL);
    }

    return 0;
}