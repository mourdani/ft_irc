#include "Server.hpp"

int Server::user(User *user, std::vector<std::string> args)
{
	if (user->getUsername().compare(""))
	{
		user->send_code(ERR_ALREADYREGISTRED, ":You may not reregister");
		return 0;
	}
	if (args.size() < 2)
	{
		user->send_code(ERR_NEEDMOREPARAMS, ":Usage: /USER <user>");
		return 0;
	}
	user->setUsername(args[1]);
	return 0;
}
