#include "../include/PorterStemmer.h"

/*��������������������Ԥ��������������������������*/
// �������ܣ��ж��ַ��Ƿ��Ǹ�����ĸ
bool PorterStemmer::isConsonant(char ch) {
    return std::string("bcdfghjklmnpqrstvwxyz").find(ch) != std::string::npos;
}

// �������ܣ��ж��ַ����Ƿ���ָ����׺��β
bool PorterStemmer::endsWith(const std::string& word, const std::string& suffix) {
    return word.size() >= suffix.size() && word.substr(word.size() - suffix.size()) == suffix;
}

// �������ܣ��滻�ַ���ĩβ��ָ����׺Ϊָ�����滻�ַ���
void PorterStemmer::replaceEnd(std::string& word, const std::string& suffix, const std::string& replacement) {
    if (endsWith(word, suffix)) {
        word.erase(word.size() - suffix.size());
        word += replacement;
    }
}

// �������ܣ������ַ���ĩβ�ĸ�����ĸ���еĳ���
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

// �������ܣ��жϵ����Ƿ����ض�������
bool PorterStemmer::isStressedClosedSyllable(const std::string& word) {
    int length = word.size();
    if (length < 3) {
        return false; // ���ʳ���С��3һ�������ض�������
    }

    // �ض������ڵ���������һ��������ĸ��ͷ������һ��Ԫ����ĸ��Ȼ����һ��������ĸ��β
    if (PorterStemmer::isConsonant(word[length - 3]) && !PorterStemmer::isConsonant(word[length - 2]) && PorterStemmer::isConsonant(word[length - 1])) {
        return true;
    }
    else {
        return false;
    }
}

// �ֵ��ʼ��
PorterStemmer::PorterStemmer() {
    // ��ʼ���ֵ�
    dictionary = {
        // ���ʸ�������任
        {"men", "man"},
{"women", "woman"},
{"feet", "foot"},
{"teeth", "tooth"},
{"geese", "goose"},
{"mice", "mouse"},
{"lice", "louse"},
{"children", "child"},
{"oxen", "ox"},
// ���ʲ�����任
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

// ��Ӹ���ĵ��ʺͶ�Ӧ��ԭ��
    };
}

/*�����������������������崦���㷨��������������������*/
// ���ʸ���ת�������㷨
void PorterStemmer::step3(std::string& word) {
    // �����β���� 's'����ֱ�ӷ���ԭ��
    if (word.back() != 's') {
        return;
    }

    // ��'ies'��β���з���
    if (endsWith(word, "ies")) {
        if (isConsonant(word[word.size() - 4])) { // 'i' ǰ����ĸ���Ǹ�������Ԫ��
            word.replace(word.size() - 3, 3, "y"); // ȥ�� 'ies' ��Ϊ 'y'
        }
        else {
            word.replace(word.size() - 3, 3, "i"); // ȥ�� 'ies' ��Ϊ 'i'
        }
    }

    // �� 'ves' ��β���з�����ȥ�� 'ves' ��Ϊ 'f' �� 'fe'
    else if (endsWith(word, "ves")) {
        if (endsWith(word.substr(0, word.size() - 3), "af") || endsWith(word.substr(0, word.size() - 3), "of") || endsWith(word.substr(0, word.size() - 3), "if")) {
            word.replace(word.size() - 4, 3, "fe"); // ���������'af'  'of' 'if' ����� 'fe'
        }
        else {
            word.erase(word.size() - 3); // ȥ�� 'ves'
            word += "f"; // ����������� 'f'
        }
    }

    // ��"es"�Ĵ���
    else if (endsWith(word, "es")) {
        // ���ʸ������һ����ĸ�Ƿ�Ϊ 's', 'x', 'sh', 'ch'
        std::string last_letter_check = "sxshch";
        bool is_last_letter_valid = last_letter_check.find(word[word.size() - 3]) != std::string::npos;

        // ����ʸ��� 's', 'x', 'sh', 'ch' ��β�������� 'o' ��β��ǰ���Ǹ�����ȥ�� 'es'
        if (is_last_letter_valid || (word[word.size() - 3] == 'o' && isConsonant(word[word.size() - 4]))) {
            word.erase(word.size() - 2); // ȥ�� 'es'
        }
        // ����ȥ��s
        else {
            word.pop_back(); // ȥ����β�� 's'
        }
    }

    // �����ȥ�� 's' �����
    else{
        word.pop_back(); // ȥ����β�� 's'
    }
}

/*��������������������������ж��ʵ���ʽת������������������*/
// ȥ����ȥʽ"ed"
void PorterStemmer::step2a(std::string& word) {
    // ���ȼ����Ƿ���"ed"��β
    if (endsWith(word, "ed")) {
        // ���"ed"ǰ��"e"����ȥ��"ed"
        if (word.size() > 3 && word[word.size() - 3] == 'e') {
            word.erase(word.size() - 2); // ȥ��"ed"
        }
        else {
            // ���"ed"ǰ�Ǹ�������ȥ��"ed"
            if (endsWith(word, "ed") && isConsonant(word[word.size() - 3])) {
                word.erase(word.size() - 2); // ȥ��"ed"
                // ������������ȥ��"ed"����"at", "bl", "iz"��β�������"e"
                if (endsWith(word, "at") || endsWith(word, "bl") || endsWith(word, "iz")) {
                    word += "e";
                }
            }
        }
    }
}

// ȥ������ʱ"ing"
void PorterStemmer::step2b(std::string& word) {

    if (endsWith(word, "ing")) {
        // ȥ��"ing"
        word.erase(word.size() - 3);

        // ����e�Ĳ��֣����ȥ��"ing"��ʸ���"at", "bl", "iz"��"iv"��β
        if (endsWith(word, "at") || endsWith(word, "bl") || endsWith(word, "iz") || endsWith(word, "iv")) {
            word += "e";
        }

        // ie��y�Ĳ��֣����ȥ��"ing"��ʸ��Ը�����ĸ��"ie"��β
        else if (word.size() > 3 && word[word.size() - 1] == 'y' &&
            isConsonant(word[word.size() - 2])) {
            // ���yǰ�Ǹ�������ȥy��ie
            word.pop_back(); // ȥ��'y'
            word[word.size() - 2] = 'e'; // ��'i'��Ϊ'ie'
        }

        // ��ԭ˫д��β
        if (word.size() > 3 && word.substr(word.size() - 3) == "ing") {
            if (isStressedClosedSyllable(word)) {
                word.erase(word.size() - 4);
            }
            std::string root = word.substr(0, word.size() - 3);
            if (root.size() > 2 && isConsonant(root.back()) && root[root.size() - 1] != root[root.size() - 2]) {
                // ���ʸ��Ƿ���������β�Ĵ�
                std::string doubleConsonants = "bbddffggmmnnpprrtt";
                if (doubleConsonants.find(root.substr(root.size() - 2)) == std::string::npos) {
                    word = root + root.back();
                }
            }
        }
    }
}

/*������������������������������ݴʺ͸��ʵ���ʽת������������������*/
// ���ʴʸ���ȡ
void PorterStemmer::step1a(std::string& word) {
    // ����ward(s)��β��ֱ��ȥ��ward(s)
    if (endsWith(word, "ward") || endsWith(word, "wards")) {
        word.erase(word.size() - 4); // ɾ����׺ ward �� wards
    }

    // ����ly��β
    if (endsWith(word, "ly")) {
        // ��Ϊ"ably"����Ϊ"able"
        if (endsWith(word, "ably")) {
            word.replace(word.size() - 4, 4, "able"); // �滻Ϊ able
        }
        // ��lyǰ��i��ȥly����i��y
        else if (word.size() > 2 && word[word.size() - 3] == 'i') {
            word.erase(word.size() - 2); // ɾ����׺ ly
            word += 'y'; // ��i��Ϊy
        }
        // �������ֱ��ɾ��ly
        else {
            word.erase(word.size() - 2); // ɾ����׺ ly
        }
    }
}

// ���ݴʴʸ���ȡ
void PorterStemmer::step1b(std::string& word) {
    // �������ݴʸ��ʱȽϼ���߼���ʽ
    if (endsWith(word, "er") || endsWith(word, "est")) {
        // ��er/estǰ��i����iǰ�Ƿ�Ϊ����
        if (word.size() >= 3 && word[word.size() - 2] == 'i') {
            char beforeI = word[word.size() - 3];
            if (isConsonant(beforeI)) {
                // ������ȥer/est��i��Ϊy
                word.erase(word.size() - 3, 2);
                word += 'y';
            }
        }

        // �ض������ڵ�ȥ��er/est����ȥ��һ����β��ĸ
        if (isStressedClosedSyllable(word)) {
            if (endsWith(word, "er")) {
                word.erase(word.size() - 2);
            }
            else if (endsWith(word, "est")) {
                word.erase(word.size() - 3);
            }
            word.erase(word.size() - 1);
        }

        // �������ֱ��ȥer/est���ų���er/est��β�ĵ��ʣ�
        else if (endsWith(word, "er")) {
            word.erase(word.size() - 2);
        }
        else if (endsWith(word, "est") ){
            word.erase(word.size() - 3);
        }
    }

    // ȥ�����ݴʺ�׺
    replaceEnd(word, "ative", "");
    replaceEnd(word, "ical", "ic");
    replaceEnd(word, "ful", "");
    replaceEnd(word, "ness", "");
    replaceEnd(word, "ern", "");

    // ������� -ic ��β������ǰ���Ǹ�����ȥ�� -ic
    if (endsWith(word, "ic") && isConsonant(word[word.size() - 2])) {
        word.pop_back();
    }
}

/*������������������������任���ʴ���������������������*/
void PorterStemmer::step4(std::string& word) {
    // ���ֵ��в���ԭ��
    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        word = it->second; // �滻Ϊԭ��
    }
}

// �ӿڣ����ڵ��ô�����
std::string PorterStemmer::stem(std::string word) {
    // ȷ������ĵ������ٰ��������ַ�
    if (word.length() <= 2) {
        return word;
    }

    // Ԥ����: ������ת��ΪСд
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    // ���� 1: ���ݴʸ��ʴ���
    step1a(word);   // adv.
    step1b(word);   // adj.

    // ���� 2: ���ʳ��洦��
    step2a(word); // ed
    step2b(word); // ing

    // ���� 3: ���ʳ��洦��
    step3(word);

    // ���� 4: ��������
    step4(word);

    // ��󷵻ش����ĵ���
    return word;
}
