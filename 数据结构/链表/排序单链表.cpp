#include <iostream>
using namespace std;

// 定义链表节点结构
typedef struct node
{
    int val;           // 整型数据
    struct node *next; // 指向下一个节点的指针
} Node;

// 定义链表
typedef struct link
{
    // 记录链表的有效元素数量 可有可无
    int length;
    // 头节点
    Node *head;
    // 尾节点
    Node *tail;
} Link;

// 创建节点
Node *createNode(int value)
{
    Node *newNode = new Node{value};
    if (newNode)
    {
        newNode->next = NULL; // 新节点的next指针初始化为NULL,因为没有后续的元素了
    }
    return newNode;
}

// 创建链表
// 参数：无
// 返回值：链表
Link *createLink()
{
    Link *link = new Link{0}; // 初始化长度为0
    if (link)
    {
        link->head = NULL;
        link->tail = NULL;
    }
    return link;
}

// 在链表尾部添加节点
// 参数：插入的值 链表
// 返回值:无  返回头节点：里面的值改变了（值传递，参数的形式要是地址变量）  指向改变了（地址传递，返回新的地址）
void insertNodeAtTail(Link *link, int value)
{
    // 创建节点
    Node *newNode = createNode(value);
    // 头节点为有效元素，链表不为空
    if (link->head)
    {
        // 让尾节点的next指向新节点
        link->tail->next = newNode;
        // 更新尾节点
        link->tail = newNode;
    }
    // 如果链表为空，新节点即是头节点也是尾节点
    else
    {
        link->head = newNode;
        link->tail = newNode;
    }
    // 有效长度+1
    link->length++;
}

// 在头部添加节点
void insertNodeAtHead(Link *link, int value)
{
    // 创建节点
    Node *newNode = createNode(value);
    // 头节点为有效元素，链表不为空
    if (link->head)
    {
        // 新节点的next指向原来头节点
        newNode->next = link->head;
        // 更新头节点
        link->head = newNode;
    }
    // 链表为空
    else
    {
        link->head = newNode;
        link->tail = newNode;
    }

    // 有效长度+1
    link->length++;
}

// 在中间添加节点（假设顺序（从小到大））
void insertNodeAtMiddle(Link *link, int value)
{
    // 链表为空或者插入的值小于头节点的值
    if (!link->head || value < link->head->val)
    {
        // 头插法
        insertNodeAtHead(link, value);
        return;
    }

    Node *current = link->head;
    // 从头节点下一个位置开始判断插入
    while (current->next)
    {
        if (value > current->val && value < current->next->val)
        {
            // 创建节点
            Node *newNode = createNode(value);
            // 新节点的next指向当前节点的next
            newNode->next = current->next;
            // 当前节点的next指向新节点
            current->next = newNode;
            link->length++;
            return;
        }
        // 往后遍历
        current = current->next;
    }
    // 尾插法
    insertNodeAtTail(link, value);
}

// 删除节点
void deleteNode(Link *link, int value)
{
    // 空链表
    if (!link->head)
    {
        std::cout << "链表为空" << std::endl;
        return;
    }
    // 删除头节点
    else if (link->head->val == value)
    {
        // 链表就这一个元素
        if (link->head == link->tail)
        {
            // 删除头节点
            delete link->head;
            // 头尾节点置空
            link->head = NULL;
            link->tail = NULL;
        }
        else
        {
            // 更新头节点
            Node *newNode = link->head->next;
            // 删除头节点
            delete link->head;
            // 更新头节点
            link->head = newNode;
        }
        // 长度-1
        link->length--;
        return;
    }
    // 从前往后遍历
    Node *current = link->head;
    // 遍历链表 当前节点的下一个节点
    while (current->next)
    {
        // 找到要删除的节点了
        if (current->next->val == value)
        {
            // 要删除的是当前节点的下一个节点
            Node *needDelNode = current->next;
            // 不是尾节点
            if (current->next->next)
            {
                // 更新节点指向
                current->next = current->next->next;
            }
            // 尾节点
            else
            {
                current->next = NULL;
                // 更新尾节点
                link->tail = current;
            }
            // 删除下一个节点
            delete needDelNode;
            needDelNode = NULL;
            link->length--; // 提前结束
            return;
        }

        // 向后遍历
        current = current->next;
    }
    // 执行到此处说明没找到删除的这个节点信息
}

// 打印链表
void printLink(Link *link)
{
    // 判断是不是空链表
    if (!link->head)
    {
        std::cout << "链表为空" << std::endl;
        return;
    }
    Node *current = link->head;
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
void deinitLink(Link *link)
{
    // 判断是不是空链表
    if (!link->head)
    {
        std::cout << "链表为空" << std::endl;
        return;
    }
    Node *current = link->head;
    // 向后遍历
    while (current)
    {
        // 要删除的节点
        Node *needDelNode = current;
        // 向后遍历
        current = current->next;
        // 删除节点
        delete needDelNode;
        needDelNode = NULL;
    }

    // 更新链表为空
    link->head = NULL;
    link->tail = NULL;
    link->length = 0;
}

int main()
{
    // 创建链表
    Link *link = createLink();

    // 插入
    insertNodeAtMiddle(link, 1); // 头
    insertNodeAtMiddle(link, 5); // 尾
    insertNodeAtMiddle(link, 3); // 中
    insertNodeAtMiddle(link, 2); // 中
    insertNodeAtMiddle(link, 4); // 中

    // 打印链表
    printLink(link);

    // 删除
    deleteNode(link, 1); // 头
    deleteNode(link, 5); // 尾
    deleteNode(link, 3); // 中

    // 打印链表
    printLink(link);

    // 清理链表
    deinitLink(link);
    return 0;
}