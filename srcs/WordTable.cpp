#include "../include/WordTable.h"

// 获取节点的高度
int WordTable::getHeight(TreeNode* node) {
    if (node == nullptr) {
        return 0;  // 空节点高度为0
    }
    return node->height;  // 返回节点的高度
}

// 更新节点的高度
void WordTable::updateHeight(TreeNode* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));  // 节点高度等于左右子树高度的最大值加1
}

// 右旋操作
TreeNode* WordTable::rightRotate(TreeNode* y) {
    TreeNode* x = y->left;  // x是y的左子节点
    TreeNode* T2 = x->right;  // T2是x的右子节点

    // 执行旋转
    x->right = y;
    y->left = T2;

    // 更新高度
    updateHeight(y);
    updateHeight(x);

    return x;  // 返回新的根节点x
}

// 左旋操作
TreeNode* WordTable::leftRotate(TreeNode* x) {
    TreeNode* y = x->right;  // y是x的右子节点
    TreeNode* T2 = y->left;  // T2是y的左子节点

    // 执行旋转
    y->left = x;
    x->right = T2;

    // 更新高度
    updateHeight(x);
    updateHeight(y);

    return y;  // 返回新的根节点y
}

// 获取节点的平衡因子
int WordTable::getBalance(TreeNode* node) {
    if (node == nullptr) {
        return 0;  // 空节点平衡因子为0
    }
    return getHeight(node->left) - getHeight(node->right);  // 左子树高度减去右子树高度
}

// 插入节点
TreeNode* WordTable::insert(TreeNode* node, const std::string& word) {
    if (node == nullptr) {
        return new TreeNode(word);  // 创建新节点
    }

    if (word < node->data.word) {
        node->left = insert(node->left, word);  // 插入左子树
    }
    else if (word > node->data.word) {
        node->right = insert(node->right, word);  // 插入右子树
    }
    else {
        // 单词已存在，增加频率
        node->data.frequency++;
        return node;
    }

    // 更新祖先节点的高度
    updateHeight(node);

    // 获取祖先节点的平衡因子，检查节点是否失衡
    int balance = getBalance(node);

    // 如果节点失衡，有4种情况

    // 左左情况
    if (balance > 1 && word < node->left->data.word) {
        return rightRotate(node);
    }

    // 右右情况
    if (balance < -1 && word > node->right->data.word) {
        return leftRotate(node);
    }

    // 左右情况
    if (balance > 1 && word > node->left->data.word) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // 右左情况
    if (balance < -1 && word < node->right->data.word) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // 返回未改变的节点指针
    return node;
}

// 打印单词表
void WordTable::print() {
    printHelper(root);  // 调用辅助函数打印
}

// 辅助函数，用于递归打印单词表
void WordTable::printHelper(TreeNode* node) {
    if (node == nullptr) {
        return;  // 空节点直接返回
    }
    printHelper(node->left);  // 先打印左子树
    std::cout << node->data.word << " : " << node->data.frequency << std::endl;  // 打印当前节点
    Sleep(500);  // 暂停500毫秒
    printHelper(node->right);  // 再打印右子树
}

// 搜索单词的辅助函数
int WordTable::searchhelper(TreeNode* node, const std::string& word) {
    if (node == nullptr) {
        return 0;  // 未找到返回0
    }

    if (word < node->data.word) {
        return searchhelper(node->left, word);  // 在左子树搜索
    }
    else if (word > node->data.word) {
        return searchhelper(node->right, word);  // 在右子树搜索
    }
    else {
        return node->data.frequency;  // 找到返回频率
    }
}

// 搜索单词
int WordTable::search(const std::string& word) {
    return searchhelper(root, word);  // 调用辅助函数搜索
}

// 获取根节点
TreeNode* WordTable::getRoot() {
    return root;
}

// 析构函数，释放内存
WordTable::~WordTable() {
    deleteTree(root);  // 递归删除树
}

// 递归删除树
void WordTable::deleteTree(TreeNode* node) {
    if (node == nullptr) {
        return;  // 空节点直接返回
    }
    deleteTree(node->left);  // 先删除左子树
    deleteTree(node->right);  // 再删除右子树
    delete node;  // 删除当前节点
}

// 插入单词
void WordTable::insert(const std::string& word) {
    root = insert(root, word);  // 调用插入函数，更新根节点
}

// 获取单词和频率的向量
void WordTable::getVector(std::vector<std::string>& words, std::vector<int>& frequencies) {
    getVec(root, words, frequencies);  // 调用辅助函数获取
}

// 辅助函数，用于递归获取单词和频率的向量
void WordTable::getVec(TreeNode* node, std::vector<std::string>& words, std::vector<int>& frequencies) {
    if (!node) return;  // 空节点直接返回
    getVec(node->left, words, frequencies);  // 先处理左子树
    words.push_back(node->data.word);  // 添加单词
    frequencies.push_back(node->data.frequency);  // 添加频率
    getVec(node->right, words, frequencies);  // 再处理右子树
}