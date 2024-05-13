#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// 获取CPU架构
const char* get_cpu_architecture() {
#if defined(__x86_64__) || defined(_M_X64)
    return "amd64";
#elif defined(__i386) || defined(_M_IX86)
    return "x86";
#elif defined(__arm__) || defined(_M_ARM)
    return "arm";
#elif defined(__aarch64__)
    return "aarch64";
#elif defined(__mips__)
    return "mips";
#else
    return "unknown";
#endif
}

// 获取操作系统
const char* get_operating_system() {
#if defined(_WIN32) || defined(_WIN64)
    return "windows";
#elif defined(__linux__)
    return "linux";
#elif defined(__APPLE__) && defined(__MACH__)
    return "mac";
#else
    return "unknown";
#endif
}

// 获取用户权限
const char* get_user_privilege() {
    if (geteuid() == 0) {
        return "root";
    } else {
        return "user";
    }
}
