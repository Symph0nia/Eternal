#include "unity.h"
#include "linux_persistence_bashrc.h"
#include <string.h>
#include <stdlib.h>

// 设置环境
void setUp(void) {
    // 这里是每个测试之前需要运行的代码
}

// 清理环境
void tearDown(void) {
    // 清理 .bashrc 文件，删除测试中添加的行
    const char* bashrc_path = getenv("HOME");
    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s/.bashrc", bashrc_path);

    FILE *read = fopen(full_path, "r");
    FILE *write = fopen(full_path, "r+");

    if (read && write) {
        char line[512];
        while (fgets(line, sizeof(line), read)) {
            if (strstr(line, "# 持久化命令") == NULL && strstr(line, "/eternal") == NULL) {
                fputs(line, write);
            }
        }
        ftruncate(fileno(write), ftell(write));
        fclose(read);
        fclose(write);
    } else {
        perror("清理时无法打开 .bashrc 文件");
    }
}

// 测试 setup_bashrc_persistence 函数
void test_setup_bashrc_persistence(void) {
    setup_bashrc_persistence();

    // 验证 .bashrc 文件中是否包含特定的行
    const char* bashrc_path = getenv("HOME");
    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s/.bashrc", bashrc_path);
    FILE *bashrc = fopen(full_path, "r");
    char buffer[1024];
    int found = 0;

    if (bashrc) {
        while (fgets(buffer, sizeof(buffer), bashrc)) {
            if (strstr(buffer, "/eternal")) {
                found = 1;
                break;
            }
        }
        fclose(bashrc);
        TEST_ASSERT_TRUE(found);
    } else {
        TEST_FAIL_MESSAGE("无法打开 .bashrc 文件进行验证");
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_setup_bashrc_persistence);
    return UNITY_END();
}
