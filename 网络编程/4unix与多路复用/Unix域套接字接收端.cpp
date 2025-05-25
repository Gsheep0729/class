#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/un.h> // uniux
#include <cstring>

#define ADDRESS_PATH "/home/thirteen/unix.socket"

int main()
{
    int sockid = socket(AF_UNIX,SOCK_STREAM,0);
    if(sockid == -1){
        perror("套件字创建错误");
        return -1;
    }
    std::cout << "套接字申请完成!" << std::endl;
    // 绑定地址
    struct sockaddr_un addr;
    addr.sun_family   = AF_UNIX;
    strcpy(addr.sun_path,ADDRESS_PATH);

    if(bind(sockid,(struct sockaddr*)&addr,sizeof(addr)) == -1)
    {
        perror("绑定失败");
        return -2;
    }
    std::cout << "套接字绑定完成!" << std::endl;
    std::cout << "等待客户端连接请求..." << std::endl;

    // 监听
    if(listen(sockid,5) == -1)
    {
        perror("监听失败");
        return -3;
    }

    int sock_client = -1;
    // 等待连接
    while(1)
    {
        sock_client = accept(sockid,nullptr,nullptr);
        if(sock_client == -1)continue;
        break;
    }
    std::cout << "客户端连接完成!" << std::endl;

    while(1)
    {
        char buffer[2048]={0};
        if(recv(sock_client,buffer,2047,0) == -1)break;
        std::cout << "新信息:" << buffer << std::endl;
        if(buffer == std::string("exit"))break;
    }
    std::cout << "连接关闭!" << std::endl;
    close(sock_client);
    close(sockid);
    return 0;
}