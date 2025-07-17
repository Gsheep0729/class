#include <iostream>        // 使用: std::cout, std::endl
#include <cstring>         // 使用: memset(), strcmp(), strlen()
#include <unistd.h>        // 使用: close()
#include <arpa/inet.h>     // 使用: inet_pton(), htons()

#define SERVER_IP "127.0.0.1" // 服务器IP地址
#define PORT 8888
#define BUFFER_SIZE 1024

int main()
{
    char buffer[BUFFER_SIZE] = {0};

    /*
    创建UDP套接字：
        参数 SOCK_DGRAM 表示 UDP 数据报
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
        sin_port 使用 htons() 转换端口字节序
        sin_addr 通过 inet_pton() 将字符串IP转换为二进制格式
    */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    /*
    转换IP地址：
        int inet_pton(int af, const char *src, void *dst);
        参数：
            af: 地址族（AF_INET）
            src: 字符串格式IP地址
            dst: 存储转换后的二进制地址
    */
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0)
    {
        perror("IP地址转换失败");
        return -1;
    }

    while (1)
    {
        scanf("%s", buffer); // 从标准输入读取消息

        /*
        发送消息到服务器：
            sendto 的 addr 参数指定服务器地址信息
            MSG_CONFIRM 用于链路层确认（可选）
        */
        int n = sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, 
                     (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if (n < 0)
        {
            perror("发送失败");
            return -1;
        }

        // 发送 "quit" 则退出循环
        if (!strcmp(buffer, "quit"))
        {
            break;
        }

        /*
        接收服务器响应：
            此处不需要获取发送方地址（最后一个参数为NULL）
        */
        n = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, NULL, NULL);
        buffer[n] = '\0'; // 确保字符串以空字符结尾
        std::cout << "收到服务器的反馈： " << buffer << std::endl;

        memset(buffer, 0, strlen(buffer)); // 清空缓冲区
    }

    close(sockfd); // 关闭套接字
    return 0;
}