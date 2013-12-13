#include "udp.h"

char* program_name = NULL;
//错误处理
void error(int status, int err, char* fmt, ...){
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

//输入
//    本地ip
//    本地端口
//    协议
//输出
//    本地socket
static void set_address(struct sockaddr_in* sockAddr, const char* hName,
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
//创建udp socket
SOCKET udp_server_socket(const char* hName, const char* sName,
                         struct sockaddr_in* localAddr){
    SOCKET s;
    const char* protocol = "udp";
    //设置本地地址
    set_address(localAddr, hName, sName, protocol);
    //生成socket
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if(!isvalidsock(s)){
        error(1, errno, "socket create failed, host:%s, port:%s, protocol:%s",
              hName, sName, protocol);
    }
    return s;
}

//创建udp socket
SOCKET udp_client_socket(const char* hName, const char* sName,
                         struct sockaddr_in* serverAddr){
    SOCKET s;;
    const char* protocol = "udp";
    //设置本地地址
    set_address(serverAddr, hName, sName, protocol);
    //生成socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(!isvalidsock(s)){
        error(1, errno, "socket create failed, host:%s, port:%s, protocol:%s",
              hName, sName, protocol);
    }
    return s;
}
