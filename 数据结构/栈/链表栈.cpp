#include <iostream>
#include <stdlib.h>
using namespace std;

// 定义链表节点结构体
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 定义栈的结构体
typedef struct
{
    Node *top; // 栈顶指针
} Stack;

// 初始化栈
void initStack(Stack *s)
{
    s->top = NULL; // 初始时栈为空，栈顶指针指向NULL
}

// 判断栈是否为空
bool isEmpty(Stack *s)
{
    return s->top == NULL;
}

// 向栈中添加元素（push）
void push(Stack *s, int item)
{
    Node *newNode = new Node; // 分配新节点内存
    if (!newNode)             // 0 NULL \0
    {
        cout << "申请内存失败" << endl;
        return;
    }
    newNode->data = item; // 设置节点数据
    // 新节点指向原来的栈顶
    newNode->next = s->top;
    // 更新栈顶指针
    s->top = newNode;
}

// 从栈中删除元素（pop）
bool pop(Stack *s, int *item)
{
    // 空栈
    if (isEmpty(s))
    {
        cout << "栈是空的" << endl;
        return false;
    }
    // 保存原栈顶节点
    Node *oldTop = s->top;
    //// 取出原栈顶元素的值
    *item = oldTop->data;
    //// 更新栈顶指针
    s->top = oldTop->next; // 3-2-1  2-1
    // 释放原栈顶节点的内存
    delete oldTop;
    oldTop = NULL;
    return true;
}

// 获取栈顶元素但不删除（peek）
bool peek(Stack *s, int *item)
{
    // 空栈
    if (isEmpty(s))
    {
        cout << "栈是空的" << endl;
        return false;
    }
    *item = s->top->data; // 直接访问栈顶节点的数据
    return true;
}

// 释放栈中所有节点的内存（可选，通常在栈不再需要时调用）
void freeStack(Stack *s)
{
    // 当前节点
    Node *current = s->top;
    // 下一个节点
    Node *next = NULL;
    while (current)
    {
        // 释放当前节点
        next = current->next;
        // 释放当前节点
        delete current;
        // 移动到下一个节点
        current = next;
    }
    s->top = NULL; // 栈变为空
}

int main()
{
    Stack s;
    initStack(&s);

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    int poppedElement = 0;
    if (pop(&s, &poppedElement))
    {
        cout << "删除的元素是：" << poppedElement << endl; // 3
    }

    int topElement = 0;
    if (peek(&s, &topElement))
    {
        cout << "栈顶元素是：" << topElement << endl; // 2
    }

    if (peek(&s, &topElement))
    {
        cout << "栈顶元素是：" << topElement << endl; // 2
    }

    if (isEmpty(&s))
    {
        cout << "栈是空的" << endl;
    }

    freeStack(&s);

    return 0;
}