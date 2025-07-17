#ifndef TOKEN_H  
#define TOKEN_H  

/*定义了一个名为 token_t 的结构体，用于表示链表节点
每个节点包含两个成员：一个指向字符数组的指针 name，用于存储名称；
一个指向下一个节点的指针 next，用于链接下一个节点*/
typedef struct node
{  
    char *name;//名称
    struct node *next;//下一个节点
} token_t;//可以使用struct node为类型，也可以使用它的别名token_t为类型

void print_token(token_t *p);//打印token

#endif // TOKEN_H  