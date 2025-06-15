/* 文件传输相关函数实现*/
#include "fileTrans.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <dirent.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

/*
 * 功能：创建服务器进入监听状态
 * 参数：
 *      ipv4：服务器地址
 *      port：端口号
 * 返回值：
 *      成功：返回创建好的服务器套接字
 *      失败：-1
 */
int createServer(const char *ipv4, int port)
{
    // 创建Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
    {
        perror("createServer:创建套接字失败");
        return -1;
    }

    struct sockaddr_in address;
    // 初始化地址和端口
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY); // 监听所有的IPv4
    //address.sin_addr.s_addr = inet_addr(ipv4);// 服务器绑定到指定地址
    address.sin_port = htons(port);

    int opt = 1;
    // SO_REUSEPORT 允许多个套接字绑定到同一个地址和端口上。并非所有操作系统都支持（例如，Windows 不支持此选项）
    // SO_REUSEADDR 允许在同一端口上启动服务器的监听，即使之前的服务器尚未关闭或仍在处理连接
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定套接字到端口
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("createServer:绑定端口失败");
        close(sockfd);
        return -1;
    }

    // 监听连接，最大连接5
    if (listen(sockfd, 5) < 0)
    {
        perror("监听失败");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

/*
 * 功能：创建客户端进入连接请求
 * 参数：
 *      ipv4：服务器地址
 *      port：端口号
 * 返回值：
 *      成功：返回创建好的客户端套接字
 *      失败：-1
 */
int createClient(const char *ipv4, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // 创建套接字文件描述符
    if (sock < 0)
    {
        perror("createClient:创建套接字失败");
        return -1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // 将地址从文本转换为二进制形式
    if (inet_pton(AF_INET, ipv4, &serv_addr.sin_addr) <= 0)
    {
        perror("createClient:ip地址转化失败");
        return -1;
    }

    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("createClient:连接到服务器失败");
        return -1;
    }

    return sock;
}

/*
 * 功能：发送数据包
 * 参数：
 *      sock：通信套接字
 *      package：发送的数据包
 * 返回值：
 *      成功：true
 *      失败：false
 */
bool sendPackage(int sock, Package *package)
{
    //发送包大小，0表示无特殊发送标志（默认阻塞发送）
    int ret = send(sock, package, sizeof(*package), 0);
    if (ret == -1)
    {
        perror("sendPackage:发送失败");
        return false;
    }
    //如果全部发送完毕，返回true
    return ret == sizeof(*package);

}

/*
 * 功能：接收数据包
 * 参数：
 *      sock：通信套接字
 *      package：接收的数据包
 * 返回值：
 *      接收到的数据包的大小
 *          正数：实际接收到的字节数
 *          0：连接已关闭
 *          负数：接收失败
 */
int recvPackage(int sock, Package *package)
{
    // 标准输入输出流接收消息，接收包大小的包数据
    int ret = read(sock, package, sizeof(*package));
    if (ret < 0)
    {
        perror("recvPackage:接收消息失败");
    }
    else if (ret == 0)
    {
        perror("recvPackage:通信中断");
    }
    return ret;
}

/*
 * 功能：获取文件指针
 * 参数：
 *      package：接收的数据包
 *      filename：文件名
 *      mode：文件打开方式
 * 返回值：
 *      成功：文件指针
 *      失败：NULL
 */
FILE *getFp(Package *package, std::string filename, const char *mode)
{
    // 打开文件
    FILE *fp = fopen(filename.c_str(), mode);
    if (!fp)
    {
        perror("getFp:文件打开失败");
        package->errorCode = errno;
        return NULL;
    }
    // 打开文件成功
    package->errorCode = 0;
    return fp;
}

/*
 * 功能：依次向文件中写入内容
 * 参数：
 *      sock：通信套接字
 *      package：接收的数据包
 *      fp：文件指针
 *      mutex：锁
 * 返回值：
 *      成功：true
 *      失败：false
 */
bool writeFile(int socket, Package *package, FILE *fp, pthread_mutex_t mutex)
{
    int size = 0;//记录已写入的字节数
    pthread_mutex_lock(&mutex); // 加锁
    while (1)
    {
        // 接收包
        int ret = recvPackage(socket, package);
        if (ret <= 0)
        {
            cout << "writeFile:接收消息失败" << endl;
            return false;
        }
        // 写入文件
        size = fwrite(package->file, 1, strlen(package->file), fp);
        if (size < 0)
        {
            perror("writeFile:文件写入失败");
            pthread_mutex_unlock(&mutex);
            return false;
        }
        else if (size < MAX_FILE_SIZE - 1)//为字符串终止符\0预留空间
        {
            // 写入完毕
            break;
        }
    }
    pthread_mutex_unlock(&mutex); // 解锁
    fclose(fp);
    package->errorCode = 0;
    return true;
}

/*
 * 功能：依次从文件中读取内容再发送
 * 参数：
 *      sock：通信套接字
 *      package：接收的数据包
 *      fp：文件指针
 *      mutex：锁
 * 返回值：
 *      成功：true
 *      失败：false
 */
bool readFile(int socket, Package *package, FILE *fp, pthread_mutex_t mutex)
{
    int size = 0;//用于存储每次读取的字节数
    pthread_mutex_lock(&mutex); // 加锁
    do
    {
        // 先清空，防止旧数据
        memset(package->file, 0, MAX_FILE_SIZE);
        // 一次读取MAX_FILE_SIZE-1字节，为\0留位置
        size = fread(package->file, 1, MAX_FILE_SIZE - 1, fp);
        if (size < 0)
        {
            perror("readFile:读取文件失败");
            package->errorCode = errno;
            pthread_mutex_unlock(&mutex);
            return false;
        }
        // 发送数据
        if (!sendPackage(socket, package))
        {
            perror("readFile:发送文件数据失败");
            pthread_mutex_unlock(&mutex);
            return false;
        }
    } while (size == MAX_FILE_SIZE - 1); // 未读满，继续读取
    pthread_mutex_unlock(&mutex); // 解锁
    fclose(fp);
    return true;
}


/*
 * 功能：读取包目录下所有文件
 * 参数：
 *      sock：通信套接字
 *      package：接收的数据包
 * 返回值：
 *      成功：true
 *      失败：false
 */
bool readDir(int socket, Package *package)
{
    // 添加路径日志
    cout << "尝试打开目录: " << package->path << endl;
    
    // 如果路径为空，使用当前目录
    if (strlen(package->path) == 0)
    {
        if (getcwd(package->path, MAX_FILE_PATH_SIZE) == NULL)
        {
            perror("无法获取当前工作目录");
            package->errorCode = errno;
            return false;
        }
    }

    DIR *dir = opendir(package->path);//打开目录
    if (dir == NULL)
    {
        perror("readDir:打开目录失败");
        package->errorCode = errno;
        return false;
    }
    struct dirent *entry; //dirent* 结构体用于存储目录项信息
    while ((entry = readdir(dir)) != NULL)//循环读取目录项
    {
        if (entry->d_type == DT_REG) // 如果是普通文件
        {
            //cout  << "readDir:正在读取文件" << entry->d_name << "..." << endl;
            // 填充文件名到数据包
            if (package != NULL) // 确保 package 有效
            {
                strncpy(package->name, entry->d_name, MAX_FILE_NAME_SIZE - 1);
                package->name[MAX_FILE_NAME_SIZE - 1] = '\0'; // 显式终止字符串
                // 通过socket发送数据包
                if (!sendPackage(socket, package))//读取到一个文件就发送一个数据包
                {
                    closedir(dir);
                    return false;
                }
            }
            else
            continue;// 
        }
        else if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 
                && strcmp(entry->d_name, "..") != 0)
        {
            strncpy(package->name, entry->d_name, MAX_FILE_NAME_SIZE - 1);
            package->name[MAX_FILE_NAME_SIZE - 1] = '\0';
            package->errorCode = 0;
            if (!sendPackage(socket, package))//读取到一个文件就发送一个数据包
            {
                closedir(dir);
                return false;
            }
        }
    }
    // 发送结束标志
    package->errorCode = 1;
    if (sendPackage(socket, package))
    cout  << "已发送文件列表" << endl;

    closedir(dir);


    return true;
}


/*
 * 功能：生成唯一的文件名
 * 参数：
 *       filePath：文件路径
 * 返回值：
 *       如果文件不存在，直接返回文件名（包括完整路径）
 *       如果文件已存在，生成唯一的文件名（包括完整路径），并返回
 *
 */
std::string generateUniqueFilename(const std::string& filePath)
{
    if (!fs::exists(filePath)) return filePath;
    
    std::string baseName = filePath;
    std::string extension = "";
    
    size_t dotPos = filePath.rfind('.');
    size_t slashPos = filePath.rfind('/');
    if (dotPos != std::string::npos && dotPos > slashPos)
    {
        baseName = filePath.substr(0, dotPos);
        extension = filePath.substr(dotPos);
    }
    
    int count = 1;
    std::string newFilePath;
    do
    {
        newFilePath = baseName + "(" + std::to_string(count++) + ")" + extension;
    } while (fs::exists(newFilePath));
    
    return newFilePath;
}