#include "../include/WordTable.h"

// ��ȡ�ڵ�ĸ߶�
int WordTable::getHeight(TreeNode* node) {
    if (node == nullptr) {
        return 0;  // �սڵ�߶�Ϊ0
    }
    return node->height;  // ���ؽڵ�ĸ߶�
}

// ���½ڵ�ĸ߶�
void WordTable::updateHeight(TreeNode* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));  // �ڵ�߶ȵ������������߶ȵ����ֵ��1
}

// ��������
TreeNode* WordTable::rightRotate(TreeNode* y) {
    TreeNode* x = y->left;  // x��y�����ӽڵ�
    TreeNode* T2 = x->right;  // T2��x�����ӽڵ�

    // ִ����ת
    x->right = y;
    y->left = T2;

    // ���¸߶�
    updateHeight(y);
    updateHeight(x);

    return x;  // �����µĸ��ڵ�x
}

// ��������
TreeNode* WordTable::leftRotate(TreeNode* x) {
    TreeNode* y = x->right;  // y��x�����ӽڵ�
    TreeNode* T2 = y->left;  // T2��y�����ӽڵ�

    // ִ����ת
    y->left = x;
    x->right = T2;

    // ���¸߶�
    updateHeight(x);
    updateHeight(y);

    return y;  // �����µĸ��ڵ�y
}

// ��ȡ�ڵ��ƽ������
int WordTable::getBalance(TreeNode* node) {
    if (node == nullptr) {
        return 0;  // �սڵ�ƽ������Ϊ0
    }
    return getHeight(node->left) - getHeight(node->right);  // �������߶ȼ�ȥ�������߶�
}

// ����ڵ�
TreeNode* WordTable::insert(TreeNode* node, const std::string& word) {
    if (node == nullptr) {
        return new TreeNode(word);  // �����½ڵ�
    }

    if (word < node->data.word) {
        node->left = insert(node->left, word);  // ����������
    }
    else if (word > node->data.word) {
        node->right = insert(node->right, word);  // ����������
    }
    else {
        // �����Ѵ��ڣ�����Ƶ��
        node->data.frequency++;
        return node;
    }

    // �������Ƚڵ�ĸ߶�
    updateHeight(node);

    // ��ȡ���Ƚڵ��ƽ�����ӣ����ڵ��Ƿ�ʧ��
    int balance = getBalance(node);

    // ����ڵ�ʧ�⣬��4�����

    // �������
    if (balance > 1 && word < node->left->data.word) {
        return rightRotate(node);
    }

    // �������
    if (balance < -1 && word > node->right->data.word) {
        return leftRotate(node);
    }

    // �������
    if (balance > 1 && word > node->left->data.word) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // �������
    if (balance < -1 && word < node->right->data.word) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // ����δ�ı�Ľڵ�ָ��
    return node;
}

// ��ӡ���ʱ�
void WordTable::print() {
    printHelper(root);  // ���ø���������ӡ
}

// �������������ڵݹ��ӡ���ʱ�
void WordTable::printHelper(TreeNode* node) {
    if (node == nullptr) {
        return;  // �սڵ�ֱ�ӷ���
    }
    printHelper(node->left);  // �ȴ�ӡ������
    std::cout << node->data.word << " : " << node->data.frequency << std::endl;  // ��ӡ��ǰ�ڵ�
    Sleep(500);  // ��ͣ500����
    printHelper(node->right);  // �ٴ�ӡ������
}

// �������ʵĸ�������
int WordTable::searchhelper(TreeNode* node, const std::string& word) {
    if (node == nullptr) {
        return 0;  // δ�ҵ�����0
    }

    if (word < node->data.word) {
        return searchhelper(node->left, word);  // ������������
    }
    else if (word > node->data.word) {
        return searchhelper(node->right, word);  // ������������
    }
    else {
        return node->data.frequency;  // �ҵ�����Ƶ��
    }
}

// ��������
int WordTable::search(const std::string& word) {
    return searchhelper(root, word);  // ���ø�����������
}

// ��ȡ���ڵ�
TreeNode* WordTable::getRoot() {
    return root;
}

// �����������ͷ��ڴ�
WordTable::~WordTable() {
    deleteTree(root);  // �ݹ�ɾ����
}

// �ݹ�ɾ����
void WordTable::deleteTree(TreeNode* node) {
    if (node == nullptr) {
        return;  // �սڵ�ֱ�ӷ���
    }
    deleteTree(node->left);  // ��ɾ��������
    deleteTree(node->right);  // ��ɾ��������
    delete node;  // ɾ����ǰ�ڵ�
}

// ���뵥��
void WordTable::insert(const std::string& word) {
    root = insert(root, word);  // ���ò��뺯�������¸��ڵ�
}

// ��ȡ���ʺ�Ƶ�ʵ�����
void WordTable::getVector(std::vector<std::string>& words, std::vector<int>& frequencies) {
    getVec(root, words, frequencies);  // ���ø���������ȡ
}

// �������������ڵݹ��ȡ���ʺ�Ƶ�ʵ�����
void WordTable::getVec(TreeNode* node, std::vector<std::string>& words, std::vector<int>& frequencies) {
    if (!node) return;  // �սڵ�ֱ�ӷ���
    getVec(node->left, words, frequencies);  // �ȴ���������
    words.push_back(node->data.word);  // ��ӵ���
    frequencies.push_back(node->data.frequency);  // ���Ƶ��
    getVec(node->right, words, frequencies);  // �ٴ���������
}