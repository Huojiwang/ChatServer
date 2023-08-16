#include "ChatServer.hpp"
#include<iostream>
#include <signal.h>

using namespace std;

void resethandler(int){
    ChatService::getinstance()->reset();
    exit(0);
}

int main(){
    
    signal(SIGINT,resethandler);
    EventLoop loop;
    InetAddress addr("127.0.0.1",6000);
    ChatServer server(&loop,addr,"ChatServer");

    server.start();
    loop.loop();

    return 0;
}