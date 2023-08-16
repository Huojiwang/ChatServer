#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include <unordered_map>
#include <functional>
#include <muduo/net/TcpConnection.h>
#include <mutex>
#include <muduo/base/Logging.h>
#include "json.hpp"
// #include<memory>
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include"groupmodel.hpp"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

// 表示处理消息的回调方法
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;
class ChatService
{
public:
    // 获取单例对象的结构函数
    static ChatService *getinstance();

    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp tm);

    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp tm);

    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);

    //处理客户端异常退出
    void clientCloseExcetion(const TcpConnectionPtr &conn);

    //1v1聊天
    void oneChat(const TcpConnectionPtr &conn,json &js,Timestamp time);

    //添加好友业务
    void addFriend(const TcpConnectionPtr &conn,json &js,Timestamp time);

    
    //服务器夜场，业务重置方法
    void reset();

    //创建群组
    void createGroup(const TcpConnectionPtr &conn,json &js,Timestamp time);
    
    //加入群组
    void addGroup(const TcpConnectionPtr &conn,json &js,Timestamp time);

    void groupChat(const TcpConnectionPtr &conn,json &js,Timestamp time);

    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
private:
    ChatService();
    unordered_map<int, MsgHandler> _msgHandlerMap;
    // 数据操作类对象
    UserModel _userModel;

    //存储在线用户的
    unordered_map<int,TcpConnectionPtr> _userConnMap;
    //定义互斥锁 保证_userConnMap的线程安全
    mutex _connMutex;
    //离线消息
    OfflineMsgModel _offlinemsgmodel;
    //存储好友信息
    friendmodel _friendModel;

    GroupModel _groupmodel;
};

#endif