#include <iostream>   // 提供 cout/endl 用于 createNode(内存失败输出)、levelPrint(节点值输出)
#include <cstdlib>    // 提供 malloc/free/exit 用于 createNode(节点内存分配)、deleteNode(节点释放)
#include <vector>     // 提供动态数组支持 用于 searchAll(存储搜索结果节点指针)
#include <string>    // 提供字符串流功能 用于 parsePreorder(解析逗号分隔输入)
using namespace std;

// 定义二叉树节点结构体
typedef struct TreeNode
{
    int val;                // 节点存储的数据
    int height;             // 记录树的高度
    int count;              // 相同的个数
    int size;               // 该节点为根的子树总节点数
    struct TreeNode *left;  // 指向左子节点的指针
    struct TreeNode *right; // 指向右子节点的指针
} TreeNode;




//#########AVL树辅助函数######
// 创建一个新的二叉树节点
TreeNode *createNode(int value)
{
    // TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode)); // malloc分配内存
    TreeNode *newNode = new TreeNode; // new分配内存
    if (!newNode)
    {
        cout << "申请内存失败" << endl;
        exit(-1);
    }
    newNode->val = value;  // 设置节点值
    newNode->height = 1;   // 新节点的初始高度为1
    newNode->count = 1;    // 默认一个节点的个数是1
    newNode->size = 1;     // 索引序号
    newNode->left = NULL;  // 初始化左子节点指针为NULL
    newNode->right = NULL; // 初始化右子节点指针为NULL
    return newNode;        // 返回新创建的节点
}

// 获取节点的高度
int getHeight(TreeNode *p_tree)
{
    // 空树
    if (!p_tree) return 0;
    // 树的高度
    return p_tree->height;
}

// 获取两个节点中较高的高度
int maxHeight(TreeNode *a, TreeNode *b)
{
    //使用正则匹配
    int ha = a ? a->height : 0;
    int hb = b ? b->height : 0;
    return (ha > hb) ? ha : hb;
}

// 获取节点的平衡因子
int getBalance(TreeNode *p_tree)
{
    if (!p_tree) return 0;
    // 左子树高度 - 右子树高度
    return getHeight(p_tree->left) - getHeight(p_tree->right);
}

// 更新size
void updateSize(TreeNode* node)
{
    if (!node) return;
    node->size = node->count;  // 自身重复次数
    if (node->left) node->size += node->left->size;
    if (node->right) node->size += node->right->size;
}





//#########插入节点######

// 左旋操作:只涉及原根节点的右子树，以及原根节点的右子树的左子树位置变化
void leftRotate(TreeNode **p_tree)
{
    // 1. 记录原根节点的右子树
    TreeNode *rightTree = (*p_tree)->right;
    // 2. 记录原右子树的左子树
    TreeNode *rightTreeLeft = rightTree->left;

    // 执行旋转操作
    // 步骤1: 将原根节点变为右子树的左子节点
    rightTree->left = *p_tree;
    // 步骤2: 将原右子树的左子节点变为原根节点的右子节点
    (*p_tree)->right = rightTreeLeft;

    // 更新受影响节点的高度
    // 原根节点高度需重新计算（原右子树的左子节点已改变）
    (*p_tree)->height = maxHeight((*p_tree)->left, (*p_tree)->right) + 1;
    // 原右子树节点高度需重新计算（新增了左子节点）
    rightTree->height = maxHeight(rightTree->left, rightTree->right) + 1;

    // 更新节点大小
    updateSize(*p_tree);
    updateSize(rightTree);


    // 更新全局根节点指针
    *p_tree = rightTree;
}

// 右旋操作:只涉及原根节点的左子树，以及原根节点的左子树的右子树位置变化
void rightRotate(TreeNode **p_tree)
{
    // 1. 记录原根节点的左子树
    TreeNode *leftTree = (*p_tree)->left;
    // 2. 记录原左子树的右子树
    TreeNode *leftTreeRight = leftTree->right;

    // 执行旋转操作
    // 步骤1: 将原根节点变为左子树的右子节点
    leftTree->right = *p_tree;
    // 步骤2: 将原左子树的右子节点变为原根节点的左子节点
    (*p_tree)->left = leftTreeRight;

    // 更新受影响节点的高度
    // 原根节点高度需重新计算（原左子树的右子节点已改变）
    (*p_tree)->height = maxHeight((*p_tree)->left, (*p_tree)->right) + 1;
    // 原左子树节点高度需重新计算（新增了右子节点）
    leftTree->height = maxHeight(leftTree->left, leftTree->right) + 1;

     // 更新节点大小
    updateSize(*p_tree);
    updateSize(leftTree);

    // 更新全局根节点指针
    *p_tree = leftTree;
}


// 在有序二叉树里插入节点(递归方式)
void insertNodeRec(TreeNode **root, int value)
{
    // 1. 正常的插入
    // 遇到空节点，则作为根节点插入
    if (!*root)
    {
        *root = createNode(value);
        return;
    }
    // 不为空，则判断往左还是右子树遍历
    // 允许重复值插入左子树
    if (value == (*root)->val)
    {
        (*root)->count++;  // 增加相同值的计数
    }

    else if (value < (*root)->val){
        insertNodeRec(&(*root)->left, value);}
    else{
        insertNodeRec(&(*root)->right, value);}


    // 更新根节点的高度
    (*root)->height = maxHeight((*root)->left, (*root)->right) + 1;
    updateSize(*root);//更新节点大小

    // 检查是否平衡并修复
    int balance = getBalance(*root);

    // LL
    if (balance > 1 && value <= (*root)->left->val)
    {
        // 右旋
        cout << "插入数字" <<value<< "后为LL型,进行右旋操作" << endl;
        rightRotate(root);
    }

    // RR
    else if (balance < -1 && value > (*root)->right->val)
    {
        // 左旋
        cout << "插入数字" <<value<< "后为RR型,进行左旋操作" << endl;
        leftRotate(root);
    }

    // LR
    else if (balance > 1 && value > (*root)->left->val)
    {
        cout << "插入数字" <<value<< "后为LR型,先进行左旋再右旋操作" << endl;
        // 对被破坏节点的左孩子进行左旋
        leftRotate(&(*root)->left);
        // 右旋
        rightRotate(root);
    }

    // RL
    else if (balance < -1 && value <= (*root)->right->val)
    {
        cout << "插入数字" <<value<< "后为RL型,进行右旋再左旋操作" << endl;
        // 对被破坏节点的右孩子进行右旋
        rightRotate(&(*root)->right);
        // 左旋
        leftRotate(root);
    }
}





//#########功能函数#######
// 递归法中序遍历（左子树 -> 根节点 -> 右子树）

void inOrderPrint(TreeNode *root)
{
    if (!root) return;
    inOrderPrint(root->left);// 访问左子树
    cout << root->val;
    if (root->count > 1) cout << "(" << root->count << ")";// 访问当前节点
    cout << " ";
    inOrderPrint(root->right);// 访问右子树
}

// 搜索所有匹配节点（包括重复）
void searchAll(TreeNode* root, int value, vector<TreeNode*>& results)
{
    if (!root) return;
    if (root->val == value) results.push_back(root);
    searchAll(root->left, value, results);
    searchAll(root->right, value, results);
}

// 检查树是否为AVL树
bool isAVLTree(TreeNode* root) {
    if (!root) return true;

    // 检查当前节点平衡因子
    int balance = getBalance(root);
    //只需检查平衡因子的绝对值
    if (abs(balance) > 1) return false;

    // 递归检查左右子树
    return isAVLTree(root->left) && isAVLTree(root->right);
}







//######打印树形结构########

// 获取树的高度（用于打印）
int treeHeight(TreeNode* root)
{
    if (!root) return 0;
    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

// 打印树形结构
void printTree(TreeNode* root, int space = 0, int height = 0, bool isLeft = false, bool isRoot = true)
{
    if (!root) return;
    // 获取树的高度
    if (height == 0) height = treeHeight(root);
    // 计算缩进空格，每多一层，缩进空格数增加1
    space += height;

    // 先递归打印右子树
    printTree(root->right, space, height - 1, false, false);

    // 打印当前节点
    for (int i = height; i < space; i++) {
        cout << "  ";
    }

    // 根节点特殊处理
    if (isRoot)
    {
        cout << "      " <<root->val;  // 根节点不加前缀
        if(root->count > 1) cout << "(" << root->count << ")";
    }
    else
    {
        if (isLeft) {
            cout << " └─" << root->val;
            if(root->count > 1) cout << "(" << root->count << ")";
        } else {
            cout << " ┌─" << root->val;
            if(root->count > 1) cout << "(" << root->count << ")";
        }
    }
    cout << "\n";

    // 递归打印左子树
    printTree(root->left, space, height - 1, true, false);
}







//########AVL树判别程序##########
// 解析先序序列为整数数组
vector<int> parsePreorder(const string& input)
{
    vector<int> result;
    if (input.empty()) return result;  // 处理空输入

    size_t start = 0;
    size_t end = input.find(',');

    // 逐个处理每个由逗号分隔的token，并尝试转换为整数
    // 无效或无法转换的token将被忽略
    while (end != string::npos) {
        string token = input.substr(start, end - start);
        if (!token.empty())
        {
            try {
                result.push_back(stoi(token)); 
            } catch (...) {
                // 忽略无效输入
            }
        }
        start = end + 1;
        end = input.find(',', start);
    }

    // 处理输入字符串末尾的最后一个token，并尝试转换为整数
    // 无效或无法转换的token将被忽略
    if (start < input.length()) {
        string token = input.substr(start);
        if (!token.empty()) {
            try {
                result.push_back(stoi(token));
            } catch (...) {
                // 忽略无效输入
            }
        }
    }

    return result;
}


// 根据前序遍历序列重建二叉搜索树BST
TreeNode* buildTreeFromPreorder(vector<int>& preorder, int& index, int min, int max)
{
    // 终止条件：索引越界时返回空指针
    if (index >= preorder.size()) return NULL;

    int val = preorder[index];
    // 当前值超出有效范围时返回空指针（维护二叉搜索树性质）
    if (val < min || val > max) return NULL;

    // 创建当前根节点并递增索引
    TreeNode* root = createNode(val);
    index++;

    // 递归构建左右子树：
    // 左子树所有节点值必须小于当前根节点值
    root->left = buildTreeFromPreorder(preorder, index, min, val);
    // 右子树所有节点值必须大于当前根节点值
    root->right = buildTreeFromPreorder(preorder, index, val, max);

    // 更新节点高度
    root->height = maxHeight(root->left, root->right) + 1;
    // 更新子树大小
    updateSize(root);
    

    return root;
}









//######删除和清除######
// 辅助函数，用于找到树中的最小节点
TreeNode *findMin(TreeNode *root)
{
    while (root->left) root = root->left;
    return root;
}

// 删除节点
void deleteNode(TreeNode **root, int key)
{
    if (*root == NULL) return;

    // 如果要删除的节点在左子树中
    if (key < (*root)->val)
        deleteNode(&((*root)->left), key);
    // 如果要删除的节点在右子树中
    else if (key > (*root)->val)
        deleteNode(&((*root)->right), key);
    // 如果找到了要删除的节点
    else
    {
        // 处理有重复值的情况
        if ((*root)->count > 1)
        {
            (*root)->count--;  // 减少计数而不是删除节点
            updateSize(*root);
            return;
        }


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
    if (*root == NULL) return;

    // 与插入逻辑一模一样
    //  更新高度
    (*root)->height = 1 + maxHeight((*root)->left, (*root)->right);
    // 获取平衡因子
    int balance = getBalance((*root));

    // 平衡因子大于1（LL型）
    if (balance > 1 && getBalance((*root)->left) >= 0)
    {
        cout << "删除值为" << key << "的节点时,节点" << (*root)->val << "为LL型,执行右旋操作" << endl;
        rightRotate(root);
        return;
    }

    // 平衡因子大于1且左子树的平衡因子小于0（LR型）
    else if (balance > 1 && getBalance((*root)->left) < 0)
    {
        cout << "删除值为" << key << "的节点时,节点" << (*root)->val << "为LR型,执行右旋操作" << endl;
        cout << "LR" << endl;
        leftRotate(&(*root)->left);
        rightRotate(root);
        return;
    }

    // 平衡因子小于-1（RR型）
    else if (balance < -1 && getBalance((*root)->right) <= 0)
    {
        cout << "删除值为" << key << "的节点时,节点" << (*root)->val << "为RR型,执行左旋操作" << endl;
        leftRotate(root);
        return;
    }

    // 平衡因子小于-1且右子树的平衡因子大于0（RL型）
    else if (balance < -1 && getBalance((*root)->right) > 0)
    {
        cout << "删除值为" << key << "的节点时,节点" << (*root)->val << "为RL型,执行左旋操作" << endl;
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








//######索引搜索（中序搜索->下标搜索）########
TreeNode* indexSearch(TreeNode* root, int index)
{
    // 处理终止条件：根节点为空或索引超出有效范围
    if (!root || index <= 0 || index > root->size)
        return NULL;// 如果索引超出范围

    // 获取左子树节点数量
    int leftSize = root->left ? root->left->size : 0;

    // 如果索引小于等于左子树节点数量，则继续在左子树中查找
    if (index <= leftSize)
        return indexSearch(root->left, index);
    
    // 处理当前节点命中情况
    else if (index <= leftSize + root->count)
        return root;
    
    // 处理右子树递归情况（需调整索引值）
    else
        return indexSearch(root->right, index - leftSize - root->count);
}

// 索引删除
void indexDelete(TreeNode** root, int index)
{
    TreeNode* node = indexSearch(*root, index);
    if (node)
        deleteNode(root, node->val);
}








int main()
{
    TreeNode *root = nullptr;



    // cout << "默认插入数组{1,2,3,5,7,8,9}" << endl;
    // insertNodeRec(&root, 1);
    // insertNodeRec(&root, 2);
    // insertNodeRec(&root, 3);//LL型
    // insertNodeRec(&root, 5);
    // insertNodeRec(&root, 7);
    // insertNodeRec(&root, 8);//RR型
    // insertNodeRec(&root, 9);
    // printTree(root);



    while (true)
    {
        cout << "\n************AVL树操作菜单************\n"
             << "1. 创建AVL树(插入多个值)\n"
             << "2. 插入节点\n"
             << "3. 删除节点\n"
             << "4. 按值搜索\n"
             << "5. 按索引搜索\n"
             << "6. 按索引删除\n"
             << "7. 中序遍历(Ascend)\n"
             << "8. 打印树结构\n"
             << "9. 根据先序序列构建BST并检查是否为AVL\n"
             << "0. 退出\n"
             << "请选择操作: ";

        //分别记录用户操作选择，输入的值和索引
        int choice, value, index;
        string input;//保存输入的字符串
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cout << "请输入要插入的值(英文逗号分隔): ";
                cin.ignore(); //清除输入缓冲区残留的换行符，防止后续getline异常终止
                getline(cin, input); //获取输入存入input
                vector<int> values = parsePreorder(input); //将字符串转换成vector
                for (int val : values) {insertNodeRec(&root, val);}//循环插入节点
                cout << "AVL树创建完成\n";
                printTree(root);
                break;
            }
            case 2:
            {
                cout << "请输入要插入的值: ";
                cin >> value;
                insertNodeRec(&root, value);
                cout << "插入后的树结构:\n";
                printTree(root);
                break;
            }
            case 3:
            {
                cout << "请输入要删除的值: ";
                cin >> value;
                deleteNode(&root, value);
                cout << "删除后的树结构:\n";
                printTree(root);
                break;
            }
            case 4:
            {
                cout << "请输入要搜索的值: ";
                cin >> value;
                vector<TreeNode*> results;
                searchAll(root, value, results);
                if (results.empty()) {
                    cout << "未找到值为 " << value << " 的节点\n";
                } else {
                    cout << "找到 " << results.size() << " 个值为 " << value << " 的节点\n";
                    for (int i = 0; i < results.size(); i++) {
                        cout << "节点" << i+1 << ": 值=" << results[i]->val
                             << ", 计数=" << results[i]->count << endl;
                    }
                }
                break;
            }
            case 5:
            {
                cout << "请输入要搜索的索引(1-" << (root ? root->size : 0) << "): ";
                cin >> index;
                TreeNode* node = indexSearch(root, index);
                if (node) {
                    cout << "索引 " << index << " 对应的节点值: " << node->val;
                    if (node->count > 1) cout << " (计数:" << node->count << ")";
                    cout << endl;
                } else {
                    cout << "无效索引!" << endl;
                }
                break;
            }
            case 6:
            {
                cout << "请输入要删除的索引(1-" << (root ? root->size : 0) << "): ";
                cin >> index;
                indexDelete(&root, index);
                cout << "索引删除后的树结构:\n";
                printTree(root);
                break;
            }
            case 7:
            {
                cout << "中序遍历结果: ";
                inOrderPrint(root);
                cout << endl;
                break;
            }
            case 8:
            {
                printTree(root);
                break;
            }
            case 9:
            {
                cout << "请输入先序序列(英文逗号分隔): ";
                cin.ignore();
                getline(cin, input);
                vector<int> preorder = parsePreorder(input);
                int idx = 0;
                TreeNode* bstRoot = buildTreeFromPreorder(preorder, idx, INT_MIN, INT_MAX);

                cout << "构建的BST树结构:\n";
                printTree(bstRoot);

                if (isAVLTree(bstRoot)) cout << "该BST是一棵AVL树\n";
                    else cout << "该BST不是AVL树\n";

                deinitTree(bstRoot);
                break;
            }
            case 0:
            {
                deinitTree(root);
                cout << "程序已退出\n";
                return 0;
            }
            default:
                cout << "无效选择!\n";
        }
    }
}



/*// 测试代码
int main()
{
    // 初始化根节点为NULL
    TreeNode *root = NULL;
    // 依次递归插入5，2，1，3，7，8


    //1.依次手动输入
    cout << "请输入要插入的数字的个数：" << endl;
    int n;
    cin >> n ;
    cout << "请依次输入"<< n <<"个要插入AVL树的数字：" << endl;
    int val;
    for(int i = 0; i < n; i++)
    {
        cout<<"请输入第"<<i+1<<"个数字："<<endl;
        cin>>val;
        insertNodeRec(&root, val);
    }
    cout << "插入完毕，请查看结果：" << endl;
    printTree(root);


    // //2.逐个自动输入
    // cout << "默认插入数组{5,2,1,3,7,8,9}" << endl;
    // insertNodeRec(&root, 5);
    // insertNodeRec(&root, 2);
    // insertNodeRec(&root, 1);//LL型
    // insertNodeRec(&root, 3);
    // insertNodeRec(&root, 7);
    // insertNodeRec(&root, 8);//RR型
    // insertNodeRec(&root, 9);
    // printTree(root);


    // //3.打印逐个自动输入各阶段
    // cout << "默认插入数组{5,2,1,3,7,8}" << endl;
    // int val[] = {5,2,1,3,7,8};
    // int length = sizeof(val) / sizeof(val[0]); // 计算数组长度
    // for(int i = 0; i < length; i++)
    // {
    //     insertNodeRec(&root, val[i]);
    //     printTree(root);
    //     cout << "-----------------------------------------" <<endl;
    // }



    // cout << "中序遍历:";
    // inOrderPrint(root);
    // cout << endl;

    deinitTree(root);
    root = NULL;

    return 0;
}

*/