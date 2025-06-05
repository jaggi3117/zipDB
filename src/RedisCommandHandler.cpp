#include "../include/RedisCommandHandler.h"
//include data base also

#include <vector>
#include <sstream>
#include <algorithm>
#include <exception>
#include <iostream>


std::vector<std::string> parseRespCommand(const std::string &input){
    std::vector<std::string> tokens;
    if(input.empty()) return tokens;

    //fuck it 
    
    if(input[0] != '*'){

    }
}