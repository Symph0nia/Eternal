#!/bin/bash

# 提示选择语言
echo "Select language (选择语言):"
options=("English" "中文")
select lang in "${options[@]}"
do
    case $lang in
        "English")
            LANGUAGE="EN"
            break
            ;;
        "中文")
            LANGUAGE="CN"
            break
            ;;
        *) echo "Invalid option $REPLY (无效选项)";;
    esac
done

# 设置语言相关的提示信息
if [ "$LANGUAGE" == "EN" ]; then
    MSG_ARCH="Select CPU architecture:"
    MSG_OS="Select operating system:"
    MSG_FEATURES="Select features:"
    ARCH_OPTIONS=("amd64" "arm" "mips")
    OS_OPTIONS=("windows" "linux" "mac")
    FEATURE_OPTIONS=("Registry Modification" "Bashrc Modification" "Both")
    INVALID_OPTION="Invalid option $REPLY"
    CONFIG_SAVED="Configuration saved to"
else
    MSG_ARCH="选择CPU架构:"
    MSG_OS="选择操作系统:"
    MSG_FEATURES="选择功能:"
    ARCH_OPTIONS=("amd64" "arm" "mips")
    OS_OPTIONS=("windows" "linux" "mac")
    FEATURE_OPTIONS=("注册表修改" "Bashrc修改" "两者都有")
    INVALID_OPTION="无效选项 $REPLY"
    CONFIG_SAVED="配置已保存到"
fi

# 函数选择选项
select_option() {
    local prompt="$1"
    shift
    local options=("$@")
    echo "$prompt"
    select opt in "${options[@]}"
    do
        if [[ " ${options[*]} " == *" $opt "* ]]; then
            echo "$opt"
            break
        else
            echo "$INVALID_OPTION"
        fi
    done
}

# 获取用户选择
ARCH=$(select_option "$MSG_ARCH" "${ARCH_OPTIONS[@]}")
OS=$(select_option "$MSG_OS" "${OS_OPTIONS[@]}")
FEATURES=$(select_option "$MSG_FEATURES" "${FEATURE_OPTIONS[@]}")

# 创建配置目录并生成配置文件
mkdir -p ../config
CONF_FILE="../config/current_config.conf"
echo "ARCH=${ARCH}" > $CONF_FILE
echo "OS=${OS}" >> $CONF_FILE
if [[ "$FEATURES" == *"Registry"* ]]; then
    echo "FEATURE_REGISTRY_MOD=1" >> $CONF_FILE
fi
if [[ "$FEATURES" == *"Bashrc"* ]]; then
    echo "FEATURE_BASHRC_MOD=1" >> $CONF_FILE
fi

echo "$CONFIG_SAVED $CONF_FILE"

# 运行Makefile
cd ..
make all
