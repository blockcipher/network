#include "udp.h"
void connProc(SOCKET s, struct sockaddr_in* localAddr, char* buff, int size){
    socklen_t localAddrLen = sizeof(*localAddr);
    printf("udp server connProc: %s\n", buff);
    if(0>sendto(s, "hello world\n", 13, 0, (struct sockaddr*)localAddr, localAddrLen)){
    error(1, errno, "sendto failed");
    }
}
//接受处理
static void server(SOCKET s, struct sockaddr_in* localAddr){
    socklen_t localAddrLen = 0;
    char buff[1] = {0};
    int size = 0;
    //接受数据
    do{
        printf("waiting for data...\n");
        localAddrLen = sizeof(*localAddr);
        size = recvfrom(s, buff, sizeof(buff), 0, (struct sockaddr*)localAddr, &localAddrLen);
        if(size < 0){
            error(1, errno, "recvfrom failed");
        }
        connProc(s, localAddr, buff, size);
    }while(1);
}

int main(int argc, char** argv){
    SOCKET s, cs;
    struct sockaddr_in localAddr;
    char* hName = NULL;
    char* sName = NULL;
    //初始化
    INIT();
    if(2 == argc){
        sName = argv[1];
    }
    else if(3 == argc){
        hName = argv[1];
        sName = argv[2];
    }
    else{
        error(1, 0, "输入参数不是两个");
    }
    printf("input host:%s, port: %s\n", hName, sName);
    s = udp_server_socket(hName, sName, &localAddr);
    server(s, &localAddr);
    EXIT(0);
}
