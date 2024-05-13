#ifndef RELEASE_H
#define RELEASE_H

#include <stddef.h>

// 声明释放嵌入文件的函数
int release_file(const char *path, const unsigned char *data, size_t size);

#endif // RELEASE_H
