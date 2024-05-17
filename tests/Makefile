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

TARGET_LINUX_PERSISTENCE_CRONTAB = $(OUTDIR)/test_linux_persistence_crontab

TARGET_LINUX_PERSISTENCE_LD_PRELOAD = $(OUTDIR)/test_linux_persistence_ld_preload

# 单个源文件列表，包括 Unity 源文件和你的 info.c 源文件
SOURCES_INFO = test_info.c ../src/info.c unity/unity.c

SOURCES_LINUX_PERSISTENCE_BASHRC = test_linux_persistence_bashrc.c ../src/linux_persistence_bashrc.c unity/unity.c

SOURCES_LINUX_PERSISTENCE_CRONTAB = test_linux_persistence_crontab.c ../src/linux_persistence_crontab.c unity/unity.c

SOURCES_LINUX_PERSISTENCE_LD_PRELOAD = test_linux_persistence_ld_preload.c ../src/linux_persistence_ld_preload.c unity/unity.c

# 编译单个测试 info 并链接成一个可执行文件
$(TARGET_INFO): $(SOURCES_INFO)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_LINUX_PERSISTENCE_BASHRC): $(SOURCES_LINUX_PERSISTENCE_BASHRC)
	$(CC) $(CFLAGS) -DBASHRC_MOD -o $@ $^

$(TARGET_LINUX_PERSISTENCE_CRONTAB): $(SOURCES_LINUX_PERSISTENCE_CRONTAB)
	$(CC) $(CFLAGS) -DCRONTAB_MOD -o $@ $^

$(TARGET_LINUX_PERSISTENCE_LD_PRELOAD): $(SOURCES_LINUX_PERSISTENCE_LD_PRELOAD)
	$(CC) $(CFLAGS) -DLD_PRELOAD_MOD -o $@ $^

# 运行所有测试
test_all: $(TARGET_INFO) $(TARGET_LINUX_PERSISTENCE_BASHRC) $(TARGET_LINUX_PERSISTENCE_CRONTAB) $(TARGET_LINUX_PERSISTENCE_LD_PRELOAD)
	./$(TARGET_INFO)
	./$(TARGET_LINUX_PERSISTENCE_BASHRC)
	./$(TARGET_LINUX_PERSISTENCE_CRONTAB)
	./$(TARGET_LINUX_PERSISTENCE_LD_PRELOAD)

# 运行单个测试
test_info: $(TARGET_INFO)
	./$(TARGET_INFO)

test_linux_persistence_bashrc: $(TARGET_LINUX_PERSISTENCE_BASHRC)
	./$(TARGET_LINUX_PERSISTENCE_BASHRC)

test_linux_persistence_crontab: $(TARGET_LINUX_PERSISTENCE_CRONTAB)
	./$(TARGET_LINUX_PERSISTENCE_CRONTAB)

test_linux_persistence_ld_preload: $(TARGET_LINUX_PERSISTENCE_LD_PRELOAD)
	./$(TARGET_LINUX_PERSISTENCE_LD_PRELOAD)

# 清理编译产生的文件
clean:
	rm -rf $(OUTDIR)

.PHONY: test_info test_all clean
