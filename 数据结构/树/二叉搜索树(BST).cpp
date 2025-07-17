#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

// 定义二叉树节点结构体
typedef struct TreeNode
{
    int val;                // 节点存储的数据
    struct TreeNode *left;  // 指向左子节点的指针
    struct TreeNode *right; // 指向右子节点的指针
} TreeNode;

// 创建一个新的二叉树节点
TreeNode *createNode(int value)
{
    TreeNode *newNode = new TreeNode; // 分配内存
    if (!newNode)
    {
        cout << "申请内存失败" << endl;
        exit(-1);
    }
    newNode->val = value;  // 设置节点值
    newNode->left = NULL;  // 初始化左子节点指针为NULL
    newNode->right = NULL; // 初始化右子节点指针为NULL
    return newNode;
}

// 在有序二叉树里插入节点(循环方式)
void insertNodeLoop(TreeNode **p_tree, int value)
{
    // 如果树为空作为根节点插入
    if (!*p_tree)
    {
        *p_tree = createNode(value);
        return;
    }
    // 不为空
    // 从根节点开始遍历
    TreeNode *father = NULL;
    TreeNode *currentTreeNode = *p_tree;
    while (currentTreeNode)
    {
        father = currentTreeNode; // 将当前结点作为下一个结点的父结点
        if (value < currentTreeNode->val)
        {
            // 小于当前节点值，在左子树去遍历
            currentTreeNode = currentTreeNode->left;
        }
        else if (value > currentTreeNode->val)
        {
            // 大于当前节点值，在右子树去遍历
            currentTreeNode = currentTreeNode->right;
        }
        else
        {
            // 该值已经在树里了
            return;
        }
    }
    // 结束循环后 currentTreeNode为空 在father节点进行插入
    // 找到空位置了，需要判断是左插还是右插，才能正确设置father的左右节点信息
    TreeNode *newNode = createNode(value);
    // 左插
    if (value < father->val)
    {
        father->left = newNode;
    }
    // 右插
    else
    {
        father->right = newNode;
    }
}

// 在有序二叉树里插入节点(递归方式)
void insertNodeRec(TreeNode **p_tree, int value)
{
    // 如果树为空作为根节点插入
    if (!*p_tree)
    {
        *p_tree = createNode(value);
        return;
    }
    // 不为空
    if (value < (*p_tree)->val)
    {
        // 小于当前节点值，在左子树去遍历
        insertNodeRec(&(*p_tree)->left, value);
    }
    else if (value > (*p_tree)->val)
    {
        // 大于当前节点值，在右子树去遍历
        insertNodeRec(&(*p_tree)->right, value);
    }
    else
    {
        // 该值已经在树里了
        return;
    }
}

// 先序遍历（根左右）
void frontPrint(TreeNode *p_tree)
{
    if (!p_tree)
    {
        return;
    }

    // 打印根结点
    cout.width(2);
    cout << p_tree->val << " ";

    // 遍历左子树
    frontPrint(p_tree->left);

    // 遍历右子树
    frontPrint(p_tree->right);
}

// 中序遍历(左根右)
void middlePrint(TreeNode *p_tree)
{
    if (!p_tree)
    {
        return;
    }
    // 遍历左子树
    middlePrint(p_tree->left);

    // 打印根结点
    cout.width(2);
    std::cout << p_tree->val << " ";

    // 遍历右子树
    middlePrint(p_tree->right);
}

// 后序遍历(左右根)
void backPrint(TreeNode *p_tree)
{
    if (!p_tree)
    {
        return;
    }
    // 遍历左子树
    backPrint(p_tree->left);

    // 遍历右子树
    backPrint(p_tree->right);

    // 打印根结点
    cout.width(2);
    std::cout << p_tree->val << " ";
}

// 层次遍历（一层一层遍历）
void levelPrint(TreeNode *p_tree)
{
    if (!p_tree)
    {
        cout << "树是空的" << endl;
        return;
    }

    // 创建队列，存储树中每个节点
    queue<TreeNode *> q;
    // 先存储根节点
    q.push(p_tree);

    while (!q.empty())
    {
        // 拿到第一个节点
        TreeNode *currentNode = q.front();
        // 将其出队
        q.pop();

        // 访问当前节点
        cout.width(2);
        cout << currentNode->val << " ";

        // 如果左子节点存在，则加入队列
        if (currentNode->left)
        {
            q.push(currentNode->left);
        }

        // 如果右子节点存在，则加入队列
        if (currentNode->right)
        {
            q.push(currentNode->right);
        }
    }
    cout << endl;
}

// 辅助函数，用于找到树中的最小节点
TreeNode *findMin(TreeNode *root)
{
    // 左子树存在
    while (root->left)
    {
        // 一直遍历左子树
        root = root->left;
    }
    // 不存在左子树 ，根节点就是最小节点
    return root;
}

// 删除节点
void deleteNode(TreeNode **root, int key)
{
    if (*root == NULL)
    {
        return;
    }
    // 如果要删除的节点在左子树中
    if (key < (*root)->val)
    {
        // 递归遍历
        deleteNode(&((*root)->left), key);
    }
    // 如果要删除的节点在右子树中
    else if (key > (*root)->val)
    {
        // 递归遍历
        deleteNode(&((*root)->right), key);
    }
    // 如果找到了要删除的节点
    else
    {
        // 如果节点是叶子节点
        if ((*root)->left == NULL && (*root)->right == NULL)
        {
            delete *root;
            *root = NULL;
            return;
        }
        // 如果节点只有一个右子节点
        if ((*root)->left == NULL)
        {
            TreeNode *tmp = *root;
            // 用右子节点去替换根节点
            (*root) = (*root)->right;
            // 删除原来根节点内容
            delete tmp;
            tmp = NULL;
            return;
        }
        else if ((*root)->right == NULL)
        {
            TreeNode *tmp = *root;
            // 用左子节点去替换根节点
            (*root) = (*root)->left; // 2->lest = 1  root 2 (*root)->left 1
            // 删除原来根节点内容
            delete tmp;
            tmp = NULL;
            return;
        }
        // 如果节点有两个子节点，找到右子树中的最小节点（或左子树中的最大节点）
        else
        {
            TreeNode *minNode = findMin((*root)->right);
            // // 把里面的值替换  依次赋值
            (*root)->val = minNode->val;
            // 删除右子树中的最小节点
            deleteNode(&((*root)->right), minNode->val);
            // 替换节点
            // (*root) = minNode;
            // // 直接删掉最小节点  不太行
            // delete minNode;
            // minNode = NULL;
        }
    }
}

// 树的清理函数(后序遍历)
void deinitTree(TreeNode *root)
{
    if (!root)
    {
        return;
    }
    deinitTree(root->left);
    deinitTree(root->right);
    delete root;
}

int main()
{
    // 创建节点
    TreeNode *root = createNode(0);
    // 循环插入
    insertNodeLoop(&root, 3);
    insertNodeLoop(&root, 2);
    insertNodeLoop(&root, 4);
    insertNodeLoop(&root, 1);
    insertNodeLoop(&root, 5);

    // 递归插入
    insertNodeRec(&root, -3);
    insertNodeRec(&root, -5);
    insertNodeRec(&root, -1);
    insertNodeRec(&root, -2);
    insertNodeRec(&root, -4);

    // 先序遍历
    frontPrint(root);
    std::cout << std::endl;

    // 中序遍历
    middlePrint(root);
    std::cout << std::endl;

    // 后序遍历
    backPrint(root);
    std::cout << std::endl;

    // 层次遍历
    levelPrint(root);

    cout << "-----------" << endl;

    // 删除-2节点
    deleteNode(&root, -3);
    // 层次遍历
    levelPrint(root);

    deinitTree(root);
    root = NULL;

    return 0;
}