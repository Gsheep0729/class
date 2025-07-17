#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

int main()
{   
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock == -1)
    {
        perror("创建错误");
        return -1;
    }

    // 加入多播组
    struct ip_mreq multicast_addr;
    multicast_addr.imr_interface.s_addr = INADDR_ANY; // 任意网卡
    multicast_addr.imr_multiaddr.s_addr = inet_addr("239.0.0.10"); // 多播组地址

    if(setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&multicast_addr,sizeof(multicast_addr)) == -1)
    {
        perror("加入多播组失败");
        close(sock);
        return -1;
    }


    // 配置多播地址
    struct sockaddr_in local;
    local.sin_family   = AF_INET;
    local.sin_port     = htons(9988);
    local.sin_addr.s_addr=INADDR_ANY;
    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) == -1)
    {
        perror("绑定失败");
        // 退出多播组
        setsockopt(sock,IPPROTO_IP,IP_DROP_MEMBERSHIP,&multicast_addr,sizeof(multicast_addr));
        close(sock);
        return -1;
    }

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
    // 退出多播组
    setsockopt(sock,IPPROTO_IP,IP_DROP_MEMBERSHIP,&multicast_addr,sizeof(multicast_addr));
    close(sock);
    return 0;
}