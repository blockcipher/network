#include "udp.h"

char* program_name = NULL;
//������
void error(int status, int err, char* fmt, ...){
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
    //��ַ
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
    //�˿�
    port = strtol(sName, &endptr, 0);
    if('\0' == *endptr){
        sockAddr->sin_port = htons(port);
    }
    else{
        //û��������ʹ�������ַ
        sp = getservbyname(sName, protocol);
        if(NULL==sp){
            error(1, 0, "unknown service:%s\n", sName);
        }
        sockAddr->sin_port = sp->s_port;
    }
}
//����udp socket
SOCKET udp_server_socket(const char* hName, const char* sName,
                         struct sockaddr_in* localAddr){
    SOCKET s;
    const char* protocol = "udp";
    //���ñ��ص�ַ
    set_address(localAddr, hName, sName, protocol);
    //����socket
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if(!isvalidsock(s)){
        error(1, errno, "socket create failed, host:%s, port:%s, protocol:%s",
              hName, sName, protocol);
    }
    return s;
}

//����udp socket
SOCKET udp_client_socket(const char* hName, const char* sName,
                         struct sockaddr_in* serverAddr){
    SOCKET s;;
    const char* protocol = "udp";
    //���ñ��ص�ַ
    set_address(serverAddr, hName, sName, protocol);
    //����socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(!isvalidsock(s)){
        error(1, errno, "socket create failed, host:%s, port:%s, protocol:%s",
              hName, sName, protocol);
    }
    return s;
}
