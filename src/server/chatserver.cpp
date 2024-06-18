#include"chatserver.hpp"
#include"json.hpp"
#include"chatservice.hpp"
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop* loop, const InetAddress& listenAddr, const string& nameArg)
    :_server(loop, listenAddr, nameArg)
    ,_loop(loop)
    {
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1)); //给服务器注册用户连接的创建和断开回调

        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));//给服务器注册用户读写事件回调

        _server.setThreadNum(4); //设置服务器端的线程数量（一个I/O线程，三个worker线程）
    }

void ChatServer::start(){
    _server.start();
}

//上报连接相关信息的回调函数
void ChatServer::onConnection(const TcpConnectionPtr& conn){
    if(conn->connected()){
        cout<< conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<" stat:online"<<endl; //toIpPort()成员函数方法（将sockaddr类型转换为ip:port字符串类型）
    }
    else{
        cout<< conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<" stat:offline"<<endl;
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown(); //相当于close(fd)
    }
}

//上报读写事件相关信息的回调函数
void ChatServer::onMessage(const TcpConnectionPtr& conn,
                            Buffer* buffer,
                            Timestamp time){
    string buf = buffer->retrieveAllAsString(); //接受缓冲区的所有数据
    json js = json::parse(buf); //将字符串转成js数据（js的反序列化）
    //完全解耦网络模块的代码和业务模块的代码
    //通过js["msg_id"]获取=》业务处理=》
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    msgHandler(conn, js, time);
    // cout<< "recv data:" << buf <<"time:"<<time.toString() <<endl;
    // conn->send(buf);
}

