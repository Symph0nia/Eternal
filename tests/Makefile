# 指定编译器
CC = gcc

# 指定编译器标志，包括头文件路径
CFLAGS = -I../include -Iunity

# 输出目录
OUTDIR = target

# 确保输出目录存在
$(shell mkdir -p $(OUTDIR))

# 定义目标文件
TARGET_INFO = $(OUTDIR)/test_info

TARGET_LINUX_PERSISTENCE_BASHRC = $(OUTDIR)/test_linux_persistence_bashrc

# 单个源文件列表，包括 Unity 源文件和你的 info.c 源文件
SOURCES_INFO = test_info.c ../src/info.c unity/unity.c

SOURCES_LINUX_PERSISTENCE_BASHRC = test_linux_persistence_bashrc.c ../src/linux_persistence_bashrc.c unity/unity.c
# 所有测试的可执行文件名
TARGET_ALL = $(OUTDIR)/test_all

# 所有测试源文件列表，可按需添加更多
SOURCES_ALL = $(SOURCES_INFO)  # 示例，可以添加更多测试文件

# 编译单个测试 info 并链接成一个可执行文件
$(TARGET_INFO): $(SOURCES_INFO)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_LINUX_PERSISTENCE_BASHRC): $(SOURCES_LINUX_PERSISTENCE_BASHRC)
	$(CC) $(CFLAGS) -DBASHRC_MOD -o $@ $^

# 编译所有测试并链接成一个可执行文件
$(TARGET_ALL): $(SOURCES_ALL)
	$(CC) $(CFLAGS) -o $@ $^

# 运行单个测试
test_info: $(TARGET_INFO)
	./$(TARGET_INFO)

test_linux_persistence_bashrc: $(TARGET_LINUX_PERSISTENCE_BASHRC)
	./$(TARGET_LINUX_PERSISTENCE_BASHRC)

# 运行所有测试
test_all: $(TARGET_ALL)
	./$(TARGET_ALL)

# 清理编译产生的文件
clean:
	rm -rf $(OUTDIR)

.PHONY: test_info test_all clean
