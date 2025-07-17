#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    key_t key = ftok(".", 222);       // 生成键值
    int shmid = shmget(key, 0, 0666); // 获取共享内存
    if (shmid == -1)
    {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    char *shm_addr = (char *)shmat(shmid, NULL, 0); // 连接共享内存
    if (shm_addr == (char *)-1)
    {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    // 使用共享内存...
    // 从共享内存段获取数据,将数据输出到显示器
    printf("%s\n", shm_addr);

    // 暂时先不断开,验证是否可以多个进程同时操作共享内存
    getchar();

    // 断开共享内存连接
    if (shmdt(shm_addr) == -1)
    { // 分离共享内存
        perror("shmdt failed");
        exit(EXIT_FAILURE);
    }

    // 如果需要，可以删除共享内存（注意：这通常在其他进程不再需要访问该共享内存时进行）
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl(IPC_RMID) failed");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory segment deleted successfully.\n");
}