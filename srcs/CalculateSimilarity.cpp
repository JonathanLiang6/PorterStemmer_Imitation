#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ����������Ӵ����ȣ�ʹ�ö�̬�滮��
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

// ���ļ��ж�ȡ�ı�
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

// �����ı����ƶȣ�ֱ�ӱȽ��������֣�
double calculateSimilarity(const string& file1, const string& file2) {
    string paragraph1 = readTextFromFile(file1);
    string paragraph2 = readTextFromFile(file2);

    if (paragraph1.empty() || paragraph2.empty()) {
        cerr << "One or both files are empty." << endl;
        return 0.0;
    }

    // ����������Ӵ�����
    int maxCommonLen = longestCommonSubstring(paragraph1, paragraph2);

    // �������ƶ�
    double similarity = static_cast<double>(maxCommonLen) / max(paragraph1.length(), paragraph2.length());

    return similarity;
}
