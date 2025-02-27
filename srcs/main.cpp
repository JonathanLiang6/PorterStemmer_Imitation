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

int main()
{

	while (true)
	{
		std::cout << "����һ���ı�����ϵͳ����Ҫ�ִ��㷨�ο�Porter Stemmer�㷨ʵ��" << std::endl;
		std::cout << "��ϵͳ��֧��Ӣ��txt�ı����ļ�·������˫б�ּܷ���" << std::endl;
		std::cout << "��������ѡ�����:" << std::endl;
		std::cout << "1. �򿪱����ļ����ҵ���" << std::endl;
		std::cout << "2. ʹ��ϵͳʾ���ļ����ҵ���(TestFile)" << std::endl;
		std::cout << "3. �Ƚ��ı����ƶ�" << std::endl;
		std::cout << "4. �˳�����" << std::endl;

		int choice;
		std::cin >> choice;

		if (choice == 1)
		{
			std::string file1;
			std::cout << "��������ļ���·��: ";
			std::cin >> file1;
			TextProcessor fileone;

			if (!fileone.processTextFile(file1))
			{
				std::cout << "�޷����ļ�������·���Ƿ���ȷ��" << std::endl;
				std::cout << std::endl;
				continue;
			}
			std::cout << "�ļ�" << file1 << "��Ӧ�ĵ��ʱ�����" << std::endl;
			fileone.print();
			std::cout << "������Ҫ���ҵĵ���:";
			std::string word1;
			std::cin >> word1;
			Sleep(10);
			std::cout << "�������ҵĵ���Ƶ��Ϊ" << fileone.search(word1);
			std::cout << std::endl;
			Sleep(10);
		}

		else if (choice == 2)
		{
			std::ifstream file("../test/TestFile.txt");
			if (!file.is_open())
			{
				std::cerr << "Error opening file: " << "TestFile.txt" << std::endl;
				return false;
			}
			TextProcessor systemfile;
			std::cout << "�ļ�" << "TestFile.txt" << "��Ӧ�ĵ��ʱ�����" << std::endl;
			if (systemfile.processTextFile("../test/TestFile.txt"))
			{
				systemfile.print();
			}
			std::cout << "������Ҫ���ҵĵ���:";
			std::string word1;
			std::cin >> word1;
			Sleep(10);
			std::cout << "�������ҵĵ���Ƶ��Ϊ" << systemfile.search(word1);
			std::cout << std::endl;
			Sleep(10);
		}

		else if (choice == 3)
		{
			std::string file1, file2;
			std::cout << "�������һ���ļ���·��: ";
			std::cin >> file1;
			std::cout << "������ڶ����ļ���·��: ";
			std::cin >> file2;
			TextProcessor fileone;
			TextProcessor filetwo;
			if (!fileone.processTextFile(file1) || !filetwo.processTextFile(file2))
			{
				std::cout << "�޷����ļ�������·���Ƿ���ȷ��" << std::endl;
				std::cout << std::endl;
				continue;
			}
			std::cout << "��ƪ�ı������������ƶȵ��ı����ƶ�Ϊ��";
			Sleep(10);
			std::cout << calculateSimilarity(fileone, filetwo) << std::endl;
			Sleep(10);
			std::cout << "��ƪ�ı���������������ı����ƶ�Ϊ��";
			Sleep(10);
			std::cout << calculateSimilarity(file1, file2) << std::endl;
			Sleep(10);
		}

		else if (choice == 4)
		{
			std::cout << "�˳�����" << std::endl;
			break;
		}

		else
		{
			std::cout << "��Ч��ѡ�����ԵȲ��������롣\n"
					  << std::endl;
			std::cin.clear();
			int MaxWordAmount = 9999;
			std::cin.ignore(MaxWordAmount, '\n');
			// continue;
		}
		Sleep(8);
		system("cls");
	}

	return 0;
}
