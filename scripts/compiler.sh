#!/bin/bash

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

if [ "$LANGUAGE" == "EN" ]; then
    echo "Select CPU architecture:"
    options=("amd64" "arm" "mips")
    select opt in "${options[@]}"
    do
        case $opt in
            "amd64")
                ARCH="amd64"
                break
                ;;
            "arm")
                ARCH="arm"
                break
                ;;
            "mips")
                ARCH="mips"
                break
                ;;
            *) echo "Invalid option $REPLY";;
        esac
    done

    echo "Select operating system:"
    options=("windows" "linux" "mac")
    select opt in "${options[@]}"
    do
        case $opt in
            "windows")
                OS="windows"
                break
                ;;
            "linux")
                OS="linux"
                break
                ;;
            "mac")
                OS="mac"
                break
                ;;
            *) echo "Invalid option $REPLY";;
        esac
    done

    echo "Select features:"
    features=()
    options=("Registry Modification" "Bashrc Modification" "Both")
    select opt in "${options[@]}"
    do
        case $opt in
            "Registry Modification")
                features+=("REGISTRY_MOD")
                break
                ;;
            "Bashrc Modification")
                features+=("BASHRC_MOD")
                break
                ;;
            "Both")
                features+=("REGISTRY_MOD" "BASHRC_MOD")
                break
                ;;
            *) echo "Invalid option $REPLY";;
        esac
    done

    CONF_FILE="config/${ARCH}_${OS}.conf"
    echo "ARCH=${ARCH}" > $CONF_FILE
    echo "OS=${OS}" >> $CONF_FILE
    for feature in "${features[@]}"
    do
        echo "FEATURE_${feature}=1" >> $CONF_FILE
    done

    echo "Configuration saved to $CONF_FILE"
else
    echo "选择CPU架构:"
    options=("amd64" "arm" "mips")
    select opt in "${options[@]}"
    do
        case $opt in
            "amd64")
                ARCH="amd64"
                break
                ;;
            "arm")
                ARCH="arm"
                break
                ;;
            "mips")
                ARCH="mips"
                break
                ;;
            *) echo "无效选项 $REPLY";;
        esac
    done

    echo "选择操作系统:"
    options=("windows" "linux" "mac")
    select opt in "${options[@]}"
    do
        case $opt in
            "windows")
                OS="windows"
                break
                ;;
            "linux")
                OS="linux"
                break
                ;;
            "mac")
                OS="mac"
                break
                ;;
            *) echo "无效选项 $REPLY";;
        esac
    done

    echo "选择功能:"
    features=()
    options=("注册表修改" "Bashrc修改" "两者都有")
    select opt in "${options[@]}"
    do
        case $opt in
            "注册表修改")
                features+=("REGISTRY_MOD")
                break
                ;;
            "Bashrc修改")
                features+=("BASHRC_MOD")
                break
                ;;
            "两者都有")
                features+=("REGISTRY_MOD" "BASHRC_MOD")
                break
                ;;
            *) echo "无效选项 $REPLY";;
        esac
    done

    CONF_FILE="config/${ARCH}_${OS}.conf"
    echo "ARCH=${ARCH}" > $CONF_FILE
    echo "OS=${OS}" >> $CONF_FILE
    for feature in "${features[@]}"
    do
        echo "FEATURE_${feature}=1" >> $CONF_FILE
    done

    echo "配置已保存到 $CONF_FILE"
fi

make all CONF_FILE=$CONF_FILE
