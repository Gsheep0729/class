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
    struct sockaddr_in multicast_addr_inet;
    multicast_addr_inet.sin_family   = AF_INET;
    multicast_addr_inet.sin_port     = htons(9988);
    multicast_addr_inet.sin_addr.s_addr=inet_addr("239.0.0.10");

    while(1)
    {
        char buffer[2048]={0};
        std::cout << "Please Input:";
        std::cin >> buffer;
        sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&multicast_addr_inet,sizeof(multicast_addr_inet));
        if(buffer == std::string("exit"))break;
    }
    // 退出多播组
    setsockopt(sock,IPPROTO_IP,IP_DROP_MEMBERSHIP,&multicast_addr,sizeof(multicast_addr));
    close(sock);
    return 0;
}