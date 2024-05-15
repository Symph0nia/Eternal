#include <stdio.h>
#include <windows.h>
#include "windows_persistence_replace_dll.h"

void replace_dll(const char* targetPath, const char* dllPath) {
    BOOL result;

    // 尝试复制文件到目标路径
    result = CopyFile(dllPath, targetPath, FALSE);
    if (result) {
        printf("DLL 替换成功：%s\n", targetPath);
    } else {
        DWORD dwError = GetLastError();
        if (dwError == ERROR_FILE_NOT_FOUND) {
            printf("源DLL文件未找到：%s\n", dllPath);
        } else if (dwError == ERROR_ACCESS_DENIED) {
            printf("访问目标路径被拒绝：%s\n", targetPath);
            // 尝试提升权限或检查文件是否正在使用
        } else {
            printf("DLL 替换失败，错误代码：%ld\n", dwError);
        }
    }
}
