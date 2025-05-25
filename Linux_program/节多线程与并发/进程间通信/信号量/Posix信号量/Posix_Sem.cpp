#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

using namespace std;

int main()
{
    // 删除已存在的信号量
    if (sem_unlink("/tmp") == -1)
    {
           perror("sem_unlink");
        exit(EXIT_FAILURE);
    }
    // 打开信号量
    sem_t *sem = sem_open("/tmp", O_CREAT | O_EXCL , 0666, 0);
    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // 信号量减1
    int i = 1;
    while (i <= 20)
    {
        sem_wait(sem);
        int value = 0;
        sem_getvalue(sem, &value);
        printf("Process B: Waiting semaphore %d\n", value);
        i++;
    }

    // 关闭信号量
    sem_close(sem);

    // 删除信号量
    sem_unlink("/tmp");

    return 0;
}