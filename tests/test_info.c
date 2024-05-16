#include "unity.h"
#include "info.h" // 假设你的函数定义在这个文件中

void setUp(void) {
    // 这里是每个测试之前需要运行的代码
}

void tearDown(void) {
    // 这里是每个测试之后需要运行的代码
}

// 测试 CPU 架构
void test_cpu_architecture(void) {
    const char* arch = get_cpu_architecture();
    TEST_ASSERT_NOT_NULL(arch);
    printf("CPU Architecture: %s\n", arch);
}

// 测试操作系统
void test_operating_system(void) {
    const char* os = get_operating_system();
    TEST_ASSERT_NOT_NULL(os);
    printf("Operating System: %s\n", os);
}

// 测试用户权限
void test_user_privilege(void) {
    const char* privilege = get_user_privilege();
    TEST_ASSERT_NOT_NULL(privilege);
    printf("User Privilege: %s\n", privilege);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_cpu_architecture);
    RUN_TEST(test_operating_system);
    RUN_TEST(test_user_privilege);
    return UNITY_END();
}
