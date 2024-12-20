# 指定编译器
CXX = g++
# 可执行文件名
EXEC = main
# 源文件
SRC = main.cpp
# PDF 文件
PDF = report.pdf
# LaTeX 编译器
LATEX = xelatex  # 使用 xelatex 编译器来处理中文
# 中文支持包
LATEX_FLAGS = -shell-escape

# 默认目标
all: $(EXEC)
	@echo "Running $(EXEC):"
	./$(EXEC)

# 生成可执行文件
$(EXEC): $(SRC)
	$(CXX) -o $(EXEC) $(SRC)

# 生成 PDF 文件
report: $(PDF)

$(PDF): report.tex
	$(LATEX) $(LATEX_FLAGS) report.tex
	$(LATEX) $(LATEX_FLAGS) report.tex # 运行两次以处理引用

# 清理编译生成的文件
clean:
	rm -f $(EXEC) $(PDF) *.aux *.log *.out

.PHONY: all clean report

