#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

int main()
{
    int sock = socket(AF_INET,SOCK_DGRAM,0);

    int size = 128000;
    socklen_t len = sizeof(size);
    setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&size,len);

    getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&size,&len);
    std::cout << size << std::endl;

    close(sock);
    return 0;
}