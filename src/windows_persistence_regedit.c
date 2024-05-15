#include <stdio.h>
#include <windows.h>
#include "windows_persistence_regedit.h"

void add_autostart_program(const char* program_name, const char* path) {
    HKEY hKey;
    LONG lResult;
    DWORD dwDisposition;

    // 打开或创建键
    lResult = RegCreateKeyEx(HKEY_CURRENT_USER,
                             "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                             0, NULL, REG_OPTION_NON_VOLATILE,
                             KEY_WRITE, NULL, &hKey, &dwDisposition);

    if (lResult != ERROR_SUCCESS) {
        printf("打开注册表键失败: %ld\n", lResult);
        return;
    }

    // 设置程序路径
    lResult = RegSetValueEx(hKey, program_name, 0, REG_SZ, (const BYTE*)path, strlen(path) + 1);
    if (lResult == ERROR_SUCCESS) {
        printf("自启动程序已添加到注册表。\n");
    } else {
        printf("设置注册表值失败: %ld\n", lResult);
    }

    // 关闭键
    RegCloseKey(hKey);
}
