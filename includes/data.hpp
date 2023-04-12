//
// Created by d420d4 on 10/04/23.
//

#ifndef FT_IRC_DATA_H
#define FT_IRC_DATA_H

#include <string>
#include <map>
#include "User.hpp"
#include "Canal.hpp"

struct irc_data { // This structure is named "myDataType"
    std::string password;
    int port;
    std::map<std::string, User> users;
    std::map<std::string, Canal> canals;
};

bool	user_exists(irc_data data, std::string nickname);
bool	canal_exist(irc_data data, std::string canal);
bool	add_user(irc_data data, User user);
bool	add_canal(irc_data data, User user);
User    *get_user(irc_data data, std::string hostname);
Canal    *get_canal(irc_data data, std::string canal);

#endif //FT_IRC_DATA_H
