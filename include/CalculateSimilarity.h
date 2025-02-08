#pragma once

#include <string>

// 计算最长公共子串长度（使用动态规划）
int longestCommonSubstring(const std::string& str1, const std::string& str2);

// 从文件中读取文本
std::string readTextFromFile(const std::string& filename);

// 计算文本相似度（直接比较整段文字）
double calculateSimilarity(const std::string& file1, const std::string& file2);


