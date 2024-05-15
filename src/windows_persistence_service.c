#include <stdio.h>
#include <windows.h>
#include "windows_persistence_service.h"

void create_windows_service(const char* serviceName, const char* displayName, const char* binPath) {
    SC_HANDLE schSCManager;
    SC_HANDLE schService;

    // 打开服务控制管理器
    schSCManager = OpenSCManager(
        NULL,                    // 本地计算机
        NULL,                    // ServicesActive数据库
        SC_MANAGER_ALL_ACCESS);  // 完全访问权限

    if (NULL == schSCManager) {
        printf("OpenSCManager 失败：%ld\n", GetLastError());
        return;
    }

    // 创建服务
    schService = CreateService(
        schSCManager,              // SCM数据库
        serviceName,               // 服务名
        displayName,               // 服务显示名
        SERVICE_ALL_ACCESS,        // 完全访问服务
        SERVICE_WIN32_OWN_PROCESS, // 服务类型
        SERVICE_AUTO_START,        // 服务启动类型
        SERVICE_ERROR_NORMAL,      // 错误控制类型
        binPath,                   // 服务的二进制
        NULL,                      // 无负载排序组
        NULL,                      // 无标签标识
        NULL,                      // 无依赖
        NULL,                      // LocalSystem账户
        NULL);                     // 无密码

    if (schService == NULL) {
        printf("CreateService 失败：%ld\n", GetLastError());
    } else {
        printf("服务创建成功。\n");
    }

    // 关闭服务控制管理器的句柄
    if (schSCManager) {
        CloseServiceHandle(schSCManager);
    }
    if (schService) {
        CloseServiceHandle(schService);
    }
}
