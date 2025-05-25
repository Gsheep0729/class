#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

int main()
{
    int sock = socket(AF_INET,SOCK_STREAM,0);

    const char opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));// 地址就被复用了

    close(sock);
    return 0;
}