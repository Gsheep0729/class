/*假设需要你为图书馆建立一个计算机处理的卡片目录系统。
第一步，你需要建立一个原型，使之能够存储1000本书的如下信息:
1·书名
2·一个最多包含五位作者的名单
3·美国国会图书馆的目录号
4·至少五个主题词
5·出版商
6·出版年
7·该书是否流通
为此图书馆数据库原型设计合适的数据结构，可以存储所有必要的信息。
给出你的定义后，可以按照语句:
libraryDB libdata;
进行声明，且变量1ibdata应该包含1000册书的信息。
要记住，书的实际数量通常少于这个上界。
编写过程searchBySubject，将图书馆数据库和一个主题词作为参数。
如果某本书的主题词中包含该主题词，则searchBySubject应显示
该书的书名、第一作者的姓名，以及国会图书馆目录号码。*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define Parking_fee 5.0//每小时停车费
#define max_car 50//最大停车数，方便计算剩余车位

/* 定义一个结构体，用于存储车辆的信息 */
typedef struct 
{
    char name[10];//车牌号
    int num;//车位号
    time_t now_time;//储存当前时间戳,直接根据时间戳来计算时长，储存的时间再转化
}Car;


Car park[max_car];//定义一个全局结构体数组并初始化，用于存储车辆的信息
int park_num = max_car;//park_num用来记录车位剩余数量

void park_initialize()
{
    for (int i = 0; i < max_car; i++)
    {
        park[i].name[0]  = '\0';//车牌号初始化为空,方便检索l
    }
}


//车位分配,根据顺序来分配
int park_alloc()
{
    for (int i = 0; i < max_car; i++)
    {
        if (park[i].name[0] == '\0')//如果车位为空，则返回车位号
        {
            park_num--;//车位-1
            return i;
        }
    }
    return -1;
}
// 车位释放
void park_free(int num)
{
    if (park[num].name[0] != '\0')//如果车位不为空，则释放车位
    {
        park[num].name[0] = '\0';//将车位号对应的车牌号置为空
        park_num++;//车位数量加1
    }
}



//车辆进入
void car_enter()
{
    Car car;
    int num =park_alloc();
    if(num == -1)
    {
        printf("车位已满，请稍后再试\n");
        return;
    }
    printf("请输入车牌号：");
    scanf("%s", car.name);//记录车牌号
    car.num = num;//记录车位号
    car.now_time = time(NULL);//获取当前时间的时间戳，记录时间
    struct tm *now = localtime(&car.now_time);//将时间戳转换为本地时间
    park[car.num] = car;//将当前车辆信息存入数组

    FILE *parkfile = fopen("parkfile.txt", "a");//将信息存入本地文件，保证程序退出后数据不会丢失
    if (parkfile == NULL)
    {
        printf("文件打开失败！\n");
        return;
    }
    fprintf(parkfile,"[进入]，车牌号为%s 车位：%d 时间：%d年%d月%d日 %2d:%2d:%2d \n",
        car.name,(car.num+=1),//车牌和车位信息
        now->tm_year + 1900,now->tm_mon + 1,now->tm_mday,//年月日
        now->tm_hour,now->tm_min,now->tm_sec);//时分秒
    fclose(parkfile);

    printf("欢迎%s车主回家,%d号车位，剩余%d个空位\n", car.name,car.num,park_num);
}


//车辆离开
void car_leave()
{
    Car car;
    printf("请输入车牌号：");
    scanf("%s", car.name);
    for (int i = 0; i < max_car; i++)
    {
        if (strcmp(park[i].name, car.name) == 0){//如果找到车牌号，则释放车位 
            //查询当前时间时间以记录数据
            time_t  now_time = time(NULL);//创建一个新的tm结构体来储存当前时间戳
            struct tm *now = localtime(&now_time);

            FILE *parkfile = fopen("parkfile.txt", "a");
            if (parkfile == NULL){
            printf("文件打开失败！\n");
            return;
            }
            fprintf(parkfile,"[离开]，车牌号为%s 车位：%d 时间：%d年%d月%d日 %2d:%2d:%2d \n",
                car.name,park[i].num+1,//车牌和车位信息
                now->tm_year + 1900,now->tm_mon + 1,now->tm_mday,//年月日
                now->tm_hour,now->tm_min,now->tm_sec);//时分秒
            fclose(parkfile);
            int hours = (int)ceil((now_time - park[i].now_time)/3600);
            printf("一共停车%d小时，收费：%d元,剩余%d个空位\n",hours, hours * Parking_fee,park_num+1);

            park_free(i);
            break;
        }
        if(i > max_car - 2)
        {
            printf("没有找到%s车主的停车记录\n", car.name);
            break;
        }
    }
}

//查询车位信息
void car_find()
{
    printf("您要查询车位信息还是车牌信息？\n1.车位信息\n2.车牌信息\n请输入：");
    int find_num;
    scanf("%d", &find_num);
    switch (find_num){
        case 1:{
            printf("请输入车位号：");
            int num;
            scanf("%d", &num);
            if (num > max_car || num < 0){
                printf("车位号错误，请重新输入\n");
                break;
            }
            if (park[num].name[0] == '\0'){
                printf("车位%d为空\n", num);
            }
            else{
                printf("车位%d已被%s车主使用\n", num, park[num].name);
            }
            break;
        }
        case 2:{
            printf("请输入车牌号：");
            char name[10];
            scanf("%s", name);
            for (int i = 0; i < max_car; i++){
                if (strcmp(park[i].name, name) == 0){
                    printf("车牌%s车主停在%d号位\n", name,i+1);
                }
                if(i > max_car - 2){
                    printf("没有找到%s车主的停车记录\n", name);
                    break;
                }
            }
            break;
        }
    }
}

//菜单，每次完成操作后需要重新显示菜单
void menu()
{
    printf("\n===校园停车管理系统===\n");
    printf("1. 车辆入场\n");
    printf("2. 车辆离开\n");
    printf("3. 车位查询\n");
    printf("4. 退出系统\n");
    printf("请输入相应的数字以进行操作：");
}
int main()
{
    park_initialize();//开始时将全部车位初始化为空
    //根据不同情况来操作
    int menu_num;//记录菜单的选择
    do
    {
        menu();
        scanf("%d", &menu_num);
        switch (menu_num)
        {
            case 1:{car_enter();
                break;//完成相应操作后跳出switch循环，进行下一次操作
            }
            case 2:{car_leave();
                break;
            }
            case 3:{car_find();
                break;}
            case 4:{break;}
            default:{printf("无此操作，请输入正确的数字以进行操作\n");}
        }
        printf("---------------------------");
    } while (menu_num != 4);
}
