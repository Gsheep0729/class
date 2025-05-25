#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8081
#define BUFFER_SIZE 1024

// 自定义协议结构体
typedef struct
{
    int32_t message_type;      // 消息类型
    int32_t message_length;    // 消息内容长度（不包括message_type和message_length）
    char message[BUFFER_SIZE]; // 消息内容
} MyProtocol;

// 反序列化函数 protocol出参 提取到的网络字节序里的内容   buffer：网络字节序
void deserialize(MyProtocol *protocol, const char *buffer)
{
    const int32_t *net_message_type = (const int32_t *)buffer;
    const int32_t *net_message_length = (const int32_t *)(buffer + sizeof(int32_t));

    // 反序列化
    protocol->message_type = ntohl(*net_message_type);
    protocol->message_length = ntohl(*net_message_length);

    // 提取消息
    memcpy(protocol->message, buffer + 2 * sizeof(int32_t), protocol->message_length);

    // 确保字符串以\0结尾
    protocol->message[protocol->message_length] = '\0';
}

// 接收结构体
void receive_struct(int sock, MyProtocol *protocol)
{
    char buffer[sizeof(protocol->message_type) + sizeof(protocol->message_length) + BUFFER_SIZE];
    // 接受结构体
    ssize_t bytes_received = recv(sock, buffer, sizeof(buffer), 0);
    if (bytes_received < 0)
    {
        perror("接收数据失败");
        exit(EXIT_FAILURE);
    }

    printf("bytes_received = %lu\n", bytes_received);

    // 计算实际接收到的消息长度（不包括message_type和message_length本身的大小）
    int32_t net_message_length;
    memcpy(&net_message_length, buffer + sizeof(int32_t), sizeof(int32_t));

    // 反序列化长度
    net_message_length = ntohl(net_message_length);
    //    int32_t message_type;      // 消息类型
    // int32_t message_length;    // 消息内容长度（不包括message_type和message_length）
    // char message[BUFFER_SIZE]; // 消息内容
    if (bytes_received < sizeof(int32_t) * 2 + net_message_length)
    {
        fprintf(stderr, "接收到的数据不完整\n");
        exit(EXIT_FAILURE);
    }

    // 反序列化数据
    deserialize(protocol, buffer);
    // 确保字符串以\0结尾（虽然deserialize已经处理，但再次确保）
    protocol->message[protocol->message_length] = '\0';
}

int main()
{
    int server_fd;
    // 创建IPV4套接字文件描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("创建套接字失败");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    // 初始化地址和端口
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // 监听所有的IPV4
    address.sin_port = htons(PORT);

    // 绑定套接字到端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("绑定端口失败");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(server_fd, 3) < 0)
    {
        perror("监听失败");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "服务器正在等待客户端连接..." << PORT << std::endl;

    int addrlen = sizeof(address);
    int new_socket;

    // 接受连接
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("连接失败");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "客户端连接成功！\n";

    // 示例：接收结构体
    MyProtocol recv_protocol;
    receive_struct(new_socket, &recv_protocol);
    printf("收到客户端消息: %s\n", recv_protocol.message);

    // // 等一段时间关闭
    getchar();

    // 关闭套接字
    close(new_socket);
    close(server_fd);

    return 0;
}