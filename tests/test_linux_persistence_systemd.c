#include "unity.h"
#include "linux_persistence_systemd.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

// 设置环境
void setUp(void) {
    // 这里是每个测试之前需要运行的代码
}

// 清理环境
void tearDown(void) {
    // 删除测试中创建的 systemd 服务文件和清理相关系统设置
    const char* systemd_path = "/etc/systemd/system";
    char service_path[512];
    snprintf(service_path, sizeof(service_path), "%s/eternal.service", systemd_path);

    remove(service_path);  // 删除服务文件
    system("systemctl daemon-reload");  // 重新加载 systemd 配置
    system("systemctl disable eternal.service");  // 禁用服务
}

// 测试 setup_systemd_persistence 函数
void test_setup_systemd_persistence(void) {
    setup_systemd_persistence();

    // 验证 systemd 服务文件是否被正确创建
    const char* systemd_path = "/etc/systemd/system";
    char service_path[512];
    snprintf(service_path, sizeof(service_path), "%s/eternal.service", systemd_path);

    struct stat statbuf;
    int result = stat(service_path, &statbuf);
    TEST_ASSERT_TRUE_MESSAGE(result == 0, "Systemd 服务文件没有被创建");

    // 验证 systemd 服务是否能被正确启用和启动
    char command_output[1024];
    FILE *fp = popen("systemctl is-enabled eternal.service", "r");
    if (fgets(command_output, sizeof(command_output), fp) != NULL) {
        TEST_ASSERT_TRUE_MESSAGE(strstr(command_output, "enabled"), "服务未被启用");
    }
    pclose(fp);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_setup_systemd_persistence);
    return UNITY_END();
}
