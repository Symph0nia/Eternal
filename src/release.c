#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bind_files.h"

// 释放嵌入的文件到指定路径
int release_file(const char *path, const unsigned char *data, size_t size) {
    FILE *file = fopen(path, "wb");
    if (!file) {
        perror("fopen");
        return -1;
    }
    fwrite(data, 1, size, file);
    fclose(file);
    return 0;
}

// 释放所有嵌入的文件
void release_all_files() {
    // 对于每个文件，调用 release_file 函数
#ifdef example1 // 示例变量名
    release_file("/path/to/release/example1", example1, example1_size);
#endif

    // 对每个嵌入的文件添加类似的行
    // 在此添加生成脚本生成的每个文件对应的行
}
