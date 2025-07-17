/*1.进行文件的复制操作
2.增加一个参数实现部分文件复制，
如参数分别为from，to，50%即为从from文件复制50%的内容到to文件*/
#include <iostream>
using namespace std;
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    char *buffer = new char[BUFFER_SIZE];
    FILE *from, *to;
    int percent = 100;

    if(argc < 3)
    {
        cout << "用法: " << argv[0] << " <源文件> <目标文件> [百分比]" << endl;
        return -1;
    }
    else if(argc == 3)//2个文件参数，默认100%复制,使用行I/O
    {
        from = fopen(argv[1], "rb");
        to = fopen(argv[2], "wb");
        if(from == NULL || to == NULL)
        {
            cout << "文件打开失败" << endl;
            return -1;
        }
        //检查文件指针from是否到达文件末尾，字符I/O
        // while(!feof(from))
        // {
        //     char c = fgetc(from);//缓冲区
        //     fputc(c, to);
        // }
        /*
        ssize_t getdelim(char **lineptr, size_t *n, int delimiter, FILE *stream);
        char **lineptr：指向一个指针，该指针将指向存储读取行的内存。
        size_t *n：指向一个变量，该变量存储当前分配给 *lineptr 的内存大小。
        int delimiter：指定行的分隔符（通常是换行符 \n）。
        FILE *stream：要读取的文件流。
        */
        size_t len = BUFFER_SIZE;//存储当前分配给 *buffer 的内存大小。
        ssize_t read;//读取的字节数。
        //fgets
        while(!feof(from))//行I/O
        {
            fgets(buffer, BUFFER_SIZE, from);//读取一行，并保存到 buffer 中。
            fputs(buffer, to);
        }

    //     //getdelim
    //     while(/* read = */getdelim(&buffer, &len, '\n', from) != -1)//行I/O
    //     {
    //         //fgets(buffer, BUFFER_SIZE, from);
    //         fputs(buffer, to);
    //     } 
    }
    else if(argc == 4)//3个文件参数，复制指定百分比，使用块I/O
    {
        int percent = atoi(argv[3]);
        if(percent > 100 || percent < 0)
        {
            cout << "参数错误,请输入0-100的数字" << endl;
            return -1;
        }
        from = fopen(argv[1], "rb");
        to = fopen(argv[2], "wb");
        if(from == NULL || to == NULL)
        {
            cout << "文件打开失败" << endl;
            return -1;
        }
        //获取文件总字节数来确定需要拷贝的字节数
        fseek(from, 0, SEEK_END);//移动文件指针到文件末尾
        long file_size = ftell(from);//获取文件指针位置
        long copy_size = file_size * percent/100;
        fseek(from, 0, SEEK_SET);//从文件开头开始读写
        while (copy_size > 0)
        {
            fread(buffer, 1, 1, from);//从from读1次，每次1个字节，存储到buffer中
            fwrite(buffer, 1, 1, to);//同理将buffer中的内容写入到to中
            copy_size--;
        }
        
    }
    fclose(from);
    fclose(to);

    return 0;
}