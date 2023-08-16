#ifndef PUBLIC_H
#define PUBLIC_H
/*
server and Client 公共wenjian
*/
enum EnMsgType{
    LOGIN_MSG = 1,  //登录消息
    LOGIN_MSG_ACK,  //登录响应信息
    LOGINOUT_MSG,     //注销信息

    REG_MSG ,        //register msg
    REG_MSG_ACK,
    
    ONE_CHAT_MSG,   //聊天消息

    ADD_FRIEND_MSG, //添加好友消息
    
    CREATE_GROUP_MSG,   //创建群组
    ADD_GROUP_MSG,      //加入群组
    GROUP_CHAT_MSG      //群聊天
};



#endif