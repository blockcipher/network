#include "tcp.h"
//接受处理
static void server(SOCKET s, struct sockaddr_in* clientAddr){
    printf("accepted one connect\n");
}

int main(int argc, char** argv){
    SOCKET s, cs;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = 0;
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
    s = tcp_server_socket(hName, sName);
    //接受连接
    do{
        printf("waiting for connecting...\n");
        clientAddrLen = sizeof(clientAddr);
        cs = accept(s, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if(!isvalidsock(cs)){
            error(1, errno, "accept failed");
        }
        server(cs, &clientAddr);
        CLOSE(cs);
    }while(1);
    EXIT(0);
}
