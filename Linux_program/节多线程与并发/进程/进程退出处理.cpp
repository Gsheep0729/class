#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

void cleanup1(void)
{
    printf("Executing cleanup function 1\n");
}

void cleanup2(void)
{
    printf("Executing cleanup function 2\n");
}

int main()
{

    // 注册两个清理函数
    atexit(cleanup1);
    atexit(cleanup2);

    printf("Main function is running\n");

    // 杀死进程 kill -9
    _exit(0);
    // // 终止进程 kill -15
    //exit(0);
    // // 正常结束，执行已注册的函数
    return 0;
}