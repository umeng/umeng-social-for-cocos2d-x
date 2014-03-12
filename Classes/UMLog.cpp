
#include "UMLog.h"
#include <string>

using namespace std;

void UMLog::D(char const* tag, char const* msg)
{
    __android_log_print(ANDROID_LOG_DEBUG, tag, msg);
}

void UMLog::E(char const* tag, char const* msg)
{
    __android_log_print(ANDROID_LOG_ERROR, tag, msg);
}

void UMLog::I(char const* tag, char const* msg)
{
    __android_log_print(ANDROID_LOG_INFO,tag, msg);
}

void UMLog::V(char const* tag, char const* msg)
{
    __android_log_print(ANDROID_LOG_VERBOSE, tag, msg);
}



