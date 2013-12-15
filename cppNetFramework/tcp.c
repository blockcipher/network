#include "netFrame.h"

//创建tcp server
SOCKET tcp_server_socket(const char* hName, const char* sName){
    SOCKET s;
    struct sockaddr_in localAddr;
    const char* protocol = "tcp";
    const int on = 1;
    //设置本地地址
    set_address(&localAddr, hName, sName, protocol);
    //生成socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(!isvalidsock(s)){
        error(1, errno, "socket create failed, host:%s, port:%s, protocol:%s",
              hName, sName, protocol);
    }
    if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))){
        error(1, errno, "setsockopt failed");
    }
    if(bind(s, (struct sockaddr*)&localAddr, sizeof(localAddr))){
        error(1, errno, "socket bind failed, host:%s, port:%s, protocol:%s",
              hName, sName, protocol);
    }
    if(listen(s, NLISTEN)){
        error(1, errno, "listen failed");
    }
    return s;
}

//创建tcp client
SOCKET tcp_client_socket(const char* hName, const char* sName,
                         struct sockaddr_in* serverAddr){
    SOCKET s;;
    const char* protocol = "tcp";
    //设置本地地址
    set_address(serverAddr, hName, sName, protocol);
    //生成socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(!isvalidsock(s)){
        error(1, errno, "socket create failed, host:%s, port:%s, protocol:%s",
              hName, sName, protocol);
    }
    //连接到服务器
    if(connect(s, (struct sockaddr*)serverAddr, sizeof(*serverAddr))){
        error(1, errno, "connect failed, host:%s, port:%s, protocol:%s",
                         hName, sName, protocol);
    }
    return s;
}
