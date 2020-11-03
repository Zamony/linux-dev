#define _GNU_SOURCE
#include <dlfcn.h>

#include <errno.h>
#include <string.h>

typedef int (*orig_unlink_f_type)(const char *filename);

int unlink(char *filename) {
    if (strstr(filename, "FIX") != NULL) {
        errno = EPERM;
        return 1;
    }

    orig_unlink_f_type orig_unlink;
    orig_unlink = (orig_unlink_f_type)dlsym(RTLD_NEXT, "unlink");
    return orig_unlink(filename);
}