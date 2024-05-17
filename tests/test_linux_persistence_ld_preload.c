#include "unity.h"
#include "linux_persistence_ld_preload.h"
#include <string.h>
#include <stdlib.h>

// 设置环境
void setUp(void) {
    // 这里是每个测试之前需要运行的代码
}

// 清理环境
void tearDown(void) {
    // 清理 /etc/ld.so.preload 文件，删除测试中添加的行
    const char* ld_preload_path = "/etc/ld.so.preload";
    FILE *read = fopen(ld_preload_path, "r");
    FILE *write = fopen("/tmp/ld.so.preload.clean", "w");

    if (read && write) {
        char line[512];
        char* test_lib = "libpreload.so";  // 假设这是测试中添加的唯一标识
        while (fgets(line, sizeof(line), read)) {
            if (strstr(line, test_lib) == NULL) {
                fputs(line, write);
            }
        }
        fclose(read);
        fclose(write);

        // Replace old ld.so.preload with the clean one
        rename("/tmp/ld.so.preload.clean", ld_preload_path);
    } else {
        if (read) fclose(read);
        if (write) fclose(write);
        perror("清理时无法打开 ld.so.preload 文件");
    }
}

// 测试 setup_ld_preload_persistence 函数
void test_setup_ld_preload_persistence(void) {
    setup_ld_preload_persistence();

    // 验证 /etc/ld.so.preload 文件中是否包含特定的行
    const char* ld_preload_path = "/etc/ld.so.preload";
    FILE *ld_preload_file = fopen(ld_preload_path, "r");
    char buffer[1024];
    int found = 0;

    if (ld_preload_file) {
        while (fgets(buffer, sizeof(buffer), ld_preload_file)) {
            if (strstr(buffer, "libpreload.so")) {
                found = 1;
                break;
            }
        }
        fclose(ld_preload_file);
        TEST_ASSERT_TRUE(found);
    } else {
        TEST_FAIL_MESSAGE("无法打开 ld.so.preload 文件进行验证");
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_setup_ld_preload_persistence);
    return UNITY_END();
}
