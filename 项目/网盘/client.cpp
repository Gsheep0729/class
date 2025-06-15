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
            if (package->errorCode == 1)
            {
                // 完成标志
                cout << endl;
                break;
            }
            else if (package->errorCode == 0)
            cout << package->name << " 、 ";
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
    package->errorCode = 0;
    package->cmd = CMD_NULL;
}


bool deals(int socket, Package *package)
{
    // LS命令
    package->errorCode = 0;//使用前再初始化一次，防止重复时的错误
    package->cmd = LS;
    if (!sendPackage(socket, package))
    {
        cout << "发送命令失败" << endl;
        return false;
    }
    // 获取处理结果
    getDealResult(socket, package);
    return true;
}


bool dealUpload(int socket, Package *package)
{
    /*上传客户端文件到服务器：输入本地指定路径文件，然后上传至服务器工作目录下 */
    package->cmd = UPLOAD;
    if (!sendPackage(socket, package))
    {
        cout << "发送UPLOAD命令失败" << endl;
        return false;
    }

    string localFilePath = "";
    cout << "请输入要上传的本地文件完整路径: " << endl;
    cin >> localFilePath;

    // 检查本地要上传的文件是否存在
    FILE *fp = fopen(localFilePath.c_str(), "r");
    if (!fp)
    {
        perror("文件打开失败");
        return false;
    }
    fclose(fp);

    // 获取本地要上传的文件名
    string fileName = localFilePath.substr(localFilePath.find_last_of("/\\") + 1);

    // 设置package.name为文件名
    strncpy(package->name, fileName.c_str(), MAX_FILE_NAME_SIZE - 1);
    package->name[MAX_FILE_NAME_SIZE - 1] = '\0';

    // 打开文件准备上传
    fp = getFp(package, localFilePath, "r");
    if (!fp)
    {
        cout << "上传打开文件失败" << endl;
        return false;
    }

    //  发送本地要上传的文件名
    sendPackage(socket, package);

    return readFile(socket, package, fp, mutex);
}

bool dealDownload(int socket, Package *package)
{
    package->cmd = DOWNLOAD;
    if (!sendPackage(socket, package))
    {
        cout << "发送命令失败" << endl;
        return false;
    }

    string fileName = "";
    cout << "请输入要下载的服务器文件名: " << endl;
    cin >> fileName;

    // 设置package.name为要下载的文件名
    strncpy(package->name, fileName.c_str(), MAX_FILE_NAME_SIZE - 1);
    package->name[MAX_FILE_NAME_SIZE - 1] = '\0';

    // 发送要下载的文件名
    if (!sendPackage(socket, package))
    {
        cout << "发送要下载的文件名失败" << endl;
        return false;
    }

    // 生成客户端保存文件的路径
    string filePath = string(CLIPATH) + "/" + fileName;
    string uniquePath = generateUniqueFilename(filePath); // 自动处理重命名

    // 打开文件准备写入
    FILE *fp = getFp(package, uniquePath, "w");
    if (!fp)
    {
        cout << "下载打开文件失败" << endl;
        return false;
    }
    
    bool success = writeFile(socket, package, fp, mutex);
    
    if (success)
    {
        //下载成功后显示文件路径
        cout << "文件下载成功！保存路径: " << uniquePath << endl;
    }
    
    return success;
}

bool dealFatherDir(int socket, Package *package, string &currentDir)
{
    // 参数校验
    if (!package) {
        cout << "无效的 package 指针" << endl;
        return false;
    }

    // 设置命令并发送
    package->cmd = FATHERDIR;
    package->errorCode = 4;
    if (!sendPackage(socket, package)) {
        cout << "发送FATHERDIR命令失败" << endl;
        // 恢复 package 状态
        package->cmd = CMD_NULL;
        return false;
    }
    if (recvPackage(socket, package)<= 0)
    {
        cout << "服务器未响应...请重新再试" << endl;
        // 恢复 package 状态
        package->cmd = CMD_NULL;
        return false;
    }
    else
    {
        //接受响应
        if (package->errorCode == 0)
        {
            return true;
        }
        else if(package->errorCode == -1)
        {
            cout << "已经是根目录咯～～" << endl;
            return false;
        }
        

    }
    return false;

}

bool dealSonDir(int socket, Package *package, string &currentDir)
{
    
    // SONDIR命令
    package->cmd = SONDIR;
    if (!sendPackage(socket, package))
    {
        return false;
    }

    string pathName = "";
    std::cout << "请输入子目录名: " << endl;
    std::cin >> pathName;

    // 将要进入的子目录名存入package->name
    strncpy(package->name, pathName.c_str(), MAX_FILE_NAME_SIZE - 1);
    package->name[MAX_FILE_NAME_SIZE - 1] = '\0';

    // 发送子目录名
    if (!sendPackage(socket, package)) {
        cout << "发送子目录名失败" << endl;
        return false;
    }

    // 接收服务器响应（包含新路径）
    recvPackage(socket, package);

    if (package->errorCode != 0)
    {
        cout << "进入子目录失败: " << package->errorCode << endl;
        return false;
    }

    // 进入子目录成功，更新当前路径
    currentDir = package->path;
    cout << "已进入目录: " << currentDir << endl;
    
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
    // 定义时始化结构体
    memset(&package, 0, sizeof(Package));

    while (1)
    {
        //每次打印菜单前先接受服务端的路径包以打印菜单（此时包只含工作路径）
        if (recvPackage(socket, &package) <= 0)
        {
            cout << "接受服务端路径包失败" << endl;
            exit(EXIT_FAILURE);//立即终止当前程序运行
        }
        string currentDir = package.path;
        printMenu(currentDir);
        int choice;

        cin >> choice;//输入的同时阻塞

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
        package.cmd = CMD_NULL;
        package.errorCode = 0;
    }

    return 0;
}