#include "unity.h"
#include "linux_persistence_sshrc.h"
#include <string.h>
#include <stdlib.h>

// 设置环境
void setUp(void) {
    // 这里是每个测试之前需要运行的代码
}

// 清理环境
void tearDown(void) {
    // 清理 ~/.ssh/rc 文件，删除测试中添加的行
    const char* home_path = getenv("HOME");
    if (home_path) {
        char user_ssh_rc_path[512];
        snprintf(user_ssh_rc_path, sizeof(user_ssh_rc_path), "%s/.ssh/rc", home_path);
        FILE *read = fopen(user_ssh_rc_path, "r");
        FILE *write = fopen("/tmp/ssh_rc_clean", "w");

        if (read && write) {
            char line[512];
            while (fgets(line, sizeof(line), read)) {
                if (strstr(line, "/tmp/eternal") == NULL) {
                    fputs(line, write);
                }
            }
            fclose(read);
            fclose(write);

            // Replace old .ssh/rc with the clean one
            rename("/tmp/ssh_rc_clean", user_ssh_rc_path);
        } else {
            if (read) fclose(read);
            if (write) fclose(write);
            perror("清理时无法打开 .ssh/rc 文件");
        }
    }
}

// 测试 setup_user_sshrc_persistence 函数
void test_setup_user_sshrc_persistence(void) {
    setup_user_sshrc_persistence();

    // 验证 ~/.ssh/rc 文件中是否包含特定的行
    const char* home_path = getenv("HOME");
    if (home_path) {
        char user_ssh_rc_path[512];
        snprintf(user_ssh_rc_path, sizeof(user_ssh_rc_path), "%s/.ssh/rc", home_path);
        FILE *user_ssh_rc_file = fopen(user_ssh_rc_path, "r");
        char buffer[1024];
        int found = 0;

        if (user_ssh_rc_file) {
            while (fgets(buffer, sizeof(buffer), user_ssh_rc_file)) {
                if (strstr(buffer, "/tmp/eternal")) {
                    found = 1;
                    break;
                }
            }
            fclose(user_ssh_rc_file);
            TEST_ASSERT_TRUE(found);
        } else {
            TEST_FAIL_MESSAGE("无法打开 ~/.ssh/rc 文件进行验证");
        }
    } else {
        TEST_FAIL_MESSAGE("无法获取HOME环境变量");
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_setup_user_sshrc_persistence);
    return UNITY_END();
}
