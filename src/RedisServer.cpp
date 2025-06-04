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
    running = false; //atomic op
    if(server_socket != -1){
        //persisting database
        if(RedisDatabase::getInstance().dump("dump.my_rdb")){
            std::cout<<"persistance process success \n";
        }
        else{
            std::cerr<<"Error dumping database \n";
        }
        close(server_socket); //close sys call
    }
    std::cout<<"server shutdown complete \n";
}

void RedisServer::run(){
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0){
        std::cerr<<"can not create socket \n";
        return;
    }

    int opt = 1; //option level for tcp protocol going to be used in socket
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddr{}; //sockaddr_in struct instance for socket config
    
    serverAddr.sin_family = AF_INET; //ipv4
    serverAddr.sin_port = htons(port); //convert to network system
    serverAddr.sin_addr.s_addr = INADDR_ANY; //can accept from any ip 

    if(bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
        std::cerr<<"socket bind failed in server \n";
        return;
    }

    //max pending connections -> 10
    //making socket passive -> later on accept sys call
    //clien::connect() and server::accept() connection between these sates are backlog thats why set 10
    if(listen(server_socket, 10) < 0){
        std::cerr<<"server listen errror \n";
        return;
    }

    std::cout<<"redis server listening on port "<<port<<"\n";
    
}