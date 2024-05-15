#ifndef WINDOWS_PERSISTENCE_SERVICE_H
#define WINDOWS_PERSISTENCE_SERVICE_H

// 声明创建Windows服务的函数
void create_windows_service(const char* serviceName, const char* displayName, const char* binPath);

#endif // WINDOWS_PERSISTENCE_SERVICE_H
