#include "../include/PorterStemmer.h"

/*——————————预备函数——————————*/
// 函数功能：判断字符是否是辅音字母
bool PorterStemmer::isConsonant(char ch) {
    return std::string("bcdfghjklmnpqrstvwxyz").find(ch) != std::string::npos;
}

// 函数功能：判断字符串是否以指定后缀结尾
bool PorterStemmer::endsWith(const std::string& word, const std::string& suffix) {
    return word.size() >= suffix.size() && word.substr(word.size() - suffix.size()) == suffix;
}

// 函数功能：替换字符串末尾的指定后缀为指定的替换字符串
void PorterStemmer::replaceEnd(std::string& word, const std::string& suffix, const std::string& replacement) {
    if (endsWith(word, suffix)) {
        word.erase(word.size() - suffix.size());
        word += replacement;
    }
}

// 函数功能：计算字符串末尾的辅音字母序列的长度
int PorterStemmer::getMeasure(const std::string& word) {
    int measure = 0;
    bool wasConsonant = false;
    for (int i = word.size() - 1; i >= 0; --i) {
        if (isConsonant(word[i])) {
            if (!wasConsonant) {
                measure++;
                wasConsonant = true;
            }
            else {
                wasConsonant = false;
            }
        }
        else {
            wasConsonant = false;
        }
    }
    return measure;
}

// 函数功能：判断单词是否是重读闭音节
bool PorterStemmer::isStressedClosedSyllable(const std::string& word) {
    int length = word.size();
    if (length < 3) {
        return false; // 单词长度小于3一定不是重读闭音节
    }

    // 重读闭音节的条件：以一个辅音字母开头，接着一个元音字母，然后是一个辅音字母结尾
    if (PorterStemmer::isConsonant(word[length - 3]) && !PorterStemmer::isConsonant(word[length - 2]) && PorterStemmer::isConsonant(word[length - 1])) {
        return true;
    }
    else {
        return false;
    }
}

// 字典初始化
PorterStemmer::PorterStemmer() {
    // 初始化字典
    dictionary = {
        // 名词复数特殊变换
        {"men", "man"},
{"women", "woman"},
{"feet", "foot"},
{"teeth", "tooth"},
{"geese", "goose"},
{"mice", "mouse"},
{"lice", "louse"},
{"children", "child"},
{"oxen", "ox"},
// 动词不规则变换
{"bought", "buy"},
{"fought", "fight"},
{"sought", "seek"},
{"thought", "think"},
{"brought", "bring"},
{"caught", "catch"},
{"taught", "teach"},
{"dug", "dig"},
{"spun", "spin"},
{"stuck", "stick"},
{"struck", "strike"},
{"swung", "swing"},
{"won", "win"},
{"hung", "hang"},
{"bled", "bleed"},
{"fed", "feed"},
{"fled", "flee"},
{"sped", "speed"},
{"led", "lead"},
{"bent", "bend"},
{"lent", "lend"},
{"sent", "send"},
{"spent", "spend"},
{"felt", "feel"},
{"dealt", "deal"},
{"built", "build"},
{"rebuilt", "rebuild"},
{"kept", "keep"},
{"slept", "sleep"},
{"swept", "sweep"},
{"wept", "weep"},
{"made", "make"},
{"laid", "lay"},
{"paid", "pay"},
{"said", "say"},
{"stood", "stand"},
{"understood", "understand"},
{"misunderstood", "misunderstand"},
{"sold", "sell"},
{"told", "tell"},
{"retold", "retell"},
{"shone", "shine"},
{"smelt", "smell"},
{"spelt", "spell"},
{"burnt", "burn"},
{"dreamt", "dream"},
{"got", "get"},
{"shot", "shoot"},
{"meant", "mean"},
{"met", "meet"},
{"blest", "bless"},
{"lost", "lose"},
{"sat", "sit"},
{"left", "leave"},
{"held", "hold"},
{"slid", "slide"},
{"heard", "hear"},
{"found", "find"},
{"wound", "wind"},
{"had", "have/has"},
{"swollen", "swell"},
{"dove", "dive"},
{"threw", "throw"},
{"beat", "beat"},
{"began", "begin"},
{"drank", "drink"},
{"rang", "ring"},
{"sang", "sing"},
{"swam", "swim"},
{"sank", "sink"},
{"shrank", "shrink"},
{"chose", "choose"},
{"froze", "freeze"},
{"spoke", "speak"},
{"stole", "steal"},
{"broke", "break"},
{"rose", "rise"},
{"arose", "arise"},
{"drove", "drive"},
{"rode", "ride"},
{"wrote", "write"},
{"blew", "blow"},
{"grew", "grow"},
{"knew", "know"},
{ "sett", "set" },
{ "lif", "life" },
{ "bu", "bus" },
{ "flo", "flow" },
{ "spr", "spring" },
{ "hous", "house" },
{ "famiy", "family" },
{ "gloriou", "glorious" },
{ "howe", "how" },
{ "hours", "hour" },
{"threw", "throw"},
{"shook", "shake"},
{"took", "take"},
{"mistook", "mistake"},
{"undertook", "undertake"},
{"tore", "tear"},
{"wore", "wear"},
{"swore", "swear"},
{"drew", "draw"},
{"flew", "fly"},
{"woke", "wake"},
{"awoke", "awake"},
{"saw", "see"},
{"foresaw", "foresee"},
{"bit", "bite"},
{"hid", "hide"},
{"ate", "eat"},
{"fell", "fall"},
{"gave", "give"},
{"forgave", "forgive"},
{"forgot", "forget"},
{"forbad", "forbid"},
{"went", "go"},
{"did", "do"},
{"lay", "lie"},
{"born", "bear"},
{"hung", "hang"},
{"learnt", "learn"}

// 添加更多的单词和对应的原型
    };
}

/*——————————具体处理算法——————————*/
// 名词复数转单数的算法
void PorterStemmer::step3(std::string& word) {
    // 如果结尾不是 's'，则直接返回原词
    if (word.back() != 's') {
        return;
    }

    // 对'ies'结尾进行分析
    if (endsWith(word, "ies")) {
        if (isConsonant(word[word.size() - 4])) { // 'i' 前的字母不是辅音，即元音
            word.replace(word.size() - 3, 3, "y"); // 去掉 'ies' 改为 'y'
        }
        else {
            word.replace(word.size() - 3, 3, "i"); // 去掉 'ies' 变为 'i'
        }
    }

    // 对 'ves' 结尾进行分析，去掉 'ves' 改为 'f' 或 'fe'
    else if (endsWith(word, "ves")) {
        if (endsWith(word.substr(0, word.size() - 3), "af") || endsWith(word.substr(0, word.size() - 3), "of") || endsWith(word.substr(0, word.size() - 3), "if")) {
            word.replace(word.size() - 4, 3, "fe"); // 特殊情况，'af'  'of' 'if' 后面加 'fe'
        }
        else {
            word.erase(word.size() - 3); // 去掉 'ves'
            word += "f"; // 其他情况，加 'f'
        }
    }

    // 对"es"的处理
    else if (endsWith(word, "es")) {
        // 检查词根的最后一个字母是否为 's', 'x', 'sh', 'ch'
        std::string last_letter_check = "sxshch";
        bool is_last_letter_valid = last_letter_check.find(word[word.size() - 3]) != std::string::npos;

        // 如果词根以 's', 'x', 'sh', 'ch' 结尾，或者以 'o' 结尾且前面是辅音，去掉 'es'
        if (is_last_letter_valid || (word[word.size() - 3] == 'o' && isConsonant(word[word.size() - 4]))) {
            word.erase(word.size() - 2); // 去掉 'es'
        }
        // 否则，去掉s
        else {
            word.pop_back(); // 去掉结尾的 's'
        }
    }

    // 最后考虑去掉 's' 的情况
    else{
        word.pop_back(); // 去掉结尾的 's'
    }
}

/*——————————下面进行动词的形式转换————————*/
// 去除过去式"ed"
void PorterStemmer::step2a(std::string& word) {
    // 首先检查词是否以"ed"结尾
    if (endsWith(word, "ed")) {
        // 如果"ed"前是"e"，则去掉"ed"
        if (word.size() > 3 && word[word.size() - 3] == 'e') {
            word.erase(word.size() - 2); // 去掉"ed"
        }
        else {
            // 如果"ed"前是辅音，则去掉"ed"
            if (endsWith(word, "ed") && isConsonant(word[word.size() - 3])) {
                word.erase(word.size() - 2); // 去掉"ed"
                // 并且如果这个词去掉"ed"后以"at", "bl", "iz"结尾，则添加"e"
                if (endsWith(word, "at") || endsWith(word, "bl") || endsWith(word, "iz")) {
                    word += "e";
                }
            }
        }
    }
}

// 去除进行时"ing"
void PorterStemmer::step2b(std::string& word) {

    if (endsWith(word, "ing")) {
        // 去掉"ing"
        word.erase(word.size() - 3);

        // 补充e的部分，如果去掉"ing"后词根以"at", "bl", "iz"或"iv"结尾
        if (endsWith(word, "at") || endsWith(word, "bl") || endsWith(word, "iz") || endsWith(word, "iv")) {
            word += "e";
        }

        // ie变y的部分，如果去掉"ing"后词根以辅音字母加"ie"结尾
        else if (word.size() > 3 && word[word.size() - 1] == 'y' &&
            isConsonant(word[word.size() - 2])) {
            // 如果y前是辅音，则去y变ie
            word.pop_back(); // 去掉'y'
            word[word.size() - 2] = 'e'; // 将'i'变为'ie'
        }

        // 还原双写词尾
        if (word.size() > 3 && word.substr(word.size() - 3) == "ing") {
            if (isStressedClosedSyllable(word)) {
                word.erase(word.size() - 4);
            }
            std::string root = word.substr(0, word.size() - 3);
            if (root.size() > 2 && isConsonant(root.back()) && root[root.size() - 1] != root[root.size() - 2]) {
                // 检查词根是否是重音结尾的词
                std::string doubleConsonants = "bbddffggmmnnpprrtt";
                if (doubleConsonants.find(root.substr(root.size() - 2)) == std::string::npos) {
                    word = root + root.back();
                }
            }
        }
    }
}

/*——————————下面进行形容词和副词的形式转换————————*/
// 副词词根提取
void PorterStemmer::step1a(std::string& word) {
    // 若以ward(s)结尾，直接去掉ward(s)
    if (endsWith(word, "ward") || endsWith(word, "wards")) {
        word.erase(word.size() - 4); // 删除后缀 ward 或 wards
    }

    // 若以ly结尾
    if (endsWith(word, "ly")) {
        // 若为"ably"，则换为"able"
        if (endsWith(word, "ably")) {
            word.replace(word.size() - 4, 4, "able"); // 替换为 able
        }
        // 若ly前是i，去ly，将i改y
        else if (word.size() > 2 && word[word.size() - 3] == 'i') {
            word.erase(word.size() - 2); // 删除后缀 ly
            word += 'y'; // 将i改为y
        }
        // 其他情况直接删除ly
        else {
            word.erase(word.size() - 2); // 删除后缀 ly
        }
    }
}

// 形容词词根提取
void PorterStemmer::step1b(std::string& word) {
    // 处理形容词副词比较级最高级形式
    if (endsWith(word, "er") || endsWith(word, "est")) {
        // 若er/est前是i，则看i前是否为辅音
        if (word.size() >= 3 && word[word.size() - 2] == 'i') {
            char beforeI = word[word.size() - 3];
            if (isConsonant(beforeI)) {
                // 辅音则去er/est，i改为y
                word.erase(word.size() - 3, 2);
                word += 'y';
            }
        }

        // 重读闭音节的去除er/est后再去除一个结尾字母
        if (isStressedClosedSyllable(word)) {
            if (endsWith(word, "er")) {
                word.erase(word.size() - 2);
            }
            else if (endsWith(word, "est")) {
                word.erase(word.size() - 3);
            }
            word.erase(word.size() - 1);
        }

        // 其他情况直接去er/est（排除以er/est结尾的单词）
        else if (endsWith(word, "er")) {
            word.erase(word.size() - 2);
        }
        else if (endsWith(word, "est") ){
            word.erase(word.size() - 3);
        }
    }

    // 去除形容词后缀
    replaceEnd(word, "ative", "");
    replaceEnd(word, "ical", "ic");
    replaceEnd(word, "ful", "");
    replaceEnd(word, "ness", "");
    replaceEnd(word, "ern", "");

    // 如果词以 -ic 结尾，并且前面是辅音，去除 -ic
    if (endsWith(word, "ic") && isConsonant(word[word.size() - 2])) {
        word.pop_back();
    }
}

/*——————————特殊变换单词处理——————————*/
void PorterStemmer::step4(std::string& word) {
    // 在字典中查找原型
    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        word = it->second; // 替换为原型
    }
}

// 接口，用于调用处理方法
std::string PorterStemmer::stem(std::string word) {
    // 确保输入的单词至少包含两个字符
    if (word.length() <= 2) {
        return word;
    }

    // 预处理: 将单词转换为小写
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    // 步骤 1: 形容词副词处理
    step1a(word);   // adv.
    step1b(word);   // adj.

    // 步骤 2: 动词常规处理
    step2a(word); // ed
    step2b(word); // ing

    // 步骤 3: 名词常规处理
    step3(word);

    // 步骤 4: 其他处理
    step4(word);

    // 最后返回处理后的单词
    return word;
}
