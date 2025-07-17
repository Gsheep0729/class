#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>

int main()
{
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock == -1)
    {
    	perror("Create socket error");
    	return -1;
    }
    
    int opt = 1;
    if(-1==setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&opt,sizeof(opt)))
    {
    	perror("Start Broadcast error");
    	close(sock);
    	return -1;
    }// 开启广播通信，允许接收广播消息
    
    struct sockaddr_in broadcast;
    broadcast.sin_family   = AF_INET;
    broadcast.sin_port     = htons(9988);
    broadcast.sin_addr.s_addr = inet_addr("192.168.126.255");

    while(1)
    {
        char buffer[2048]={0};
        std::cout << "Please Input:";
        std::cin >> buffer;
        sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&broadcast,sizeof(broadcast));
        if(buffer == std::string("exit"))break;
    }
    close(sock);
    return 0;
}
