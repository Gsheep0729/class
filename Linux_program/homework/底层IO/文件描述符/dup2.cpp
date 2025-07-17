#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int fd;
    // 打开文件
    if ((fd = open("myoutput", O_WRONLY | O_CREAT, 0644)) == -1)
    {
        perror("打开失败");
        return 1;
    }

    /*文件描述符 0：标准输入（stdin），用于从输入源（如键盘）读取数据。
    文件描述符 1：标准输出（stdout），用于向输出目标（如终端）写入正常输出信息。
    文件描述符 2：标准错误（stderr），用于向输出目标（如终端）写入错误信息。
    */

    // 使用 dup2 将标准输出（文件描述符 1）重定向到文件描述符 fd
    if (dup2(fd, 1) == -1)
    {
        perror("dup2失败");
        close(fd);
        return 1;
    }

    //将标准输出到终端修改输出到文件
    printf("***这里是高扬的测试文字1.0***D\n");

    // 关闭原始文件描述符
    close(fd);

    return 0;
}