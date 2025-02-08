#include"../include/TextProcessor.h"
#include"../include/PorterStemmer.h"
#include"../include/WordTable.h"

// 检查单词是否只包含英文字符
bool TextProcessor::isEnglish(const std::string& word) {
    for (char c : word) {
        if (!std::isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

// 去除单词中的标点符号，并替换为一个空格
void TextProcessor::removePunctuation(std::string& word) {
    for (char& c : word) {
        if (std::ispunct(static_cast<unsigned char>(c))) {
            c = ' '; // 将标点替换为一个空格
        }
    }
    // 移除字符串两端的空格
    word.erase(0, word.find_first_not_of(" "));
    word.erase(word.find_last_not_of(" ") + 1);
}

// 转换单词为小写
void TextProcessor::toLowerCase(std::string& word) {
    std::transform(word.begin(), word.end(), word.begin(),
        [](char c) { return std::tolower(static_cast<unsigned char>(c)); });
}

void TextProcessor::processAbbreviations(std::string& word) {
    // 对’s的处理
    size_t pos = word.find("'s");
    if (pos != std::string::npos) {
        word.replace(pos, 2, " is");
    }

    // 对’re的处理
    pos = word.find("'re");
    if (pos != std::string::npos) {
        word.replace(pos, 3, " are");
    }

    // 对’ll的处理
    pos = word.find("'ll");
    if (pos != std::string::npos) {
        word.replace(pos, 3, " will");
    }

    // 对’ve的处理
    pos = word.find("'ve");
    if (pos != std::string::npos) {
        word.replace(pos, 3, " have");
    }

    // 对’d的处理
    pos = word.find("'d");
    if (pos != std::string::npos) {
        // 判断后一个单词是否是动词的原形
        std::istringstream iss(word);
        std::string nextWord;
       // 决定还原为哪个
        while (iss >> nextWord) {
            // 过去分词用had
            if (nextWord.size() >= 2 && (nextWord.substr(nextWord.size() - 2) == "ed" || nextWord.substr(nextWord.size() - 2) == "en")) {
                word.replace(pos, 2, " had");
            }
            // 因只有两种情况，其他情况均为would
            else {
                word.replace(pos, 2, " would");
            }
            break;  // 只需要判断下一个单词即可，所以找到后就可以跳出循环
        }
    }
    // 可以根据需要继续添加其他缩写的处理
}

// 输出部分
void TextProcessor::printWords() {
    WordTable::print(); // 确保这里调用了基类的 print 方法
}

// 词根提取
void TextProcessor::processWords(const std::string& word) {
    PorterStemmer stemmer;
    std::string stem = stemmer.stem(word);
    // 将词根插入到AVL树中
    WordTable::insert(stem);
}

// 处理文本文件，将每个单词插入到AVL树中，并打印单词及其频率
bool TextProcessor::processTextFile(const std::string& filename) {
    // 打开文件
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            // 转换为小写以统一单词格式
            toLowerCase(word);

            // 处理单词的缩写形式
            processAbbreviations(word);

            // 去除单词中的标点符号，并替换为一个空格
            removePunctuation(word);


            // 分割由空格连接的单词
            std::istringstream wordStream(word);
            std::string subWord;
            while (wordStream >> subWord) {
                if (!isEnglish(subWord)) {
                    std::cerr << "Error: The word '" << subWord << "' contains non-English characters." << std::endl;
                    continue;
                }
                processWords(subWord);
            }
        }
    }

    file.close();
    return true;
}
