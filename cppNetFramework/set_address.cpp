#include "netFrame.h"

//输入
//    本地ip
//    本地端口
//    协议
//输出
//    本地socket
void set_address(struct sockaddr_in* sockAddr, const char* hName,
                 const char* sName, const char* protocol){
    struct servent* sp;
    struct hostent* hp;
    char* endptr;
    short port;
    bzero(sockAddr, sizeof(*sockAddr));
    sockAddr->sin_family = AF_INET;
    //地址
    if(NULL != hName){
        if(!inet_aton(hName, &sockAddr->sin_addr)){
            //hName不是点分十进制地址
            hp = gethostbyname(hName);
            if(NULL==hp){
                error(1, 0, "unknown host:%s\n", hName);
            }
            //hName是域名且获取到了ip
            sockAddr->sin_addr = *(struct in_addr*)hp->h_addr;
        }
    }
    else{
        //没有输入则使用任意地址
        sockAddr->sin_addr.s_addr = htonl(INADDR_ANY);
    }
    //端口
    port = strtol(sName, &endptr, 0);
    if('\0' == *endptr){
        sockAddr->sin_port = htons(port);
    }
    else{
        //没有输入则使用任意地址
        sp = getservbyname(sName, protocol);
        if(NULL==sp){
            error(1, 0, "unknown service:%s\n", sName);
        }
        sockAddr->sin_port = sp->s_port;
    }
}

