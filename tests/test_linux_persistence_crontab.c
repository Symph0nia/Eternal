#include "unity.h"
#include "linux_persistence_crontab.h"
#include <string.h>
#include <stdlib.h>

// 设置环境
void setUp(void) {
    // 这里是每个测试之前需要运行的代码
}

// 清理环境
void tearDown(void) {
    // 清理 crontab，删除测试中添加的行
    system("crontab -l | grep -v '/eternal' | crontab -"); // 删除含有 '/eternal' 的行
}

// 测试 setup_crontab_persistence 函数
void test_setup_crontab_persistence(void) {
    setup_crontab_persistence();

    // 验证 crontab 中是否包含特定的行
    FILE *crontab = popen("crontab -l", "r");
    char buffer[1024];
    int found = 0;

    if (crontab) {
        while (fgets(buffer, sizeof(buffer), crontab)) {
            if (strstr(buffer, "/eternal")) {
                found = 1;
                break;
            }
        }
        pclose(crontab);
        TEST_ASSERT_TRUE(found);
    } else {
        TEST_FAIL_MESSAGE("无法打开 crontab 进行验证");
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_setup_crontab_persistence);
    return UNITY_END();
}
