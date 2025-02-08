#ifndef PORTERSTEMMER_H
#define PORTERSTEMMER_H

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

class PorterStemmer {
public:
    // 特殊变换所需字典初始化
    PorterStemmer();

    // 接口，用于调用处理方法
    std::string stem(std::string word);

private:
    // 特殊变换所需字典
    std::unordered_map<std::string, std::string> dictionary;
    // 预备处理函数
    bool isConsonant(char ch);
    bool endsWith(const std::string& word, const std::string& suffix);
    bool isStressedClosedSyllable(const std::string& word);
    void replaceEnd(std::string& word, const std::string& suffix, const std::string& replacement);
    int getMeasure(const std::string& word);

    // 具体处理步骤
    void step1a(std::string& word);
    void step1b(std::string& word);
    void step2a(std::string& word);
    void step2b(std::string& word);
    void step3(std::string& word);
    void step4(std::string& word);
};
#endif // PORTERSTEMMER_H