/*客户端主程序*/
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <locale.h>
#include <sys/stat.h>
#include "fileTrans.h"

#define SERVER_IP "127.0.0.1"  // 客户端IP地址
#define PORT 8088                   // 端口号
#define CLIPATH "/media/gy/win/VSCODE/class/项目/网盘/下载目录" // 客户端下载目录

// 定义互斥锁
pthread_mutex_t mutex;

using namespace std;

// 打印菜单
void printMenu(string currentDir)
{
    cout << "-------------这是一个目录页面--------------" << endl;
    cout << "当前所在目录: " << currentDir << endl;
    cout << "1.查看当前目录下的文件" << endl;
    cout << "2.上传文件（暂不支持文件夹）" << endl;
    cout << "3.下载文件（暂不支持文件夹）" << endl;
    cout << "4.返回上一级目录" << endl;
    cout << "5.进入子目录" << endl;
    cout << "6.关闭客户端通信" << endl;
    cout << "7.关闭服务器" << endl;
    cout << "请输入您的选择：" ;
}

// 接受服务器传回的数据包
void getDealResult(int socket, Package *package)
{
    while (1)
    {
        int ret = recvPackage(socket, package);
        if (ret > 0)
        {
            if (package->errorCode != 0)
            {
                // 处理错误
                cout << endl <<"处理完成" <<  endl;
                break;
            }
            cout << package->name << endl;
        }
        else if (ret == 0)
        {
            cout << "连接已中断" << endl;
            // 销毁互斥锁
            pthread_mutex_destroy(&mutex);
            // 关闭套接字
            close(socket);
            cout << "客户端已关闭" << endl;
            exit(0);
        }
        else
        {
            cout << "接收消息失败" << endl;
            // 销毁互斥锁
            pthread_mutex_destroy(&mutex);
            // 关闭套接字
            close(socket);
            cout << "客户端已关闭" << endl;
            exit(0);
        }
    }
    // 清空 package 的 file 字段，以便后续请求时不会残留旧数据
    memset(package->file, 0, MAX_FILE_SIZE);
}



bool deals(int socket, Package *package)
{
    // LS命令
    package->errorCode = 0;//使用前再初始化一次，防止重复时的错误
    package->cmd = LS;
    sendPackage(socket, package);
    cout << "客户端发送的路径: " << package->path << endl; // 调试输出
    // 发送客户端的套接字和路径（包里）
    std::cout << "发送成功" << std::endl;
    cout << "等待处理结果" << endl;
    // 获取处理结果
    getDealResult(socket, package);
    return true;
}


bool dealUpload(int socket, Package *package)
{
    /*上传客户端文件到服务器：输入本地指定路径文件，然后上传至服务器工作目录下 */
    package->cmd = UPLOAD;

    string localFilePath = "";
    cout << "请输入要上传的本地文件完整路径: " << endl;
    cin >> localFilePath;

    // 检查文件是否存在
    FILE *fp = fopen(localFilePath.c_str(), "r");
    if (!fp)
    {
        perror("文件打开失败");
        return false;
    }
    fclose(fp);

    // 获取文件名
    string fileName = localFilePath.substr(localFilePath.find_last_of("/\\") + 1);

    // 设置package.name为文件名
    strncpy(package->name, fileName.c_str(), MAX_FILE_NAME_SIZE - 1);
    package->name[MAX_FILE_NAME_SIZE - 1] = '\0';

    // 打开文件准备上传
    fp = getFp(package, localFilePath, "r");
    if (!fp)
    {
        return false;
    }

    sendPackage(socket, package);
    return readFile(socket, package, fp, mutex);
}

bool dealDownload(int socket, Package *package)
{
    /*下载服务器端文件到客户端：输入服务器文件名称，然后下载到客户端制定目录下  */
    package->cmd = DOWNLOAD;

    string fileName = "";
    cout << "请输入要下载的服务器文件名: " << endl;
    cin >> fileName;

    // string savePath = "";
    // cout << "请输入文件保存的本地路径: " << endl;
    // cin >> savePath;

    // 设置文件名
    strncpy(package->name, fileName.c_str(), MAX_FILE_NAME_SIZE - 1);
    package->name[MAX_FILE_NAME_SIZE - 1] = '\0';

    sendPackage(socket, package);

    getDealResult(socket, package);
    if (package->errorCode != 0)
    {
        cout << "下载文件失败:" << strerror(package->errorCode) << endl;
        return false;
    }

    // // 创建保存目录（如果不存在）
    // struct stat st = {0};
    // if (stat(savePath.c_str(), &st) == -1)
    // {
    //     mkdir(savePath.c_str(), 0700);
    // }

    // // 完整保存路径
    // string fullSavePath = savePath + "/" + fileName;

    FILE *fp = getFp(package, CLIPATH, "w");
    if (!fp)
    {
        return false;
    }

    return writeFile(socket, package, fp, mutex);
}

bool dealFatherDir(int socket, Package *package, string &currentDir)
{
    // FATHERDIR命令
    package->cmd = FATHERDIR;

    if (currentDir == "/")
    {
        return false;
    }
    // 找到字符ch最后一次出现的位置
    int lastPos = currentDir.find_last_of('/');
    // 如果找到了字符ch
    if (lastPos != std::string::npos)
    {
        // 只有一层目录 如/home 保留/
        if (lastPos == 0)
        {
            currentDir = currentDir.substr(0, lastPos + 1);
        }
        else
        {
            // 返回从字符串开始到字符ch最后一次出现位置（包含该位置）的子字符串
            currentDir = currentDir.substr(0, lastPos);
        }
    }
    // 修改服务器路径
    strcpy(package->path, currentDir.c_str());
    return sendPackage(socket, package);
}

bool dealSonDir(int socket, Package *package, string &currentDir)
{
    // SONDIR命令
    package->cmd = SONDIR;

    string pathName = "";
    std::cout << "请输入子目录名: " << endl;
    std::cin >> pathName;

    string tmp_dir = currentDir;
    tmp_dir += "/" + pathName;

    // 修改服务器路径
    strcpy(package->path, tmp_dir.c_str());

    sendPackage(socket, package);
    getDealResult(socket, package);
    if (package->errorCode != 0)
    {
        cout << "进入子目录失败: " << strerror(package->errorCode) << endl;
        // 将当前目录改回
        strcpy(package->path, currentDir.c_str());
        return false;
    }
    // 进入子目录成功，更新当前路径
    package->errorCode = 0;
    currentDir = tmp_dir;
    return true;
}

void dealQuitClient(int socket, Package *package)
{
    package->cmd = QUIT_CLIENT;
    sendPackage(socket, package);
    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);
    // 关闭套接字
    close(socket);
    cout << "客户端退出成功" << endl;
    // 程序结束
    exit(0);
}

void dealQuitServer(int socket, Package *package)
{
    package->cmd = QUIT_SERVER;
    sendPackage(socket, package);
    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);
    // 关闭套接字
    close(socket);
    cout << "服务器关闭成功" << endl;
    exit(0);
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

    // 创建客户端
    int socket = createClient(SERVER_IP, PORT);
    if (socket < 0)
    {
        perror("创建客户端失败");
        exit(EXIT_FAILURE);
    }
    cout << "客户端创建成功" << endl;

    Package package;
    // 初始化结构体
    memset(&package, 0, sizeof(package));  // 定义时始化结构体
    recvPackage(socket, &package);
    string currentDir = package.path;

    while (1)
    {
        printMenu(currentDir);
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            deals(socket, &package);
            break;
        case 2:
            dealUpload(socket, &package);
            break;
        case 3:
            dealDownload(socket, &package);
            break;
        case 4:
            dealFatherDir(socket, &package, currentDir);
            break;
        case 5:
            dealSonDir(socket, &package, currentDir);
            break;
        case 6:
            dealQuitClient(socket, &package);
            break;
        case 7:
            dealQuitServer(socket, &package);
            break;
        default:
            cout << "无效的选择，请重新输入" << endl;
        }
    }

    return 0;
}