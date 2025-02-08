#include"../include/TextProcessor.h"
#include"../include/PorterStemmer.h"
#include"../include/WordTable.h"

// ��鵥���Ƿ�ֻ����Ӣ���ַ�
bool TextProcessor::isEnglish(const std::string& word) {
    for (char c : word) {
        if (!std::isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

// ȥ�������еı����ţ����滻Ϊһ���ո�
void TextProcessor::removePunctuation(std::string& word) {
    for (char& c : word) {
        if (std::ispunct(static_cast<unsigned char>(c))) {
            c = ' '; // ������滻Ϊһ���ո�
        }
    }
    // �Ƴ��ַ������˵Ŀո�
    word.erase(0, word.find_first_not_of(" "));
    word.erase(word.find_last_not_of(" ") + 1);
}

// ת������ΪСд
void TextProcessor::toLowerCase(std::string& word) {
    std::transform(word.begin(), word.end(), word.begin(),
        [](char c) { return std::tolower(static_cast<unsigned char>(c)); });
}

void TextProcessor::processAbbreviations(std::string& word) {
    // �ԡ�s�Ĵ���
    size_t pos = word.find("'s");
    if (pos != std::string::npos) {
        word.replace(pos, 2, " is");
    }

    // �ԡ�re�Ĵ���
    pos = word.find("'re");
    if (pos != std::string::npos) {
        word.replace(pos, 3, " are");
    }

    // �ԡ�ll�Ĵ���
    pos = word.find("'ll");
    if (pos != std::string::npos) {
        word.replace(pos, 3, " will");
    }

    // �ԡ�ve�Ĵ���
    pos = word.find("'ve");
    if (pos != std::string::npos) {
        word.replace(pos, 3, " have");
    }

    // �ԡ�d�Ĵ���
    pos = word.find("'d");
    if (pos != std::string::npos) {
        // �жϺ�һ�������Ƿ��Ƕ��ʵ�ԭ��
        std::istringstream iss(word);
        std::string nextWord;
       // ������ԭΪ�ĸ�
        while (iss >> nextWord) {
            // ��ȥ�ִ���had
            if (nextWord.size() >= 2 && (nextWord.substr(nextWord.size() - 2) == "ed" || nextWord.substr(nextWord.size() - 2) == "en")) {
                word.replace(pos, 2, " had");
            }
            // ��ֻ��������������������Ϊwould
            else {
                word.replace(pos, 2, " would");
            }
            break;  // ֻ��Ҫ�ж���һ�����ʼ��ɣ������ҵ���Ϳ�������ѭ��
        }
    }
    // ���Ը�����Ҫ�������������д�Ĵ���
}

// �������
void TextProcessor::printWords() {
    WordTable::print(); // ȷ����������˻���� print ����
}

// �ʸ���ȡ
void TextProcessor::processWords(const std::string& word) {
    PorterStemmer stemmer;
    std::string stem = stemmer.stem(word);
    // ���ʸ����뵽AVL����
    WordTable::insert(stem);
}

// �����ı��ļ�����ÿ�����ʲ��뵽AVL���У�����ӡ���ʼ���Ƶ��
bool TextProcessor::processTextFile(const std::string& filename) {
    // ���ļ�
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
            // ת��ΪСд��ͳһ���ʸ�ʽ
            toLowerCase(word);

            // �����ʵ���д��ʽ
            processAbbreviations(word);

            // ȥ�������еı����ţ����滻Ϊһ���ո�
            removePunctuation(word);


            // �ָ��ɿո����ӵĵ���
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
