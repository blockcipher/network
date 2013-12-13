#include "tcpServer.h"

char* program_name = NULL;
//������
void error(int status, int err, char* fmt, ...){
    //���������Ϣ
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%s:\n", program_name);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    //���������Ϣ�ʹ�����
    if(err){
        fprintf(stderr, ":%s (%d)\n", strerror(err), err);
    }
    //�Ƿ��˳�
    if(status){
        EXIT(status);
    }
}

//����
//    ����ip
//    ���ض˿�
//    Э��
//���
//    ����socket
static void set_address(struct sockaddr_in* sockAddr, const char* hName,
                        const char* sName, const char* protocol){
    struct servent* sp;
    struct hostent* hp;
    char* endptr;
    short port;
    bzero(sockAddr, sizeof(*sockAddr));
    sockAddr->sin_family = AF_INET;
    if(NULL != hName){
        if(!inet_aton(hName, &sockAddr->sin_addr)){
            //hName���ǵ��ʮ���Ƶ�ַ
            hp = gethostbyname(hName);
            if(NULL==hp){
                error(1, 0, "unknown host:%s\n", hName);
            }
            //hName�������һ�ȡ����ip
            sockAddr->sin_addr = *(struct in_addr*)hp->h_addr;
        }
    }
    else{
        //û��������ʹ�������ַ
        sockAddr->sin_addr.s_addr = htonl(INADDR_ANY);
    }
}
//����tcp socket
SOCKET tcp_socket(char* hName, char* sName){
    SOCKET s;
    struct sockaddr_in localAddr;
    const char* protocol = "tcp";
    const int on = 1;
    //���ñ��ص�ַ
    set_address(&localAddr, hName, sName, protocol);
    //����socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(!isvalidsock(s)){
        error(1, errno, "socket call failed, host:%s, port:%s, protocol:%s",
              hName, sName, protocol);
    }
    if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))){
        error(1, errno, "setsockopt failed");
    }
    if(bind(s, (struct sockaddr*)&localAddr, sizeof(localAddr))){
        error(1, errno, "bind failed");
    }
    if(listen(s, NLISTEN)){
        error(1, errno, "listen failed");
    }
    return s;
}
