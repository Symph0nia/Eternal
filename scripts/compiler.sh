#!/bin/bash

# 设置语言相关的提示信息
MSG_ARCH="Select CPU architecture:"
MSG_OS="Select operating system:"
MSG_FEATURES="Select features:"
ARCH_OPTIONS=("amd64" "arm" "mips")
OS_OPTIONS=("windows" "linux" "mac")
FEATURE_OPTIONS=("Registry Modification" "Bashrc Modification" "Both")
INVALID_OPTION="Invalid option $REPLY"
CONFIG_SAVED="Configuration saved to"

# 获取CPU架构选择
echo "$MSG_ARCH"
select ARCH in "${ARCH_OPTIONS[@]}"
do
    if [[ " ${ARCH_OPTIONS[*]} " == *" $ARCH "* ]]; then
        break
    else
        echo "$INVALID_OPTION"
    fi
done

# 获取操作系统选择
echo "$MSG_OS"
select OS in "${OS_OPTIONS[@]}"
do
    if [[ " ${OS_OPTIONS[*]} " == *" $OS "* ]]; then
        break
    else
        echo "$INVALID_OPTION"
    fi
done

# 获取功能选择
echo "$MSG_FEATURES"
select FEATURE in "${FEATURE_OPTIONS[@]}"
do
    if [[ " ${FEATURE_OPTIONS[*]} " == *" $FEATURE "* ]]; then
        break
    else
        echo "$INVALID_OPTION"
    fi
done

# 创建配置目录并生成配置文件
mkdir -p ../config
CONF_FILE="../config/current_config.conf"
echo "ARCH=$ARCH" > $CONF_FILE
echo "OS=$OS" >> $CONF_FILE
if [[ "$FEATURE" == "Registry Modification" || "$FEATURE" == "Both" ]]; then
    echo "FEATURE_REGISTRY_MOD=1" >> $CONF_FILE
fi
if [[ "$FEATURE" == "Bashrc Modification" || "$FEATURE" == "Both" ]]; then
    echo "FEATURE_BASHRC_MOD=1" >> $CONF_FILE
fi

echo "$CONFIG_SAVED $CONF_FILE"

# 运行Makefile
cd ..
make all
