//
// Created by d420d4 on 11/04/23.
//
#include "User.hpp"
#include "Server.hpp"
#include <iostream>
#include "errorCodes.hpp"

User::User(std::string hostname) {
    _nickname = "*";
	_realname = "";
	_username = "";
    _hostname = hostname;
	_operator = 0;
    _pass = "";
    _registered = false;
	_command = "";
}

User::User(std::string nickname, std::string realname, std::string hostname) {
    _nickname = nickname;
    _realname = realname;
	_username = "";
    _hostname = hostname;
	_operator = 0;
    _pass = "";
    _registered = false;
	_command = "";
}

User::User() {
	_command = "";
    _registered = false;
}

User::~User() {
}

User &User::operator=(const User &user) {
    this->_hostname = user._hostname;
    this->_nickname = user._nickname;
    this->_operator = user._operator;
    this->_realname = user._realname;
    this->fd = user.fd;
    this->_registered = user._registered;

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

void User::setRegistered(bool registered) {
	_registered = registered;
}

bool User::isRegistered() const {
	return _registered; 
}

int User::getFd() const {
    return fd;
}

void User::setFd(int fd) {
    this->fd = fd;
}

const std::string &User::getPass() const {
	return _pass;
}

void User::setPass(const std::string &pass) {
	_pass = pass;
}
std::string	User::getServerName() const
{
	return _server_name;
}

void	User::setServerName(std::string name)
{
	_server_name = name;
}

void	User::setCommand(std::string command)
{
	_command = command;
}

std::string	&User::getCommand()
{
	return _command;
}

std::string	User::prefix()
{
	return ":" + _nickname + "!" + _username + "@" + _server_name;
}

void User::send_msg(std::string msg) {
    std::cout << BOLDYELLOW << "Sending to " << _nickname << ": " << msg << RESET << "\n" << std::endl;
    write(fd, (msg + "\r\n").c_str(), msg.length() + 2);

}

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
	reply.append(msg);
	send_msg(reply);
}

int	User::send_unregistered_code(void)
{
    if (this->isRegistered() == false)
    {	
    	this->send_code(ERR_NOTREGISTERED, ":You have not registered");
		return 1;
    }
    return 0;
}
