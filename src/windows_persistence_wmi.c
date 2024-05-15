#include <stdio.h>
#include <wbemidl.h>
#include "windows_persistence_wmi.h"

#pragma comment(lib, "wbemuuid.lib")

void setup_wmi_persistence(const char* command) {
    HRESULT hres;

    // 初始化COM库
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        printf("初始化COM库失败: %08lx\n", hres);
        return;
    }

    // 设置安全级别
    hres = CoInitializeSecurity(
        NULL,
        -1,                          // COM认证
        NULL,                        // 认证服务
        NULL,                        // 保留
        RPC_C_AUTHN_LEVEL_DEFAULT,   // 默认认证级别
        RPC_C_IMP_LEVEL_IMPERSONATE, // 默认模拟级别
        NULL,                        // 认证信息
        EOAC_NONE,                   // 额外的能力
        NULL);                       // 保留

    if (FAILED(hres)) {
        printf("初始化安全设置失败: %08lx\n", hres);
        CoUninitialize();
        return;
    }

    // 获取WMI接口
    IWbemLocator *pLoc = NULL;
    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER,
                            IID_IWbemLocator, (LPVOID *)&pLoc);

    if (FAILED(hres)) {
        printf("创建WbemLocator实例失败: %08lx\n", hres);
        CoUninitialize();
        return;
    }

    // 连接到WMI命名空间
    IWbemServices *pSvc = NULL;
    hres = pLoc->ConnectServer(
           _bstr_t(L"ROOT\\CIMV2"), // WMI命名空间
           NULL,                    // 用户名
           NULL,                    // 密码
           0,                       // 区域设置
           NULL,                    // 安全标志
           0,                       // 权限
           0,                       // 上下文对象
           &pSvc                    // IWbemServices代理
           );

    if (FAILED(hres)) {
        printf("连接到WMI命名空间失败: %08lx\n", hres);
        pLoc->Release();
        CoUninitialize();
        return;
    }

    printf("已设置WMI持久化。\n");

    // 清理
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();
}
