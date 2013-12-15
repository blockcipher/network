#ifndef __udp_server_h__
#define __udp_server_h__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
extern char* program_name;
//初始化程序名,输入中可能包含路径
#define INIT()(program_name = strrchr(argv[0], '/')) ? program_name++ : \
                                                       (program_name = argv[0])
//退出程序
#define EXIT(s) exit(s)
//错误处理
#define set_errno(e) errno = (e)
void error(int status, int err, const char* fmt, ...);

//socket相关
#define NLISTEN 1
#define CLOSE(s) if(close(s)) error(1, errno, "close failed")
#define isvalidsock(s) ((s) > 0)
typedef int SOCKET;
//(域名或ip,服务名或端口号)转化为地址
void set_address(struct sockaddr_in* sockAddr, const char* hName,
                 const char* sName, const char* protocol);
                 
//创建udp socket
SOCKET udp_server_socket(const char* hName, const char* sName, struct sockaddr_in* localAddr);
SOCKET udp_client_socket(const char* hName, const char* sName, struct sockaddr_in* serverAddr);

//创建tcp socket
SOCKET tcp_server_socket(const char* hName, const char* sName);
SOCKET tcp_client_socket(const char* hName, const char* sName, struct sockaddr_in* serverAddr);

#endif

