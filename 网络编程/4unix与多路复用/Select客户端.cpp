#include <iostream>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

int main()
{
    int client = socket(AF_INET,SOCK_STREAM,0);
    if(client == -1)return -1;
    std::cout << "套接字创建成功" << std::endl;

    struct sockaddr_in server;
    server.sin_family        = AF_INET;
    server.sin_port          = htons(9988);
    server.sin_addr.s_addr   = inet_addr("192.168.126.129");
    if(connect(client,(struct sockaddr*)&server,sizeof(server)) == -1)
    {
        perror("连接失败");
        return -1;
    }

    while(1)
    {
        char buffer[2048]={0};
        std::cout << "请输入:";
        std::cin >> buffer;
        if(send(client,buffer,strlen(buffer),0) <= 0)break;
        if(buffer == std::string("exit"))break;
    }
    std::cout << "关闭连接" << std::endl;
    close(client);
    return 0;
}