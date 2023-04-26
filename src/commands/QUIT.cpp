#include "Server.hpp"

int	Server::quit(User& user, std::vector<std::string> args)
{
	(void)user;
	(void)args;
	close(user.getFd());
	return 2;
}
