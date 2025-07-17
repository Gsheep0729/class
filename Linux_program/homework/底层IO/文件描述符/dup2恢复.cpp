#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int fd;
    int original_stdout = dup(1);// 保存原始的标准输出文件描述符
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
    printf("***这里是高扬的测试文字1.0***\n");

    //关闭原始文件描述符
    close(fd);

    //恢复原始标准输出
    dup2(original_stdout, 1);
    if (dup2(original_stdout, 1) == -1)
    {
        perror("恢复标准输出失败");
    }
    
    close(original_stdout);

    // 测试 printf 是否恢复正常
    printf("***这里是高扬的测试文字2.0***\n");

    return 0;
}