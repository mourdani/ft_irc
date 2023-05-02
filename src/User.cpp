//
// Created by d420d4 on 11/04/23.
//
#include "User.hpp"
#include <iostream>
#include "errorCodes.hpp"

User::User(std::string hostname) {
    _nickname = "";
	_realname = "";
	_username = "";
    _hostname = hostname;
	_operator = 0;
}

User::User(std::string nickname, std::string realname, std::string hostname) {
    _nickname = nickname;
    _realname = realname;
	_username = "";
    _hostname = hostname;
	_operator = 0;
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
    this->fd = fd;
}

std::string	User::getServerName() const
{
	return _server_name;
}

void	User::setServerName(std::string name)
{
	_server_name = name;
}

std::string	User::prefix()
{
	return ":" + _nickname + "!" + _username + "@" + _server_name;
}

void User::send_msg(std::string msg) {
	std::cout << "sending: \"" << msg << "\" to user " << _nickname << std::endl;
    write(fd, msg.c_str(), msg.length());

}
#include <iostream>
void	User::send_code(std::string code, std::string msg)
{
	std::string	reply;
	
	reply = ":";
	reply.append(getServerName());
	reply.append(" ");
	if (code.size())
	{
		reply.append(code);
		reply.append(" ");
	}
	reply.append(getNickname());
	reply.append(" ");
	if (code.compare(RPL_LIST))
		reply.append(":");
	reply.append(msg);
	reply.append("\r\n");
	send_msg(reply);
}
