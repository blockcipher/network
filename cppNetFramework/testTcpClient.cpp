#include "tcp.h"
//接受处理
static void client(SOCKET s, struct sockaddr_in* serverAddr){
    printf("hello\n");
}

int main(int argc, char** argv){
    SOCKET s, cs;
    struct sockaddr_in serverAddr;
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
    s = tcp_client_socket(hName, sName, &serverAddr);
    //客户端处理
    client(s, &serverAddr);
    EXIT(0);
}
