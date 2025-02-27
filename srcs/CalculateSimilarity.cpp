#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 计算最长公共子串长度（使用动态规划）
int longestCommonSubstring(const string& str1, const string& str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
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
string readTextFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }

    string text;
    string line;
    while (getline(file, line)) {
        text += line + " ";
    }
    file.close();

    return text;
}

// 计算文本相似度（直接比较整段文字）
double calculateSimilarity(const string& file1, const string& file2) {
    string paragraph1 = readTextFromFile(file1);
    string paragraph2 = readTextFromFile(file2);

    if (paragraph1.empty() || paragraph2.empty()) {
        cerr << "One or both files are empty." << endl;
        return 0.0;
    }

    // 计算最长公共子串长度
    int maxCommonLen = longestCommonSubstring(paragraph1, paragraph2);

    // 计算相似度
    double similarity = static_cast<double>(maxCommonLen) / max(paragraph1.length(), paragraph2.length());

    return similarity;
}
