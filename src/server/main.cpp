#include"chatserver.hpp"
#include"chatservice.hpp"
#include<signal.h>
#include<iostream>

void sigfunc(int num)
{
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cerr << "command invalid! example: ./server 127.0.0.1 6000" << endl;
        exit(-1);
    }
    signal(SIGINT, sigfunc);
    EventLoop loop;
    InetAddress addr(argv[1], atoi(argv[2])); //192.168.146.128:6000 or 192.168.146.128:6002
    ChatServer server(&loop, addr, "ChatServer");
    server.start(); //把listenfd通过epoll_ctl添加到epoll上
    loop.loop(); //相当于epoll_wait(),开启循环
    return 0;
}