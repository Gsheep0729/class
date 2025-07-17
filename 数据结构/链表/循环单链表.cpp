#include <iostream>
using namespace std;

// 定义链表节点结构体
typedef struct CircularListNode
{
    int data;
    struct CircularListNode *next;
} CircularListNode;

// 创建新节点
CircularListNode *createNode(int data)
{
    CircularListNode *newNode = (CircularListNode *)malloc(sizeof(CircularListNode));
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 初始化链表 只修改值（值传递） 修改指向（地址传递）
void initCircularLinkedList(CircularListNode **head)
{
    *head = NULL;
}

// 插入节点到链表末尾
void appendNode(CircularListNode **head, int data)
{
    CircularListNode *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        newNode->next = *head; // 构成循环
    }
    else
    {
        CircularListNode *tmp = *head;
        while (tmp->next != *head)
        {
            // 找到最后一个节点
            tmp = tmp->next;
        }
        tmp->next = newNode;   // 将新节点插入到链表末尾
        newNode->next = *head; // 新节点指向头节点，形成循环
    }
}

// 打印链表
void printList(CircularListNode *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    CircularListNode *temp = head;
    do
    {
        printf("%d ", temp->data);
        temp = temp->next;

    } while (temp != head); // 当回到头节点时停止
    printf("\n");
}

// 销毁链表
void destroyList(CircularListNode **head)
{
    CircularListNode *current = *head;
    if (current == NULL)
        return; // 如果链表为空，则直接返回

    // 如果链表中只有一个节点
    if (current->next = current)
    {
        free(current);
        *head = NULL;
        return;
    }

    // 处理链表中有多个节点的情况
    CircularListNode *temp = NULL;
    do
    {
        temp = current;          // current当前节点  tmp销毁的节点  被销毁后的指针不能做任何使用 只能重新指向一块有效区域或者指控
        current = current->next; // 下一个节点
        free(temp);

    } while (current != *head); // 当回到头节点时停止

    *head = NULL; // 将头指针置为NULL，表示链表已为空
}

int main()
{
    CircularListNode *head = NULL;
    initCircularLinkedList(&head);
    appendNode(&head, 1);
    appendNode(&head, 3);
    appendNode(&head, 2);

    printList(head);

    destroyList(&head);

    return 0;
}