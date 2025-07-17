#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX_SIZE 100 // 定义栈的最大容量

// 栈的结构体定义
typedef struct
{
    int top;             // 栈顶元素的下标。
    int items[MAX_SIZE]; // 栈元素存放的空间
} Stack;

// 初始化栈
void initStack(Stack *s)
{
    s->top = -1; // 栈空时，栈顶索引为-1
}

// 判断栈是否为空
bool isEmpty(Stack *s)
{
    return s->top == -1;
}

// 判断栈是否已满
bool isFull(Stack *s)
{
    return s->top == MAX_SIZE - 1;
}

// 向栈中添加元素
bool push(Stack *s, int item)
{
    // 栈满了
    if (isFull(s))
    {
        cout << "栈满了" << endl;
        return false;
    }

    // 栈顶索引 + 1 s->top ++
    // 把元素放到新的索引处 3->4
    s->items[++s->top] = item; // 先增加栈顶索引，再赋值
    return true;
}

// 从栈中删除元素 并且获取被删除的值 因为要修改实参，所以item地址传递
bool pop(Stack *s, int *item)
{
    // 空栈
    if (isEmpty(s))
    {
        cout << "栈是空的" << endl;
        return false;
    }
    // 获取删除的栈顶元素   栈顶索引 -1 3->2
    *item = s->items[s->top--]; // 先取值，再减少栈顶索引
    return true;
}

// 获取栈顶元素但不删除
bool peek(Stack *s, int *item)
{
    // 空栈
    if (isEmpty(s))
    {
        cout << "栈是空的" << endl;
        return false;
    }
    // 获取栈顶元素
    *item = s->items[s->top];
    return true;
}

int main()
{
    Stack s;
    initStack(&s);

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    int topElement = 0;
    if (peek(&s, &topElement))
    {
        cout << "栈顶元素是" << topElement << endl;
    }

    int poppedElement = 0;
    if (pop(&s, &poppedElement))
    {
        cout << "删除的元素是" << poppedElement << endl;
    }

    if (isEmpty(&s))
    {
        cout << "栈是空的" << endl;
    }

    return 0;
}