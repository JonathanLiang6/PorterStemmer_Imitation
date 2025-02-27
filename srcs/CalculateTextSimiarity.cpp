#include <vector>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "../include/WordTable.h"
#include "../include/calculateTextsimiarity.h"
#include "../include/Textprocessor.h"

// 计算最长公共子串长度（使用动态规划）
int longestCommonSubstring(const std::string& str1, const std::string& str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));
    int maxLen = 0;

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                maxLen = max(maxLen, dp[i][j]);
            }
            else {
                dp[i][j] = 0;
            }
        }
    }

    return maxLen;
}

// 从文件中读取文本
std::string readTextFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
    }

    std::string text;
    std::string line;
    while (std::getline(file, line)) {
        text += line + " ";
    }
    file.close();

    return text;
}

// 计算文本相似度（直接比较整段文字）
double calculateSimilarity(const std::string& file1, const std::string& file2) {
    std::string paragraph1 = readTextFromFile(file1);
    std::string paragraph2 = readTextFromFile(file2);

    if (paragraph1.empty() || paragraph2.empty()) {
        std::cerr << "One or both files are empty." << std::endl;
        return 0.0;
    }

    // 计算最长公共子串长度
    int maxCommonLen = longestCommonSubstring(paragraph1, paragraph2);

    // 计算相似度
    double similarity = static_cast<double>(maxCommonLen) / max(paragraph1.length(), paragraph2.length());

    return similarity;
}

// 计算两个向量的点积
double dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    double dot = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        dot += a[i] * b[i];
    }
    return dot;
}

// 计算向量的模
double getModule(const std::vector<double>& vec) {
    double v_sum = 0.0;
    for (double value : vec) {
        v_sum += value * value;
    }
    return std::sqrt(v_sum);
}

// 计算两个向量的余弦相似度
double getSimilarity(const std::vector<double>& a, const std::vector<double>& b) {
    double ab_sum = dotProduct(a, b);
    double a_sum = getModule(a);
    double b_sum = getModule(b);
    return ab_sum / (a_sum * b_sum);
}

// 计算两个单词表的余弦相似度
double calculateSimilarity(TextProcessor& wordTable1, TextProcessor& wordTable2) {
    std::vector<std::string> words1, words2;
    std::vector<int> freq1, freq2;

    wordTable1.getVector(words1, freq1);
    wordTable2.getVector(words2, freq2);

    // 利用 unordered_map 将所有单词合并到一个集合中
    std::unordered_map<std::string, int> wordIndex;
    int index = 0; // index 为键值
    for (const auto& word : words1) {
        if (wordIndex.find(word) == wordIndex.end()) {
            wordIndex[word] = index++;
        }
    }
    for (const auto& word : words2) {
        if (wordIndex.find(word) == wordIndex.end()) {
            wordIndex[word] = index++;
        }
    }

    // 构建频率向量
    std::vector<double> vec1(index, 0), vec2(index, 0);
    for (size_t i = 0; i < words1.size(); ++i) {
        vec1[wordIndex[words1[i]]] = freq1[i];
    }
    for (size_t i = 0; i < words2.size(); ++i) {
        vec2[wordIndex[words2[i]]] = freq2[i];
    }
    double cosine = getSimilarity(vec1, vec2);
    return cosine;
}