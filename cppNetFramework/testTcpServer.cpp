#include "netFrame.h"
void connProc(SOCKET s, struct sockaddr_in* clientAddr){
    printf("tcp server connProc\n");
    send(s, "hello world\n", 13, 0);
}
//接受处理
static void server(SOCKET s){
    SOCKET cs;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = 0;
    //接受连接
    do{
        printf("waiting for connecting...\n");
        clientAddrLen = sizeof(clientAddr);
        cs = accept(s, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if(!isvalidsock(cs)){
            error(1, errno, "accept failed");
        }
        connProc(cs, &clientAddr);
        CLOSE(cs);
    }while(1);
}

int main(int argc, char** argv){
    SOCKET s;
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
    server(s);
    EXIT(0);
}
