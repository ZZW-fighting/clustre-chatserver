// #include<iostream>
// #include<functional>
// #include<muduo/net/TcpServer.h>
// #include<muduo/net/EventLoop.h>
// using namespace std;
// using namespace muduo;
// using namespace muduo::net;
// using namespace placeholders;

// class ChatServer
// {
// public:
//     ChatServer(EventLoop* loop, const InetAddress& listenAddr, const string& nameArg)
//     :_server(loop, listenAddr, nameArg)
//     ,_loop(loop)
//     {
//         _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1)); //给服务器注册用户连接的创建和断开回调

//         _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));//给服务器注册用户读写事件回调

//         _server.setThreadNum(4); //设置服务器端的线程数量（一个I/O线程，三个worker线程）
//     }
//     //开启事件循环
//     void start(){
//         _server.start();
//     }
// private:
//     void onConnection(const TcpConnectionPtr& conn){
//         if(conn->connected()){
//             cout<< conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<" stat:online"<<endl;
//         }
//         else{
//             cout<< conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<" stat:offline"<<endl;
//             conn->shutdown(); //相当于close(fd)
//         }

//     }

//     void onMessage(const TcpConnectionPtr& conn,
//                             Buffer* buffer,
//                             Timestamp time)
//     {
//         string buf = buffer->retrieveAllAsString();
//         cout<< "recv data:" << buf <<"time:"<<time.toString() <<endl;
//         conn->send(buf);
//     }
                    
//     TcpServer _server;
//     EventLoop *_loop;
// };

// int main()
// {
//     EventLoop loop;
//     InetAddress addr("192.168.146.128", 6000);
//     ChatServer server(&loop, addr, "ChatServer");
//     server.start(); //把listenfd通过epoll_ctl添加到epoll上
//     loop.loop(); //相当于epoll_wait()
//     return 0;
// }