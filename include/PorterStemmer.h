#ifndef PORTERSTEMMER_H
#define PORTERSTEMMER_H

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

class PorterStemmer {
public:
    // ����任�����ֵ��ʼ��
    PorterStemmer();

    // �ӿڣ����ڵ��ô�����
    std::string stem(std::string word);

private:
    // ����任�����ֵ�
    std::unordered_map<std::string, std::string> dictionary;
    // Ԥ��������
    bool isConsonant(char ch);
    bool endsWith(const std::string& word, const std::string& suffix);
    bool isStressedClosedSyllable(const std::string& word);
    void replaceEnd(std::string& word, const std::string& suffix, const std::string& replacement);
    int getMeasure(const std::string& word);

    // ���崦����
    void step1a(std::string& word);
    void step1b(std::string& word);
    void step2a(std::string& word);
    void step2b(std::string& word);
    void step3(std::string& word);
    void step4(std::string& word);
};
#endif // PORTERSTEMMER_H