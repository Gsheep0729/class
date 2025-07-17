#include <iostream>        // 使用: std::cout, std::endl
#include <cstring>         // 使用: memset(), strcmp()
#include <unistd.h>        // 使用: close()
#include <arpa/inet.h>     // 使用: inet_ntoa(), htons(), ntohs()

#define PORT 8888
#define BUFFER_SIZE 1024

int main()
{
    char buffer[BUFFER_SIZE] = {0};

    /*
    创建UDP套接字：
        int socket(int domain, int type, int protocol);
    参数：
        domain: 协议族，AF_INET 表示 IPv4
        type: 套接字类型，SOCK_DGRAM 表示 UDP 数据报
        protocol: 默认协议，设为 0
    返回值：
        成功返回套接字文件描述符，失败返回 -1
    */
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("创建套接字失败");
        return -1;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr)); // 初始化结构体

    /*
    填充服务器地址信息：
        struct sockaddr_in {
            sa_family_t    sin_family; // 地址族（AF_INET）
            in_port_t      sin_port;   // 端口号（需用 htons() 转换字节序）
            struct in_addr sin_addr;   // IP地址（INADDR_ANY 表示监听所有接口）
        };
    */
    serv_addr.sin_family = AF_INET;         // IPv4
    serv_addr.sin_addr.s_addr = INADDR_ANY; // 监听所有网络接口
    serv_addr.sin_port = htons(PORT);       // 端口转换为网络字节序

    /*
    绑定套接字到指定端口：
        int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    参数：
        sockfd: 套接字文件描述符
        addr: 服务器地址结构体指针
        addrlen: 结构体长度
    返回值：
        成功返回 0，失败返回 -1
    */
    if (bind(sockfd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("绑定失败");
        return -1;
    }

    std::cout << "UDP服务器创建成功，等待连接..." << PORT << std::endl;

    struct sockaddr_in cli_addr;    // 存储客户端地址信息
    socklen_t cli_len = sizeof(cli_addr); // 客户端地址结构体长度

    while (true)
    {
        /*
        接收客户端数据：
            ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                             struct sockaddr *src_addr, socklen_t *addrlen);
        参数：
            flags: MSG_WAITALL 表示阻塞直到收到完整数据
            src_addr: 发送方的地址信息
            addrlen: 输入输出参数，传入地址结构体长度
        返回值：
            成功返回接收字节数，失败返回 -1
        */
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, 
                        (struct sockaddr *)&cli_addr, &cli_len);
        buffer[n] = '\0'; // 确保字符串以空字符结尾

        std::cout << "收到消息： " << buffer << " 来自于 " 
                  << inet_ntoa(cli_addr.sin_addr) << ":" 
                  << ntohs(cli_addr.sin_port) << std::endl;

        // 发送响应消息
        const char *response = "消息已收到";
        /*
        发送数据到客户端：
            ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                           const struct sockaddr *dest_addr, socklen_t addrlen);
        参数：
            flags: MSG_CONFIRM 用于链路层确认（可选）
            dest_addr: 目标地址信息
        */
        sendto(sockfd, response, strlen(response), MSG_CONFIRM, 
             (const struct sockaddr *)&cli_addr, cli_len);

        // 收到 "quit" 则退出循环
        if (!strcmp(buffer, "quit"))
        {
            break;
        }
    }

    close(sockfd); // 关闭套接字
    return 0;
}