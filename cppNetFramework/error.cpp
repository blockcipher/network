#include "netFrame.h"

char* program_name = NULL;
//错误处理
void error(int status, int err, const char* fmt, ...){
    //输出定制消息
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%s:", program_name);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    printf("\n");
    //输出错误消息和错误码
    if(err){
        fprintf(stderr, ":%s (%d)\n", strerror(err), err);
    }
    //是否退出
    if(status){
        EXIT(status);
    }
}

