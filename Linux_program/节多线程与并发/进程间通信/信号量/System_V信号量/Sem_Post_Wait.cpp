#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

using namespace std;

int main()
{
    // 创建信号量
    sem_t *sem = sem_open("/tmp", O_CREAT | O_EXCL, 0666, 0);
    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // 信号量加1
    int i = 1;
    while (i <= 20)
    {
        sleep(1);
        sem_post(sem);
        printf("Process A: Posting semaphore %d\n", i);
        i++;
    }

    // 关闭信号量
    sem_close(sem);

    return 0;
}