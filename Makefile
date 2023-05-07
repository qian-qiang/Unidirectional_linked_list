# Makefile

# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra

# 目标文件
TARGET = error

# 获取当前文件夹路径
CURRENT_DIR := $(shell pwd)

# 获取所有的 .c 文件
SRCS := $(wildcard $(CURRENT_DIR)/*.c)

# 所有对象文件（由源文件生成）
OBJS := $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 生成目标文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)
