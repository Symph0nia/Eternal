#ifndef WINDOWS_PERSISTENCE_SCHEDULER_H
#define WINDOWS_PERSISTENCE_SCHEDULER_H

// 声明设置任务计划程序持久化的函数
void setup_task_scheduler(const char* taskName, const char* command);

#endif // WINDOWS_PERSISTENCE_SCHEDULER_H