//
// Created by d420d4 on 11/04/23.
//
#include "Canal.hpp"

Canal::Canal() {

}

Canal::Canal(std::string name) {
    _name = name;
}

Canal::Canal(const Canal &canal) {
    *this = canal;
}

Canal::~Canal() {

}

Canal &Canal::operator=(const Canal &canal) {
    _name = canal._name;
    _users = canal._users;

    return *this;
}

const std::string &Canal::getName() const {
    return _name;
}

void Canal::setName(const std::string &name) {
    _name = name;
}

bool	Canal::checkUser(int id)
{
	if (_users.find(id) == _users.end())
		return 0;
	return 1;
}

void	Canal::addUser(User user)
{
	this->_users.insert(std::pair<int, User>(user.getFd(), user));
}

void	Canal::removeUser(User user)
{
	this->_users.erase(user.getFd());
}

