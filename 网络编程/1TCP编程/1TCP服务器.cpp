/*
总结：套接字就是一个文件描述符，指向一个网络连接（通过ip地址和端口将两台主机连接），可以进行读写操作
1.创建套接字 -> 初始化地址和端口 -> 绑定端口 -> 监听端口 -> 等待客户端连接
2.接受客户端连接 -> 向客户端发送消息 -> 进入循环接收客户端消息
3.判断是否收到退出信号（"T"） -> 如果是退出信号，跳出循环并关闭套接字
*/
#include <iostream>     // 标准输入输出流（std::cout）
#include <cstring>      // 字符串处理函数（memset, strlen）
#include <unistd.h>     // POSIX系统接口（close, read）
#include <arpa/inet.h>  // 网络转换工具（htons, inet_pton）
#include <sys/socket.h> // 套接字接口（socket, bind, listen, accept, send）

#define PORT 8081
#define BUFFER_SIZE 1024

int main()
{
    int server_fd;// 服务器套接字文件描述符

    /*
    int socket(int domain, int type, int protocol);
参数：
	domain:代表通信协议族
			AF_INET---IPv4的协议
			AF_INET6--IPv6的协议
	type:代表创建什么类型的套接字
			SOCK_STREAM：流式套接字(TCP)
			SOCK_DGRAM：数据报套接字(UDP)
	protocol:具体的协议
			0代表默认协议
返回值：
	返回该套接字的文件描述符(句柄)
    */
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("创建套接字失败");
        exit(EXIT_FAILURE);
    }
    /*
        struct sockaddr_in
        {
            sa_family_t     sin_family; // 地址族，通常是AF_INET
            in_port_t       sin_port; // 16-bit端口号，需要使用htons()转换为网络字节序
            struct in_addr  sin_addr; // 32-bit IPv4地址
            char            sin_zero[8]; // 填充字节，为保持与struct sockaddr一致
        };

    */
    struct sockaddr_in address;
    // 初始化地址和端口
    address.sin_family = AF_INET;// 设置为AF_INET，表示IPv4协议
    address.sin_addr.s_addr = htonl(INADDR_ANY); // 设置为INADDR_ANY，允许监听所有网络接口（htonl函数将32位整数从主机字节序转换为网络字节序）
    address.sin_port = htons(PORT);// 设置为htons(PORT)，将端口号转换为网络字节序

    /*
bind(绑定端口号)：
    int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
参数：
	sockfd：socket接口的返回值，既创建套接字的描述符
	addr:类型为struct sockaddr,该结构体下边有详细说明，参数代表地址
	addrlen:地址信息长度

sockaddr结构体：
    struct sockaddr {
     sa_family_t sa_family;
     char  sa_data[14]; 地址信息
    }
    */
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("绑定端口失败");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    std::cout << "绑定端口成功：" << PORT << std::endl;

    // 监听来自文件描述符server_fd的套接字描述符,并且设置相应套接字排队的最大连接数
    if (listen(server_fd, 3) < 0)
    {
        perror("监听失败");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    std::cout << "监听开始..." << PORT << std::endl;

    std::cout << "服务器正在等待客户端连接..." << PORT << std::endl;

    socklen_t addrlen = sizeof(address);
    int new_socket;

    // 在内核三次握手完成后，建立连接，则进入accept函数进行连接
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0)
    {
        //  错误处理
        perror("连接失败");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    /*此时连接成功后，accept()会创造一个新的socket用于连接客户，原来的socket仍然在等待客户连接，
    好比你吃饭先跟前台定好位置，由服务员来接管后续的服务，前台会继续接客*/

    std::cout << "羔羊客户端连接成功！\n";

    const char *hello = "你好呀～～小王!";
    // 发送消息给客户端
    send(new_socket, hello, strlen(hello), MSG_NOSIGNAL);
    std::cout << "向璨猫客户端发送消息成功!\n";

    char buffer[BUFFER_SIZE] = {0};

    while (1)
    {
        // 接收来自客户端的消息
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        std::cout << "从客户端收到消息： " << buffer << std::endl;

        // 收到T退出
        if (!strcmp(buffer, "T"))
        {
            break;
        }

        memset(buffer, 0, strlen(buffer));
    }

    // 关闭套接字
    close(new_socket);
    close(server_fd);//最后关闭服务器套接字停止连接新用户

    return 0;
}