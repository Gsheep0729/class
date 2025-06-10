/*服务端主程序*/
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <locale.h>
#include <sys/stat.h>
#include "fileTrans.h"

#define SERVER_IP "127.0.0.1"  // 服务器IP地址
#define PORT 8088                   // 端口号
#define SERVER_WORK_DIR "/home/gy/桌面" // 服务器工作目录

// 定义互斥锁
pthread_mutex_t mutex;

using namespace std;

/**
 * 线程任务：等待子进程的结束
 */
void task(void *data)
{
    pid_t pid = *(pid_t *)data;
    waitpid(pid, NULL, 0);
    std::cout << "连接进程:" << pid << "退出" << std::endl;
}

//处理连接
bool dealConnect(int clientSocket, int serverSocket, Package *package)
{
    switch (package->cmd)
    {
        // ... [其他命令处理] ...
        
        case UPLOAD:
        {
            /* 上传文件到服务器工作目录 */
            string serverFilePath = string(SERVER_WORK_DIR) + package->path + "/" + package->name;
            
            // 确保目录存在
            size_t pos = serverFilePath.find_last_of('/');
            if (pos != string::npos) {
                string dirPath = serverFilePath.substr(0, pos);
                mkdir(dirPath.c_str(), 0700); // 创建目录
            }
            
            FILE *serverFile = fopen(serverFilePath.c_str(), "w");
            if (!serverFile)
            {
                perror("文件创建失败");
                package->errorCode = errno;
                sendPackage(clientSocket, package);
                return false;
            }
            return writeFile(clientSocket, package, serverFile, mutex);
        }

        case DOWNLOAD:
        {
            /* 从服务器工作目录下载文件 */
            string filePath = string(SERVER_WORK_DIR) + package->path + "/" + package->name;
            FILE *file = fopen(filePath.c_str(), "r");
            if (!file)
            {
                perror("文件打开失败");
                package->errorCode = errno;
                sendPackage(clientSocket, package);
                return false;
            }
            return readFile(clientSocket, package, file, mutex);
        }
        
        // ... [其他命令处理] ...
    }
}


/**
 * 子进程的任务
 */
void process_main(int clientSocket, int serverSocket) // 类似于子进程的main函数
{

    
    while (1)
    {
        Package package;
        // 接收消息
        int ret = recvPackage(clientSocket, &package);
        if (ret > 0)// 接收成功
        {
            // 处理连接
            dealConnect(clientSocket, serverSocket, &package);
        }
        else if (ret == 0)
        {
            cout << "通信已中断" << endl;
            // 销毁互斥锁
            pthread_mutex_destroy(&mutex);
            // 关闭套接字
            close(clientSocket);
            // 关闭进程
            exit(0);
        }
        else
        {
            cout << "接收消息失败" << endl;
        }
        cout << "------------------处理成功------------------" << endl;
        if  (package.cmd == QUIT_CLIENT)// 客户端断开连接停止服务
        {
            break;
        }
    }
}

int main()
{
    // 设置编码格式为UTF-8
    setlocale(LC_ALL, "en_US.UTF-8");
    // 初始化互斥锁
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    // 创建服务器
    int serverSocket = createServer(SERVER_IP, PORT);
    if (serverSocket < 0)
    {
        perror("创建服务器失败");
        return -1;
    }
    cout << "创建服务器成功" << endl;

    int clientSocket = 0;
    // 等待客户端连接
    while (1)
    {
        // 记录客户端信息
        struct sockaddr_in address;
        socklen_t len = sizeof(address);
        cout << "等待连接" << endl;
        // 阻塞等待，在serverSocket上监听客户端连接，成功时保存客户端地址到address
        clientSocket = accept(serverSocket, (struct sockaddr *)&address, &len);
        if (clientSocket < 0)
        {
            perror("连接失败");
            close(serverSocket);
            return -1;
        }
        cout << "客户端连接成功" << endl;

        // 每连接成功一次，都创建一个子进程去和客户端进行通信
        pid_t pid = fork();
        if (pid == 0) // 子进程
        {
            cout << "客户端连接成功--子进程" << endl;
            // 子进程负责处理连接
            process_main(clientSocket, serverSocket);
        }
        else if (pid > 0) // 父进程
        {
            cout << "客户端连接成功--父进程" << endl;
            // 将任务添加到线程池（todo: 将线程池代码加入项目）
            // addTask(pool, task, &pid);
        }
    }
    return 0;
}