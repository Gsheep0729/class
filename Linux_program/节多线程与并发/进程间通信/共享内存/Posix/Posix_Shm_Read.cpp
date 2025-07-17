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
    // 打开已存在的共享内存对象
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // 将共享内存对象映射到进程的地址空间
    void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
        perror("mmap");
        close(shm_fd);
        exit(EXIT_FAILURE);
    }

    // 从共享内存中读取数据
    char buffer[SHM_SIZE + 1] = {0}; // +1为\0留空间
    strcpy(buffer, (char *)shm_ptr);
    buffer[SHM_SIZE] = '\0'; // 确保以\0结尾

    // 打印读取到的数据
    printf("Data read from shared memory: %s\n", buffer);

    // 取消映射
    if (munmap(shm_ptr, SHM_SIZE) == -1)
    {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // 删除共享内存对象名称
    if (shm_unlink(SHM_NAME) == -1)
    {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    // 关闭文件描述符
    close(shm_fd);

    return 0;
}