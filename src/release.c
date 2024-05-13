#include <stdio.h>
#include <stdlib.h>
#include "release.h"
#include "bind_files.h"

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
