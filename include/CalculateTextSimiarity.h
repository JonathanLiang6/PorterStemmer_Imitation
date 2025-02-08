#ifndef CALCULATE_TEXT_SIMILARITY_H
#define CALCULATE_TEXT_SIMILARITY_H

#include <vector>
#include <cmath>
#include <unordered_map>
#include <string>

#include "WordTable.h"
#include "Textprocessor.h"

// ����������Ӵ����ȣ�ʹ�ö�̬�滮��
int longestCommonSubstring(const std::string& str1, const std::string& str2);

// ���ļ��ж�ȡ�ı�
std::string readTextFromFile(const std::string& filename);

// �����ı����ƶȣ�ֱ�ӱȽ��������֣�
double calculateSimilarity(const std::string& file1, const std::string& file2);

// ���������ĵ��
double dotProduct(std::vector<double>& a, std::vector<double>& b);

// ����������ģ
double getModule(std::vector<double>& vec);

// ���������������������ƶ�
double getSimilarity(const std::vector<double>& a, const std::vector<double>& b);

// �����������ʱ���������ƶ�
double calculateSimilarity(TextProcessor& wordTable1, TextProcessor& wordTable2);

#endif // CALCULATE_TEXT_SIMILARITY_H
