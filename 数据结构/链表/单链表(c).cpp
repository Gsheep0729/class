#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
} node;

node* init_node()//1无参:分配内存和初始化
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = 0;
    new_node->next = NULL;
    return new_node;
}

node* create_node(int data)//有参：分配内存和初始化为目标数据
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

/*头插法*/
// node* arry(int arr[], int n) {
//     node *head = NULL; // 初始化头指针为NULL
//     for (int i = 0; i < n; i++) {
//         node *newNode = (node*)malloc(sizeof(node)); // 为新节点分配内存
//         newNode->data = arr[i]; // 设置新节点的数据
//         newNode->next = head; // 将新节点的next指向当前的头结点
//         head = newNode; // 更新头结点为新节点
//     }
//     return head; // 返回头结点
// }

/*尾插法*/
node *arry(int data[],int size)//数组链表
{
    node *head = init_node();//初始化数组的头节点
    node *p = head;
    for (int i = 0; i < size; i++)
    {
        node *new_node = create_node(data[i]);//创建过渡新节点
        p->next = new_node;//通过P将新节点链接到链表末尾
        p = p->next;//将游标移动到下一个节点
    }
    return head;
}


//2求单链表长度
int length(node* head)//求单链表长度
{
    int len = 0;
    node* p = head->next;
    while (p != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}

//3按位置查找
node *find_node(node* head, int pos)//按位置查找
{
    node* p = head->next;
    for (int i = 0; i < pos; i++)
    {
        p = p->next;
    }
    return p;
}

//4按值查找
node *find_node_by_value(node* head, int value)//按值查找
{
    node* p = head->next;
    while (p != NULL)
    {
        if (p->data == value)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

//5在位置i插入一个数据元素
node *insert_node(node* head, int pos, int value)//在位置pos插入一个数据元素
{
    node* p = head;
    for (int i = 0; i < pos; i++)
    {
        p = p->next;
    }
    node* new_node = create_node(value);
    new_node->next = p->next;
    p->next = new_node;
    return head;
}

//6删除位置i的数据元素
node *delete_node(node* head, int pos)//6删除位置i的数据元素
{
    node* p = head;
    for (int i = 0; i < pos; i++)
    {
        p = p->next;
    }
    node* temp = p->next;
    p->next = p->next->next;
    free(temp);
    return head;
}

//7打印链表
void print_node(node* head)
{
    printf("head");
    node* p = head->next;
    while (p != NULL)
    {
        printf(" -> %d", p->data);
        p = p->next;
    }
    printf("\n");
}

//8销毁单链表
void destroy_node(node* head)//销毁单链表
{
    node* p = head->next;
    while (p != NULL)
    {
        node* temp = p;
        p = p->next;
        free(temp);
    }
    free(head);
}

int main()
{
    node *head = init_node();//初始化头节点
    node *first = create_node(0);//初始化第一个节点
    head->next = first;//first连接到头结点

    int data[]={1,2,3,4,5};
    int size = sizeof(data) / sizeof(data[0]);
    first -> next = arry(data,size)->next;
    printf("初始化链表：");
    print_node(head);
    printf("链表长度为：%d\n",length(head));
    printf("第3个节点的值为:%d\n",find_node(head,3)->data);
    printf("值为3的节点为:%d\n",find_node_by_value(head,3)->data);
    insert_node(head,3,6);
    printf("插入第3节点后：");
    print_node(head);
    delete_node(head,4);
    printf("删除第4节点后：");
    print_node(head);
    destroy_node(head);

    return 0;
}