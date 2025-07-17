#include <iostream>
using namespace std;

// 定义链表节点结构
typedef struct listNode
{
    int val;                 // 整型数据
    struct listNode *p_prev; // 指向上一个节点的指针
    struct listNode *p_next; // 指向下一个节点的指针
} ListNode;

// 创建节点
// 参数：value 要创建的节点的值
// 返回值：ListNode* 创建的节点
ListNode *createNode(int value)
{
    ListNode *newNode = new ListNode{value}; // 动态分配内存，并设置新节点的值
    if (newNode != NULL)
    {
        newNode->p_prev = NULL; // 新节点的p_prev指针初始化为NULL,因为没有前面的元素了
        newNode->p_next = NULL; // 新节点的p_next指针初始化为NULL,因为没有后续的元素了
    }
    return newNode; // 此处可以返回局部变量的地址是因为newNode在堆区，生命周期在delete后才结束
}

// 在头部添加节点
// head:链表的头节点； value:要插入的值
// ListNode*：返回头节点
ListNode *insertNodeAtHead(ListNode *head, int value)
{
    // 必须的 head==NULL  双向必须  单向可以不必须
    if (head == NULL)
    {
        // 如果链表为空，新节点即为头节点
        head = createNode(value);
        return head;
    }

    // 创建新节点 2  新节点1  边变成 1-2
    ListNode *newHead = createNode(value);
    // 让新节点的p_next指向头节点
    newHead->p_next = head;
    // 让头节点的p_prev指向新节点
    head->p_prev = newHead;
    // 返回新的头节点
    return newHead;
}

// 在尾部添加节点
// head:链表的头节点； value:要插入的值
ListNode *insertNodeAtTail(ListNode *head, int value)
{
    if (head == NULL)
    {
        // 如果链表为空，新节点即为头节点
        head = createNode(value);
    }
    else
    {
        // 定义中间变量，找到原来尾节点
        ListNode *current = head;
        // 遍历链表找到最后一个节点
        while (current->p_next)
        {
            // 向后遍历
            current = current->p_next;
        }

        // current就是尾节点
        ListNode *newNode = createNode(value);
        // 无顺序要求
        current->p_next = newNode;
        newNode->p_prev = current;
    }

    // 返回头节点，在调用该函数时要用head接受该返回值来更新头节点
    return head;
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
        ListNode *second = first->p_next;

        // first不是尾节点
        while (second)
        {
            // 需要判断相邻两个节点的大小关系 例如：1-3 插入2
            if (value > first->val && value < second->val)
            {
                ListNode *newNode = createNode(value);
                // 无顺序要求
                // 让新节点的p_next指向second节点
                newNode->p_next = second;
                // 让second节点的p_prev指向新节点
                second->p_prev = newNode;
                // 让first节点的p_next指向新节点
                first->p_next = newNode;
                // 让新节点的p_prev指向first节点
                newNode->p_prev = first;
                // 提前结束
                return head;
            }

            // 向后遍历
            first = second;
            second = first->p_next;
        }
        // 尾插法1-2 3
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
    else if (head->val == value)
    {
        // 记录新的头节点
        ListNode *newHead = head->p_next;
        // 新的头节点前面为空
        newHead->p_prev = NULL;
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
        // current和current->next都可以
        while (current)
        {
            // 使用一个指针的方式
            // 不是尾节点 例如：1-2-3删除2 变成1-3
            if (current->val == value)
            {
                // 不是尾节点
                if (current->p_next)
                {
                    // 更新节点指向 1的p_next指向3  current是2
                    current /*2*/->p_prev /*1*/->p_next = current /*2*/->p_next /*3*/;
                    // 3的p_prev指向1  current是2
                    current /*2*/->p_next /*3*/->p_prev = current /*2*/->p_prev /*1*/;
                }
                else
                {
                    // current是2 1的p_next指向空
                    current /*2*/->p_prev /*1*/->p_next = NULL;
                }
                // 删除当前节点
                delete current;
                current = NULL;
                // 提前结束
                return head;
            }
            // 向后遍历
            current = current->p_next;
        }
    }

    return head;
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
        current = current->p_next;
        // 删除节点
        delete needDelNode;
        needDelNode = NULL;
    }
}

// 打印链表
// head:链表的头节点；
void printNode(ListNode *head)
{
    // 判断是不是空链表
    if (head == NULL)
    // if (NULL = head)
    {
        std::cout << "链表为空" << std::endl;
        return;
    }

    // current前向遍历的指针
    ListNode *current = head;
    // current_prev后向遍历的指针
    ListNode *current_prev = head->p_prev;

    // 正向遍历
    while (current)
    {
        // 输出内容
        std::cout << current->val << " ";
        // 向后遍历 1-2-3-NULL current_prev 3  current NULL
        current_prev = current;
        current = current->p_next;
    }
    std::cout << std::endl;

    // 反向
    while (current_prev)
    {
        // 输出内容
        std::cout << current_prev->val << " ";
        // 向前遍历
        current_prev = current_prev->p_prev;
    }
    std::cout << std::endl;
}

int main()
{
    // 初始化链表头指针
    ListNode *head = NULL; // 初始化链表为空链表

    // 插入
    head = insertNodeAtMiddle(head, 1); // 头
    head = insertNodeAtMiddle(head, 5); // 尾
    head = insertNodeAtMiddle(head, 3); // 中
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
    head = NULL;
    deinitNode(head);
    head = NULL;

    return 0;
}