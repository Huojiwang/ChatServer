#include "db/mysqldb.hpp"
#include <muduo/base/Logging.h>

using std::string;
// 数据库配置信息
static string server = "127.0.0.1";
static string user = "root";
static string password = "123456";
static string dbname = "chat";

//初始化数据库连接
MySQL::MySQL()
{
    _conn = mysql_init(nullptr);
}

MySQL::~MySQL(){
    if(_conn != nullptr){
        mysql_close(_conn);
    }
}

bool MySQL::connect(){
    MYSQL *p = mysql_real_connect(_conn,server.c_str(),user.c_str(),password.c_str(),dbname.c_str(),3306,nullptr,0);

    if(nullptr != p){
        //c/c++默认编码是ASCII,如果不设置,从MYSQL上拉下来的中文是乱码的
        mysql_query(_conn,"set names gbk");
        LOG_INFO << "connect mysql success!";
    }else{
        LOG_INFO <<"connect mysql fail!";
    }
    return p;
}

bool MySQL::update(string sql){
    if(mysql_query(_conn,sql.c_str())){
        LOG_INFO << __FILE__ <<":"<<__LINE__<<":"<<sql<<"update failure !";
        return false;
    }
    return true;
}

//查询操作
MYSQL_RES *MySQL::query(string sql){
    if(mysql_query(_conn,sql.c_str())){
        LOG_INFO<< __FILE__ << ":" << __LINE__ << ":"
                 << sql << "query failure!!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

//get connection
MYSQL* MySQL::getConnection()
{
    return _conn;
}