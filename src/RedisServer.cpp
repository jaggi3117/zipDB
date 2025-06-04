#include "../include/RedisServer.h"
#include "../include/RedisCommandHandler.h"
#include "../include/RedisDatabase.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <vector>
#include <thread>
#include <cstring>
#include <signal.h>


//created global pointer (signal handling)
static RedisServer* globalServer = nullptr;

void signalHandler(int signum){
    if(globalServer){
        std::cout<<"\n came signal "<<signum<<", shutting down.. \n";
        globalServer->shutdown();
    }
    //returning signum integer to os after exit obv not exit(0)
    exit(signum);
}

RedisServer::RedisServer(int port) : port(port), server_socket(-1), running(true){
    globalServer = this;
    setupSignalHandler();
}

void RedisServer::shutdown(){
    //socket server shutdown
}

void RedisServer::run(){
    //socket server start
    //planning to use threads obv
    //persisting DB should not be affected
    //

}