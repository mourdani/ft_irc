//
// Created by d420d4 on 11/04/23.
//
#include "User.hpp"

User::User(std::string hostname) {
    _hostname = hostname;
}

User::User() {

}

User::~User() {

}

User &User::operator=(const User &user) {
    this->_hostname = user._hostname;
    this->_nickname = user._nickname;
    this->_operator = user._operator;
    this->_realname = user._realname;

    return *this;
}

User::User(const User &user) {
    *this = user;
}
