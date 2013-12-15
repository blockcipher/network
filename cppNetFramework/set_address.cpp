#include "netFrame.h"

//����
//    ����ip
//    ���ض˿�
//    Э��
//���
//    ����socket
void set_address(struct sockaddr_in* sockAddr, const char* hName,
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

