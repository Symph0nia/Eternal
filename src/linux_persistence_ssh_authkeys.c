#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef SSH_AUTH_KEYS_MOD
void setup_add_ssh_authorized_key(const char* username, const char* public_key) {
    char ssh_dir_path[256];
    char auth_keys_path[256];

    printf("为用户 %s 添加 SSH 公钥...\n", username);

    // 构造.ssh目录和authorized_keys文件的路径
    snprintf(ssh_dir_path, sizeof(ssh_dir_path), "/home/%s/.ssh", username);
    snprintf(auth_keys_path, sizeof(auth_keys_path), "%s/authorized_keys", ssh_dir_path);

    // 确保.ssh目录存在
    mkdir(ssh_dir_path, 0700);
    chown(ssh_dir_path, getpwnam(username)->pw_uid, getpwnam(username)->pw_gid);

    // 打开authorized_keys文件，添加公钥
    FILE* file = fopen(auth_keys_path, "a");
    if (file == NULL) {
        perror("打开 authorized_keys 文件失败");
        return;
    }
    fprintf(file, "%s\n", public_key);
    fclose(file);

    // 更改文件权限，确保只有用户自己可以访问
    chmod(auth_keys_path, 0600);
    chown(auth_keys_path, getpwnam(username)->pw_uid, getpwnam(username)->pw_gid);

    printf("公钥已添加到 %s。\n", auth_keys_path);
}
#endif