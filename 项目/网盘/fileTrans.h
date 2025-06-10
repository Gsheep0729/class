
/* 文件传输相关函数 */
#ifndef __FILETRANS_H__
#define __FILETRANS_H__

#include <iostream>

// 文件路径规模
#define MAX_FILE_PATH_SIZE 128
// 文件名规模
#define MAX_FILE_NAME_SIZE 32
// 文件规模
#define MAX_FILE_SIZE 512

// 命令类型
enum CMD
{
    LS = 1,       // 查看文件列表
    UPLOAD,       // 上传文件
    DOWNLOAD,     // 下载文件
    FATHERDIR,    // 上一级目录
    SONDIR,       // 下一级目录
    QUIT_CLIENT,  // 关闭客户端通信
    QUIT_SERVER   // 关闭服务器
};

// 数据包的结构体
typedef struct
{
    CMD cmd;                     // 命令类型
    int errorCode;               // 命令执行的结果 0表示未完成或失败，1表示完成
    char path[MAX_FILE_PATH_SIZE]; // 服务器工作路径
    char name[MAX_FILE_NAME_SIZE]; // 文件名字
    char file[MAX_FILE_SIZE];     // 文件内容
} Package;

/*
 * 功能：创建服务器
 * 参数：
 *      ipv4：服务器地址
 *      port：端口号
 * 返回值：
 *      成功：返回创建好的服务器套接字
 *      失败：-1
 */
int createServer(const char *ipv4, int port);

/*
 * 功能：创建客户端
 * 参数：
 *      ipv4：服务器地址
 *      port：端口号
 * 返回值：
 *      成功：返回创建好的客户端套接字
 *      失败：-1
 */
int createClient(const char *ipv4, int port);

/*
 * 功能：发送数据包
 * 参数：
 *      sock：通信套接字
 *      package：发送的数据包
 * 返回值：
 *      成功：true
 *      失败：false
 */
bool sendPackage(int sock, Package *package);

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
int recvPackage(int sock, Package *package);

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
FILE *getFp(Package *package, std::string filename, const char *mode);

/*
 * 功能：向文件中写入内容
 * 参数：
 *      sock：通信套接字
 *      package：接收的数据包
 *      fp：文件指针
 *      mutex：锁
 * 返回值：
 *      成功：true
 *      失败：false
 */
bool writeFile(int socket, Package *package, FILE *fp, pthread_mutex_t mutex);

/*
 * 功能：从文件中读取内容
 * 参数：
 *      sock：通信套接字
 *      package：接收的数据包
 *      fp：文件指针
 *      mutex：锁
 * 返回值：
 *      成功：true
 *      失败：false
 */
bool readFile(int socket, Package *package, FILE *fp, pthread_mutex_t mutex);

/*
 * 功能：读取目录下所有文件
 * 参数：
 *      sock：通信套接字
 *      package：接收的数据包
 * 返回值：
 *      成功：true
 *      失败：false
 */
bool readDir(int socket, Package *package);

#endif