/*客户端主程序*/
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
#define SERPath "/home/gy/桌面" //  服务器默认工作目录

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
    string fileName = ""; // 初始文件名为空
    FILE *fp = NULL;

    switch (package->cmd)
    {
        // 查看当前目录下文件
        case LS:
            return readDir(clientSocket, package);

        // 上传文件
        case UPLOAD:
        {
            /*上传客户端文件到服务器：输入本地指定路径文件，然后上传至服务器工作目录下 */
            std::string serverFilePath = std::string(get_current_dir_name()) + "/" + std::string(package->name);
            FILE *serverFile = getFp(package, serverFilePath, "w+");
            if (!serverFile)
            {
                return false;
            }
            return writeFile(clientSocket, package, serverFile, mutex);
        }

        // 下载文件
        case DOWNLOAD:
        {
            /*下载服务器端文件到客户端：输入服务器文件名称，然后下载到客户端制定目录下*/
            std::string filePath = std::string(SERPath) + "/" + std::string(package->name);
            FILE *file = getFp(package, filePath, "r");
            if (!file)
            {
                return false;
            }
            sendPackage(clientSocket, package);
            if (!file)
            {
                return false;
            }
            return readFile(clientSocket, package, file, mutex);
        }

        // 返回父目录
        case FATHERDIR:
            if (chdir(package->path) < 0)
            {
                perror("返回父目录失败");
                package->errorCode = errno;
                sendPackage(clientSocket, package);
                return false;
            }
            package->errorCode = 0;
            return true;

        // 进入子目录
        case SONDIR:
            if (chdir(package->path) < 0)
            {
                perror("进入子目录失败");
                package->errorCode = errno;
                sendPackage(clientSocket, package);
                return false;
            }
            package->errorCode = 0;
            sendPackage(clientSocket, package);
            return true;

        // 客户端断开连接
        case QUIT_CLIENT:
            pthread_mutex_destroy(&mutex);
            close(clientSocket);
            return true;

        // 关闭服务器
        case QUIT_SERVER:
            if (kill(getppid(), SIGTERM) == -1)
            {
                perror("父进程终止失败");
                exit(EXIT_FAILURE);
            }
            pthread_mutex_destroy(&mutex);
            close(clientSocket);
            close(serverSocket);
            cout << "服务器关闭成功" << endl;
            exit(0);
            break;

        default:
            cout << "未知命令" << endl;
            return false;
    }

    cout << "未知命令" << endl;
    return false;
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
        if (package.errorCode  != 0)
        {
            cout << package.cmd  << ": " << "处理完成" << endl;
        }
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

    Package package;
    
    // 初始化结构体
    memset(&package, 0, sizeof(package));  // 定义时始化结构体

    string currentDir = SERPath; // 初始下载目录
    // 初始化路径
    strncpy(package.path, currentDir.c_str(), MAX_FILE_PATH_SIZE - 1);
    package.path[MAX_FILE_PATH_SIZE - 1] = '\0';  // 确保终止符

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

        // 每连接成功一次，都创建一个子进程去和客户端进行通信
        pid_t pid = fork();
        if (pid == 0) // 子进程
        {
            cout << "客户端连接成功--子进程" << endl;
            // 发送初始化信息
            sendPackage(clientSocket, &package);
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