#include "netFrame.h"

char* program_name = NULL;
//������
void error(int status, int err, const char* fmt, ...){
    //���������Ϣ
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%s:", program_name);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    printf("\n");
    //���������Ϣ�ʹ�����
    if(err){
        fprintf(stderr, ":%s (%d)\n", strerror(err), err);
    }
    //�Ƿ��˳�
    if(status){
        EXIT(status);
    }
}

