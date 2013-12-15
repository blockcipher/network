#include "netFrame.h"

//创建udp server
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

//创建udp client
SOCKET udp_client_socket(const char* hName, const char* sName,
                         struct sockaddr_in* serverAddr){
    SOCKET s;;
    const char* protocol = "udp";
    //设置本地地址
    set_address(serverAddr, hName, sName, protocol);
    //生成socket
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if(!isvalidsock(s)){
        error(1, errno, "socket create failed, host:%s, port:%s, protocol:%s",
              hName, sName, protocol);
    }
    return s;
}
