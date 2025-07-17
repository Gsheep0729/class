/*流程：判断选项->解析遍历目录->根据选项完成各项目录的信息检索*/
#include <stdio.h> // printf, fprintf
#include <stdlib.h>  // exit, EXIT_FAILURE
#include <dirent.h>  // DIR, struct dirent, opendir, readdir, closedir
#include <sys/stat.h> // stat, struct stat, S_IRUSR等权限宏
//#include <unistd.h>  // (本代码中未直接使用相关函数)
#include <string.h>  // strerror, strlen, snprintf
#include <time.h>    // time_t, ctime
#include <getopt.h>  // getopt, optind
#include <errno.h>   // errno, strerror
/*这是一个用来显示目录内容，包括文件名、文件类型、权限、大小、修改时间等的结构体
struct dirent {
    ino_t          d_ino;       // inode 编号
    char           d_name[256]; // 文件名
    // 其他系统可能包含：
    // d_type：文件类型（如 DT_REG 常规文件、DT_DIR 目录）
};
*/

// 全局选项标志
int a_flag = 0;    // 显示隐藏文件
int i_flag = 0;    // 显示inode
int l_flag = 0;    // 显示详细信息

// 打印文件权限
void print_mode(mode_t mode)
{
    printf("%c%c%c%c%c%c%c%c%c",
        (mode & S_IRUSR) ? 'r' : '-', // [用户] 读权限 (Owner Read)
        (mode & S_IWUSR) ? 'w' : '-', // [用户] 写权限 (Owner Write)
        (mode & S_IXUSR) ? 'x' : '-', // [用户] 执行权限 (Owner Execute)
        (mode & S_IRGRP) ? 'r' : '-', // [组] 读权限 (Group Read)
        (mode & S_IWGRP) ? 'w' : '-', // [组] 写权限 (Group Write)
        (mode & S_IXGRP) ? 'x' : '-', // [组] 执行权限 (Group Execute)
        (mode & S_IROTH) ? 'r' : '-', // [其他] 读权限 (Others Read)
        (mode & S_IWOTH) ? 'w' : '-', // [其他] 写权限 (Others Write)
        (mode & S_IXOTH) ? 'x' : '-'); // [其他] 执行权限 (Others Execute)
}

// 格式化时间戳
char* format_time(time_t t)
{
    char* str = ctime(&t);
    str[strlen(str)-1] = '\0'; // 去掉换行符
    return str;
}

// 处理单个文件条目
void process_entry(struct dirent *entry, const char *dir_path)
{
    if (!a_flag && entry->d_name[0] == '.')
    {
        return; // 跳过隐藏文件（除非有-a选项）
    }

    char full_path[1024];// 存储文件路径
    snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);// 拼接文件路径

    struct stat st;//用于存储文件或目录的元数据信息（如权限、大小、时间戳等）
    /*选项是什么就打印什么
    选项：
    选项	作用	示例输出（部分）
    -a	显示所有文件（含隐藏文件）	. .. .gitignore main.c
    -i	显示 inode 编号	23456 main.c
    -l	显示长格式信息	-rw-r--r-- 1 user staff 512
    -al	组合选项：显示所有文件长格式	-rw-r--r-- 1 user staff .gitignore
    -li	组合选项：显示 inode 和长格式	23456 -rw-r--r-- 1 user staff
    */
    // 如果启用了-l选项，则获取文件详细信息
    // 使用stat函数获取文件状态，存储到st结构体中
    if (l_flag && stat(full_path, &st) != 0)
    {
        perror("stat");
        return;
    }

    // 如果启用了-i选项，打印inode编号
    if (i_flag)
    {
        printf("%8lu ", (unsigned long)st.st_ino);
    }
    
    // 如果启用了-l选项，以长格式输出文件信息
    if (l_flag)
    {
        print_mode(st.st_mode);// 打印文件权限（如-rw-r--r--）
        printf(" %2lu %6d %6d %8ld %s %s\n",
           (unsigned long)st.st_nlink,  // 硬链接数
           st.st_uid,                   // 用户ID
           st.st_gid,                   // 组ID
           (long)st.st_size,            // 文件大小
           format_time(st.st_mtime),    // 格式化的修改时间
           entry->d_name);              // 文件名
    }
    else
    {
        //未启用-l选项时，以简单格式输出文件名
        printf("%s  ", entry->d_name);
    }
}

// 遍历目录并打印内容
void list_dir(const char *path)
{
    DIR *dir = opendir(path);//打开指定路径的目录
    if (!dir)
    {
        fprintf(stderr, "my_ls: 无法打开目录 '%s': %s\n", path, strerror(errno));
        return;
    }
    /*
    #include <dirent.h>
    struct dirent *readdir(DIR *dirp);
    参数：dirp 是目录流指针，由 opendir() 函数返回。
返回值：
成功：返回指向下一个目录项（struct dirent）的指针。
结束：遍历完所有条目后返回 NULL，并设置 errno 为 0。
错误：发生错误时返回 NULL，并设置 errno 为非零值（如 EBADF 表示无效的目录流）。
    */
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)// 遍历目录项储存在entry中
    {
        process_entry(entry, path);//处理目录项并打印
    }

    if (!l_flag)printf("\n");// 在非l选项下，打印换行符
    closedir(dir);
}

int main(int argc, char *argv[])
{
    int opt;// 选项
    const char *target_dir = "."; // 默认当前目录

    // 依次读取选项
    while ((opt = getopt(argc, argv, "ail")) != -1)
    {
        switch (opt)
        {
            case 'a': a_flag = 1; break;
            case 'i': i_flag = 1; break;
            case 'l': l_flag = 1; break;
            default:
                fprintf(stderr, "用法: %s [-a] [-i] [-l] [目录]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    //如果跟有路径参数，则使用
    if (optind < argc)
    {
        target_dir = argv[optind];
    }

    list_dir(target_dir);
    return 0;
}