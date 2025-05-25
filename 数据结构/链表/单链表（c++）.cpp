#include <iostream>
using namespace std;

// 定义链表节点结构
typedef struct listNode
{
    int val;               // 整型数据
    struct listNode *next; // 指向下一个节点的指针
} ListNode;

// 创建节点
//  参数：value  要创建的节点的值
//  返回值：ListNode* 创建的节点
ListNode *createNode(int value)
{
    ListNode *newNode = new ListNode{value}; // 动态分配内存，并设置新节点的值
    if (newNode != NULL)
    {
        newNode->next = NULL; // 新节点的next指针初始化为NULL,因为没有后续的元素了
    }
    return newNode; // 此处可以返回局部变量的地址是因为newNode在堆区，生命周期在delete后才结束
}

// 在尾部添加节点
// head:链表的头节点； value:要插入的值
// ListNode*：返回头节点 为什么要有返回值？因为如果没有返回值，那么head = creataNode(value)这一行更新了head的值
// 但此时参数ListNode*只是改变了指针的值，参数传递方式是值传递而非地址传递，所以形参只是实参的副本，并不会影响到实参
// 解决方法：(任选其一)
//  1. 在调用该函数的时候每次都让head接受函数返回值来更新head
//  2. 将head改为地址传递，即二级指针ListNode**
//  3. 将head改为引用传递，即二级指针ListNode*&
ListNode *insertNodeAtTail(ListNode *head, int value)
{
    if (head == NULL)
    {
        // 如果链表为空，新节点即为头节点
        head = createNode(value);
    }
    else
    {
        // 定义中间变量，防止head误操作导致头节点位置错误
        ListNode *current = head;
        // 遍历链表找到最后一个节点
        while (current->next)
        {
            // 向后遍历
            current = current->next;
        }
        // 将最后一个节点的next指针指向新节点
        current->next = createNode(value);
    }
    // 返回头节点，在调用该函数时要用head接受该返回值来更新头节点
    return head;
}

// 在头部添加节点
// head:链表的头节点； value:要插入的值
// ListNode*：返回头节点
ListNode *insertNodeAtHead(ListNode *head, int value)
{
    // if (head == NULL)
    //{
    //     // 如果链表为空，新节点即为头节点
    //     head = createNode(value);
    // }
    // 让newNode指向头节点
    ListNode *newHead = createNode(value);
    // 让新节点指向头节点
    newHead->next = head;
    // 返回新的头节点
    return newHead;
}

// 在中间添加节点（假设顺序（从小到大））
// head:链表的头节点； newNode:要插入的节点
ListNode *insertNodeAtMiddle(ListNode *head, int value)
{
    if (head == NULL)
    {
        // 如果链表为空，新节点即为头节点
        head = createNode(value);
    }
    else
    {
        // 比头节点小 例如：2-3插入1
        if (value < head->val)
        {
            // 头插
            head = insertNodeAtHead(head, value);
            // 结束
            return head;
        }

        // 使用两个指针的方式
        // 前面的节点
        ListNode *first = head;
        // 下一个节点
        ListNode *second = first->next;

        // first不是尾节点
        while (second)
        {
            // 需要判断相邻两个节点的大小关系 例如：1-3 插入2
            if (value >= first->val && value <= second->val)
            {
                ListNode *newNode = createNode(value);
                // 一定是先连接后面节点，在连接前面节点，因为节点只记录了下一个节点的地址信息，如果先连接前面，则后面的地址信息就丢失了
                // 先连接后面的节点，即先连接2-3
                newNode->next = second;
                // 然后让前面的节点指向新节点，即1-2
                first->next = newNode;
                // 提前结束
                return head;
            }
            // 向后遍历
            first = second;
            second = first->next;
        }
        // 尾插法
        head = insertNodeAtTail(head, value);
    }
    return head;
}

// 删除节点
// head:链表的头节点； value:要删除的值
ListNode *deleteNode(ListNode *head, int value)
{
    if (head == NULL)
    {
        // 如果链表为空，结束
        return NULL;
    }
    // 删除的是头节点
    else if (value == head->val)
    {
        // 记录新的头节点
        ListNode *newHead = head->next;
        // 删除头节点。防止内存泄露
        delete head;
        // 更新头节点
        head = newHead;
    }
    // 非头节点
    else
    {
        // 从前往后遍历
        ListNode *current = head;
        // 遍历链表
        while (current->next)
        {
            // 使用一个指针的方式
            // 所以要删除当前节点的下一个节点 current->next
            if (current->next->val == value)
            {
                // 要删除的是当前节点的下一个节点 1-2-3删除2 变成1-3
                // current 1
                // current->next 2
                ListNode *needDelNode = current->next;
                // 中间节点
                if (current->next->next)
                {
                    // 更新节点指向
                    current->next = current->next->next;
                }
                // 尾节点1-2 删除2 变成1
                else
                {
                    current->next = NULL;
                }
                // 删除下一个节点
                delete needDelNode;
                needDelNode = NULL;

                // 提前结束
                return head;
            }

            // 向后遍历
            current = current->next;
        }
        // 没找到这个节点信息
    }
    // 执行到此处说明没找到删除的这个节点信息
    return head;
}

// 打印链表
// head:链表的头节点；
void printNode(ListNode *head)
{
    // 判断是不是空链表
    if (head == NULL)
    {
        std::cout << "链表为空" << std::endl;
        return;
    }
    ListNode *current = head;
    // 遍历
    while (current)
    {
        // 输出内容
        std::cout << current->val << " ";
        // 向后遍历
        current = current->next;
    }
    std::cout << std::endl;
}

// 清空链表
// head:链表的头节点；
void deinitNode(ListNode *head)
{
    // 判断是不是空链表
    if (head == NULL)
    {
        std::cout << "链表为空" << std::endl;
        return;
    }
    ListNode *current = head;
    // 向后遍历
    while (current)
    {
        // 要删除的节点
        ListNode *needDelNode = current;
        // 向后遍历
        current = current->next;
        // 删除节点
        delete needDelNode;
        needDelNode = NULL;
    }
}

int main()
{
    // 初始化链表头指针
    ListNode *head = NULL; // 初始化链表为空链表

    // 插入
    head = insertNodeAtMiddle(head, 1); // 头
    head = insertNodeAtMiddle(head, 5); // 尾
    head = insertNodeAtMiddle(head, 3); // 尾
    head = insertNodeAtMiddle(head, 2);
    head = insertNodeAtMiddle(head, 4);

    // 打印链表
    printNode(head);

    // 删除
    head = deleteNode(head, 1); // 头
    head = deleteNode(head, 5); // 尾
    head = deleteNode(head, 3); // 中

    // 打印链表
    printNode(head);

    // 清理链表
    deinitNode(head);

    return 0;
}