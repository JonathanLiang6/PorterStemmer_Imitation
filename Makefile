# 编译器设置
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
INCLUDES = -Iinclude

# 目标文件
TARGET = main

# 源文件
SOURCES = main.cpp CalculateSimilarity.cpp CalculateTextSimiarity.cpp PorterStemmer.cpp TestProcessor.cpp WordTable.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJECTS)
    @echo "Linking $(TARGET)..."
    $(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) || { echo "Linking failed"; exit 1; }

# 编译源文件
main.o: main.cpp include/Textprocessor.h include/WordTable.h include/CalculateTextSimiarity.h
    @echo "Compiling $<..."
    $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ || { echo "Compilation of $< failed"; exit 1; }

CalculateSimilarity.o: CalculateSimilarity.cpp include/Textprocessor.h include/WordTable.h include/CalculateTextSimiarity.h
    @echo "Compiling $<..."
    $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ || { echo "Compilation of $< failed"; exit 1; }

CalculateTextSimiarity.o: CalculateTextSimiarity.cpp include/WordTable.h include/calculateTextsimiarity.h include/Textprocessor.h
    @echo "Compiling $<..."
    $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ || { echo "Compilation of $< failed"; exit 1; }

PorterStemmer.o: PorterStemmer.cpp include/PorterStemmer.h
    @echo "Compiling $<..."
    $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ || { echo "Compilation of $< failed"; exit 1; }

TestProcessor.o: TestProcessor.cpp include/TextProcessor.h include/PorterStemmer.h include/WordTable.h
    @echo "Compiling $<..."
    $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ || { echo "Compilation of $< failed"; exit 1; }

WordTable.o: WordTable.cpp include/WordTable.h
    @echo "Compiling $<..."
    $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ || { echo "Compilation of $< failed"; exit 1; }

# 清理生成的文件
clean:
    rm -f $(OBJECTS) $(TARGET)

# 运行目标
run: $(TARGET)
    ./$(TARGET)