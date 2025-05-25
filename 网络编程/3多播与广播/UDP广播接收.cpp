#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

int main()
{
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock == -1)
    {
    	perror("Create socket error");
    	return -1;
    }
    
    struct sockaddr_in local;
    local.sin_family   = AF_INET;
    local.sin_port     = htons(9988);
    local.sin_addr.s_addr = INADDR_ANY;
    if(bind(sock,(struct sockaddr*)&local,sizeof(local))==-1)
        return -1;
    
    std::cout << "绑定完成" << std::endl;

    int opt = 1;
    if(-1==setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&opt,sizeof(opt)))
    {
    	perror("Start Broadcast error");
    	close(sock);
    	return -1;
    }// 开启广播通信，允许接收广播消息

    while(1)
    {
        std::cout << "接收用户的数据..." << std::endl;
        char buffer[2048]={0};
        struct sockaddr_in remote;
        socklen_t len = sizeof(remote);
        int size = recvfrom(sock,buffer,2047,0,(struct sockaddr*)&remote,&len);
        
        std::cout << size << std::endl;

        if(buffer == std::string("exit"))
            std::cout << inet_ntoa(remote.sin_addr) <<":退出了!"<<std::endl;
        else
        std::cout << inet_ntoa(remote.sin_addr) <<":"<< buffer <<std::endl;
    }

    close(sock);
    return 0;
}
