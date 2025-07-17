#include <iostream>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

bool isReadable(int fd)
{
    // 创建一个监听请求的结构体数据
    struct pollfd read_poll_fd;
    read_poll_fd.fd = fd; // 文件描述
    read_poll_fd.events = POLLIN; // 读就绪

    // 进行监听
    if(poll(&read_poll_fd,1,3000)>0)
    {
        if(read_poll_fd.revents & POLLIN) // 判断是否读就绪
            return true;
    }
    return false;
}

int main()
{
    int server = socket(AF_INET,SOCK_STREAM,0);
    if(server == -1)return -1;
    std::cout << "套接字创建成功" << std::endl;

    struct sockaddr_in local;
    local.sin_family        = AF_INET;
    local.sin_port          = htons(9988);
    local.sin_addr.s_addr   = inet_addr("192.168.126.129");
    if(bind(server,(struct sockaddr*)&local,sizeof(local)) == -1)
    {
        perror("绑定失败");
        return -1;
    }
    std::cout << "地址绑定完成" << std::endl;

    if(listen(server,10) == -1)return -1;
    std::cout << "监听完毕!" << std::endl;

    int client = -1;
    std::cout << "等待客户端连接请求..." << std::endl;
    while(1)
        if((client=accept(server,nullptr,nullptr)) == -1)continue;
        else break;
    std::cout << "新客户端连接" << std::endl;


    while(1)
    {
        char buffer[2048]={0};
        // if(recv(client,buffer,2047,0) <= 0)break; // 阻塞
        // // 有消息在缓冲区：读就绪
        // // 无消息在缓冲区：读未就绪

        // 先判断是否有数据可以接收
        if(isReadable(client))
        {
            if(recv(client,buffer,2047,0)<=0)break;
            std::cout << "客户端消息:" << buffer << std::endl;
        }
        else // 没有数据的时候就做其他事情
            std::cout << "\r客户端无消息:" << buffer << std::endl;
    }
    std::cout << "关闭连接" << std::endl;

    close(client);
    close(server);
    return 0;
}