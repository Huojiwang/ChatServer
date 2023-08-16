#ifndef CHATSERVER_H
#define CHATSERVER_H

#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<iostream>
#include<string>
#include<functional>
#include"ChatService.hpp"


using namespace muduo;
using namespace std::placeholders;
using namespace muduo::net;
using std::cout;
using std::endl;
/*

1. 组合TCPserver对象
2. 创建EventLoop事件循环对象指针
3. 明确Tcpserver构造函数需要什么参数，输出ChatServer的构造函数
4. 在当前服务器类的构造函数中注册处理连接和读写的回调
*/
class ChatServer{
    public:
        //初始化聊天服务器对象
        ChatServer(EventLoop *loop, const InetAddress &listenAddr,const string &nameArg);      //事件循环//Ip+port//服务器名字 
       
        //启动服务
        void start();

    private:
        //上报连接事件相关函数
        void onConnection(const TcpConnectionPtr &conn);
        //上报读写事件相关函数
        void onMessage(const TcpConnectionPtr& conn,Buffer *buffer,Timestamp time);
        TcpServer _server;  //组合muduo库
        EventLoop *_loop;   //event事件循环对象的指针

};


#endif