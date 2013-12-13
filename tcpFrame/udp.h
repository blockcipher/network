#ifndef __tcp_server_h__
#define __tcp_server_h__
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
//��ʼ��������,�����п��ܰ���·��
#define INIT()(program_name = strrchr(argv[0], '/')) ? program_name++ : \
                                                       (program_name = argv[0])
//�˳�����
#define EXIT(s) exit(s)
//socket���
#define NLISTEN 1
#define CLOSE(s) if(close(s)) error(1, errno, "close failed")
#define isvalidsock(s) ((s) > 0)
typedef int SOCKET;
//������
#define set_errno(e) errno = (e)
void error(int status, int err, char* fmt, ...);
//����udp socket
SOCKET udp_server_socket(const char* hName, const char* sName, struct sockaddr_in* localAddr);
SOCKET udp_client_socket(const char* hName, const char* sName, struct sockaddr_in* serverAddr);

#endif

