//
// Created by d420d4 on 10/04/23.
//

#ifndef FT_IRC_DATA_H
#define FT_IRC_DATA_H

#include <string>
#include <map>

struct irc_data { // This structure is named "myDataType"
    std::string password;
    int port;
    std::map<std::string, User> users;
};

#endif //FT_IRC_DATA_H
