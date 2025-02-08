# 文本分析系统

## 项目依赖

- C++11标准
- 标准库 `<iostream>`, `<fstream>`, `<string>`, `<vector>`, `<algorithm>`, `<unordered_map>`, `<cmath>`, `<windows.h>`

## 作者:Jonathan.Liang

## 项目概述

本项目是一个文本分析系统，主要功能包括：
- 读取英文文本文件并生成单词表(分词算法基于PorterStemmer算法进行改进)
- 查找单词及其频率
- 比较两篇文本的相似度（基于最长公共子串和余弦相似度）

## 项目结构
- `main.cpp`: 主程序入口，提供用户交互界面。
- `CalculateSimilarity.cpp` 和 `CalculateTextSimiarity.cpp`: 提供文本相似度计算功能。
- `PorterStemmer.cpp`: 实现Porter Stemmer算法，用于词根提取。
- `TestProcessor.cpp`: 处理文本文件，生成单词表。
- `WordTable.cpp`: 实现AVL树，用于存储和管理单词表。
- `include/` 目录：包含所有头文件。
- `TestFile.txt`：预输入文件，作为样例。

## 编译与运行
1. 确保系统已安装C++编译器（如g++）。
2. 在项目根目录下运行 `make` 命令编译项目。
3. 运行 `make run` 命令启动程序。

## 使用说明
程序启动后，会显示一个菜单，用户可以选择以下操作：
- **1. 打开本地文件查找单词**：输入文件路径，程序将读取文件并生成单词表，用户可以查找单词及其频率。
- **2. 使用系统示例文件查找单词**：使用内置的示例文件 `TestFile.txt`，程序将读取文件并生成单词表，用户可以查找单词及其频率。
- **3. 比较文本相似度**：输入两个文件路径，程序将计算并显示两篇文本的相似度。
- **4. 退出程序**：退出程序。

## 示例
假设项目目录下有一个示例文件 `TestFile.txt`，内容如下：
```cmd
This is a test file. The file contains some test data.
```
运行程序并选择选项2，程序将显示：
```cmd
文件TestFile.txt对应的单词表如下 
a : 1 
contain : 1 
data : 1 
file : 2 
is : 1 
some : 1 
test : 2 
this : 1 
the : 1
```
输入要查找的单词 `test`，程序将显示：
```cmd
您所查找的单词频率为2
```
## 版权所有 ©2025 Jonathan.Liang保留所有权利。