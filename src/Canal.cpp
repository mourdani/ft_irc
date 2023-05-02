//
// Created by d420d4 on 11/04/23.
//
#include "Canal.hpp"

Canal::Canal() {
    _topic = "";
	_chanop = NULL;
    _name = "No name is set";
}

Canal::Canal(std::string name) {
    _topic = "";
	_chanop = NULL;
    _name = name;
}

Canal::Canal(const Canal &canal)
{
	_chanop = NULL;
	*this = canal;
}

Canal::~Canal()
{
}

Canal &Canal::operator=(const Canal &canal)
{
	_name = canal._name;
	_users = canal._users;

	return *this;
}

const std::string &Canal::getName() const
{
	return _name;
}

std::map<int, User *>	Canal::getUsers() const {
	return _users;
}

void Canal::setName(const std::string &name)
{
	_name = name;
}

bool	Canal::checkUser(int id)
{
	if (_users.find(id) == _users.end())
	return 0;
	return 1;
}

void	Canal::setChanop(User *user)
{
	_chanop = user;
}

User	*Canal::getChanop()
{
	return _chanop;
}

void	Canal::addUser(User *user)
{
	this->_users.insert(std::pair<int, User *>(user->getFd(), user));
}

void	Canal::removeUser(User user)
{
	this->_users.erase(user.getFd());
}

void	Canal::removeUser(int id)
{
	this->_users.erase(id);
}


void Canal::setTopic(const std::string &topic) {
	_topic = topic;
}

std::string Canal::getTopic() const {
	return _topic;
}
