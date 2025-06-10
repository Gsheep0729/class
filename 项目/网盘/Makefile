# Makefile云盘编译
# 指定C++编译器
CXX = g++

# 定义目标文件
TARGETS = server client

# 定义源文件
SRCS_SERVER = server.cpp fileTrans.cpp
SRCS_CLIENT = client.cpp fileTrans.cpp

# 定义目标文件（不带.cpp后缀，转换为.o后缀）
OBJS_SERVER = $(SRCS_SERVER:.cpp=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.cpp=.o)

# 默认目标，构建所有TARGETS
all: $(TARGETS)

# 生成server可执行文件
server: $(OBJS_SERVER)
	$(CXX) -o $@ $^ -lpthread

# 生成client可执行文件
client: $(OBJS_CLIENT)
	$(CXX) -o $@ $^ -lpthread

# 通用模式规则：将.cpp编译为.o
%.o : %.cpp
	$(CXX) -c $< -o $@

# 清理中间文件和可执行文件
clean:
	rm -f $(TARGETS) $(OBJS_SERVER) $(OBJS_CLIENT)

# 伪目标声明
.PHONY: all clean