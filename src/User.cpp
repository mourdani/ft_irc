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

const std::string &User::getNickname() const {
    return _nickname;
}

void User::setNickname(const std::string &nickname) {
    _nickname = nickname;
}

const std::string &User::getRealname() const {
    return _realname;
}

void User::setRealname(const std::string &realname) {
    _realname = realname;
}

const std::string &User::getHostname() const {
    return _hostname;
}

void User::setHostname(const std::string &hostname) {
    _hostname = hostname;
}

bool User::isOperator() const {
    return _operator;
}

void User::setOperator(bool op) {
    _operator = op;
}
