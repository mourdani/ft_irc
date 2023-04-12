//
// Created by d420d4 on 11/04/23.
//

#include <string>
#include "Canal.hpp"
#include "data.hpp"

bool user_exists(irc_data data, std::string nickname) {
    for (std::map<std::string, User>::iterator it = data.users.begin(); it != data.users.end(); ++it)
        if (it->second.getNickname() == nickname)
            return true;

    return false;
}

bool canal_exist(irc_data data, std::string canal) {
    for (std::map<std::string, Canal>::iterator it = data.canals.begin(); it != data.canals.end(); ++it)
        if (it->second.getName() == canal)
            return true;

    return false;
}

bool add_user(irc_data data, User user) {
    if (user_exists(data, user.getNickname()))
        return false;
    data.users.insert(std::pair<std::string, User>(user.getHostname(), user));

    return true;
}

bool add_canal(irc_data data, Canal canal) {
    if (canal_exist(data, canal.getName()))
        return false;
    data.canals.insert(std::pair<std::string, Canal>(canal.getName(), canal));

    return true;
}

User *get_user(irc_data data, std::string nickname) {
    for (std::map<std::string, User>::iterator it = data.users.begin(); it != data.users.end(); ++it)
        if (it->second.getNickname() == nickname)
            return &it->second;

    return NULL;
}

Canal *get_canal(irc_data data, std::string canal) {
    for (std::map<std::string, Canal>::iterator it = data.canals.begin(); it != data.canals.end(); ++it)
        if (it->second.getName() == canal)
            return &it->second;

    return NULL;
}
