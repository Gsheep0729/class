#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{

    // pid_t getpid(void); 获取进程ID
    pid_t pid = getpid();

    cout << "当前进程ID是：" << pid << endl;

    getchar();

    return 0;
}