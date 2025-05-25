#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

// 定义二叉树节点结构体
typedef struct TreeNode
{
    int val;                // 节点存储的数据
    int height;             // 记录树的高度
    struct TreeNode *left;  // 指向左子节点的指针
    struct TreeNode *right; // 指向右子节点的指针
} TreeNode;

// 创建一个新的二叉树节点
TreeNode *createNode(int value)
{
    // TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode)); // 分配内存
    TreeNode *newNode = new TreeNode; // 分配内存
    if (!newNode)
    {
        cout << "申请内存失败" << endl;
        exit(-1);
    }
    newNode->val = value;  // 设置节点值
    newNode->height = 1;   // 新节点的初始高度为1
    newNode->left = NULL;  // 初始化左子节点指针为NULL
    newNode->right = NULL; // 初始化右子节点指针为NULL
    return newNode;        // 返回新创建的节点
}

// 获取节点的高度
int getHeight(TreeNode *p_tree)
{
    // 空树
    if (!p_tree)
    {
        return 0;
    }
    // 树的高度
    return p_tree->height;
}

// 获取两个节点中较高的高度
int maxHeight(TreeNode *a, TreeNode *b)
{
    // a为空
    if (!a)
    {
        return b->height;
    }
    // b为空
    if (!b)
    {
        return a->height;
    }
    // 返回二者较大的
    return (a->height > b->height) ? a->height : b->height;
}

// 右旋
void rightRotate(TreeNode **p_tree)
{
    // 原根节点（0）的左子树（-3）
    TreeNode *leftTree = (*p_tree)->left;
    // 左子树（-3）的右子树（-1）
    TreeNode *leftTreeRight = leftTree->right;

    // 执行旋转
    // 1. 将原根节点（0）变成左子树（-3）的右子树
    leftTree->right = *p_tree;
    // 2. 将原来左子树（-3）的右子树（-1）变成原根节点（0）的左子树
    (*p_tree)->left = leftTreeRight;

    // 更新高度，只有-3和0的高度受到影响
    // 原根节点（0）高度受到影响
    (*p_tree)->height = maxHeight((*p_tree)->left, (*p_tree)->right) + 1;
    // 原根节点（0）的左子树（-3）高度受到影响
    leftTree->height = maxHeight(leftTree->left, leftTree->right) + 1;

    // 更新根节点
    *p_tree = leftTree;
}

// 左旋
void leftRotate(TreeNode **p_tree)
{
    // 原根节点（0）的右子树（3）
    TreeNode *rightTree = (*p_tree)->right;
    // 右子树（3）的左子树（1）
    TreeNode *rightTreeLeft = rightTree->left;

    // 执行旋转
    // 1. 将原根节点（0）变成右子树（3）的左子树
    rightTree->left = *p_tree;
    // 2. 将原来右子树（3）的左子树（1）变成原根节点（0）的右子树
    (*p_tree)->right = rightTreeLeft;

    // 更新高度
    // 原根节点（0）高度受到影响
    (*p_tree)->height = maxHeight((*p_tree)->left, (*p_tree)->right) + 1;
    // 原根节点（0）的右子树（3）高度受到影响
    rightTree->height = maxHeight(rightTree->left, rightTree->right) + 1;

    // 更新根节点
    *p_tree = rightTree;
}

// 获取节点的平衡因子
int getBalance(TreeNode *p_tree)
{
    if (!p_tree)// 空树
    {
        return 0;
    }
    // 左子树高度 - 右子树高度
    return getHeight(p_tree->left) - getHeight(p_tree->right);
}

// 在有序二叉树里插入节点(递归方式)
void insertNodeRec(TreeNode **p_tree, int value)
{
    // 1. 正常的插入
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

    // 更新树的高度
    (*p_tree)->height = maxHeight((*p_tree)->left, (*p_tree)->right) + 1;

    // 检查是否平衡并修复
    int balance = getBalance(*p_tree);

    // LL
    if (balance > 1 && value < (*p_tree)->left->val)
    {
        // 右旋
        rightRotate(p_tree);
        return;
    }

    // RR
    else if (balance < -1 && value > (*p_tree)->right->val)
    {
        // 左旋
        leftRotate(p_tree);
        return;
    }

    // LR
    else if (balance > 1 && value > (*p_tree)->left->val)
    {
        // 对被破坏节点的左孩子进行左旋
        leftRotate(&(*p_tree)->left);
        // 右旋
        rightRotate(p_tree);
        return;
    }

    // RL
    else if (balance < -1 && value < (*p_tree)->right->val)
    {
        // 对被破坏节点的右孩子进行右旋
        rightRotate(&(*p_tree)->right);
        // 左旋
        leftRotate(p_tree);
        return;
    }
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
    while (root->left)
    {
        root = root->left;
    }
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
        deleteNode(&((*root)->left), key);
    }
    // 如果要删除的节点在右子树中
    else if (key > (*root)->val)
    {
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
        // 如果节点只有一个子节点
        if ((*root)->left == nullptr)
        {
            TreeNode *temp = (*root);
            (*root) = (*root)->right;
            delete temp;
            temp = NULL;
        }
        else if ((*root)->right == NULL)
        {
            TreeNode *temp = (*root);
            (*root) = (*root)->left;
            delete temp;
            temp = NULL;
        }
        // 如果节点有两个子节点，找到右子树中的最小节点（或左子树中的最大节点）
        else
        {
            // 这里我们找到右子树中的最小节点，并替换当前节点
            TreeNode *minNode = findMin((*root)->right);
            (*root)->val = minNode->val;
            // 删除右子树中的最小节点
            deleteNode(&((*root)->right), minNode->val);
        }
    }

    // 树为空
    if (*root == NULL)
    {
        return;
    }

    // 与插入逻辑一模一样
    //  更新高度
    (*root)->height = 1 + maxHeight((*root)->left, (*root)->right);
    // 获取平衡因子
    int balance = getBalance((*root));

    // 平衡因子大于1（LL型）
    if (balance > 1 && getBalance((*root)->left) >= 0)
    {
        rightRotate(root);
        return;
    }

    // 平衡因子大于1且左子树的平衡因子小于0（LR型）
    else if (balance > 1 && getBalance((*root)->left) < 0)
    {
        leftRotate(&(*root)->left);
        rightRotate(root);
        return;
    }

    // 平衡因子小于-1（RR型）
    else if (balance < -1 && getBalance((*root)->right) <= 0)
    {
        leftRotate(root);
        return;
    }

    // 平衡因子小于-1且右子树的平衡因子大于0（RL型）
    else if (balance < -1 && getBalance((*root)->right) > 0)
    {
        rightRotate(&(*root)->right);
        leftRotate(root);
        return;
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

// 主函数示例
int main()
{
    // 创建节点
    TreeNode *root = createNode(0);

    // // 下列场景为LL型触发右旋
    // // 递归插入
    // insertNodeRec(&root, -3);
    // insertNodeRec(&root, 3);
    // insertNodeRec(&root, -5);
    // insertNodeRec(&root, -1);
    // insertNodeRec(&root, -4);
    // // 层次遍历
    // levelPrint(root);

    // // 下列场景RR型触发左旋
    // // 递归插入
    // insertNodeRec(&root, -3);
    // insertNodeRec(&root, 3);
    // insertNodeRec(&root, 1);
    // insertNodeRec(&root, 4);
    // // 层次遍历
    // insertNodeRec(&root, 5);
    // // 层次遍历
    // levelPrint(root);

    // // 下列场景为LR型
    // // 递归插入
    // insertNodeRec(&root, -3);
    // insertNodeRec(&root, 3);
    // insertNodeRec(&root, -4);
    // insertNodeRec(&root, -2);
    // insertNodeRec(&root, -1);
    // // 层次遍历
    // levelPrint(root);

    // 下列场景为RL型
    // 递归插入
    insertNodeRec(&root, -3);
    insertNodeRec(&root, 3);
    insertNodeRec(&root, 2);
    insertNodeRec(&root, 4);
    insertNodeRec(&root, 1);
    // 层次遍历
    levelPrint(root);

    deinitTree(root);
    root = NULL;

    return 0;
}