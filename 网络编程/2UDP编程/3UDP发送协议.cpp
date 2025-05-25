#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1" // 服务器的IP地址，这里假设在同一台机器上
#define PORT 8080
#define BUFFER_SIZE 1024

// 自定义协议结构体
typedef struct
{
    int32_t message_type;      // 消息类型
    int32_t message_length;    // 消息内容长度（不包括message_type和message_length）
    char message[BUFFER_SIZE]; // 消息内容
} MyProtocol;

// 序列化函数 protocol入参  buffer出参
void serialize(const MyProtocol *protocol, char *buffer)
{
    int32_t net_message_type = htonl(protocol->message_type);
    int32_t net_message_length = htonl(protocol->message_length);

    memcpy(buffer, &net_message_type, sizeof(net_message_type));
    // 指针后移
    buffer += sizeof(net_message_type);
    memcpy(buffer, &net_message_length, sizeof(net_message_length));
    // 指针后移
    buffer += sizeof(net_message_type);

    memcpy(buffer, protocol->message, protocol->message_length);
}

// 发送结构体
void send_struct(int sock, const MyProtocol *protocol)
{
    char buffer[sizeof(protocol->message_type) + sizeof(protocol->message_length) + protocol->message_length];
    // 序列化
    serialize(protocol, buffer);

    ssize_t bytes_to_send = sizeof(protocol->message_type) + sizeof(protocol->message_length) + protocol->message_length;
    // 发送消息
    ssize_t bytes_sent = send(sock, buffer, bytes_to_send, 0);
    if (bytes_sent != bytes_to_send)
    {
        perror("发送数据失败");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    int sock = 0;
    // 创建套接字文件描述符
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("创建套接字失败");
        return -1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 将地址从文本转换为二进制形式
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0)
    {
        perror("ip地址转化失败");
        return -1;
    }

    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("连接到服务器失败");
        return -1;
    }

    std::cout << "客户端成功连接到服务器" << std::endl;

    // 示例：发送结构体
    MyProtocol send_protocol = {1, sizeof("Hello, World!"), "Hello, World!"};
    send_struct(sock, &send_protocol);

    std::cout << "客户端发送消息成功" << std::endl;

    // // 等一段时间关闭
    // sleep(5);
    getchar();

    // 关闭套接字
    close(sock);

    return 0;
}