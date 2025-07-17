#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;
int global = 10;
int main()
{
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
sleep(1);
// 子进程
cout << "在子进程中，pid = " << getpid() << ", global = " << global <<
endl;
}
else
{
global = 100;
// 父进程
cout << "在父进程中，父进程pid = " << getpid() << "， 子进程pid = " << pid <<
"， global = " << global << endl;
}
return 0;
}
