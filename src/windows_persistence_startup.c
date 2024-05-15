#include <stdio.h>
#include <shlobj.h> // 包含SHGetFolderPath函数
#include "windows_persistence_startup.h"

void add_to_startup_folder(const char* filename, const char* filepath) {
    char startupPath[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_STARTUP, NULL, SHGFP_TYPE_CURRENT, startupPath);

    if (result != S_OK) {
        printf("无法获取启动文件夹路径：%ld\n", result);
        return;
    }

    // 构建目标文件路径
    strcat(startupPath, "\\");
    strcat(startupPath, filename);

    // 复制文件到启动文件夹
    BOOL copyResult = CopyFile(filepath, startupPath, FALSE);
    if (copyResult) {
        printf("文件成功复制到启动文件夹：%s\n", startupPath);
    } else {
        printf("文件复制失败，错误代码：%ld\n", GetLastError());
    }
}
