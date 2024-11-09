# Makefile用于编译并生成报告

# 设置编译器和编译选项
CXX = g++
CXXFLAGS = -O2

# 报告文件
REPORT_TEX = report.tex

# 测试程序的目标
TARGET = test
TEST_SRC = test.cpp

# 默认目标：编译测试程序并生成报告
.PHONY: all test report

# 默认目标：编译并生成报告
all: test report

# 编译 test.cpp 生成可执行文件 test
test: $(TEST_SRC)
	ulimit -s unlimited  # 取消栈大小限制
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TEST_SRC)

# 编译 .tex 文件生成 PDF 报告
report: $(REPORT_TEX)
	pdflatex $(REPORT_TEX)

# 清理中间文件
clean:
	rm -f $(TARGET) $(TARGET).o $(REPORT_TEX:.tex=.pdf) *.log *.aux
