#include "tcpServer.h"
//接受处理
static void server(SOCKET s, struct sockaddr_in* clientAddr){
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
        sName = argv[0];
    }
    else if(3 == argc){
        hName = argv[0];
        sName = argv[1];
    }
    else{
        error(1, 0, "输入参数不是两个");
    }
    printf("host:%s, port: %s", hName, sName);
    s = tcp_socket(hName, sName);
    //接受连接
    do{
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
