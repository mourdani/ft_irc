//
// Created by d420d4 on 11/04/23.
//
#include "User.hpp"

User::User(std::string hostname) {
    _nickname = "tmp";
    _hostname = hostname;
}

User::User(std::string nickname, std::string realname, std::string hostname) {
    _nickname = nickname;
    _realname = realname;
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
	this->fd = user.fd;

    return *this;
}

bool	User::operator==(const User &user)
{
	return this->fd == user.fd;
}

bool	User::operator!=(const User &user)
{
	return this->fd != user.fd;	
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

const std::string &User::getUsername() const {
	return _username;
}

void User::setUsername(const std::string &username) {
	_username = username;
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

int User::getFd() const {
    return fd;
}

void User::setFd(int fd) {
    User::fd = fd;
}

void User::send_msg(std::string msg) {

    write(fd, msg.c_str(), msg.length());

}
