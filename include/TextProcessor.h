#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <algorithm>

#include "WordTable.h"

class TextProcessor : public WordTable {
public:
    TextProcessor() {} // ���캯��
    ~TextProcessor() = default;

    bool processTextFile(const std::string& filename);
    void printWords(); // ������ʱ�
    void processWords(const std::string& word);

private:
    bool isEnglish(const std::string& word);
    void removePunctuation(std::string& word);
    void toLowerCase(std::string& word);
    void processAbbreviations(std::string& word);
};

#endif // TEXTPROCESSOR_H

