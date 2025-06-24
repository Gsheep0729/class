#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

/**
 * 打印文件权限
 * 根据文件的模式位，输出文件类型和权限信息
 * mode 文件的模式位
 */
void print_perms(mode_t mode) {
    char type;
    // 判断并设置文件类型
    if (S_ISREG(mode)) type = '-';
    else if (S_ISDIR(mode)) type = 'd';
    else if (S_ISCHR(mode)) type = 'c';
    else if (S_ISBLK(mode)) type = 'b';
    else if (S_ISFIFO(mode)) type = 'p';
    else if (S_ISLNK(mode)) type = 'l';
    else if (S_ISSOCK(mode)) type = 's';
    else type = '?';

    // 初始化权限字符串数组
    char perms[10];
    perms[0] = (mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (mode & S_IWUSR) ? 'w' : '-';
    perms[2] = (mode & S_IXUSR) ? 'x' : '-';
    perms[3] = (mode & S_IRGRP) ? 'r' : '-';
    perms[4] = (mode & S_IWGRP) ? 'w' : '-';
    perms[5] = (mode & S_IXGRP) ? 'x' : '-';
    perms[6] = (mode & S_IROTH) ? 'r' : '-';
    perms[7] = (mode & S_IWOTH) ? 'w' : '-';
    perms[8] = (mode & S_IXOTH) ? 'x' : '-';
    perms[9] = '\0';

    // 处理特殊权限位
    if (mode & S_ISUID) perms[2] = (perms[2] == 'x') ? 's' : 'S';
    if (mode & S_ISGID) perms[5] = (perms[5] == 'x') ? 's' : 'S';
    if (mode & S_ISVTX) perms[8] = (perms[8] == 'x') ? 't' : 'T';

    // 输出文件类型和权限信息
    printf("%c%s ", type, perms);
}

/**
 * 主函数
 * 接受命令行参数，获取并打印文件信息
 * argc 参数个数
 * argv 参数指针数组
 * 程序退出状态
 */
int main(int argc, char *argv[]) {
    // 检查命令行参数个数
    if (argc != 2) {
        fprintf(stderr, "using like :%s <file>\n", argv[0]);
        return 1;
    }

    // 获取文件信息
    struct stat sb;
    if (stat(argv[1], &sb) == -1) {
        perror("stat");
        return 1;
    }

    printf("作用:权限   硬链接数 用户组ID 文件大小    修改时间 文件名\n");
    // 格式化输出
    print_perms(sb.st_mode);
    printf("%5lu ", sb.st_nlink);
    printf("%5u %5u ", sb.st_uid, sb.st_gid);
    printf("%10lld ", (long long)sb.st_size);

    // 格式化修改时间
    char mtime[20];
    strftime(mtime, 20, "%Y-%m-%d %H:%M", localtime(&sb.st_mtime));
    printf("%s %s\n", mtime, argv[1]);

    return 0;
}