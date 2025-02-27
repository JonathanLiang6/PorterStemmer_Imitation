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

// ����������Ӵ����ȣ�ʹ�ö�̬�滮��
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

// ���ļ��ж�ȡ�ı�
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

// �����ı����ƶȣ�ֱ�ӱȽ��������֣�
double calculateSimilarity(const std::string& file1, const std::string& file2) {
    std::string paragraph1 = readTextFromFile(file1);
    std::string paragraph2 = readTextFromFile(file2);

    if (paragraph1.empty() || paragraph2.empty()) {
        std::cerr << "One or both files are empty." << std::endl;
        return 0.0;
    }

    // ����������Ӵ�����
    int maxCommonLen = longestCommonSubstring(paragraph1, paragraph2);

    // �������ƶ�
    double similarity = static_cast<double>(maxCommonLen) / max(paragraph1.length(), paragraph2.length());

    return similarity;
}

// �������������ĵ��
double dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    double dot = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        dot += a[i] * b[i];
    }
    return dot;
}

// ����������ģ
double getModule(const std::vector<double>& vec) {
    double v_sum = 0.0;
    for (double value : vec) {
        v_sum += value * value;
    }
    return std::sqrt(v_sum);
}

// ���������������������ƶ�
double getSimilarity(const std::vector<double>& a, const std::vector<double>& b) {
    double ab_sum = dotProduct(a, b);
    double a_sum = getModule(a);
    double b_sum = getModule(b);
    return ab_sum / (a_sum * b_sum);
}

// �����������ʱ���������ƶ�
double calculateSimilarity(TextProcessor& wordTable1, TextProcessor& wordTable2) {
    std::vector<std::string> words1, words2;
    std::vector<int> freq1, freq2;

    wordTable1.getVector(words1, freq1);
    wordTable2.getVector(words2, freq2);

    // ���� unordered_map �����е��ʺϲ���һ��������
    std::unordered_map<std::string, int> wordIndex;
    int index = 0; // index Ϊ��ֵ
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

    // ����Ƶ������
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