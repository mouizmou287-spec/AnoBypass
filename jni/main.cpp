#include <jni.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <android/log.h>
#include <sys/ptrace.h>

#define LOG_TAG "AnoBypass"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static ssize_t (*orig_read)(int fd, void *buf, size_t count) = nullptr;
static int (*orig_open)(const char *pathname, int flags, ...) = nullptr;
static long (*orig_ptrace)(int request, pid_t pid, void *addr, void *data) = nullptr;

int my_open(const char *pathname, int flags, ...) {
    if (pathname) {
        if (strstr(pathname, "magisk") || strstr(pathname, "frida") || strstr(pathname, "riru")) {
            return -1;
        }
    }
    if (!orig_open) orig_open = (int(*)(const char*, int, ...))dlsym(RTLD_NEXT, "open");
    return orig_open(pathname, flags);
}

long my_ptrace(int request, pid_t pid, void *addr, void *data) {
    return 0; 
}

void inject_hooks() {
    LOGI("AnoBypass: Starting hooks...");
}

extern "C" [[gnu::visibility("default")]] void zygisk_module_entry(JNIEnv *env, jobject app) {
    LOGI("AnoBypass loaded!");
    inject_hooks();
}
