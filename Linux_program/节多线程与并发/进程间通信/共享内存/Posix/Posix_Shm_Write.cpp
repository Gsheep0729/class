#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/my_shared_memory"
#define SHM_SIZE 4096

int main()
{
    // 创建或打开共享内存对象
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // 设置共享内存对象的大小
    if (ftruncate(shm_fd, SHM_SIZE) == -1)
    {
        perror("ftruncate");
        close(shm_fd);
        return 1;
    }

    // 将共享内存对象映射到进程的地址空间
    void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
        perror("mmap");
        close(shm_fd);
        exit(EXIT_FAILURE);
    }

    // 在共享内存中写入数据
    const char *message = "Hello from process 1!";
    strcpy((char *)shm_ptr, message);

    // 暂时先不断开,验证是否可以多个进程同时操作共享内存
    getchar();

    // 取消映射
    if (munmap(shm_ptr, SHM_SIZE) == -1)
    {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // 关闭文件描述符
    close(shm_fd);
    return 0;
}