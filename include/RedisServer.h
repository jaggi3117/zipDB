#ifndef REDIS_SERVER_H
#define REDIS_SERVER_H

#include <string>
#include <atomic>



class RedisServer{
public:
    RedisServer(int port);

private:
    int port;
    int server_socket;
    std::atomic<bool> running;
};

#endif