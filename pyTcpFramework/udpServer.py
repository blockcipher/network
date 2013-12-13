# -*- coding: UTF-8 –*-
import socket
import traceback
def tcpServer():
    (host, port) = ('', 80)
    #创建socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #设置选项，这些选项和系统相关
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    #绑定host
    s.bind((host, port))
    #启动监听,指定队列中可以等待的任务数
    s.listen(1)
    print "等待连接......"
    while True:
        try:
            (cSock, cAddr) = s.accept()
        except Exception,e:
            print e, traceback.print_exc()
            continue
        try:
            print "get connection:", cSock.getpeername()
        except Exception,e:
            print e, traceback.print_exc()
        try:
            cSock.close()
        except Exception,e:
            print e, traceback.print_exc()
        #break

if __name__ == '__main__':
    tcpServer()                