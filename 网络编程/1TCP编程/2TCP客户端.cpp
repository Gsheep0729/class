/*
1.创建套接字 -> 初始化服务器地址 -> 将服务器IP地址转换为二进制形式 -> 连接到服务器
2.接收服务器的欢迎消息 -> 进入循环发送消息给服务器
3.判断是否发送退出信号（"T"） -> 如果是退出信号，跳出循环并关闭套接字
*/
#include <iostream>       // 标准输入输出（std::cout, std::endl）
#include <cstring>        // 字符串操作（memset, strlen）
#include <unistd.h>       // 系统调用（close）
#include <arpa/inet.h>    // 网络转换（htons, inet_pton）
#include <sys/socket.h>   // 套接字接口（socket, sendto, recvfrom）

#define SERVER_IP "127.0.0.1" // 服务器的IP地址，这里假设在同一台机器上
#define PORT 8081
#define BUFFER_SIZE 1024

int main()
{
    int sock = 0;

    /*
        int socket(int domain, int type, int protocol);
        参数：
            domain: 通信协议族，AF_INET表示IPv4
            type: 套接字类型，SOCK_STREAM表示TCP
            protocol: 协议类型，0表示默认协议
        返回值：
            成功返回套接字文件描述符，失败返回-1
    */
    // 创建套接字文件描述符
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("创建套接字失败");
        return -1;
    }

    struct sockaddr_in serv_addr;

    /*
        struct sockaddr_in
        {
            sa_family_t     sin_family; // 地址族，通常是AF_INET
            in_port_t       sin_port; // 16-bit端口号，需要使用htons()转换为网络字节序
            struct in_addr  sin_addr; // 32-bit IPv4地址
            char            sin_zero[8]; // 填充字节，为保持与struct sockaddr一致
        };
    */

    serv_addr.sin_family = AF_INET; // 设置为AF_INET，表示IPv4协议
    serv_addr.sin_port = htons(PORT); // 设置为htons(PORT)，将端口号转换为网络字节序

    /*
        inet_pton函数将IP地址从文本形式转换为二进制形式
        int inet_pton(int af, const char * restrict src, void * restrict dst);
        参数：
            af: 地址族，如AF_INET
            src: 文本形式的IP地址
            dst: 二进制形式的IP地址存储位置
        返回值：
            成功返回1，无效的输入返回0，错误返回-1
    */
    // 将地址从文本转换为二进制形式
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0)
    {
        perror("ip地址转化失败");
        return -1;
    }

    /*
        int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
        参数：
            sockfd: 套接字文件描述符
            addr: 服务器地址
            addrlen: 服务器地址长度
        返回值：
            成功返回0，失败返回-1
    */
    // 发送连接请求到服务器（从这里触发TCP由内核来进行三次握手过程）
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("连接到服务器失败");
        return -1;
    }

    std::cout << "客户端成功连接到服务器" << std::endl;

    char buffer[BUFFER_SIZE] = {0};

    /*
        ssize_t read(int fd, void *buf, size_t count);
        参数：
            fd: 文件描述符
            buf: 读取数据的缓冲区
            count: 最大读取字节数
        返回值：
            成功返回实际读取的字节数，失败返回-1
    */
    // 接收来自服务器的消息
    int valread = read(sock, buffer, BUFFER_SIZE);
    std::cout << "璨猫客户端受到羔羊服务器的消息:" << buffer << std::endl;

    while (1)
    {
        // 发送消息给服务器
        std::cout << "请输入要发送的消息(输入T退出)：" << std::endl;
        scanf("%s", buffer);

        /*
            ssize_t send(int sockfd, const void *buf, size_t len, int flags);
            参数：
                sockfd: 套接字文件描述符
                buf: 发送的数据缓冲区
                len: 发送的数据长度
                flags: 发送标志
            返回值：
                成功返回发送的字节数，失败返回-1
        */
        send(sock, buffer, strlen(buffer), 0);

        // 发送quit退出
        if (!strcmp(buffer, "T"))
        {
            break;
        }
    }

    // 关闭套接字
    close(sock);
    return 0;
}