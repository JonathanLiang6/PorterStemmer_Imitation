#ifndef CALCULATE_TEXT_SIMILARITY_H
#define CALCULATE_TEXT_SIMILARITY_H

#include <vector>
#include <cmath>
#include <unordered_map>
#include <string>

#include "WordTable.h"
#include "Textprocessor.h"

// 计算最长公共子串长度（使用动态规划）
int longestCommonSubstring(const std::string& str1, const std::string& str2);

// 从文件中读取文本
std::string readTextFromFile(const std::string& filename);

// 计算文本相似度（直接比较整段文字）
double calculateSimilarity(const std::string& file1, const std::string& file2);

// 计算向量的点积
double dotProduct(std::vector<double>& a, std::vector<double>& b);

// 计算向量的模
double getModule(std::vector<double>& vec);

// 计算两个向量的余弦相似度
double getSimilarity(const std::vector<double>& a, const std::vector<double>& b);

// 计算两个单词表的余弦相似度
double calculateSimilarity(TextProcessor& wordTable1, TextProcessor& wordTable2);

#endif // CALCULATE_TEXT_SIMILARITY_H
