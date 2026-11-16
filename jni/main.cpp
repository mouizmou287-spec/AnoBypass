#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "AnoBypass"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" [[gnu::visibility("default")]] void zygisk_module_entry(JNIEnv *env, jobject app) {
    LOGI("AnoBypass: Module loaded!");
}
