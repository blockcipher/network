#include "tcp.h"
//���ܴ���
static void client(SOCKET s, struct sockaddr_in* serverAddr){
    printf("hello\n");
}

int main(int argc, char** argv){
    SOCKET s, cs;
    struct sockaddr_in serverAddr;
    char* hName = NULL;
    char* sName = NULL;
    //��ʼ��
    INIT();
    if(2 == argc){
        sName = argv[1];
    }
    else if(3 == argc){
        hName = argv[1];
        sName = argv[2];
    }
    else{
        error(1, 0, "���������������");
    }
    printf("input host:%s, port: %s\n", hName, sName);
    s = tcp_client_socket(hName, sName, &serverAddr);
    //�ͻ��˴���
    client(s, &serverAddr);
    EXIT(0);
}
