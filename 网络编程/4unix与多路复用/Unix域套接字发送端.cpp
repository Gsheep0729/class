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

    // 连接服务端
    struct sockaddr_un addr;
    addr.sun_family   = AF_UNIX;
    strcpy(addr.sun_path,ADDRESS_PATH);
    int ret = connect(sockid,(struct sockaddr*)&addr,sizeof(addr));
    std::cout << ret << std::endl;
    if(ret == -1)
    {
        perror("连接失败");
        return -2;
    }
    std::cout << "套接字连接完成!" << std::endl;

    while(1)
    {
        char buffer[2048]={0};
        std::cout  << "请输入:";
        std::cin >> buffer;
        if(send(sockid,buffer,strlen(buffer),0) == -1)break;
        if(buffer == std::string("exit"))break;
    }
    std::cout << "连接关闭!" << std::endl;
    close(sockid);
    return 0;
}