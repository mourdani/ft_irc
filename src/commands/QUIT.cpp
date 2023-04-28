#include "Server.hpp"

int	Server::quit(User& user, std::vector<std::string> args)
{
	(void)args;
	close(user.getFd());
	_user_ids.erase(user.getNickname());
	users.erase(user.getFd());
	for (std::map<std::string, Canal *>::iterator it = canals.begin(); it != canals.end(); it++)
	{
		it->second->removeUser(user);
	}
	return 2;
}
