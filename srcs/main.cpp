#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <Windows.h>
#include <locale>
#include <iostream>
#include <limits>

#include "../include/Textprocessor.h"
#include "../include/WordTable.h"
#include "../include/CalculateTextSimiarity.h"

// main.cpp
int main()
{
	while (true)
	{
		std::cout << "这是一个文本分析系统，主要算法参考Porter Stemmer算法实现" << std::endl;
		std::cout << "系统仅支持英文txt文本文件路径，请勿使用双引号输入" << std::endl;
		std::cout << "请选择操作：" << std::endl;
		std::cout << "1. 打开本地文件查找单词" << std::endl;
		std::cout << "2. 使用系统示例文件查找单词(TestFile)" << std::endl;
		std::cout << "3. 比较文本相似度" << std::endl;
		std::cout << "4. 退出程序" << std::endl;

		int choice;
		if (!(std::cin >> choice))
		{
			std::cout << "输入无效，请输入一个整数。" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (choice == 1)
		{
			std::string file1;
			std::cout << "请输入文件路径: ";
			std::cin >> file1;
			TextProcessor fileone;

			if (!fileone.processTextFile(file1))
			{
				std::cout << "无法打开文件，请检查路径是否正确。" << std::endl;
				std::cout << std::endl;
				continue;
			}
			std::cout << "文件" << file1 << "对应的单词表如下" << std::endl;
			fileone.print();
			std::cout << "请输入要查找的单词: ";
			std::string word1;
			std::cin >> word1;
			std::cout << "您所查找的单词频率为" << fileone.search(word1) << std::endl;
		}
		else if (choice == 2)
		{
			std::ifstream file("../test/TestFile.txt");
			if (!file.is_open())
			{
				std::cerr << "Error opening file: " << "TestFile.txt" << std::endl;
				continue;
			}
			TextProcessor systemfile;
			std::cout << "文件" << "TestFile.txt" << "对应的单词表如下" << std::endl;
			if (systemfile.processTextFile("../test/TestFile.txt"))
			{
				systemfile.print();
			}
			std::cout << "请输入要查找的单词: ";
			std::string word1;
			std::cin >> word1;
			std::cout << "您所查找的单词频率为" << systemfile.search(word1) << std::endl;
		}
		else if (choice == 3)
		{
			std::string file1, file2;
			std::cout << "请输入第一个文件路径: ";
			std::cin >> file1;
			std::cout << "请输入第二个文件路径: ";
			std::cin >> file2;
			TextProcessor fileone;
			TextProcessor filetwo;
			if (!fileone.processTextFile(file1) || !filetwo.processTextFile(file2))
			{
				std::cout << "无法打开文件，请检查路径是否正确。" << std::endl;
				std::cout << std::endl;
				continue;
			}
			std::cout << "两篇文本基于词频向量的文本相似度为: ";
			std::cout << calculateSimilarity(fileone, filetwo) << std::endl;
			std::cout << "两篇文本基于最长公共子串的文本相似度为: ";
			std::cout << calculateSimilarity(file1, file2) << std::endl;
		}
		else if (choice == 4)
		{
			std::cout << "退出程序" << std::endl;
			break;
		}
		else
		{
			std::cout << "无效的选择，请输入1 - 4之间的数字。" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	return 0;
}