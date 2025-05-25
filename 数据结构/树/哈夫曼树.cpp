#include <iostream>
#include <queue>
//插入时先合成森林（链表），再逐步合并生成哈夫曼树
using namespace std;

// 哈夫曼树的节点(通过节点表示一棵树)
typedef struct node
{
    // 权值
    int weight;
    // 左孩子节点
    struct node *left;
    // 右孩子节点
    struct node *right;
} Node;

// 哈夫曼树(通过树表示森林)
typedef struct HuffmanTree
{
    // 树的根节点
    Node *root;
    // 下一颗树
    HuffmanTree *nextTree;
} HuffmanTree;

// 创建一个节点
Node *createNode(int weight)
{
    Node *newNode = new Node;
    newNode->weight = weight;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// 创建哈夫曼树
HuffmanTree *createTree(Node *node)
{
    // 创建新树
    HuffmanTree *newTree = new HuffmanTree;
    // 新树的根就是node
    newTree->root = node;
    newTree->nextTree = NULL;

    return newTree;
}

// 在森林中插入新树
void insertTree(HuffmanTree **tree, HuffmanTree *newTree)
{
    // 森林是空
    // if (!(*tree)->root)
    if (!*tree)
    {
        // 当前这棵树就是第一颗哈夫曼树
        *tree = newTree;
        return;
    }
    HuffmanTree *currentTree = *tree;
    // 从下一棵树开始遍历
    while (currentTree->nextTree)//找到空的位置
    {
        currentTree = currentTree->nextTree;
    }
    //  将这颗树加入到哈夫曼森林中
    currentTree->nextTree = newTree;
}

// 从森林中删除某棵树（并非真正删除，而是合并了）
void deleteTree(HuffmanTree **tree, HuffmanTree *deleteTree)
{
    // 删除的是第一棵树，单独处理
    if ((*tree)->root->weight == deleteTree->root->weight)
    {
        // 更新第一棵树
        *tree = (*tree)->nextTree;
        delete deleteTree;
        deleteTree = NULL;
        return;
    }

    HuffmanTree *currentTree = *tree;
    // 往后遍历到该树
    while (currentTree->nextTree)
    {
        // 找到了要删除的树  currentTree
        if (currentTree->nextTree->root->weight == deleteTree->root->weight)
        {
            // 更新森林
            currentTree->nextTree = currentTree->nextTree->nextTree;
            delete deleteTree;
            deleteTree = NULL;
            return;
        }

        currentTree = currentTree->nextTree;
    }
}

// 选择合并  在森林中选取两棵根结点的权值最小的树，构造一棵新的二叉树
bool selectMerge(HuffmanTree **tree)
{
    // 森林是空的或者森林只有一棵树
    if (!(*tree) || !(*tree)->nextTree)
    {
        return false;
    }
    // 1. 找到权重最小的两棵树
    // minTree1最小的 minTree2倒数第二小
    HuffmanTree *minTree1 = NULL;
    HuffmanTree *minTree2 = NULL;

    // 先从森林里找到前两棵来为最小的两棵树初始化
    if ((*tree)->root->weight < (*tree)->nextTree->root->weight)
    {
        minTree1 = *tree;
        minTree2 = (*tree)->nextTree;
    }
    else
    {
        minTree1 = (*tree)->nextTree;
        minTree2 = *tree;
    }

    // 当前树（从第三棵树开始与前两棵书比较）
    HuffmanTree *currentTree = (*tree)->nextTree->nextTree;
    while (currentTree)
    {
        // 比较权重 小于最小
        if (currentTree->root->weight < minTree1->root->weight)
        {
            // 更新倒数第二小
            minTree2 = minTree1;
            // 更新最小
            minTree1 = currentTree;
        }
        // 比较权重 小于倒数第二小，大于最小
        else if (currentTree->root->weight < minTree2->root->weight && currentTree->root->weight > minTree1->root->weight)
        {
            // 更新倒数第二小
            minTree2 = currentTree;
        }

        // 往后访问
        currentTree = currentTree->nextTree;
    }

    // 2. 合并这两棵树
    // 创建新的父节点，权重为二者之和
    Node *newNode = createNode(minTree1->root->weight + minTree2->root->weight);
    // 创建新树
    HuffmanTree *newTree = createTree(newNode);
    // 左小右大 将两棵树合并为一颗新树
    newTree->root->left = minTree1->root;
    newTree->root->right = minTree2->root;

    // 3. 将新树插入到森林
    insertTree(tree, newTree);
    // 删除原来的两棵树
    deleteTree(tree, minTree1);
    deleteTree(tree, minTree2);

    return true;
}

// 打印哈夫曼编码
void printCodes(Node *p_node, string &code)
{
    // 哈夫曼树是空的
    if (!p_node)
    {
        return;
    }
    // 如果是叶子节点，则打印字符和对应的编码
    if (p_node->left == NULL && p_node->right == NULL)
    {
        cout << p_node->weight << ":" << code << endl;
    }
    else
    {
        // 递归地遍历左右子树，并在当前编码的基础上添加'0'或'1'
        string leftCode = code + "0";
        string rightCode = code + "1";
        printCodes(p_node->left, leftCode);
        printCodes(p_node->right, rightCode);
    }
}

// 树的清理函数(后序遍历)
void deinitTree(Node *root)
{
    if (!root)
    {
        return;
    }
    deinitTree(root->left);
    deinitTree(root->right);
    delete root;
}

// 层次遍历（一层一层遍历）
void levelPrint(HuffmanTree *p_tree)
{
    if (!p_tree)
    {
        cout << "树是空的" << endl;
        return;
    }

    // 创建队列，存储树中每个节点
    queue<Node *> q;
    // 先存储根节点
    q.push(p_tree->root);

    while (!q.empty())
    {
        // 拿到第一个节点
        Node *currentNode = q.front();
        // 将其出队
        q.pop();

        // 访问当前节点
        cout.width(2);
        cout << currentNode->weight << " ";

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

// 主函数示例
int main()
{
    int weight[] = {6, 3, 8, 2, 10, 4};
    // 创建哈夫曼树
    // HuffmanTree *tree = createTree(createNode(weight[0]));
    HuffmanTree *tree = NULL;
    cout << "开始创建..." << std::endl;
    for (int i = 0; i < sizeof(weight) / sizeof(weight[0]); i++)
    {
        // 创建树并插入森林
        insertTree(&tree, createTree(createNode(weight[i])));
    }
    cout << "创建完成！" << std::endl;

    // 选择合并
    while (selectMerge(&tree));

    // 层次遍历
    levelPrint(tree);

    string code = "";
    cout << "哈夫曼编码：" << endl;
    // 打印哈夫曼编码
    printCodes(tree->root, code);

    // 销毁树内节点
    deinitTree(tree->root);
    tree->root = NULL;

    // 销毁树
    delete tree;
    tree = NULL;

    return 0;
}