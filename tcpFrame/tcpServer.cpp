
char** programName = NULL;
#define EXIT(s) exit(s)
#define CLOSE(s) if(close(s)) error(1, errno, "close failed")
#define set_errno(e) errno = (e)
#define isvalidsock(s) ((s) > 0)
//������
void error(status, int err, char* fmt, ...){
    //���������Ϣ
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%s:", programName);
    vfprint(stderr, fmt, ap);
    va_end(ap);
    //���������Ϣ�ʹ�����
    if(err){
        fprintf(stderr, ":%s (%d)\n", strerror(err), err)
    }
    //�Ƿ��˳�
    if(status){
        EXIT(status);
    }
}

//����ģ���ʼ��
void INIT(){
}
//����
//    ����ip
//    ���ض˿�
//    Э��
//���
//    ����socket
static void set_address(struct sockadd_in* sockAddr, const char* hName,
                        char* sName, char* protocol){
    struct servent* sp;
    struct hostent* hp;
    char* endptr;
    short port;
    bzero(sockAddr, sizeof(*sockAddr));
    sockAddr->sin_family = AF_INET;
    if(NULL != hName){
        if(!inet_aton(hName, &sockAddr->sin_addr)){
            //hName���ǵ��ʮ���Ƶ�ַ
            hp = gethostbyname(hName);
            if(NULL==hp){
                error(1, 0, "unknown host:%s\n", hName);
            }
            //hName�������һ�ȡ����ip
            sockAddr->sin_addr = (struct in_addr*)hp->h_addr;
        }
    }
    else{
        //û��������ʹ�������ַ
        sockAddr->sin_addr = htonl(INADDR_ANY);
    }
}

int main(int argc char* argv){
    struct sockaddr_in localAddr;
    struct sockaddr_in peerAddr;
    //��ʼ��
    INIT();
}