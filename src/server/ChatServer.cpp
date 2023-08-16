#include "ChatServer.hpp"
#include<functional>
#include "json.hpp"
// #include<string>

using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,     //事件循环
        const InetAddress &listenAddr, //Ip+port
        const string &nameArg):_server(loop,listenAddr,nameArg),_loop(loop)         //服务器名字
        {
            //给服务器注册用户连接的创建和断开回调
            _server.setConnectionCallback(std::bind(&ChatServer::onConnection,this,_1));

            //给服务器注册用户读写事件回调
            _server.setMessageCallback(bind(&ChatServer::onMessage,this,_1,_2,_3));

            //设置服务器线程数量
            _server.setThreadNum(32);   //一个IO线程，n-1个工作线程
        }
        
void ChatServer::start(){
    _server.start();
}


void ChatServer::onConnection(const TcpConnectionPtr &conn){
    if(conn->connected()){
        cout<<conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<"state : online"<<endl;
    }else{//客户端断开连接
        cout<<conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<"state : offline"<<endl;
        ChatService::getinstance()->clientCloseExcetion(conn);
        conn->shutdown();   //sockfd释放close（fd）
        //_loop->quit();服务器断开
    }
}

void ChatServer::onMessage(const TcpConnectionPtr& conn,Buffer *buffer,Timestamp time){
    string buf = buffer->retrieveAllAsString( );
    cout<<"recv data: "<<buf<<" time: "<<time.toString()<<endl;
    json js = json::parse(buf);
    
    //通过js["msgid"]获取 业务handler   conn is time,达到目的完全解耦网络模块的代码和业务模块的代码
    auto msgHandler = ChatService::getinstance()->getHandler(js["msgid"].get<int>());
    //回调消息绑定好的事件处理器,来执行相应的业务处理
    msgHandler(conn,js,time);
    // conn->send(buf);
}