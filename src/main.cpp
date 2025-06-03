#include <iostream>
#include "../include/RedisServer.h"



int main(int argc, char* argv[]){
    int port = 6379; //default if user dont want to setup port
    if(argc >= 2) port = std::stoi(argv[1]);


    return 0;
}