#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

using namespace std;

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main()
{
    key_t key = ftok(".", 255); // 生成唯一键值

    // 尝试创建一个包含一个信号量的集合
    int semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1)
    {
        perror("semget error");
        exit(1);
    }

    // 初始化信号量的值
    union semun sem_union;
    sem_union.val = 1; // 设置要设置的信号量值
    if (semctl(semid, 0, SETVAL, sem_union) == -1)//设置信号量集合中编号为 0 的信号量的值为 sem_union.val 中的值
    {
        perror("semctl error");
        semctl(semid, 0, IPC_RMID, 0); // 清理资源
        return -1;
    }

    //创建子进程
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // 子进程
        int i = 0;
        while (i < 10)
        {
            struct sembuf sops = {0};
            sops.sem_num = 0;        // 指定第一个信号量
            sops.sem_op = -1;        // 请求资源（P操作）
            sops.sem_flg = SEM_UNDO; // 这里不使用任何特殊标志

            // 请求资源（P操作） 消耗1个资源
            if (semop(semid, &sops, 1) == -1)
            {
                perror("semop (wait)");
                exit(EXIT_FAILURE);
            }

            printf("a\n");
            printf("a\n");
            printf("a\n");
            printf("a\n");
            printf("a\n");

            // 释放资源（V操作）
            sops.sem_op = 1;
            if (semop(semid, &sops, 1) == -1)
            {
                perror("semop (wait)");
                exit(EXIT_FAILURE);
            }
            i++;
        }

        exit(EXIT_SUCCESS);
    }
    else
    {
        // 父进程
        int i = 0;
        while (i < 8)
        {
            struct sembuf sops = {0};
            sops.sem_num = 0;        // 指定第一个信号量
            sops.sem_op = -1;        // 请求资源（P操作）
            sops.sem_flg = SEM_UNDO; // 这里不使用任何特殊标志

            // 请求资源（P操作） 消耗1个资源
            if (semop(semid, &sops, 1) == -1)
            {
                perror("semop (wait)");
                exit(EXIT_FAILURE);
            }

            printf("bbbbbbbbbbbbbbbbbbbb\n");
            printf("bbbbbbbbbbbbbbbbbbb\n");
            printf("bbbbbbbbbbbbbbbbbbb\n");
            printf("bbbbbbbbbbbbbbbbbbb\n");
            printf("bbbbbbbbbbbbbbbbbbb\n");

            // 释放资源（V操作）
            sops.sem_op = 1;
            if (semop(semid, &sops, 1) == -1)
            {
                perror("semop (wait)");
                exit(EXIT_FAILURE);
            }
            i++;
        }

        // 等待子进程完成
        wait(NULL);

        // 清理信号量集（可选）
        if (semctl(semid, 0, IPC_RMID, 0) == -1)
        {
            perror("semctl(IPC_RMID)");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}