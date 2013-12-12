
char** programName = NULL;
#define EXIT(s) exit(s)
#define CLOSE(s) if(close(s)) error(1, errno, "close failed")
#define set_errno(e) errno = (e)
#define isvalidsock(s) ((s) > 0)
//错误处理
void error(status, int err, char* fmt, ...){
    //输出定制消息
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%s:", programName);
    vfprint(stderr, fmt, ap);
    va_end(ap);
    //输出错误消息和错误码
    if(err){
        fprintf(stderr, ":%s (%d)\n", strerror(err), err)
    }
    //是否退出
    if(status){
        EXIT(status);
    }
}

//网络模块初始化
void INIT(){
}
//输入
//    本地ip
//    本地端口
//    协议
//输出
//    本地socket
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
            //hName不是点分十进制地址
            hp = gethostbyname(hName);
            if(NULL==hp){
                error(1, 0, "unknown host:%s\n", hName);
            }
            //hName是域名且获取到了ip
            sockAddr->sin_addr = (struct in_addr*)hp->h_addr;
        }
    }
    else{
        //没有输入则使用任意地址
        sockAddr->sin_addr = htonl(INADDR_ANY);
    }
}

int main(int argc char* argv){
    struct sockaddr_in localAddr;
    struct sockaddr_in peerAddr;
    //初始化
    INIT();
}