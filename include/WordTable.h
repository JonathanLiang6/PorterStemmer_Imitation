#ifndef WORDTABLE_H
#define WORDTABLE_H

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

struct WordInfo {
    std::string word;  // ����
    int frequency;     // Ƶ��
    WordInfo(const std::string& w) : word(w), frequency(1) {}
};

struct TreeNode {
    WordInfo data;          // ������Ϣ
    TreeNode* left;
    TreeNode* right;
    int height;             // �ڵ�߶�
    TreeNode(const std::string& w) : data(w), left(nullptr), right(nullptr), height(1) {}
};

class WordTable {
private:
    TreeNode* root;

    // ˽�г�Ա��������
    int getHeight(TreeNode* node);
    void updateHeight(TreeNode* node);
    TreeNode* rightRotate(TreeNode* y);
    TreeNode* leftRotate(TreeNode* x);
    int getBalance(TreeNode* node);
    TreeNode* insert(TreeNode* node, const std::string& word);
    void printHelper(TreeNode* node);
    void deleteTree(TreeNode* node);
    int searchhelper(TreeNode* node, const std::string& word);
    void getVec(TreeNode* node, std::vector<std::string>& words, std::vector<int>& frequencies);

public:
    WordTable() : root(nullptr) {}
    ~WordTable();
    void insert(const std::string& word);
    void print();
    int search(const std::string& word);
    TreeNode* getRoot();
    void getVector(std::vector<std::string>& words, std::vector<int>& frequencies);
};

#endif // WORDTABLE_H