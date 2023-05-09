#include "Server.hpp"

int	Server::quit(User *user, std::vector<std::string> args)
{
	(void)args;
	close(user->getFd());
	_user_ids.erase(user->getNickname());
	users.erase(user->getFd());
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		it->second->send_msg(":" + user->getNickname() + " QUIT\r\n");
	}
	for (std::map<std::string, Canal *>::iterator it = canals.begin(); it != canals.end(); it++)
	{
		it->second->removeUser(*user);
	}
	delete user;
	return 2;
}
